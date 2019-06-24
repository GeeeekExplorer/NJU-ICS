#include "nemu.h"
#include "device/audio.h"
#include "device/i8259_pic.h"
#include "memory/memory.h"
#include "cpu/reg.h"

#include <SDL/SDL.h>

#ifdef HAS_DEVICE_AUDIO
#define MAX_CHUNK_SIZE 1024*1024

static uint8_t  audio_chunk[2][MAX_CHUNK_SIZE]; // we've got two chunks
static uint32_t audio_len[2];   
static bool audio_chunk_ready[2];   
static uint8_t audio_chunk_play_idx = 0; // the current chunk being played
static uint8_t audio_chunk_fill_idx = 0; // the chunk to be filled 
static uint32_t audio_addr; // address of AUDIO_DATA struct in user program
static uint8_t  *audio_pos;   
static uint32_t audio_state = 1;  
static int data_len = 0;


static bool audio_active = false;
static SDL_mutex* audio_mutex[2];
static SDL_Thread * monitor_thread;
static bool switch_buf = false;

#define NUM_AUDIO_WORKER 2

static int AUDIO_CP_Thread(void* ptr) {
	int idx = *(int*) ptr;
	for(int i = 0; i < data_len / NUM_AUDIO_WORKER; i++) {
		audio_chunk[audio_chunk_fill_idx][i * NUM_AUDIO_WORKER + idx]
		       	= vaddr_read(audio_addr + 4 + i * NUM_AUDIO_WORKER + idx, SREG_DS, 1);	
	}
	return 0;
}

static void copy_audio_data() {
	int i = 0;
	SDL_Thread *threads[NUM_AUDIO_WORKER];
	for(i = 0; i < NUM_AUDIO_WORKER; i++) {
		threads[i] = SDL_CreateThread(AUDIO_CP_Thread,(void*) &i);
		if(threads[i] == NULL) {
			printf("create audio thread failed!\n");
			return;
		}
	}
	for(i = 0; i < NUM_AUDIO_WORKER; i++) {
		SDL_WaitThread(threads[i], NULL);
	}
	audio_chunk_ready[audio_chunk_fill_idx] = true;
}

static int AUDIO_Monitor_Thread(void* ptr) {
	// monitors audio playback states
	while(audio_active) {
		if(switch_buf) {
			// printf("raise audio intr fill idx = %d\n", audio_chunk_fill_idx);
			i8259_raise_intr(AUDIO_IRQ);
			switch_buf = false;
		}
		SDL_Delay(1);
	}
	return 0;
}

make_pio_handler(audio_io_handler) {
	if(port == AUDIO_CTL && is_write){
		int cmd = read_io_port(AUDIO_CTL,4);
		assert(cmd == 1 || cmd == 0);
		if(monitor_thread == NULL && cmd == 0) {
			audio_chunk_fill_idx = 1;
			audio_active = true;
			switch_buf = true; // trigger the first fill operation on chunk 1
			monitor_thread = SDL_CreateThread(AUDIO_Monitor_Thread, NULL);
		}
		if(cmd != audio_state){
			//while(cmd == 0 && audio_chunk_ready[audio_chunk_play_idx] == false) {
			//	SDL_Delay(1);
			//}
			audio_state = !audio_state;
			SDL_PauseAudio(audio_state); // 0 for play
		}	
	} else if(port == AUDIO_DATA && is_write) {
		while(SDL_LockMutex(audio_mutex[audio_chunk_fill_idx]) != 0) {
			if(nemu_state == NEMU_STOP) return;
			SDL_Delay(1);
		}
		audio_addr = read_io_port(AUDIO_DATA, 4);
		data_len = vaddr_read(audio_addr, SREG_DS, 4); // first 4 bytes as data length
		assert(data_len <= MAX_CHUNK_SIZE);
		copy_audio_data();
		audio_len[audio_chunk_fill_idx] = data_len;
		SDL_UnlockMutex(audio_mutex[audio_chunk_fill_idx]); // unlock
	}
}



/* Audio Callback 
 * The audio function callback takes the following parameters:  
 * stream: A pointer to the audio buffer to be filled  
 * len: The length (in bytes) of the audio buffer  
 *  
 */   
void fill_audio(void *udata, Uint8 *stream, int len) {
	assert(audio_chunk_play_idx != audio_chunk_fill_idx);
	while(SDL_LockMutex(audio_mutex[audio_chunk_play_idx]) != 0) {
		if(nemu_state == NEMU_STOP) return;
		SDL_Delay(1);
	}
	//SDL 2.0  
	//SDL_memset(stream, 0, len);  
	if(audio_len[audio_chunk_play_idx] > 0 && audio_chunk_ready[audio_chunk_play_idx]) { // do nothing 
	} else {
		// the current chunk being played is empty	
		// need to switch buffered chunk here
		audio_chunk_ready[audio_chunk_play_idx] = false;
		bool valid_enter = false;
		do {
			while(SDL_LockMutex(audio_mutex[audio_chunk_fill_idx]) != 0) { 
				// get lock to the new play idx, i.e., the current fill idx
				if(nemu_state == NEMU_STOP) return;
				SDL_Delay(1);
			}
			if(audio_chunk_ready[audio_chunk_fill_idx] == false) {
				//printf("audio real-time warning, waiting\n");
				SDL_UnlockMutex(audio_mutex[audio_chunk_fill_idx]); // unlock
				SDL_Delay(1);
			} else {valid_enter = true;}
			if(nemu_state == NEMU_STOP) return;
		} while(valid_enter == false);
		audio_chunk_fill_idx = audio_chunk_play_idx;
		audio_chunk_play_idx = (audio_chunk_play_idx + 1) % 2; // equal to old fill idx
		audio_pos = audio_chunk[audio_chunk_play_idx ]; // should be already ready
		SDL_UnlockMutex(audio_mutex[audio_chunk_fill_idx]); // unlock the old play idx
		switch_buf = true;
	}

	len = (len > audio_len[audio_chunk_play_idx] ? audio_len[audio_chunk_play_idx] : len);  
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);  
	audio_pos += len;   
	audio_len[audio_chunk_play_idx] -= len;   
	SDL_UnlockMutex(audio_mutex[audio_chunk_play_idx]); // unlock
}


void audio_start() {
	//SDL_AudioSpec  
	SDL_AudioSpec wanted_spec;  
	wanted_spec.freq = 16000;   
	wanted_spec.format = AUDIO_S16SYS;   
	wanted_spec.channels = 1;   
	wanted_spec.silence = 0;   
	wanted_spec.samples = 1024;   
	wanted_spec.callback = fill_audio;   
  
	if (SDL_OpenAudio(&wanted_spec, NULL) < 0){   
		printf("can't open audio.\n");
		assert(0);
	} 
	audio_state = 1;
	audio_chunk_ready[0] = audio_chunk_ready[1] = false;
	audio_chunk_play_idx = 0;

	audio_chunk_fill_idx = 0;
	audio_mutex[0] = SDL_CreateMutex();
	audio_mutex[1] = SDL_CreateMutex();
	assert(audio_mutex[0]);
	assert(audio_mutex[1]);
}

void audio_stop() {
	audio_active = false;
	SDL_CloseAudio();
	SDL_DestroyMutex(audio_mutex[0]);
	SDL_DestroyMutex(audio_mutex[1]);
}

#endif
