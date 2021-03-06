﻿#include"../../../include/gfxcoder.h"
#include"../../../include/fft/sfft16x16.h"

void gfxcoder::sfft4x4_r2c_grid_perm()
{
    uint2 c[12];
    for( int i=0; i<8; ++i ){ c[i].x=v0+i; c[i].y=v8+i; }
    for( int i=0; i<8; ++i ){ CPTR(c)[16+i]=v16+i; }

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s3 ;
    const uint32_t rbase =s4 ;
    const uint32_t ncells=s6 ;
    const uint32_t nx    =s7 ;
    const uint32_t ldx   =s8 ;
    const uint32_t ldy   =s9 ;
    const uint32_t grid  =s10;
    const uint32_t tile  =s11;
    const uint32_t xmagic=s12;
    const uint32_t xshift=s13;
    const uint32_t ymagic=s14;
    const uint32_t yshift=s15;
    const uint32_t grid_x=s16;
    const uint32_t grid_y=s17;
    const uint32_t tile_x=s18;
    const uint32_t tile_y=s19;
    const uint32_t C0x   =s7 ;
    const uint32_t C0y   =s8 ;
    const uint32_t C1x   =s9 ;
    const uint32_t C1y   =s10;
    const uint32_t C2x   =s11;
    const uint32_t C2y   =s12;
    const uint32_t sk0   =s13;
    const uint32_t sk1   =s14;
    const uint32_t sk2   =s15;
    const uint32_t k0x   =s16;
    const uint32_t k0y   =s17;
    const uint32_t k1x   =s18;
    const uint32_t k1y   =s19;
    const uint32_t k2x   =s20;
    const uint32_t k2y   =s21;
    const uint32_t k3x   =s22;
    const uint32_t k3y   =s23;
    const uint32_t k4x   =s24;
    const uint32_t k4y   =s25;
    const uint32_t k5x   =s26;
    const uint32_t k5y   =s27;
    const uint32_t cbase =s0 ;
    const uint32_t ldc   =s2 ;
    const uint32_t bks   =s3 ;

    const uint32_t rvo    =v16;
    const uint32_t icell  =v17;
    const uint32_t icell_y=v18;
    const uint32_t icell_x=v19;
    const uint32_t imap   =v20;
    const uint32_t v      =v22;
    const uint32_t x      =v24;
    const uint32_t y      =v25;
    const uint32_t u      =v26;
    const uint32_t xsst   =v27;
    const uint32_t xsld   =v28;
    const uint32_t ysst   =v29;
    const uint32_t ysld   =v27;
    const uint32_t osst   =v30;
    const uint32_t osld   =v31;
    const uint32_t cvo    =v18;

    metadata_start();
    {
        metadata_set_lds_size(0x2440);
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(68);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(32);
        metadata_set_vgprcnt(32);
        metadata_set_arg(8,0x00,arg_kind_globuf,arg_type_f32);
        metadata_set_arg(4,0x08,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x0c,arg_kind_direct,arg_type_u32);
        metadata_set_arg(8,0x10,arg_kind_globuf,arg_type_f32);
        metadata_set_arg(4,0x18,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x1c,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x20,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x24,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x28,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x2c,arg_kind_direct,arg_type_u32);
        metadata_set_arg(8,0x30,arg_kind_direct,arg_type_u64);
        metadata_set_arg(8,0x38,arg_kind_direct,arg_type_u64);
        metadata_set_arg(4,0x40,arg_kind_direct,arg_type_u32);
    }
    metadata_end();

    kernel.start_descr();
    {
        kernel.enable_kernarg_segment();
        kernel.set_fp32_mode_round(amdgpu_fp_mode_rn);
        kernel.set_fp32_mode_denorm(amdgpu_fp_denorm_fsd);
        kernel.set_fp16_fp64_mode_round(amdgpu_fp_mode_rn);
        kernel.set_fp16_fp64_mode_denorm(amdgpu_fp_denorm_fn);
        kernel.enable_dx10_clamp();
        kernel.enable_ieee_mode();
        kernel.set_user_sgprcnt(2);
        kernel.enable_sgpr_group_id_x();
        kernel.enable_sgpr_group_id_y();
        kernel.enable_vgpr_iterm_id_1d();
    }
    kernel.end_descr();

    s_lda_b256(s4,argptr,0x10);
    s_lda_b128(s12,argptr,0x30);
    v_and_b32(x,ic(15),v0);
    v_and_b32(u,ic(1),v0);
    v_shr_b32(y,v0,4);
    v_shr_b32(v,x,1);
    v_shl_or_b32(icell,gidx,4,y);
    s_movk_b32(s20,0xffff);
    s_shl_b32(s21,gidy,2);
    s_sync(lgkmcnt(0));
    //==================================================================
    //d_r+=gidy*ldy+imap*ldx+icell_y*ty*nx+icell_x*tx+x
    //==================================================================
    s_shr_b32(grid_y,grid,16);
    s_shr_b32(tile_y,tile,16);
    s_and_b32(grid_x,grid,s20);
    s_and_b32(tile_x,tile,s20);
    CALC_SPLIT_IDX(imap,icell_y,icell,grid_x,xmagic,ymagic,s10);
    s_mul_i32(s10,tile_y,nx);
    v_mul_lo_u32(v21,ldx,imap);
    v_mad_u24(v23,tile_x,icell_x,x);
    v_mad_u24(v27,s10,icell_y,v21);
    v_add_shl_u32(rvo,v23,v27,2);
    S_MUL_U64_U32(s8,s21,ldy);
    S_ADD_U64(rbase,rbase,s8);
    //==================================================================
    FFT16x16_R2C_LDR_SPLIT(c,rbase,rvo,x,icell,ncells,nx);
    FFT16x16_R2C_CALC_LDS_PTRS(xsst,xsld,ysst,osst,osld,x,y,u,v,s7);
    FFT16x16_SET_RF();
    FFT16x16_SET_SCOEF();
    s_sync(vmcnt(0));
    VFFT16(c,xsst,xsld);
    HFFT16(c,ysst,ysld,u,s4,);
    //==================================================================
    //d_c+=gidy*ldc+(gidx<<4)+y*bks+x
    //==================================================================
    v_shl_or_b32(v20,gidx,4,x);
    s_shl_b32(s4,gidx,7);
    s_shl_b32(s5,gidy,3);
    s_lda_b128(cbase,argptr,0x0);
    s_movk_i32(s9,0);
    s_sync(lgkmcnt(0));
    v_mul_lo_u32(v19,bks,y);
    s_mul_i32(s7,ldc,s5);
    s_mov_b32(s8,bks);
    s_add_u32(s2,s7,s4);
    s_shl_b64(s18,s8,7);
    S_ADD_U64_U32(cbase,cbase,s2);
    v_add_shl_u32(cvo,v19,x,3);
    v_cmp_u32(ncells,v20,gt);
    FFT16x16_R2C_PERMST(cbase,cvo,s18,c,osst,osld,vcc);
}
