﻿#include"../../include/gfxcoder.h"
#include"../../include/fft/fft.h"

void gfxcoder::scgemm5x5()
{
    uint2 c[4][4], a[2][4], b[2][4];
    for( int i=0; i<32; ++i ){ ((uint32_t*)&c[0][0].x)[i]=v0+i; }
    a[0][0].x=v32; a[0][0].y=v33;
    a[0][1].x=v34; a[0][1].y=v35;
    a[0][2].x=v36; a[0][2].y=v37;
    a[0][3].x=v38; a[0][3].y=v39;
    b[0][0].x=v40; b[0][0].y=v41;
    b[0][1].x=v42; b[0][1].y=v43;
    b[0][2].x=v44; b[0][2].y=v45;
    b[0][3].x=v46; b[0][3].y=v47;
    a[1][0].x=v48; a[1][0].y=v49;
    a[1][1].x=v50; a[1][1].y=v51;
    a[1][2].x=v52; a[1][2].y=v53;
    a[1][3].x=v54; a[1][3].y=v55;
    b[1][0].x=v56; b[1][0].y=v57;
    b[1][1].x=v58; b[1][1].y=v59;
    b[1][2].x=v60; b[1][2].y=v61;
    b[1][3].x=v62; b[1][3].y=v63;

    const uint32_t argptr =s0 ;
    const uint32_t gidx   =s2 ;
    const uint32_t gidy   =s3 ;
    const uint32_t gidz   =s15;
    const uint32_t abase  =s4 ;
    const uint32_t bbase  =s6 ;
    const uint32_t lda    =s8 ;
    const uint32_t ldb    =s9 ;
    const uint32_t m      =s10;
    const uint32_t n      =s11;
    const uint32_t k      =s12;
    const uint32_t abks   =s13;
    const uint32_t bbks   =s14;
    const uint32_t col    =s13;
    const uint32_t dbtr   =s8 ;
    const uint32_t elda   =s2 ;
    const uint32_t eldb   =s3 ;
    const uint32_t cbase  =s0 ;
    const uint32_t ldc    =s2 ;
    const uint32_t cbks   =s3 ;
    const uint32_t alpha  =s27;

    const uint32_t apld=v64;
    const uint32_t bpld=v72;
    const uint32_t ao  =v80;
    const uint32_t bo  =v82;
    const uint32_t sst =v84;
    const uint32_t asld=v85;
    const uint32_t bsld=v86;
    const uint32_t csst=v87;
    const uint32_t csld=v88;
    const uint32_t tidx=v89;

    metadata_start();
    {
        metadata_set_lds_size(0x2000);
        metadata_set_kernarg_align(5);
        metadata_set_kernarg_size(64);
        metadata_set_group_size(64);
        metadata_set_sgprcnt(32);
        metadata_set_vgprcnt(90);
        metadata_set_arg(8,0x00,arg_kind_globuf,arg_type_f32);
        metadata_set_arg(4,0x08,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x0c,arg_kind_direct,arg_type_u32);
        metadata_set_arg(8,0x10,arg_kind_globuf,arg_type_f32);
        metadata_set_arg(8,0x18,arg_kind_globuf,arg_type_f32);
        metadata_set_arg(4,0x20,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x24,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x28,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x2c,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x30,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x34,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x38,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x3c,arg_kind_direct,arg_type_f32);
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
        kernel.enable_sgpr_group_id_z();
        kernel.enable_vgpr_iterm_id_1d();
    }
    kernel.end_descr();
    
    s_shl_b32(gidz,s4,3);
    s_lda_b256(s4,argptr,0x10);
    s_lda_b64(s12,argptr,0x30);
    s_lda_b32(s14,argptr,0x38);
    v_and_b32(v1,ic(15),v0);
    v_shr_b32(v2,v0,4);
    v_shl_or_b32(tidx,gidx,6,v0);
    v_shl_or_b32(v3,gidx,4,v1);
    v_shl_or_b32(v4,gidy,4,v1);
    s_sync(lgkmcnt(0));

    //abase+=gidz*abks
    //bbase+=gidz*bbks
    //x=v3<amax?v3:0
    //y=v4<bmax?v4:0
    //ao=v2*lda+x*16
    //bo=v2*ldb+y*16
    S_MUL_U64_U32(s16,abks,gidz);
    S_MUL_U64_U32(s18,bbks,gidz);
    s_shl_b32(lda,lda,3);
    s_shl_b32(ldb,ldb,3);
    S_ADD_U64(abase,abase,s16);
    S_ADD_U64(bbase,bbase,s18);
    s_add_u32(s16,ic(1),m);
    s_add_u32(s17,ic(1),n);
    s_shr_b32(s16,s16,1);
    s_shr_b32(s17,s17,1);
    v_cmp_u32(s16,v3,gt);
    v_cmov_b32(v3,zero,v3);
    v_cmp_u32(s17,v4,gt);
    v_cmov_b32(v4,zero,v4);
    v_mul_lo_u32(v5,lda,v2);
    v_mul_lo_u32(v6,ldb,v2);
    v_shl_add_u32(ao,v3,4,v5);
    v_shl_add_u32(bo,v4,4,v6);
    v_shl_add_u32(ao+1,lda,2,ao);
    v_shl_add_u32(bo+1,ldb,2,bo);
    ldg_b128(apld+0,abase,ao+0,0);
    ldg_b128(apld+4,abase,ao+1,0);
    ldg_b128(bpld+0,bbase,bo+0,0);
    ldg_b128(bpld+4,bbase,bo+1,0);

    //sst =v0<<4
    //asld=v1<<4
    //bsld=v2<<4
    //csld=v0<<2
    //csst=(v2<<8)|asld
    //col=gidy<<5
    v_and_b32(v1,ic(7),v0);
    v_shr_b32(v2,v0,3);
    v_shl_b32(sst,v0,4);
    v_shl_b32(csld,v0,2);
    v_shl_b32(asld,v1,4);
    v_shl_b32(bsld,v2,4);
    s_shl_b32(col,gidy,5);
    v_shl_or_b32(csst,v2,8,asld);
    
    VZERO32(c[0][0].x);
    s_sync(vmcnt(0));
    lsst_b128(sst,0x0000,apld+0);
    lsst_b128(sst,0x0400,apld+4);
    lsst_b128(sst,0x0800,bpld+0);
    lsst_b128(sst,0x0c00,bpld+4);
    s_sub_u32(k,k,ic(8));
    s_shl_b32(elda,lda,3);
    s_shl_b32(eldb,ldb,3);
    s_movk_i32(dbtr,0x1000);
    s_cmpk_u32(k,0,eq);
    s_cmovk_i32(elda,0);
    s_cmovk_i32(eldb,0);
    S_ADD_U64_U32(abase,abase,elda);
    S_ADD_U64_U32(bbase,bbase,eldb);
    if((kernel.icode&1)==0){ s_nop(); }
    s_sync(lgkmcnt(0));
    lsld_b128(a[0][0].x,asld,0x0000);
    lsld_b128(a[0][2].x,asld,0x0080);
    lsld_b128(b[0][0].x,bsld,0x0800);
    lsld_b128(b[0][2].x,bsld,0x0880);

__lable__(0);
    lsld_b128(a[1][0].x,asld,0x0100);
    lsld_b128(a[1][2].x,asld,0x0180);
    lsld_b128(b[1][0].x,bsld,0x0900);
    lsld_b128(b[1][2].x,bsld,0x0980);
    v_xor_b32(sst,dbtr,sst);
    s_sync(lgkmcnt(4));
    V_MAC_F32(c[0][0].x,a[0][0].x,b[0][0].x);
    s_setprio(1);
    V_MAC_F32(c[0][0].y,a[0][0].x,b[0][0].y);
    V_MAC_F32(c[0][1].x,a[0][1].x,b[0][0].x);
    V_MAC_F32(c[0][1].y,a[0][1].x,b[0][0].y);
    V_MAC_F32(c[0][2].x,a[0][2].x,b[0][0].x);
    V_MAC_F32(c[0][2].y,a[0][2].x,b[0][0].y);
    V_MAC_F32(c[0][3].x,a[0][3].x,b[0][0].x);
    V_MAC_F32(c[0][3].y,a[0][3].x,b[0][0].y);
    V_MAC_F32(c[1][0].x,a[0][0].x,b[0][1].x);
    V_MAC_F32(c[1][0].y,a[0][0].x,b[0][1].y);
    V_MAC_F32(c[1][1].x,a[0][1].x,b[0][1].x);
    V_MAC_F32(c[1][1].y,a[0][1].x,b[0][1].y);
    V_MAC_F32(c[1][2].x,a[0][2].x,b[0][1].x);
    V_MAC_F32(c[1][2].y,a[0][2].x,b[0][1].y);
    V_MAC_F32(c[1][3].x,a[0][3].x,b[0][1].x);
    V_MAC_F32(c[1][3].y,a[0][3].x,b[0][1].y);
    V_MAC_F32(c[2][0].x,a[0][0].x,b[0][2].x);
    V_MAC_F32(c[2][0].y,a[0][0].x,b[0][2].y);
    V_MAC_F32(c[2][1].x,a[0][1].x,b[0][2].x);
    V_MAC_F32(c[2][1].y,a[0][1].x,b[0][2].y);
    V_MAC_F32(c[2][2].x,a[0][2].x,b[0][2].x);
    V_MAC_F32(c[2][2].y,a[0][2].x,b[0][2].y);
    V_MAC_F32(c[2][3].x,a[0][3].x,b[0][2].x);
    V_MAC_F32(c[2][3].y,a[0][3].x,b[0][2].y);
    ldg_b128(apld+0,abase,ao+0,0);
    ldg_b128(apld+4,abase,ao+1,0);
    ldg_b128(bpld+0,bbase,bo+0,0);
    ldg_b128(bpld+4,bbase,bo+1,0);
    V_MAC_F32(c[3][0].x,a[0][0].x,b[0][3].x);
    V_MAC_F32(c[3][0].y,a[0][0].x,b[0][3].y);
    V_MAC_F32(c[3][1].x,a[0][1].x,b[0][3].x);
    V_MAC_F32(c[3][1].y,a[0][1].x,b[0][3].y);
    V_MAC_F32(c[3][2].x,a[0][2].x,b[0][3].x);
    V_MAC_F32(c[3][2].y,a[0][2].x,b[0][3].y);
    V_MAC_F32(c[3][3].x,a[0][3].x,b[0][3].x);
    V_MAC_F32(c[3][3].y,a[0][3].x,b[0][3].y);
    V_MAC_F32(c[0][0].x,a[0][0].y,b[0][0].y);
    V_MAC_F32(c[0][1].x,a[0][1].y,b[0][0].y);
    V_MAC_F32(c[0][2].x,a[0][2].y,b[0][0].y);
    V_MAC_F32(c[0][3].x,a[0][3].y,b[0][0].y);
    V_MAC_F32(c[1][0].x,a[0][0].y,b[0][1].y);
    V_MAC_F32(c[1][1].x,a[0][1].y,b[0][1].y);
    V_MAC_F32(c[1][2].x,a[0][2].y,b[0][1].y);
    V_MAC_F32(c[1][3].x,a[0][3].y,b[0][1].y);
    V_MAC_F32(c[2][0].x,a[0][0].y,b[0][2].y);
    V_MAC_F32(c[2][1].x,a[0][1].y,b[0][2].y);
    V_MAC_F32(c[2][2].x,a[0][2].y,b[0][2].y);
    V_MAC_F32(c[2][3].x,a[0][3].y,b[0][2].y);
    V_MAC_F32(c[3][0].x,a[0][0].y,b[0][3].y);
    V_MAC_F32(c[3][1].x,a[0][1].y,b[0][3].y);
    V_MAC_F32(c[3][2].x,a[0][2].y,b[0][3].y);
    V_MAC_F32(c[3][3].x,a[0][3].y,b[0][3].y);
    V_MAC_F32(c[0][0].y,a[0][0].y,neg(b[0][0].x));
    V_MAC_F32(c[0][1].y,a[0][1].y,neg(b[0][0].x));
    V_MAC_F32(c[0][2].y,a[0][2].y,neg(b[0][0].x));
    V_MAC_F32(c[0][3].y,a[0][3].y,neg(b[0][0].x));
    V_MAC_F32(c[1][0].y,a[0][0].y,neg(b[0][1].x));
    V_MAC_F32(c[1][1].y,a[0][1].y,neg(b[0][1].x));
    V_MAC_F32(c[1][2].y,a[0][2].y,neg(b[0][1].x));
    V_MAC_F32(c[1][3].y,a[0][3].y,neg(b[0][1].x));
    V_MAC_F32(c[2][0].y,a[0][0].y,neg(b[0][2].x));
    V_MAC_F32(c[2][1].y,a[0][1].y,neg(b[0][2].x));
    V_MAC_F32(c[2][2].y,a[0][2].y,neg(b[0][2].x));
    V_MAC_F32(c[2][3].y,a[0][3].y,neg(b[0][2].x));
    V_MAC_F32(c[3][0].y,a[0][0].y,neg(b[0][3].x));
    V_MAC_F32(c[3][1].y,a[0][1].y,neg(b[0][3].x));
    V_MAC_F32(c[3][2].y,a[0][2].y,neg(b[0][3].x));
    V_MAC_F32(c[3][3].y,a[0][3].y,neg(b[0][3].x));
    s_setprio(0);

    lsld_b128(a[0][0].x,asld,0x0200);
    lsld_b128(a[0][2].x,asld,0x0280);
    lsld_b128(b[0][0].x,bsld,0x0a00);
    lsld_b128(b[0][2].x,bsld,0x0a80);
    s_sync(lgkmcnt(4));
    V_MAC_F32(c[0][0].x,a[1][0].x,b[1][0].x);
    s_setprio(1);
    V_MAC_F32(c[0][0].y,a[1][0].x,b[1][0].y);
    V_MAC_F32(c[0][1].x,a[1][1].x,b[1][0].x);
    V_MAC_F32(c[0][1].y,a[1][1].x,b[1][0].y);
    V_MAC_F32(c[0][2].x,a[1][2].x,b[1][0].x);
    V_MAC_F32(c[0][2].y,a[1][2].x,b[1][0].y);
    V_MAC_F32(c[0][3].x,a[1][3].x,b[1][0].x);
    V_MAC_F32(c[0][3].y,a[1][3].x,b[1][0].y);
    V_MAC_F32(c[1][0].x,a[1][0].x,b[1][1].x);
    V_MAC_F32(c[1][0].y,a[1][0].x,b[1][1].y);
    V_MAC_F32(c[1][1].x,a[1][1].x,b[1][1].x);
    V_MAC_F32(c[1][1].y,a[1][1].x,b[1][1].y);
    V_MAC_F32(c[1][2].x,a[1][2].x,b[1][1].x);
    V_MAC_F32(c[1][2].y,a[1][2].x,b[1][1].y);
    V_MAC_F32(c[1][3].x,a[1][3].x,b[1][1].x);
    V_MAC_F32(c[1][3].y,a[1][3].x,b[1][1].y);
    V_MAC_F32(c[2][0].x,a[1][0].x,b[1][2].x);
    V_MAC_F32(c[2][0].y,a[1][0].x,b[1][2].y);
    V_MAC_F32(c[2][1].x,a[1][1].x,b[1][2].x);
    V_MAC_F32(c[2][1].y,a[1][1].x,b[1][2].y);
    V_MAC_F32(c[2][2].x,a[1][2].x,b[1][2].x);
    V_MAC_F32(c[2][2].y,a[1][2].x,b[1][2].y);
    V_MAC_F32(c[2][3].x,a[1][3].x,b[1][2].x);
    V_MAC_F32(c[2][3].y,a[1][3].x,b[1][2].y);
    V_MAC_F32(c[3][0].x,a[1][0].x,b[1][3].x);
    V_MAC_F32(c[3][0].y,a[1][0].x,b[1][3].y);
    V_MAC_F32(c[3][1].x,a[1][1].x,b[1][3].x);
    V_MAC_F32(c[3][1].y,a[1][1].x,b[1][3].y);
    V_MAC_F32(c[3][2].x,a[1][2].x,b[1][3].x);
    V_MAC_F32(c[3][2].y,a[1][2].x,b[1][3].y);
    V_MAC_F32(c[3][3].x,a[1][3].x,b[1][3].x);
    V_MAC_F32(c[3][3].y,a[1][3].x,b[1][3].y);
    V_MAC_F32(c[0][0].x,a[1][0].y,b[1][0].y);
    V_MAC_F32(c[0][1].x,a[1][1].y,b[1][0].y);
    V_MAC_F32(c[0][2].x,a[1][2].y,b[1][0].y);
    V_MAC_F32(c[0][3].x,a[1][3].y,b[1][0].y);
    V_MAC_F32(c[1][0].x,a[1][0].y,b[1][1].y);
    V_MAC_F32(c[1][1].x,a[1][1].y,b[1][1].y);
    V_MAC_F32(c[1][2].x,a[1][2].y,b[1][1].y);
    V_MAC_F32(c[1][3].x,a[1][3].y,b[1][1].y);
    V_MAC_F32(c[2][0].x,a[1][0].y,b[1][2].y);
    V_MAC_F32(c[2][1].x,a[1][1].y,b[1][2].y);
    V_MAC_F32(c[2][2].x,a[1][2].y,b[1][2].y);
    V_MAC_F32(c[2][3].x,a[1][3].y,b[1][2].y);
    V_MAC_F32(c[3][0].x,a[1][0].y,b[1][3].y);
    V_MAC_F32(c[3][1].x,a[1][1].y,b[1][3].y);
    V_MAC_F32(c[3][2].x,a[1][2].y,b[1][3].y);
    V_MAC_F32(c[3][3].x,a[1][3].y,b[1][3].y);
    V_MAC_F32(c[0][0].y,a[1][0].y,neg(b[1][0].x));
    V_MAC_F32(c[0][1].y,a[1][1].y,neg(b[1][0].x));
    V_MAC_F32(c[0][2].y,a[1][2].y,neg(b[1][0].x));
    V_MAC_F32(c[0][3].y,a[1][3].y,neg(b[1][0].x));
    V_MAC_F32(c[1][0].y,a[1][0].y,neg(b[1][1].x));
    V_MAC_F32(c[1][1].y,a[1][1].y,neg(b[1][1].x));
    V_MAC_F32(c[1][2].y,a[1][2].y,neg(b[1][1].x));
    V_MAC_F32(c[1][3].y,a[1][3].y,neg(b[1][1].x));
    V_MAC_F32(c[2][0].y,a[1][0].y,neg(b[1][2].x));
    V_MAC_F32(c[2][1].y,a[1][1].y,neg(b[1][2].x));
    V_MAC_F32(c[2][2].y,a[1][2].y,neg(b[1][2].x));
    V_MAC_F32(c[2][3].y,a[1][3].y,neg(b[1][2].x));
    V_MAC_F32(c[3][0].y,a[1][0].y,neg(b[1][3].x));
    V_MAC_F32(c[3][1].y,a[1][1].y,neg(b[1][3].x));
    V_MAC_F32(c[3][2].y,a[1][2].y,neg(b[1][3].x));
    V_MAC_F32(c[3][3].y,a[1][3].y,neg(b[1][3].x));
    s_setprio(0);
    s_cmpk_u32(k,8,eq);

    lsld_b128(a[1][0].x,asld,0x0300);
    lsld_b128(a[1][2].x,asld,0x0380);
    lsld_b128(b[1][0].x,bsld,0x0b00);
    lsld_b128(b[1][2].x,bsld,0x0b80);
    s_sync(lgkmcnt(4));
    V_MAC_F32(c[0][0].x,a[0][0].x,b[0][0].x);
    s_setprio(1);
    V_MAC_F32(c[0][0].y,a[0][0].x,b[0][0].y);
    V_MAC_F32(c[0][1].x,a[0][1].x,b[0][0].x);
    V_MAC_F32(c[0][1].y,a[0][1].x,b[0][0].y);
    V_MAC_F32(c[0][2].x,a[0][2].x,b[0][0].x);
    V_MAC_F32(c[0][2].y,a[0][2].x,b[0][0].y);
    V_MAC_F32(c[0][3].x,a[0][3].x,b[0][0].x);
    V_MAC_F32(c[0][3].y,a[0][3].x,b[0][0].y);
    V_MAC_F32(c[1][0].x,a[0][0].x,b[0][1].x);
    V_MAC_F32(c[1][0].y,a[0][0].x,b[0][1].y);
    V_MAC_F32(c[1][1].x,a[0][1].x,b[0][1].x);
    V_MAC_F32(c[1][1].y,a[0][1].x,b[0][1].y);
    V_MAC_F32(c[1][2].x,a[0][2].x,b[0][1].x);
    V_MAC_F32(c[1][2].y,a[0][2].x,b[0][1].y);
    V_MAC_F32(c[1][3].x,a[0][3].x,b[0][1].x);
    V_MAC_F32(c[1][3].y,a[0][3].x,b[0][1].y);
    V_MAC_F32(c[2][0].x,a[0][0].x,b[0][2].x);
    V_MAC_F32(c[2][0].y,a[0][0].x,b[0][2].y);
    V_MAC_F32(c[2][1].x,a[0][1].x,b[0][2].x);
    V_MAC_F32(c[2][1].y,a[0][1].x,b[0][2].y);
    V_MAC_F32(c[2][2].x,a[0][2].x,b[0][2].x);
    V_MAC_F32(c[2][2].y,a[0][2].x,b[0][2].y);
    V_MAC_F32(c[2][3].x,a[0][3].x,b[0][2].x);
    V_MAC_F32(c[2][3].y,a[0][3].x,b[0][2].y);
    V_MAC_F32(c[3][0].x,a[0][0].x,b[0][3].x);
    V_MAC_F32(c[3][0].y,a[0][0].x,b[0][3].y);
    V_MAC_F32(c[3][1].x,a[0][1].x,b[0][3].x);
    V_MAC_F32(c[3][1].y,a[0][1].x,b[0][3].y);
    V_MAC_F32(c[3][2].x,a[0][2].x,b[0][3].x);
    V_MAC_F32(c[3][2].y,a[0][2].x,b[0][3].y);
    V_MAC_F32(c[3][3].x,a[0][3].x,b[0][3].x);
    V_MAC_F32(c[3][3].y,a[0][3].x,b[0][3].y);
    V_MAC_F32(c[0][0].x,a[0][0].y,b[0][0].y);
    V_MAC_F32(c[0][1].x,a[0][1].y,b[0][0].y);
    V_MAC_F32(c[0][2].x,a[0][2].y,b[0][0].y);
    V_MAC_F32(c[0][3].x,a[0][3].y,b[0][0].y);
    V_MAC_F32(c[1][0].x,a[0][0].y,b[0][1].y);
    V_MAC_F32(c[1][1].x,a[0][1].y,b[0][1].y);
    V_MAC_F32(c[1][2].x,a[0][2].y,b[0][1].y);
    V_MAC_F32(c[1][3].x,a[0][3].y,b[0][1].y);
    V_MAC_F32(c[2][0].x,a[0][0].y,b[0][2].y);
    V_MAC_F32(c[2][1].x,a[0][1].y,b[0][2].y);
    V_MAC_F32(c[2][2].x,a[0][2].y,b[0][2].y);
    V_MAC_F32(c[2][3].x,a[0][3].y,b[0][2].y);
    V_MAC_F32(c[3][0].x,a[0][0].y,b[0][3].y);
    V_MAC_F32(c[3][1].x,a[0][1].y,b[0][3].y);
    V_MAC_F32(c[3][2].x,a[0][2].y,b[0][3].y);
    V_MAC_F32(c[3][3].x,a[0][3].y,b[0][3].y);
    V_MAC_F32(c[0][0].y,a[0][0].y,neg(b[0][0].x));
    V_MAC_F32(c[0][1].y,a[0][1].y,neg(b[0][0].x));
    V_MAC_F32(c[0][2].y,a[0][2].y,neg(b[0][0].x));
    V_MAC_F32(c[0][3].y,a[0][3].y,neg(b[0][0].x));
    V_MAC_F32(c[1][0].y,a[0][0].y,neg(b[0][1].x));
    V_MAC_F32(c[1][1].y,a[0][1].y,neg(b[0][1].x));
    V_MAC_F32(c[1][2].y,a[0][2].y,neg(b[0][1].x));
    V_MAC_F32(c[1][3].y,a[0][3].y,neg(b[0][1].x));
    V_MAC_F32(c[2][0].y,a[0][0].y,neg(b[0][2].x));
    V_MAC_F32(c[2][1].y,a[0][1].y,neg(b[0][2].x));
    V_MAC_F32(c[2][2].y,a[0][2].y,neg(b[0][2].x));
    V_MAC_F32(c[2][3].y,a[0][3].y,neg(b[0][2].x));
    V_MAC_F32(c[3][0].y,a[0][0].y,neg(b[0][3].x));
    V_MAC_F32(c[3][1].y,a[0][1].y,neg(b[0][3].x));
    V_MAC_F32(c[3][2].y,a[0][2].y,neg(b[0][3].x));
    V_MAC_F32(c[3][3].y,a[0][3].y,neg(b[0][3].x));
    s_setprio(0);
    s_cmovk_i32(elda,0);

    lsld_b128(a[0][0].x,asld,0x0400);
    lsld_b128(a[0][2].x,asld,0x0480);
    lsld_b128(b[0][0].x,bsld,0x0c00);
    lsld_b128(b[0][2].x,bsld,0x0c80);
    s_sync(lgkmcnt(4));
    V_MAC_F32(c[0][0].x,a[1][0].x,b[1][0].x);
    s_setprio(1);
    V_MAC_F32(c[0][0].y,a[1][0].x,b[1][0].y);
    V_MAC_F32(c[0][1].x,a[1][1].x,b[1][0].x);
    V_MAC_F32(c[0][1].y,a[1][1].x,b[1][0].y);
    V_MAC_F32(c[0][2].x,a[1][2].x,b[1][0].x);
    V_MAC_F32(c[0][2].y,a[1][2].x,b[1][0].y);
    V_MAC_F32(c[0][3].x,a[1][3].x,b[1][0].x);
    V_MAC_F32(c[0][3].y,a[1][3].x,b[1][0].y);
    V_MAC_F32(c[1][0].x,a[1][0].x,b[1][1].x);
    V_MAC_F32(c[1][0].y,a[1][0].x,b[1][1].y);
    V_MAC_F32(c[1][1].x,a[1][1].x,b[1][1].x);
    V_MAC_F32(c[1][1].y,a[1][1].x,b[1][1].y);
    V_MAC_F32(c[1][2].x,a[1][2].x,b[1][1].x);
    V_MAC_F32(c[1][2].y,a[1][2].x,b[1][1].y);
    V_MAC_F32(c[1][3].x,a[1][3].x,b[1][1].x);
    V_MAC_F32(c[1][3].y,a[1][3].x,b[1][1].y);
    V_MAC_F32(c[2][0].x,a[1][0].x,b[1][2].x);
    V_MAC_F32(c[2][0].y,a[1][0].x,b[1][2].y);
    V_MAC_F32(c[2][1].x,a[1][1].x,b[1][2].x);
    V_MAC_F32(c[2][1].y,a[1][1].x,b[1][2].y);
    V_MAC_F32(c[2][2].x,a[1][2].x,b[1][2].x);
    V_MAC_F32(c[2][2].y,a[1][2].x,b[1][2].y);
    V_MAC_F32(c[2][3].x,a[1][3].x,b[1][2].x);
    V_MAC_F32(c[2][3].y,a[1][3].x,b[1][2].y);
    V_MAC_F32(c[3][0].x,a[1][0].x,b[1][3].x);
    V_MAC_F32(c[3][0].y,a[1][0].x,b[1][3].y);
    V_MAC_F32(c[3][1].x,a[1][1].x,b[1][3].x);
    V_MAC_F32(c[3][1].y,a[1][1].x,b[1][3].y);
    V_MAC_F32(c[3][2].x,a[1][2].x,b[1][3].x);
    V_MAC_F32(c[3][2].y,a[1][2].x,b[1][3].y);
    V_MAC_F32(c[3][3].x,a[1][3].x,b[1][3].x);
    V_MAC_F32(c[3][3].y,a[1][3].x,b[1][3].y);
    V_MAC_F32(c[0][0].x,a[1][0].y,b[1][0].y);
    V_MAC_F32(c[0][1].x,a[1][1].y,b[1][0].y);
    V_MAC_F32(c[0][2].x,a[1][2].y,b[1][0].y);
    V_MAC_F32(c[0][3].x,a[1][3].y,b[1][0].y);
    V_MAC_F32(c[1][0].x,a[1][0].y,b[1][1].y);
    V_MAC_F32(c[1][1].x,a[1][1].y,b[1][1].y);
    V_MAC_F32(c[1][2].x,a[1][2].y,b[1][1].y);
    V_MAC_F32(c[1][3].x,a[1][3].y,b[1][1].y);
    V_MAC_F32(c[2][0].x,a[1][0].y,b[1][2].y);
    V_MAC_F32(c[2][1].x,a[1][1].y,b[1][2].y);
    V_MAC_F32(c[2][2].x,a[1][2].y,b[1][2].y);
    V_MAC_F32(c[2][3].x,a[1][3].y,b[1][2].y);
    V_MAC_F32(c[3][0].x,a[1][0].y,b[1][3].y);
    V_MAC_F32(c[3][1].x,a[1][1].y,b[1][3].y);
    V_MAC_F32(c[3][2].x,a[1][2].y,b[1][3].y);
    V_MAC_F32(c[3][3].x,a[1][3].y,b[1][3].y);
    V_MAC_F32(c[0][0].y,a[1][0].y,neg(b[1][0].x));
    V_MAC_F32(c[0][1].y,a[1][1].y,neg(b[1][0].x));
    V_MAC_F32(c[0][2].y,a[1][2].y,neg(b[1][0].x));
    V_MAC_F32(c[0][3].y,a[1][3].y,neg(b[1][0].x));
    V_MAC_F32(c[1][0].y,a[1][0].y,neg(b[1][1].x));
    V_MAC_F32(c[1][1].y,a[1][1].y,neg(b[1][1].x));
    V_MAC_F32(c[1][2].y,a[1][2].y,neg(b[1][1].x));
    V_MAC_F32(c[1][3].y,a[1][3].y,neg(b[1][1].x));
    V_MAC_F32(c[2][0].y,a[1][0].y,neg(b[1][2].x));
    V_MAC_F32(c[2][1].y,a[1][1].y,neg(b[1][2].x));
    V_MAC_F32(c[2][2].y,a[1][2].y,neg(b[1][2].x));
    V_MAC_F32(c[2][3].y,a[1][3].y,neg(b[1][2].x));
    V_MAC_F32(c[3][0].y,a[1][0].y,neg(b[1][3].x));
    V_MAC_F32(c[3][1].y,a[1][1].y,neg(b[1][3].x));
    V_MAC_F32(c[3][2].y,a[1][2].y,neg(b[1][3].x));
    V_MAC_F32(c[3][3].y,a[1][3].y,neg(b[1][3].x));
    s_setprio(0);
    s_cmovk_i32(eldb,0);

    lsld_b128(a[1][0].x,asld,0x0500);
    lsld_b128(a[1][2].x,asld,0x0580);
    lsld_b128(b[1][0].x,bsld,0x0d00);
    lsld_b128(b[1][2].x,bsld,0x0d80);
    s_sync(lgkmcnt(4));
    V_MAC_F32(c[0][0].x,a[0][0].x,b[0][0].x);
    s_setprio(1);
    V_MAC_F32(c[0][0].y,a[0][0].x,b[0][0].y);
    V_MAC_F32(c[0][1].x,a[0][1].x,b[0][0].x);
    V_MAC_F32(c[0][1].y,a[0][1].x,b[0][0].y);
    V_MAC_F32(c[0][2].x,a[0][2].x,b[0][0].x);
    V_MAC_F32(c[0][2].y,a[0][2].x,b[0][0].y);
    V_MAC_F32(c[0][3].x,a[0][3].x,b[0][0].x);
    V_MAC_F32(c[0][3].y,a[0][3].x,b[0][0].y);
    V_MAC_F32(c[1][0].x,a[0][0].x,b[0][1].x);
    V_MAC_F32(c[1][0].y,a[0][0].x,b[0][1].y);
    V_MAC_F32(c[1][1].x,a[0][1].x,b[0][1].x);
    V_MAC_F32(c[1][1].y,a[0][1].x,b[0][1].y);
    V_MAC_F32(c[1][2].x,a[0][2].x,b[0][1].x);
    V_MAC_F32(c[1][2].y,a[0][2].x,b[0][1].y);
    V_MAC_F32(c[1][3].x,a[0][3].x,b[0][1].x);
    V_MAC_F32(c[1][3].y,a[0][3].x,b[0][1].y);
    V_MAC_F32(c[2][0].x,a[0][0].x,b[0][2].x);
    V_MAC_F32(c[2][0].y,a[0][0].x,b[0][2].y);
    V_MAC_F32(c[2][1].x,a[0][1].x,b[0][2].x);
    V_MAC_F32(c[2][1].y,a[0][1].x,b[0][2].y);
    V_MAC_F32(c[2][2].x,a[0][2].x,b[0][2].x);
    V_MAC_F32(c[2][2].y,a[0][2].x,b[0][2].y);
    V_MAC_F32(c[2][3].x,a[0][3].x,b[0][2].x);
    V_MAC_F32(c[2][3].y,a[0][3].x,b[0][2].y);
    V_MAC_F32(c[3][0].x,a[0][0].x,b[0][3].x);
    V_MAC_F32(c[3][0].y,a[0][0].x,b[0][3].y);
    V_MAC_F32(c[3][1].x,a[0][1].x,b[0][3].x);
    V_MAC_F32(c[3][1].y,a[0][1].x,b[0][3].y);
    V_MAC_F32(c[3][2].x,a[0][2].x,b[0][3].x);
    V_MAC_F32(c[3][2].y,a[0][2].x,b[0][3].y);
    V_MAC_F32(c[3][3].x,a[0][3].x,b[0][3].x);
    V_MAC_F32(c[3][3].y,a[0][3].x,b[0][3].y);
    V_MAC_F32(c[0][0].x,a[0][0].y,b[0][0].y);
    V_MAC_F32(c[0][1].x,a[0][1].y,b[0][0].y);
    V_MAC_F32(c[0][2].x,a[0][2].y,b[0][0].y);
    V_MAC_F32(c[0][3].x,a[0][3].y,b[0][0].y);
    V_MAC_F32(c[1][0].x,a[0][0].y,b[0][1].y);
    V_MAC_F32(c[1][1].x,a[0][1].y,b[0][1].y);
    V_MAC_F32(c[1][2].x,a[0][2].y,b[0][1].y);
    V_MAC_F32(c[1][3].x,a[0][3].y,b[0][1].y);
    V_MAC_F32(c[2][0].x,a[0][0].y,b[0][2].y);
    V_MAC_F32(c[2][1].x,a[0][1].y,b[0][2].y);
    V_MAC_F32(c[2][2].x,a[0][2].y,b[0][2].y);
    V_MAC_F32(c[2][3].x,a[0][3].y,b[0][2].y);
    V_MAC_F32(c[3][0].x,a[0][0].y,b[0][3].y);
    V_MAC_F32(c[3][1].x,a[0][1].y,b[0][3].y);
    V_MAC_F32(c[3][2].x,a[0][2].y,b[0][3].y);
    V_MAC_F32(c[3][3].x,a[0][3].y,b[0][3].y);
    V_MAC_F32(c[0][0].y,a[0][0].y,neg(b[0][0].x));
    V_MAC_F32(c[0][1].y,a[0][1].y,neg(b[0][0].x));
    V_MAC_F32(c[0][2].y,a[0][2].y,neg(b[0][0].x));
    V_MAC_F32(c[0][3].y,a[0][3].y,neg(b[0][0].x));
    V_MAC_F32(c[1][0].y,a[0][0].y,neg(b[0][1].x));
    V_MAC_F32(c[1][1].y,a[0][1].y,neg(b[0][1].x));
    V_MAC_F32(c[1][2].y,a[0][2].y,neg(b[0][1].x));
    V_MAC_F32(c[1][3].y,a[0][3].y,neg(b[0][1].x));
    V_MAC_F32(c[2][0].y,a[0][0].y,neg(b[0][2].x));
    V_MAC_F32(c[2][1].y,a[0][1].y,neg(b[0][2].x));
    V_MAC_F32(c[2][2].y,a[0][2].y,neg(b[0][2].x));
    V_MAC_F32(c[2][3].y,a[0][3].y,neg(b[0][2].x));
    V_MAC_F32(c[3][0].y,a[0][0].y,neg(b[0][3].x));
    V_MAC_F32(c[3][1].y,a[0][1].y,neg(b[0][3].x));
    V_MAC_F32(c[3][2].y,a[0][2].y,neg(b[0][3].x));
    V_MAC_F32(c[3][3].y,a[0][3].y,neg(b[0][3].x));
    s_setprio(0);
    s_add_u32(abase,abase,elda);

    lsld_b128(a[0][0].x,asld,0x0600);
    lsld_b128(a[0][2].x,asld,0x0680);
    lsld_b128(b[0][0].x,bsld,0x0e00);
    lsld_b128(b[0][2].x,bsld,0x0e80);
    s_sync(lgkmcnt(4));
    V_MAC_F32(c[0][0].x,a[1][0].x,b[1][0].x);
    s_setprio(1);
    V_MAC_F32(c[0][0].y,a[1][0].x,b[1][0].y);
    V_MAC_F32(c[0][1].x,a[1][1].x,b[1][0].x);
    V_MAC_F32(c[0][1].y,a[1][1].x,b[1][0].y);
    V_MAC_F32(c[0][2].x,a[1][2].x,b[1][0].x);
    V_MAC_F32(c[0][2].y,a[1][2].x,b[1][0].y);
    V_MAC_F32(c[0][3].x,a[1][3].x,b[1][0].x);
    V_MAC_F32(c[0][3].y,a[1][3].x,b[1][0].y);
    V_MAC_F32(c[1][0].x,a[1][0].x,b[1][1].x);
    V_MAC_F32(c[1][0].y,a[1][0].x,b[1][1].y);
    V_MAC_F32(c[1][1].x,a[1][1].x,b[1][1].x);
    V_MAC_F32(c[1][1].y,a[1][1].x,b[1][1].y);
    V_MAC_F32(c[1][2].x,a[1][2].x,b[1][1].x);
    V_MAC_F32(c[1][2].y,a[1][2].x,b[1][1].y);
    V_MAC_F32(c[1][3].x,a[1][3].x,b[1][1].x);
    V_MAC_F32(c[1][3].y,a[1][3].x,b[1][1].y);
    V_MAC_F32(c[2][0].x,a[1][0].x,b[1][2].x);
    V_MAC_F32(c[2][0].y,a[1][0].x,b[1][2].y);
    V_MAC_F32(c[2][1].x,a[1][1].x,b[1][2].x);
    V_MAC_F32(c[2][1].y,a[1][1].x,b[1][2].y);
    V_MAC_F32(c[2][2].x,a[1][2].x,b[1][2].x);
    V_MAC_F32(c[2][2].y,a[1][2].x,b[1][2].y);
    V_MAC_F32(c[2][3].x,a[1][3].x,b[1][2].x);
    V_MAC_F32(c[2][3].y,a[1][3].x,b[1][2].y);
    V_MAC_F32(c[3][0].x,a[1][0].x,b[1][3].x);
    V_MAC_F32(c[3][0].y,a[1][0].x,b[1][3].y);
    V_MAC_F32(c[3][1].x,a[1][1].x,b[1][3].x);
    V_MAC_F32(c[3][1].y,a[1][1].x,b[1][3].y);
    V_MAC_F32(c[3][2].x,a[1][2].x,b[1][3].x);
    V_MAC_F32(c[3][2].y,a[1][2].x,b[1][3].y);
    V_MAC_F32(c[3][3].x,a[1][3].x,b[1][3].x);
    V_MAC_F32(c[3][3].y,a[1][3].x,b[1][3].y);
    V_MAC_F32(c[0][0].x,a[1][0].y,b[1][0].y);
    V_MAC_F32(c[0][1].x,a[1][1].y,b[1][0].y);
    V_MAC_F32(c[0][2].x,a[1][2].y,b[1][0].y);
    V_MAC_F32(c[0][3].x,a[1][3].y,b[1][0].y);
    V_MAC_F32(c[1][0].x,a[1][0].y,b[1][1].y);
    V_MAC_F32(c[1][1].x,a[1][1].y,b[1][1].y);
    V_MAC_F32(c[1][2].x,a[1][2].y,b[1][1].y);
    V_MAC_F32(c[1][3].x,a[1][3].y,b[1][1].y);
    V_MAC_F32(c[2][0].x,a[1][0].y,b[1][2].y);
    V_MAC_F32(c[2][1].x,a[1][1].y,b[1][2].y);
    V_MAC_F32(c[2][2].x,a[1][2].y,b[1][2].y);
    V_MAC_F32(c[2][3].x,a[1][3].y,b[1][2].y);
    V_MAC_F32(c[3][0].x,a[1][0].y,b[1][3].y);
    V_MAC_F32(c[3][1].x,a[1][1].y,b[1][3].y);
    V_MAC_F32(c[3][2].x,a[1][2].y,b[1][3].y);
    V_MAC_F32(c[3][3].x,a[1][3].y,b[1][3].y);
    V_MAC_F32(c[0][0].y,a[1][0].y,neg(b[1][0].x));
    V_MAC_F32(c[0][1].y,a[1][1].y,neg(b[1][0].x));
    V_MAC_F32(c[0][2].y,a[1][2].y,neg(b[1][0].x));
    V_MAC_F32(c[0][3].y,a[1][3].y,neg(b[1][0].x));
    V_MAC_F32(c[1][0].y,a[1][0].y,neg(b[1][1].x));
    V_MAC_F32(c[1][1].y,a[1][1].y,neg(b[1][1].x));
    V_MAC_F32(c[1][2].y,a[1][2].y,neg(b[1][1].x));
    V_MAC_F32(c[1][3].y,a[1][3].y,neg(b[1][1].x));
    V_MAC_F32(c[2][0].y,a[1][0].y,neg(b[1][2].x));
    V_MAC_F32(c[2][1].y,a[1][1].y,neg(b[1][2].x));
    V_MAC_F32(c[2][2].y,a[1][2].y,neg(b[1][2].x));
    V_MAC_F32(c[2][3].y,a[1][3].y,neg(b[1][2].x));
    V_MAC_F32(c[3][0].y,a[1][0].y,neg(b[1][3].x));
    V_MAC_F32(c[3][1].y,a[1][1].y,neg(b[1][3].x));
    V_MAC_F32(c[3][2].y,a[1][2].y,neg(b[1][3].x));
    V_MAC_F32(c[3][3].y,a[1][3].y,neg(b[1][3].x));
    s_setprio(0);
    s_addc_u32(abase+1,abase+1,zero);

    lsld_b128(a[1][0].x,asld,0x0700);
    lsld_b128(a[1][2].x,asld,0x0780);
    lsld_b128(b[1][0].x,bsld,0x0f00);
    lsld_b128(b[1][2].x,bsld,0x0f80);
    s_sync(lgkmcnt(5));
    V_MAC_F32(c[0][0].x,a[0][0].x,b[0][0].x);
    s_setprio(1);
    V_MAC_F32(c[0][0].y,a[0][0].x,b[0][0].y);
    V_MAC_F32(c[0][1].x,a[0][1].x,b[0][0].x);
    V_MAC_F32(c[0][1].y,a[0][1].x,b[0][0].y);
    V_MAC_F32(c[0][2].x,a[0][2].x,b[0][0].x);
    V_MAC_F32(c[0][2].y,a[0][2].x,b[0][0].y);
    V_MAC_F32(c[0][3].x,a[0][3].x,b[0][0].x);
    V_MAC_F32(c[0][3].y,a[0][3].x,b[0][0].y);
    V_MAC_F32(c[1][0].x,a[0][0].x,b[0][1].x);
    V_MAC_F32(c[1][0].y,a[0][0].x,b[0][1].y);
    V_MAC_F32(c[1][1].x,a[0][1].x,b[0][1].x);
    V_MAC_F32(c[1][1].y,a[0][1].x,b[0][1].y);
    V_MAC_F32(c[1][2].x,a[0][2].x,b[0][1].x);
    V_MAC_F32(c[1][2].y,a[0][2].x,b[0][1].y);
    V_MAC_F32(c[1][3].x,a[0][3].x,b[0][1].x);
    V_MAC_F32(c[1][3].y,a[0][3].x,b[0][1].y);
    V_MAC_F32(c[0][0].x,a[0][0].y,b[0][0].y);
    V_MAC_F32(c[0][1].x,a[0][1].y,b[0][0].y);
    V_MAC_F32(c[0][2].x,a[0][2].y,b[0][0].y);
    V_MAC_F32(c[0][3].x,a[0][3].y,b[0][0].y);
    V_MAC_F32(c[1][0].x,a[0][0].y,b[0][1].y);
    V_MAC_F32(c[1][1].x,a[0][1].y,b[0][1].y);
    V_MAC_F32(c[1][2].x,a[0][2].y,b[0][1].y);
    V_MAC_F32(c[1][3].x,a[0][3].y,b[0][1].y);
    V_MAC_F32(c[0][0].y,a[0][0].y,neg(b[0][0].x));
    V_MAC_F32(c[0][1].y,a[0][1].y,neg(b[0][0].x));
    V_MAC_F32(c[0][2].y,a[0][2].y,neg(b[0][0].x));
    V_MAC_F32(c[0][3].y,a[0][3].y,neg(b[0][0].x));
    V_MAC_F32(c[1][0].y,a[0][0].y,neg(b[0][1].x));
    V_MAC_F32(c[1][1].y,a[0][1].y,neg(b[0][1].x));
    V_MAC_F32(c[1][2].y,a[0][2].y,neg(b[0][1].x));
    V_MAC_F32(c[1][3].y,a[0][3].y,neg(b[0][1].x));
    s_setprio(0);
    S_ADD_U64_U32(bbase,bbase,eldb);
    s_sync(vmcnt(0)&lgkmcnt(4));
    lsst_b128(sst,0x0000,apld+0);
    lsst_b128(sst,0x0400,apld+4);
    lsst_b128(sst,0x0800,bpld+0);
    lsst_b128(sst,0x0c00,bpld+4);
    v_xor_b32(asld,dbtr,asld);
    v_xor_b32(bsld,dbtr,bsld);
    V_MAC_F32(c[2][0].x,a[0][0].x,b[0][2].x);
    s_setprio(1);
    V_MAC_F32(c[2][0].y,a[0][0].x,b[0][2].y);
    V_MAC_F32(c[2][1].x,a[0][1].x,b[0][2].x);
    V_MAC_F32(c[2][1].y,a[0][1].x,b[0][2].y);
    V_MAC_F32(c[2][2].x,a[0][2].x,b[0][2].x);
    V_MAC_F32(c[2][2].y,a[0][2].x,b[0][2].y);
    V_MAC_F32(c[2][3].x,a[0][3].x,b[0][2].x);
    V_MAC_F32(c[2][3].y,a[0][3].x,b[0][2].y);
    V_MAC_F32(c[3][0].x,a[0][0].x,b[0][3].x);
    V_MAC_F32(c[3][0].y,a[0][0].x,b[0][3].y);
    V_MAC_F32(c[3][1].x,a[0][1].x,b[0][3].x);
    V_MAC_F32(c[3][1].y,a[0][1].x,b[0][3].y);
    V_MAC_F32(c[3][2].x,a[0][2].x,b[0][3].x);
    V_MAC_F32(c[3][2].y,a[0][2].x,b[0][3].y);
    V_MAC_F32(c[3][3].x,a[0][3].x,b[0][3].x);
    V_MAC_F32(c[3][3].y,a[0][3].x,b[0][3].y);
    V_MAC_F32(c[2][0].x,a[0][0].y,b[0][2].y);
    V_MAC_F32(c[2][1].x,a[0][1].y,b[0][2].y);
    V_MAC_F32(c[2][2].x,a[0][2].y,b[0][2].y);
    V_MAC_F32(c[2][3].x,a[0][3].y,b[0][2].y);
    V_MAC_F32(c[3][0].x,a[0][0].y,b[0][3].y);
    V_MAC_F32(c[3][1].x,a[0][1].y,b[0][3].y);
    V_MAC_F32(c[3][2].x,a[0][2].y,b[0][3].y);
    V_MAC_F32(c[3][3].x,a[0][3].y,b[0][3].y);
    V_MAC_F32(c[2][0].y,a[0][0].y,neg(b[0][2].x));
    V_MAC_F32(c[2][1].y,a[0][1].y,neg(b[0][2].x));
    V_MAC_F32(c[2][2].y,a[0][2].y,neg(b[0][2].x));
    V_MAC_F32(c[2][3].y,a[0][3].y,neg(b[0][2].x));
    V_MAC_F32(c[3][0].y,a[0][0].y,neg(b[0][3].x));
    V_MAC_F32(c[3][1].y,a[0][1].y,neg(b[0][3].x));
    V_MAC_F32(c[3][2].y,a[0][2].y,neg(b[0][3].x));
    V_MAC_F32(c[3][3].y,a[0][3].y,neg(b[0][3].x));
    s_setprio(0);
    s_sub_u32(k,k,ic(8));
    s_sync(lgkmcnt(0));

    lsld_b128(a[0][0].x,asld,0x0000);
    lsld_b128(a[0][2].x,asld,0x0080);
    lsld_b128(b[0][0].x,bsld,0x0800);
    lsld_b128(b[0][2].x,bsld,0x0880);
    V_MAC_F32(c[0][0].x,a[1][0].x,b[1][0].x);
    s_setprio(1);
    V_MAC_F32(c[0][0].y,a[1][0].x,b[1][0].y);
    V_MAC_F32(c[0][1].x,a[1][1].x,b[1][0].x);
    V_MAC_F32(c[0][1].y,a[1][1].x,b[1][0].y);
    V_MAC_F32(c[0][2].x,a[1][2].x,b[1][0].x);
    V_MAC_F32(c[0][2].y,a[1][2].x,b[1][0].y);
    V_MAC_F32(c[0][3].x,a[1][3].x,b[1][0].x);
    V_MAC_F32(c[0][3].y,a[1][3].x,b[1][0].y);
    V_MAC_F32(c[1][0].x,a[1][0].x,b[1][1].x);
    V_MAC_F32(c[1][0].y,a[1][0].x,b[1][1].y);
    V_MAC_F32(c[1][1].x,a[1][1].x,b[1][1].x);
    V_MAC_F32(c[1][1].y,a[1][1].x,b[1][1].y);
    V_MAC_F32(c[1][2].x,a[1][2].x,b[1][1].x);
    V_MAC_F32(c[1][2].y,a[1][2].x,b[1][1].y);
    V_MAC_F32(c[1][3].x,a[1][3].x,b[1][1].x);
    V_MAC_F32(c[1][3].y,a[1][3].x,b[1][1].y);
    V_MAC_F32(c[2][0].x,a[1][0].x,b[1][2].x);
    V_MAC_F32(c[2][0].y,a[1][0].x,b[1][2].y);
    V_MAC_F32(c[2][1].x,a[1][1].x,b[1][2].x);
    V_MAC_F32(c[2][1].y,a[1][1].x,b[1][2].y);
    V_MAC_F32(c[2][2].x,a[1][2].x,b[1][2].x);
    V_MAC_F32(c[2][2].y,a[1][2].x,b[1][2].y);
    V_MAC_F32(c[2][3].x,a[1][3].x,b[1][2].x);
    V_MAC_F32(c[2][3].y,a[1][3].x,b[1][2].y);
    V_MAC_F32(c[3][0].x,a[1][0].x,b[1][3].x);
    V_MAC_F32(c[3][0].y,a[1][0].x,b[1][3].y);
    V_MAC_F32(c[3][1].x,a[1][1].x,b[1][3].x);
    V_MAC_F32(c[3][1].y,a[1][1].x,b[1][3].y);
    V_MAC_F32(c[3][2].x,a[1][2].x,b[1][3].x);
    V_MAC_F32(c[3][2].y,a[1][2].x,b[1][3].y);
    V_MAC_F32(c[3][3].x,a[1][3].x,b[1][3].x);
    V_MAC_F32(c[3][3].y,a[1][3].x,b[1][3].y);
    V_MAC_F32(c[0][0].x,a[1][0].y,b[1][0].y);
    V_MAC_F32(c[0][1].x,a[1][1].y,b[1][0].y);
    V_MAC_F32(c[0][2].x,a[1][2].y,b[1][0].y);
    V_MAC_F32(c[0][3].x,a[1][3].y,b[1][0].y);
    V_MAC_F32(c[1][0].x,a[1][0].y,b[1][1].y);
    V_MAC_F32(c[1][1].x,a[1][1].y,b[1][1].y);
    V_MAC_F32(c[1][2].x,a[1][2].y,b[1][1].y);
    V_MAC_F32(c[1][3].x,a[1][3].y,b[1][1].y);
    V_MAC_F32(c[2][0].x,a[1][0].y,b[1][2].y);
    V_MAC_F32(c[2][1].x,a[1][1].y,b[1][2].y);
    V_MAC_F32(c[2][2].x,a[1][2].y,b[1][2].y);
    V_MAC_F32(c[2][3].x,a[1][3].y,b[1][2].y);
    V_MAC_F32(c[3][0].x,a[1][0].y,b[1][3].y);
    V_MAC_F32(c[3][1].x,a[1][1].y,b[1][3].y);
    V_MAC_F32(c[3][2].x,a[1][2].y,b[1][3].y);
    V_MAC_F32(c[3][3].x,a[1][3].y,b[1][3].y);
    V_MAC_F32(c[0][0].y,a[1][0].y,neg(b[1][0].x));
    V_MAC_F32(c[0][1].y,a[1][1].y,neg(b[1][0].x));
    V_MAC_F32(c[0][2].y,a[1][2].y,neg(b[1][0].x));
    V_MAC_F32(c[0][3].y,a[1][3].y,neg(b[1][0].x));
    V_MAC_F32(c[1][0].y,a[1][0].y,neg(b[1][1].x));
    V_MAC_F32(c[1][1].y,a[1][1].y,neg(b[1][1].x));
    V_MAC_F32(c[1][2].y,a[1][2].y,neg(b[1][1].x));
    V_MAC_F32(c[1][3].y,a[1][3].y,neg(b[1][1].x));
    V_MAC_F32(c[2][0].y,a[1][0].y,neg(b[1][2].x));
    V_MAC_F32(c[2][1].y,a[1][1].y,neg(b[1][2].x));
    V_MAC_F32(c[2][2].y,a[1][2].y,neg(b[1][2].x));
    V_MAC_F32(c[2][3].y,a[1][3].y,neg(b[1][2].x));
    V_MAC_F32(c[3][0].y,a[1][0].y,neg(b[1][3].x));
    V_MAC_F32(c[3][1].y,a[1][1].y,neg(b[1][3].x));
    V_MAC_F32(c[3][2].y,a[1][2].y,neg(b[1][3].x));
    V_MAC_F32(c[3][3].y,a[1][3].y,neg(b[1][3].x));
    s_setprio(0);
    s_cbra_scc0(0);

    s_lda_b32(alpha,argptr,0x3c);
    s_lda_b128(s0,argptr,0x0);
    s_shl_b32(m,m,1);
    v_shl_b32(v32,tidx,2);
    v_cmp_u32(m,tidx,gt);
    s_mov_b64(s16,vcc);
    s_mov_b64(s18,exec);
    s_shl_b32(s8,col,3);
    s_mov_b32(s22,n);
    s_mov_b32(s23,col);
    s_sync(lgkmcnt(0));
    S_MUL_U64_U32(s4,cbks,gidz);
    S_MUL_U64_U32(s6,ldc,s8);
    S_ADD_U64(cbase,cbase,s4);
    S_ADD_U64(cbase,cbase,s6);
    s_mov_b64(s24,cbase);
    s_shl_b32(s20,ldc,4);
    s_shl_b32(s21,ldc,3);

    for( int i=0, ilab=1; i<4; ++i )
    {
        const int k=i&1;
        if(i>0){
            if(k!=0){
            __lable__(ilab); ++ilab;
                s_mov_b64(exec,s18);
                s_add_u32(s23,s23,ic(1));
            } else {
                s_mov_b64(exec,s18);
                s_shl_b32(s26,s21,4);
                s_add_u32(s23,s23,ic(15));
                S_ADD_U64_U32(s0,s24,s26);
            }
        }
        lsst_b128(csst,0x0000,c[i][0].x);
        lsst_b128(csst,0x0080,c[i][2].x);
        if(k==0){
            S_ADD_U64_U32(s2 ,s0 ,s20);
            S_ADD_U64_U32(s4 ,s2 ,s20);
            S_ADD_U64_U32(s6 ,s4 ,s20);
            S_ADD_U64_U32(s8 ,s6 ,s20);
            S_ADD_U64_U32(s10,s8 ,s20);
            S_ADD_U64_U32(s12,s10,s20);
            S_ADD_U64_U32(s14,s12,s20);
        } else {
            S_ADD_U64_U32(s0 ,s0 ,s21);
            S_ADD_U64_U32(s2 ,s2 ,s21);
            S_ADD_U64_U32(s4 ,s4 ,s21);
            S_ADD_U64_U32(s6 ,s6 ,s21);
            S_ADD_U64_U32(s8 ,s8 ,s21);
            S_ADD_U64_U32(s10,s10,s21);
            S_ADD_U64_U32(s12,s12,s21);
            S_ADD_U64_U32(s14,s14,s21);
        }
        s_mov_b64(exec,s16);
        s_sync(lgkmcnt(0));
        lsldx_b32x2(v0,csld,0,1);
        lsldx_b32x2(v2,csld,2,3);
        lsldx_b32x2(v4,csld,4,5);
        lsldx_b32x2(v6,csld,6,7);

        s_cmp_u32(s23,s22,lt);
        s_cbra_scc0(3);
        s_sync(lgkmcnt(3));
        v_mul_f32(v0,alpha,v0);
        stg_b32(s0,v32,0,v0);
    
        s_add_u32(s26,ic(2),s23);
        s_cmp_u32(s26,s22,lt);
        s_cbra_scc0(k==0?ilab:3);
        v_mul_f32(v1,alpha,v1);
        stg_b32(s2,v32,0,v1);
    
        s_add_u32(s26,ic(4),s23);
        s_cmp_u32(s26,s22,lt);
        s_cbra_scc0(k==0?ilab:3);
        s_sync(lgkmcnt(2));
        v_mul_f32(v2,alpha,v2);
        stg_b32(s4,v32,0,v2);
    
        s_add_u32(s26,ic(6),s23);
        s_cmp_u32(s26,s22,lt);
        s_cbra_scc0(k==0?ilab:3);
        v_mul_f32(v3,alpha,v3);
        stg_b32(s6,v32,0,v3);

        s_add_u32(s26,ic(8),s23);
        s_cmp_u32(s26,s22,lt);
        s_cbra_scc0(k==0?ilab:3);
        s_sync(lgkmcnt(1));
        v_mul_f32(v4,alpha,v4);
        stg_b32(s8,v32,0,v4);
    
        s_add_u32(s26,ic(10),s23);
        s_cmp_u32(s26,s22,lt);
        s_cbra_scc0(k==0?ilab:3);
        v_mul_f32(v5,alpha,v5);
        stg_b32(s10,v32,0,v5);

        s_add_u32(s26,ic(12),s23);
        s_cmp_u32(s26,s22,lt);
        s_cbra_scc0(k==0?ilab:3);
        s_sync(lgkmcnt(0));
        v_mul_f32(v6,alpha,v6);
        stg_b32(s12,v32,0,v6);
    
        s_add_u32(s26,ic(14),s23);
        s_cmp_u32(s26,s22,lt);
        s_cbra_scc0(k==0?ilab:3);
        v_mul_f32(v7,alpha,v7);
        stg_b32(s14,v32,0,v7);
    }
__lable__(3);
    s_endp();
}