.PHONY: nemu all clean

include Makefile.git

Submit_Script = scripts/submit

nemu: update
	$(call git_commit, "nemu")
	scripts/make_emotion.sh
	cat make.log

run: nemu
	$(call git_commit, "run")
	./nemu/nemu --testcase add

run-kernel: nemu
	$(call git_commit, "run-kernel")
	./nemu/nemu --kernel --testcase echo

#make all if you do not want to participate in the survey
all: update
	$(call git_commit, "all")
	cd nemu && make
	cd testcase && make
	cd kernel && make
	cd game && make

clean: update
	$(call git_commit, "clean")
	cd nemu && make clean
	cd game && make clean
	cd testcase && make clean
	cd kernel && make clean

# local tests to different stages of PA

test_pa-1: nemu update
	$(call git_commit, "test_pa-1")
	./nemu/nemu --test-reg
	./nemu/nemu --test-alu add
	./nemu/nemu --test-alu adc
	./nemu/nemu --test-alu sub
	./nemu/nemu --test-alu sbb
	./nemu/nemu --test-alu and
	./nemu/nemu --test-alu or
	./nemu/nemu --test-alu xor
	./nemu/nemu --test-alu shl
	./nemu/nemu --test-alu shr
	./nemu/nemu --test-alu sal
	./nemu/nemu --test-alu sar
	./nemu/nemu --test-alu mul
	./nemu/nemu --test-alu div
	./nemu/nemu --test-alu imul
	./nemu/nemu --test-alu idiv
	./nemu/nemu --test-fpu add
	./nemu/nemu --test-fpu sub
	./nemu/nemu --test-fpu mul
	./nemu/nemu --test-fpu div

test_pa-2-1: nemu update
	$(call git_commit, "test_pa-2-1")
	./nemu/nemu --autorun --testcase mov
	./nemu/nemu --autorun --testcase mov-cmp
	./nemu/nemu --autorun --testcase mov-c
	./nemu/nemu --autorun --testcase mov-jcc
	./nemu/nemu --autorun --testcase add
	./nemu/nemu --autorun --testcase add-longlong
	./nemu/nemu --autorun --testcase if-else
	./nemu/nemu --autorun --testcase fib
	./nemu/nemu --autorun --testcase bubble-sort
	./nemu/nemu --autorun --testcase quick-sort
	./nemu/nemu --autorun --testcase select-sort
	./nemu/nemu --autorun --testcase max
	./nemu/nemu --autorun --testcase min3
	./nemu/nemu --autorun --testcase pascal
	./nemu/nemu --autorun --testcase bit 
	./nemu/nemu --autorun --testcase movsx
	./nemu/nemu --autorun --testcase sub-longlong
	./nemu/nemu --autorun --testcase fact
	./nemu/nemu --autorun --testcase gotbaha
	./nemu/nemu --autorun --testcase leap-year
	./nemu/nemu --autorun --testcase matrix-mul-small
	./nemu/nemu --autorun --testcase matrix-mul
	./nemu/nemu --autorun --testcase mul-longlong 
	./nemu/nemu --autorun --testcase prime
	./nemu/nemu --autorun --testcase shuixianhua
	./nemu/nemu --autorun --testcase sum
	./nemu/nemu --autorun --testcase wanshu
	./nemu/nemu --autorun --testcase struct
	./nemu/nemu --autorun --testcase string
	./nemu/nemu --autorun --testcase hello-str 
	./nemu/nemu --autorun --testcase test-float

test_pa-2-2: nemu update
	$(call git_commit, "test_pa-2-2")
	./nemu/nemu --autorun --testcase mov --kernel
	./nemu/nemu --autorun --testcase mov-cmp --kernel
	./nemu/nemu --autorun --testcase mov-c --kernel
	./nemu/nemu --autorun --testcase mov-jcc --kernel
	./nemu/nemu --autorun --testcase add --kernel
	./nemu/nemu --autorun --testcase add-longlong --kernel
	./nemu/nemu --autorun --testcase if-else --kernel
	./nemu/nemu --autorun --testcase fib --kernel
	./nemu/nemu --autorun --testcase bubble-sort --kernel
	./nemu/nemu --autorun --testcase quick-sort --kernel
	./nemu/nemu --autorun --testcase select-sort --kernel
	./nemu/nemu --autorun --testcase max --kernel
	./nemu/nemu --autorun --testcase min3 --kernel
	./nemu/nemu --autorun --testcase pascal --kernel
	./nemu/nemu --autorun --testcase bit  --kernel
	./nemu/nemu --autorun --testcase movsx --kernel
	./nemu/nemu --autorun --testcase sub-longlong --kernel
	./nemu/nemu --autorun --testcase fact --kernel
	./nemu/nemu --autorun --testcase gotbaha --kernel
	./nemu/nemu --autorun --testcase leap-year --kernel
	./nemu/nemu --autorun --testcase matrix-mul-small --kernel
	./nemu/nemu --autorun --testcase matrix-mul --kernel
	./nemu/nemu --autorun --testcase mul-longlong  --kernel
	./nemu/nemu --autorun --testcase prime --kernel
	./nemu/nemu --autorun --testcase shuixianhua --kernel
	./nemu/nemu --autorun --testcase sum --kernel
	./nemu/nemu --autorun --testcase wanshu --kernel
	./nemu/nemu --autorun --testcase struct --kernel
	./nemu/nemu --autorun --testcase string --kernel
	./nemu/nemu --autorun --testcase hello-str  --kernel
	./nemu/nemu --autorun --testcase test-float --kernel

test_pa-2-3: nemu update
	$(call git_commit, "test_pa-2-3")
	echo "\e[0;31mTest expressions yourself\e[0m"
	./nemu/nemu --testcase add --kernel

test_pa-3-1: test_pa-2-2 update
	$(call git_commit, "test_pa-3-1")

test_pa-3-2: test_pa-2-2 update
	$(call git_commit, "test_pa-3-2")

test_pa-3-3: nemu update
	$(call git_commit, "test_pa-3-3")
	./nemu/nemu --autorun --testcase mov-c --kernel
	./nemu/nemu --autorun --testcase mov-jcc --kernel
	./nemu/nemu --autorun --testcase add --kernel
	./nemu/nemu --autorun --testcase add-longlong --kernel
	./nemu/nemu --autorun --testcase if-else --kernel
	./nemu/nemu --autorun --testcase fib --kernel
	./nemu/nemu --autorun --testcase bubble-sort --kernel
	./nemu/nemu --autorun --testcase quick-sort --kernel
	./nemu/nemu --autorun --testcase select-sort --kernel
	./nemu/nemu --autorun --testcase max --kernel
	./nemu/nemu --autorun --testcase min3 --kernel
	./nemu/nemu --autorun --testcase pascal --kernel
	./nemu/nemu --autorun --testcase bit  --kernel
	./nemu/nemu --autorun --testcase movsx --kernel
	./nemu/nemu --autorun --testcase sub-longlong --kernel
	./nemu/nemu --autorun --testcase fact --kernel
	./nemu/nemu --autorun --testcase gotbaha --kernel
	./nemu/nemu --autorun --testcase leap-year --kernel
	./nemu/nemu --autorun --testcase matrix-mul-small --kernel
	./nemu/nemu --autorun --testcase matrix-mul --kernel
	./nemu/nemu --autorun --testcase mul-longlong  --kernel
	./nemu/nemu --autorun --testcase prime --kernel
	./nemu/nemu --autorun --testcase shuixianhua --kernel
	./nemu/nemu --autorun --testcase sum --kernel
	./nemu/nemu --autorun --testcase wanshu --kernel
	./nemu/nemu --autorun --testcase struct --kernel
	./nemu/nemu --autorun --testcase string --kernel
	./nemu/nemu --autorun --testcase hello-str  --kernel
	./nemu/nemu --autorun --testcase test-float --kernel

test_pa-4-1: test_pa-3-3 update
	$(call git_commit, "test_pa-4-1")
	./nemu/nemu --autorun --testcase hello-inline --kernel

test_pa-4-2: test_pa-4-1 update
	$(call git_commit, "test_pa-4-2")
	./nemu/nemu --autorun --testcase echo --kernel

test_pa-4-3: nemu update
	$(call git_commit, "test_pa-4-3")
	./nemu/nemu --test-game --kernel --autorun


# submit to different stages of PA

submit_pa-1: update
	$(call git_commit, "submit_pa-1")
	$(Submit_Script) pa-1 $(STU_ID) $(Server_IP)

submit_pa-2-1: update
	$(call git_commit, "submit_pa-2-1")
	$(Submit_Script) pa-2-1 $(STU_ID) $(Server_IP)

submit_pa-2-2: update
	$(call git_commit, "submit_pa-2-2")
	$(Submit_Script) pa-2-2 $(STU_ID) $(Server_IP)

submit_pa-2-3: update
	$(call git_commit, "submit_pa-2-3")
	$(Submit_Script) pa-2-3 $(STU_ID) $(Server_IP)

submit_pa-3-1: update
	$(call git_commit, "submit_pa-3-1")
	$(Submit_Script) pa-3-1 $(STU_ID) $(Server_IP)

submit_pa-3-2: update
	$(call git_commit, "submit_pa-3-2")
	$(Submit_Script) pa-3-2 $(STU_ID) $(Server_IP)

submit_pa-3-3: update
	$(call git_commit, "submit_pa-3-3")
	$(Submit_Script) pa-3-3 $(STU_ID) $(Server_IP)

submit_pa-4-1: update
	$(call git_commit, "submit_pa-4-1")
	$(Submit_Script) pa-4-1 $(STU_ID) $(Server_IP)

submit_pa-4-2: update
	$(call git_commit, "submit_pa-4-2")
	$(Submit_Script) pa-4-2 $(STU_ID) $(Server_IP)

submit_pa-4-3: update
	$(call git_commit, "submit_pa-4-3")
	$(Submit_Script) pa-4-3 $(STU_ID) $(Server_IP)

update:
	./scripts/update $(STU_ID)
