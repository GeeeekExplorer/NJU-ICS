#ifndef __INSTRUCTIONS_REF_H__
#define __INSTRUCTIONS_REF_H__


#include <nemu.h>
#include <cpu/cpu.h>
#include <cpu/modrm.h>
#include <cpu/operand.h>
#include <memory/memory.h>

#include <stdio.h>

#include "scoring.h"
#include "cpu-ref/alu_ref.h"
#include "cpu-ref/fpu_ref.h"
#include "cpu-ref/instr_helper_ref.h"
 
extern uint8_t data_size;

extern instr_func opcode_entry[];

// entries for all instructions
/*
extern instr_func opcode_2_byte_entry_ref[];
extern instr_func group_1_b_entry_ref[];
extern instr_func group_1_v_entry_ref[];
extern instr_func group_1_bv_entry_ref[];
extern instr_func group_2_b_entry_ref[];
extern instr_func group_2_v_entry_ref[];
extern instr_func group_2_1b_entry_ref[];
extern instr_func group_2_1v_entry_ref[];
extern instr_func group_2_cb_entry_ref[];
extern instr_func group_2_cv_entry_ref[];
extern instr_func group_3_b_entry_ref[];
extern instr_func group_3_v_entry_ref[];
extern instr_func group_5_indirect_entry_ref[];
extern instr_func group_7_entry_ref[];
extern instr_func group_x87_d8_entry_ref[];
extern instr_func group_x87_d9_entry_ref[];
extern instr_func group_x87_da_entry_ref[];
extern instr_func group_x87_db_entry_ref[];
extern instr_func group_x87_dc_entry_ref[];
extern instr_func group_x87_dd_entry_ref[];
extern instr_func group_x87_de_entry_ref[];
extern instr_func group_x87_df_entry_ref[];
*/


/*****************************************
* NEMU2 special instructions             *
******************************************/

//make_instr_func_ref(inv);
//make_instr_func_ref(nemu_trap);
//make_instr_func_ref(break_point);

/*****************************************
* MOV                                    *
******************************************/

make_instr_func_ref(mov_r2rm_b);
make_instr_func_ref(mov_r2rm_v);
make_instr_func_ref(mov_rm2r_b);
make_instr_func_ref(mov_rm2r_v);
make_instr_func_ref(mov_i2rm_b);
make_instr_func_ref(mov_i2rm_v);
make_instr_func_ref(mov_i2r_b);
make_instr_func_ref(mov_i2r_v);
make_instr_func_ref(mov_o2a_b);
make_instr_func_ref(mov_o2a_v);
make_instr_func_ref(mov_a2o_b);
make_instr_func_ref(mov_a2o_v);
make_instr_func_ref(mov_zrm82r_v);
make_instr_func_ref(mov_zrm162r_l);
make_instr_func_ref(mov_srm82r_v);
make_instr_func_ref(mov_srm162r_l);

make_instr_func_ref(movs_v);
make_instr_func_ref(movs_b);
make_instr_func_ref(mov_c2r_l);
make_instr_func_ref(mov_r2c_l);
make_instr_func_ref(mov_rm2s_w);

make_instr_func_ref(cmova_rm2r_v);
make_instr_func_ref(cmovae_rm2r_v);
make_instr_func_ref(cmovb_rm2r_v);
make_instr_func_ref(cmovbe_rm2r_v);
make_instr_func_ref(cmovg_rm2r_v);
make_instr_func_ref(cmovge_rm2r_v);
make_instr_func_ref(cmovl_rm2r_v);
make_instr_func_ref(cmovle_rm2r_v);
make_instr_func_ref(cmovne_rm2r_v);
make_instr_func_ref(cmovno_rm2r_v);
make_instr_func_ref(cmovnp_rm2r_v);
make_instr_func_ref(cmovns_rm2r_v);
make_instr_func_ref(cmovo_rm2r_v);
make_instr_func_ref(cmovp_rm2r_v);
make_instr_func_ref(cmovs_rm2r_v);
make_instr_func_ref(cmove_rm2r_v);

/*****************************************
* CMP                                    *
******************************************/

make_instr_func_ref(cmp_i2a_b);
make_instr_func_ref(cmp_i2a_v);
make_instr_func_ref(cmp_i2rm_bv);
make_instr_func_ref(cmp_i2rm_b);
make_instr_func_ref(cmp_i2rm_v);
make_instr_func_ref(cmp_rm2r_v);
make_instr_func_ref(cmp_rm2r_b);
make_instr_func_ref(cmp_i2a_b);
make_instr_func_ref(cmp_r2rm_v);
make_instr_func_ref(cmp_r2rm_b);

make_instr_func_ref(cmps_v);
make_instr_func_ref(cmps_b);

/*****************************************
* JMP JCC                                *
******************************************/

make_instr_func_ref(jmp_short);
make_instr_func_ref(jmp_near);
make_instr_func_ref(jmp_near_indirect);
make_instr_func_ref(jmp_far_imm);

make_instr_func_ref(je_short_);
make_instr_func_ref(ja_short_);
make_instr_func_ref(jae_short_);
make_instr_func_ref(jb_short_);
make_instr_func_ref(jecxz_short_);
make_instr_func_ref(jg_short_);
make_instr_func_ref(jge_short_);
make_instr_func_ref(jl_short_);
make_instr_func_ref(jle_short_);
make_instr_func_ref(jna_short_);
make_instr_func_ref(jne_short_);
make_instr_func_ref(jno_short_);
make_instr_func_ref(jnp_short_);
make_instr_func_ref(jns_short_);
make_instr_func_ref(jo_short_);
make_instr_func_ref(jp_short_);
make_instr_func_ref(js_short_);

make_instr_func_ref(je_near);
make_instr_func_ref(ja_near);
make_instr_func_ref(jae_near);
make_instr_func_ref(jb_near);
make_instr_func_ref(jg_near);
make_instr_func_ref(jge_near);
make_instr_func_ref(jl_near);
make_instr_func_ref(jle_near);
make_instr_func_ref(jna_near);
make_instr_func_ref(jne_near);
make_instr_func_ref(jno_near);
make_instr_func_ref(jnp_near);
make_instr_func_ref(jns_near);
make_instr_func_ref(jo_near);
make_instr_func_ref(jp_near);
make_instr_func_ref(js_near);

/*****************************************
* PUSH POP                               *
******************************************/

make_instr_func_ref(push_r_v);
make_instr_func_ref(push_rm_v);
make_instr_func_ref(push_i_b);
make_instr_func_ref(push_i_v);
make_instr_func_ref(pop_r_v);
make_instr_func_ref(pusha);
make_instr_func_ref(popa);


/*****************************************
* CALL RET                               *
******************************************/

make_instr_func_ref(call_near);
make_instr_func_ref(call_near_indirect);
make_instr_func_ref(ret_near);
make_instr_func_ref(ret_near_imm16);

/*****************************************
* TEST                                   *
******************************************/

make_instr_func_ref(test_r2rm_v);
make_instr_func_ref(test_r2rm_b);
make_instr_func_ref(test_i2rm_b);
make_instr_func_ref(test_i2rm_v);
make_instr_func_ref(test_i2a_b);
make_instr_func_ref(test_i2a_v);

/*****************************************
* SUB SBB                                *
******************************************/

make_instr_func_ref(sub_r2rm_v);
make_instr_func_ref(sub_r2rm_b);
make_instr_func_ref(sub_rm2r_b);
make_instr_func_ref(sub_rm2r_v);
make_instr_func_ref(sub_i2a_b);
make_instr_func_ref(sub_i2a_v);
make_instr_func_ref(sub_i2rm_bv);
make_instr_func_ref(sub_i2rm_b);
make_instr_func_ref(sub_i2rm_v);

make_instr_func_ref(sbb_r2rm_v);
make_instr_func_ref(sbb_r2rm_b);
make_instr_func_ref(sbb_rm2r_b);
make_instr_func_ref(sbb_rm2r_v);
make_instr_func_ref(sbb_i2a_b);
make_instr_func_ref(sbb_i2a_v);
make_instr_func_ref(sbb_i2rm_bv);
make_instr_func_ref(sbb_i2rm_b);
make_instr_func_ref(sbb_i2rm_v);

/*****************************************
* XOR                                    *
******************************************/

make_instr_func_ref(xor_r2rm_v);
make_instr_func_ref(xor_r2rm_b);
make_instr_func_ref(xor_rm2r_b);
make_instr_func_ref(xor_rm2r_v);
make_instr_func_ref(xor_i2a_b);
make_instr_func_ref(xor_i2a_v);
make_instr_func_ref(xor_i2rm_bv);
make_instr_func_ref(xor_i2rm_b);
make_instr_func_ref(xor_i2rm_v);

/*****************************************
* OR                                     *
******************************************/

make_instr_func_ref(or_r2rm_v);
make_instr_func_ref(or_r2rm_b);
make_instr_func_ref(or_rm2r_b);
make_instr_func_ref(or_rm2r_v);
make_instr_func_ref(or_i2a_b);
make_instr_func_ref(or_i2a_v);
make_instr_func_ref(or_i2rm_bv);
make_instr_func_ref(or_i2rm_b);
make_instr_func_ref(or_i2rm_v);

/*****************************************
* MUL IMUL                               *
******************************************/

make_instr_func_ref(mul_rm2a_b);
make_instr_func_ref(mul_rm2a_v);

make_instr_func_ref(imul_rm2r_v);
make_instr_func_ref(imul_rm2a_b);
make_instr_func_ref(imul_rm2a_v);
make_instr_func_ref(imul_irm2r_v);
make_instr_func_ref(imul_i8rm2r_v);

/*****************************************
* DIV IDIV                               *
******************************************/

make_instr_func_ref(idiv_rm2a_b);
make_instr_func_ref(idiv_rm2a_v);
make_instr_func_ref(div_rm2a_b);
make_instr_func_ref(div_rm2a_v);

/*****************************************
* AND                                    *
******************************************/

make_instr_func_ref(and_r2rm_v);
make_instr_func_ref(and_r2rm_b);
make_instr_func_ref(and_rm2r_b);
make_instr_func_ref(and_rm2r_v);
make_instr_func_ref(and_i2a_b);
make_instr_func_ref(and_i2a_v);
make_instr_func_ref(and_i2rm_bv);
make_instr_func_ref(and_i2rm_b);
make_instr_func_ref(and_i2rm_v);

/*****************************************
* ADD ADC                                *
******************************************/

make_instr_func_ref(add_r2rm_v);
make_instr_func_ref(add_r2rm_b);
make_instr_func_ref(add_rm2r_b);
make_instr_func_ref(add_rm2r_v);
make_instr_func_ref(add_i2a_b);
make_instr_func_ref(add_i2a_v);
make_instr_func_ref(add_i2rm_bv);
make_instr_func_ref(add_i2rm_b);
make_instr_func_ref(add_i2rm_v);

make_instr_func_ref(adc_r2rm_v);
make_instr_func_ref(adc_r2rm_b);
make_instr_func_ref(adc_rm2r_b);
make_instr_func_ref(adc_rm2r_v);
make_instr_func_ref(adc_i2a_b);
make_instr_func_ref(adc_i2a_v);
make_instr_func_ref(adc_i2rm_bv);
make_instr_func_ref(adc_i2rm_b);
make_instr_func_ref(adc_i2rm_v);

/*****************************************
* SETCC                                  *
******************************************/

make_instr_func_ref(setne_b);
make_instr_func_ref(seta_b);
make_instr_func_ref(setae_b);
make_instr_func_ref(setbe_b);
make_instr_func_ref(setc_b);
make_instr_func_ref(sete_b);
make_instr_func_ref(setg_b);
make_instr_func_ref(setge_b);
make_instr_func_ref(setl_b);
make_instr_func_ref(setle_b);
make_instr_func_ref(setno_b);
make_instr_func_ref(setnp_b);
make_instr_func_ref(setns_b);
make_instr_func_ref(seto_b);
make_instr_func_ref(setp_b);
make_instr_func_ref(sets_b);

/*****************************************
* NOT                                    *
******************************************/

make_instr_func_ref(not_rm_b);
make_instr_func_ref(not_rm_v);

/*****************************************
* NEG                                    *
******************************************/

make_instr_func_ref(neg_rm_b);
make_instr_func_ref(neg_rm_v);

/*****************************************
* LEAVE                                  *
******************************************/

make_instr_func_ref(leave);

/*****************************************
* LEA                                    *
******************************************/

make_instr_func_ref(lea);

/*****************************************
* SHIFT                                  *
******************************************/

make_instr_func_ref(shl_i2rm_bv);
make_instr_func_ref(shl_i2rm_b);
make_instr_func_ref(shl_rm_v);
make_instr_func_ref(shl_rm_b);
make_instr_func_ref(shl_c2rm_bv);
make_instr_func_ref(shl_c2rm_b);

make_instr_func_ref(shr_i2rm_bv);
make_instr_func_ref(shr_i2rm_b);
make_instr_func_ref(shr_rm_v);
make_instr_func_ref(shr_rm_b);
make_instr_func_ref(shr_c2rm_bv);
make_instr_func_ref(shr_c2rm_b);

make_instr_func_ref(sar_i2rm_bv);
make_instr_func_ref(sar_i2rm_b);
make_instr_func_ref(sar_rm_v);
make_instr_func_ref(sar_rm_b);
make_instr_func_ref(sar_c2rm_bv);
make_instr_func_ref(sar_c2rm_b);

/*****************************************
* FLAGS                            *
******************************************/

make_instr_func_ref(cld);
make_instr_func_ref(clc);
make_instr_func_ref(cli);
make_instr_func_ref(sti);
make_instr_func_ref(sahf);
make_instr_func_ref(bt_r2rm_v);

/*****************************************
* STOS                                   *
******************************************/

make_instr_func_ref(stos_b);
make_instr_func_ref(stos_v);

/*****************************************
* INC                                    *
******************************************/

make_instr_func_ref(inc_r_v);
make_instr_func_ref(inc_rm_v);

/*****************************************
* DEC                                    *
******************************************/

make_instr_func_ref(dec_r_v);
make_instr_func_ref(dec_rm_v);

/*****************************************
* X87                                    *
******************************************/
/*
make_instr_func_ref(x87_fldx);
make_instr_func_ref(x87_flds);
make_instr_func_ref(x87_fldl);
make_instr_func_ref(x87_fstps);
make_instr_func_ref(x87_fsts);
make_instr_func_ref(x87_fstx);
make_instr_func_ref(x87_fstpx);
make_instr_func_ref(x87_fadds);
make_instr_func_ref(x87_faddx);
make_instr_func_ref(x87_faddlx);
make_instr_func_ref(x87_fsubs);
make_instr_func_ref(x87_fmuls);
make_instr_func_ref(x87_fmullx);
make_instr_func_ref(x87_fdivs);
make_instr_func_ref(x87_fxch);
make_instr_func_ref(x87_fucom);
make_instr_func_ref(x87_fucomp);
make_instr_func_ref(x87_fucompp);
make_instr_func_ref(x87_fucomi);
make_instr_func_ref(x87_fucomip);
make_instr_func_ref(x87_fnstsw);
make_instr_func_ref(x87_fnstcw);
make_instr_func_ref(x87_fistpl);
make_instr_func_ref(x87_fildl);
*/

/*****************************************
* CBW                                    *
******************************************/

make_instr_func_ref(cbw_a_v);

/*****************************************
* IO                                     *
******************************************/

make_instr_func_ref(in_b);
make_instr_func_ref(in_v);
make_instr_func_ref(out_b);
make_instr_func_ref(out_v);



/*****************************************
* INT                                     *
******************************************/
make_instr_func_ref(int_); // int instruction
make_instr_func_ref(iret);

/*****************************************
* MISC                                   *
******************************************/

make_instr_func_ref(nop);
//make_instr_func_ref(data_size_16);
make_instr_func_ref(rep_repe);
make_instr_func_ref(cltd);
make_instr_func_ref(lgdt);
make_instr_func_ref(lidt);
make_instr_func_ref(hlt);

/*
make_instr_func_ref(opcode_2_byte);


make_instr_func_ref(group_1_b);
make_instr_func_ref(group_1_v);
make_instr_func_ref(group_1_bv);

make_instr_func_ref(group_2_b);
make_instr_func_ref(group_2_v);
make_instr_func_ref(group_2_1b);
make_instr_func_ref(group_2_1v);
make_instr_func_ref(group_2_cb);
make_instr_func_ref(group_2_cv);

make_instr_func_ref(group_3_b);
make_instr_func_ref(group_3_v);

make_instr_func_ref(group_5_indirect);

make_instr_func_ref(group_7);

make_instr_func_ref(group_x87_d8);
make_instr_func_ref(group_x87_d9);
make_instr_func_ref(group_x87_da);
make_instr_func_ref(group_x87_db);
make_instr_func_ref(group_x87_dc);
make_instr_func_ref(group_x87_dd);
make_instr_func_ref(group_x87_de);
make_instr_func_ref(group_x87_df);
*/
#endif
