#ifndef __SCORING_H__
#define __SCORING_H__

void clear_ref();
void set_ref();
int get_ref();

// write trap info
void score_trap();
void score_expr();

// nemu config
void score_set_ia32_seg();
void score_set_ia32_page();
void score_set_tlb_enabled();
void score_set_cache_enabled();
void score_set_ia32_intr();
void score_set_has_device_timer();
void score_set_has_device_serial();
void score_set_has_device_ide();
void score_set_has_device_keyboard();
void score_set_has_device_vga();
void score_set_has_device_audio();
void score_fix_config(); // prevent further changes to config log

#endif
