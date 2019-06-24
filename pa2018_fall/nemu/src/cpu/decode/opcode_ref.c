#include "cpu/instr.h"

instr_func __ref_opcode_entry[256] = {
/* 0x00 - 0x03*/	__ref_add_r2rm_b, __ref_add_r2rm_v, __ref_add_rm2r_b, __ref_add_rm2r_v,
/* 0x04 - 0x07*/	__ref_add_i2a_b, __ref_add_i2a_v, inv, inv,
/* 0x08 - 0x0b*/	__ref_or_r2rm_b, __ref_or_r2rm_v, __ref_or_rm2r_b, __ref_or_rm2r_v,
/* 0x0c - 0x0f*/	__ref_or_i2a_b, __ref_or_i2a_v, inv, opcode_2_byte,
/* 0x10 - 0x13*/	__ref_adc_r2rm_b, __ref_adc_r2rm_v, __ref_adc_rm2r_b, __ref_adc_rm2r_v,
/* 0x14 - 0x17*/	__ref_adc_i2a_b, __ref_adc_i2a_v, inv, inv,
/* 0x18 - 0x1b*/	__ref_sbb_r2rm_b, __ref_sbb_r2rm_v, __ref_sbb_rm2r_b, __ref_sbb_rm2r_v,
/* 0x1c - 0x1f*/	__ref_sbb_i2a_b, __ref_sbb_i2a_v, inv, inv,
/* 0x20 - 0x23*/	__ref_and_r2rm_b, __ref_and_r2rm_v, __ref_and_rm2r_b, __ref_and_rm2r_v,
/* 0x24 - 0x27*/	__ref_and_i2a_b, __ref_and_i2a_v, inv, inv,
/* 0x28 - 0x2b*/	__ref_sub_r2rm_b, __ref_sub_r2rm_v, __ref_sub_rm2r_b, __ref_sub_rm2r_v,
/* 0x2c - 0x2f*/	__ref_sub_i2a_b, __ref_sub_i2a_v, inv, inv,
/* 0x30 - 0x33*/	__ref_xor_r2rm_b, __ref_xor_r2rm_v, __ref_xor_rm2r_b, __ref_xor_rm2r_v,
/* 0x34 - 0x37*/	__ref_xor_i2a_b, __ref_xor_i2a_v, inv, inv,
/* 0x38 - 0x3b*/	__ref_cmp_r2rm_b, __ref_cmp_r2rm_v, __ref_cmp_rm2r_b, __ref_cmp_rm2r_v,
/* 0x3c - 0x3f*/	__ref_cmp_i2a_b, __ref_cmp_i2a_v, inv, inv,
/* 0x40 - 0x43*/	__ref_inc_r_v, __ref_inc_r_v, __ref_inc_r_v, __ref_inc_r_v,
/* 0x44 - 0x47*/	__ref_inc_r_v, __ref_inc_r_v, __ref_inc_r_v, __ref_inc_r_v,
/* 0x48 - 0x4b*/	__ref_dec_r_v, __ref_dec_r_v, __ref_dec_r_v, __ref_dec_r_v,
/* 0x4c - 0x4f*/	__ref_dec_r_v, __ref_dec_r_v, __ref_dec_r_v, __ref_dec_r_v,
/* 0x50 - 0x53*/	__ref_push_r_v, __ref_push_r_v, __ref_push_r_v, __ref_push_r_v,
/* 0x54 - 0x57*/	__ref_push_r_v, __ref_push_r_v, __ref_push_r_v, __ref_push_r_v,
/* 0x58 - 0x5b*/	__ref_pop_r_v, __ref_pop_r_v, __ref_pop_r_v, __ref_pop_r_v,
/* 0x5c - 0x5f*/	__ref_pop_r_v, __ref_pop_r_v, __ref_pop_r_v, __ref_pop_r_v,
/* 0x60 - 0x63*/	__ref_pusha, __ref_popa, inv, inv,
/* 0x64 - 0x67*/	inv, inv, data_size_16, inv,
/* 0x68 - 0x6b*/	__ref_push_i_v, __ref_imul_irm2r_v, __ref_push_i_b, __ref_imul_i8rm2r_v,
/* 0x6c - 0x6f*/	inv, inv, inv, inv,
/* 0x70 - 0x73*/	__ref_jo_short_, __ref_jno_short_, __ref_jb_short_, __ref_jae_short_,
/* 0x74 - 0x77*/	__ref_je_short_, __ref_jne_short_, __ref_jna_short_, __ref_ja_short_,
/* 0x78 - 0x7b*/	__ref_js_short_, __ref_jns_short_, __ref_jp_short_, __ref_jnp_short_,
/* 0x7c - 0x7f*/	__ref_jl_short_, __ref_jge_short_, __ref_jle_short_, __ref_jg_short_,
/* 0x80 - 0x83*/	group_1_b, group_1_v, nemu_trap, group_1_bv,
/* 0x84 - 0x87*/	__ref_test_r2rm_b, __ref_test_r2rm_v, inv, inv,
/* 0x88 - 0x8b*/	__ref_mov_r2rm_b, __ref_mov_r2rm_v, __ref_mov_rm2r_b, __ref_mov_rm2r_v,
/* 0x8c - 0x8f*/	inv, __ref_lea, __ref_mov_rm2s_w, inv,
/* 0x90 - 0x93*/	nop, inv, inv, inv,
/* 0x94 - 0x97*/	inv, inv, inv, inv,
/* 0x98 - 0x9b*/	__ref_cbw_a_v, __ref_cltd, inv, inv,
/* 0x9c - 0x9f*/	inv, inv, __ref_sahf, inv,
/* 0xa0 - 0xa3*/	__ref_mov_o2a_b, __ref_mov_o2a_v, __ref_mov_a2o_b, __ref_mov_a2o_v,
/* 0xa4 - 0xa7*/	__ref_movs_b, __ref_movs_v, __ref_cmps_b, __ref_cmps_v,
/* 0xa8 - 0xab*/	__ref_test_i2a_b, __ref_test_i2a_v, __ref_stos_b, __ref_stos_v,
/* 0xac - 0xaf*/	inv, inv, inv, inv,
/* 0xb0 - 0xb3*/	__ref_mov_i2r_b, __ref_mov_i2r_b, __ref_mov_i2r_b, __ref_mov_i2r_b,
/* 0xb4 - 0xb7*/	__ref_mov_i2r_b, __ref_mov_i2r_b, __ref_mov_i2r_b, __ref_mov_i2r_b,
/* 0xb8 - 0xbb*/	__ref_mov_i2r_v, __ref_mov_i2r_v, __ref_mov_i2r_v, __ref_mov_i2r_v,
/* 0xbc - 0xbf*/	__ref_mov_i2r_v, __ref_mov_i2r_v, __ref_mov_i2r_v, __ref_mov_i2r_v,
/* 0xc0 - 0xc3*/	group_2_b, group_2_v, __ref_ret_near_imm16, __ref_ret_near,
/* 0xc4 - 0xc7*/	inv, inv, __ref_mov_i2rm_b, __ref_mov_i2rm_v,
/* 0xc8 - 0xcb*/	inv, __ref_leave, inv, inv,
/* 0xcc - 0xcf*/	inv, __ref_int_, inv, __ref_iret,
/* 0xd0 - 0xd3*/	group_2_1b, group_2_1v, group_2_cb, group_2_cv,
/* 0xd4 - 0xd7*/	inv, inv, inv, inv,
/* 0xd8 - 0xdb*/	group_x87_d8, group_x87_d9, group_x87_da, group_x87_db,
/* 0xdc - 0xdf*/	group_x87_dc, group_x87_dd, group_x87_de, group_x87_df,
/* 0xe0 - 0xe3*/	inv, inv, inv, __ref_jecxz_short_,
/* 0xe4 - 0xe7*/	inv, inv, inv, inv,
/* 0xe8 - 0xeb*/	__ref_call_near, __ref_jmp_near, __ref_jmp_far_imm, __ref_jmp_short,
/* 0xec - 0xef*/	__ref_in_b, __ref_in_v, __ref_out_b, __ref_out_v,
/* 0xf0 - 0xf3*/	inv, break_point, inv, __ref_rep_repe,
/* 0xf4 - 0xf7*/	__ref_hlt, inv, group_3_b, group_3_v,
/* 0xf8 - 0xfb*/	__ref_clc, inv, __ref_cli, __ref_sti,
/* 0xfc - 0xff*/	__ref_cld, inv, inv, group_5_indirect,
};

/* 0x80 */
instr_func __ref_group_1_b_entry[8] =
{__ref_add_i2rm_b, __ref_or_i2rm_b, __ref_adc_i2rm_b, __ref_sbb_i2rm_b, __ref_and_i2rm_b, __ref_sub_i2rm_b, __ref_xor_i2rm_b, __ref_cmp_i2rm_b};

/* 0x81 */
instr_func __ref_group_1_v_entry[8] =
{__ref_add_i2rm_v, __ref_or_i2rm_v, __ref_adc_i2rm_v, __ref_sbb_i2rm_v, __ref_and_i2rm_v, __ref_sub_i2rm_v, __ref_xor_i2rm_v, __ref_cmp_i2rm_v};

/* 0x83 */
instr_func __ref_group_1_bv_entry[8] =
{__ref_add_i2rm_bv, __ref_or_i2rm_bv, __ref_adc_i2rm_bv, __ref_sbb_i2rm_bv, __ref_and_i2rm_bv, __ref_sub_i2rm_bv, __ref_xor_i2rm_bv, __ref_cmp_i2rm_bv};

/* 0xc0 */
instr_func __ref_group_2_b_entry[8] =
{inv, inv, inv, inv, __ref_shl_i2rm_b, __ref_shr_i2rm_b, inv, __ref_sar_i2rm_b};

/* 0xc1 */
instr_func __ref_group_2_v_entry[8] =
{inv, inv, inv, inv, __ref_shl_i2rm_bv, __ref_shr_i2rm_bv, inv, __ref_sar_i2rm_bv};

/* 0xd0 */
instr_func __ref_group_2_1b_entry[8] =
{inv, inv, inv, inv, __ref_shl_rm_b, __ref_shr_rm_b, inv, __ref_sar_rm_b};

/* 0xd1 */
instr_func __ref_group_2_1v_entry[8] =
{inv, inv, inv, inv, __ref_shl_rm_v, __ref_shr_rm_v, inv, __ref_sar_rm_v};

/* 0xd2 */
instr_func __ref_group_2_cb_entry[8] =
{inv, inv, inv, inv, __ref_shl_c2rm_b, inv, __ref_shr_c2rm_b, __ref_sar_c2rm_b};

/* 0xd3 */
instr_func __ref_group_2_cv_entry[8] =
{inv, inv, inv, inv, __ref_shl_c2rm_bv, inv, __ref_shr_c2rm_bv, __ref_sar_c2rm_bv};

/* 0xf6 */
instr_func __ref_group_3_b_entry[8] =
{__ref_test_i2rm_b, inv, __ref_not_rm_b, __ref_neg_rm_b, __ref_mul_rm2a_b, __ref_imul_rm2a_b, __ref_div_rm2a_b, __ref_idiv_rm2a_b};

/* 0xf7 */
instr_func __ref_group_3_v_entry[8] =
{__ref_test_i2rm_v, inv, __ref_not_rm_v, __ref_neg_rm_v, __ref_mul_rm2a_v, __ref_imul_rm2a_v, __ref_div_rm2a_v, __ref_idiv_rm2a_v};

/* 0xff */
instr_func __ref_group_5_indirect_entry[8] =
{__ref_inc_rm_v, __ref_dec_rm_v, __ref_call_near_indirect, inv, __ref_jmp_near_indirect, inv, __ref_push_rm_v, inv};

instr_func __ref_group_7_entry[8] = 
{inv, inv, __ref_lgdt, __ref_lidt, inv, inv, inv, inv};

/* 0xd8 */
instr_func __ref_group_x87_d8_entry[8] =
{x87_fadds, x87_fmuls, inv, inv, x87_fsubs, inv, x87_fdivs, inv};

/* 0xd9 */
instr_func __ref_group_x87_d9_entry[8] =
{x87_flds, x87_fxch, x87_fsts, x87_fstps, inv, x87_fldx, inv, x87_fnstcw};

/* 0xda */
instr_func __ref_group_x87_da_entry[8] =
{inv, inv, inv, inv, inv, x87_fucompp, inv, inv};

/* 0xdb */
instr_func __ref_group_x87_db_entry[8] =
{x87_fildl, inv, inv, x87_fistpl, inv, x87_fucomi, inv, inv};

/* 0xdc */
instr_func __ref_group_x87_dc_entry[8] =
{x87_faddlx, x87_fmullx, inv, inv, inv, inv, inv, inv};

/* 0xdd */
instr_func __ref_group_x87_dd_entry[8] =
{x87_fldl, inv, x87_fstx, x87_fstpx, x87_fucom, x87_fucomp, inv, inv};

/* 0xde */
instr_func __ref_group_x87_de_entry[8] =
{x87_faddx, inv, inv, inv, inv, inv, inv, inv};

/* 0xdf */
instr_func __ref_group_x87_df_entry[8] =
{inv, inv, inv, inv, x87_fnstsw, x87_fucomip, inv, inv};

/* 0x.. */
// instr_func group_5_indirect_entry[8] =
// {inv, inv, inv, inv, inv, inv, inv, inv};


instr_func __ref_opcode_2_byte_entry[256] = {
/* 0x00 - 0x03*/        inv, group_7, inv, inv,
/* 0x04 - 0x07*/        inv, inv, inv, inv,
/* 0x08 - 0x0b*/        inv, inv, inv, inv,
/* 0x0c - 0x0f*/        inv, inv, inv, inv,
/* 0x10 - 0x13*/        inv, inv, inv, inv,
/* 0x14 - 0x17*/        inv, inv, inv, inv,
/* 0x18 - 0x1b*/        inv, inv, inv, inv,
/* 0x1c - 0x1f*/        inv, inv, inv, inv,
/* 0x20 - 0x23*/        __ref_mov_c2r_l, inv, __ref_mov_r2c_l, inv,
/* 0x24 - 0x27*/        inv, inv, inv, inv,
/* 0x28 - 0x2b*/        inv, inv, inv, inv,
/* 0x2c - 0x2f*/        inv, inv, inv, inv,
/* 0x30 - 0x33*/        inv, inv, inv, inv,
/* 0x34 - 0x37*/        inv, inv, inv, inv,
/* 0x38 - 0x3b*/        inv, inv, inv, inv,
/* 0x3c - 0x3f*/        inv, inv, inv, inv,
/* 0x40 - 0x43*/        inv, inv, inv, inv,
/* 0x44 - 0x47*/        __ref_cmove_rm2r_v, __ref_cmovne_rm2r_v, inv, __ref_cmova_rm2r_v,
/* 0x48 - 0x4b*/        __ref_cmovs_rm2r_v, __ref_cmovns_rm2r_v, inv, inv,
/* 0x4c - 0x4f*/        inv, __ref_cmovge_rm2r_v, inv, inv,
/* 0x50 - 0x53*/        inv, inv, inv, inv,
/* 0x54 - 0x57*/        inv, inv, inv, inv,
/* 0x58 - 0x5b*/        inv, inv, inv, inv,
/* 0x5c - 0x5f*/        inv, inv, inv, inv,
/* 0x60 - 0x63*/        inv, inv, inv, inv,
/* 0x64 - 0x67*/        inv, inv, inv, inv,
/* 0x68 - 0x6b*/        inv, inv, inv, inv,
/* 0x6c - 0x6f*/        inv, inv, inv, inv,
/* 0x70 - 0x73*/        inv, inv, inv, inv,
/* 0x74 - 0x77*/        inv, inv, inv, inv,
/* 0x78 - 0x7b*/        inv, inv, inv, inv,
/* 0x7c - 0x7f*/        inv, inv, inv, inv,
/* 0x80 - 0x83*/        __ref_jo_near, __ref_jno_near, __ref_jb_near, __ref_jae_near,
/* 0x84 - 0x87*/        __ref_je_near, __ref_jne_near, __ref_jna_near, __ref_ja_near,
/* 0x88 - 0x8b*/        __ref_js_near, __ref_jns_near, __ref_jp_near, __ref_jnp_near,
/* 0x8c - 0x8f*/        __ref_jl_near, __ref_jge_near, __ref_jle_near, __ref_jg_near,
/* 0x90 - 0x93*/        __ref_seto_b, __ref_setno_b, __ref_setc_b, __ref_setae_b,
/* 0x94 - 0x97*/        __ref_sete_b, __ref_setne_b, __ref_setbe_b, __ref_seta_b,
/* 0x98 - 0x9b*/        __ref_sets_b, __ref_setns_b, __ref_setp_b, __ref_setnp_b,
/* 0x9c - 0x9f*/        __ref_setl_b, __ref_setge_b, __ref_setle_b, __ref_setg_b,
/* 0xa0 - 0xa3*/        inv, inv, inv, __ref_bt_r2rm_v,
/* 0xa4 - 0xa7*/        inv, inv, inv, inv,
/* 0xa8 - 0xab*/        inv, inv, inv, inv,
/* 0xac - 0xaf*/        inv, inv, inv, __ref_imul_rm2r_v,
/* 0xb0 - 0xb3*/        inv, inv, inv, inv,
/* 0xb4 - 0xb7*/        inv, inv, __ref_mov_zrm82r_v, __ref_mov_zrm162r_l,
/* 0xb8 - 0xbb*/        inv, inv, inv, inv,
/* 0xbc - 0xbf*/        inv, inv, __ref_mov_srm82r_v, __ref_mov_srm162r_l,
/* 0xc0 - 0xc3*/        inv, inv, inv, inv,
/* 0xc4 - 0xc7*/        inv, inv, inv, inv,
/* 0xc8 - 0xcb*/        inv, inv, inv, inv,
/* 0xcc - 0xcf*/        inv, inv, inv, inv,
/* 0xd0 - 0xd3*/        inv, inv, inv, inv,
/* 0xd4 - 0xd7*/        inv, inv, inv, inv,
/* 0xd8 - 0xdb*/        inv, inv, inv, inv,
/* 0xdc - 0xdf*/        inv, inv, inv, inv,
/* 0xe0 - 0xe3*/        inv, inv, inv, inv,
/* 0xe4 - 0xe7*/        inv, inv, inv, inv,
/* 0xe8 - 0xeb*/        inv, inv, inv, inv,
/* 0xec - 0xef*/        inv, inv, inv, inv,
/* 0xf0 - 0xf3*/        inv, inv, inv, inv,
/* 0xf4 - 0xf7*/        inv, inv, inv, inv,
/* 0xf8 - 0xfb*/        inv, inv, inv, inv,
/* 0xfc - 0xff*/        inv, inv, inv, inv,
};

