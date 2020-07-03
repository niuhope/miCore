#include"../../include/gfxcoder.h"

/*
bbase : 0x00
bks   : 0x08
ldb   : 0x0c
grid  : 0x10
pmag  : 0x18
qmag  : 0x20
ldy   : 0x28 nx*ny
ags   : 0x2c nx*ny*ginc
abase : 0x30
ldx   : 0x38 nx*ny*ginc*ng
nx    : 0x3c
ny    : 0x40
bs    : 0x44
pad   : 0x48
*/

void gfxcoder::sco3x3q6_dtp()
{
    uint32_t a[8][8], b[8][8], c[8][8], ep[8], op[8];
    for( int i=0; i<64; ++i ){ ((uint32_t*)&c[0][0])[i]=v0+i; }
    for( int i=0; i<8; ++i ){
        b[i][1]=v64+i*6+0;
        b[i][2]=v64+i*6+1;
        b[i][3]=v64+i*6+2;
        b[i][4]=v64+i*6+3;
        b[i][5]=v64+i*6+4;
        b[i][6]=v64+i*6+5;
        b[i][0]=c[i][0];
        b[i][7]=c[i][7];
        op[i]=v112+i;
    }
    for( int i=0; i<8; ++i ){
        a[0][i]=b[0][i];
        a[7][i]=b[7][i];
        a[1][i]=c[i][1];
        a[2][i]=c[i][2];
        a[3][i]=c[i][3];
        a[4][i]=c[i][4];
        a[5][i]=c[i][5];
        a[6][i]=c[i][6];
    }

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s45;
    const uint32_t gidz  =s46;
    const uint32_t grid  =s4 ;
    const uint32_t gridx =s4 ;
    const uint32_t gridy =s5 ;
    const uint32_t pmag  =s6 ;
    const uint32_t qmag  =s8 ;
    const uint32_t ldy   =s10;
    const uint32_t ags   =s11;
    const uint32_t abase =s12;
    const uint32_t ldx   =s14;
    const uint32_t nx    =s15;
    const uint32_t ny    =s34;
    const uint32_t bs    =s41;
    const uint32_t pad   =s42;
    const uint32_t padx  =s43;
    const uint32_t pady  =s42;
    const uint32_t bbase =s0 ;
    const uint32_t bks   =s2 ;
    const uint32_t ldb   =s3 ;
    const uint32_t kcof0 =s4 ;
    const uint32_t kcof1 =s5 ;
    const uint32_t kcof2 =s6 ;
    const uint32_t kcof3 =s7 ;
    const uint32_t kcof4 =s8 ;
    const uint32_t kcof5 =s9 ;
    const uint32_t ncells=s18;

    const uint32_t ao   =v64 ;
    const uint32_t bo   =v64 ;
    const uint32_t gcell=v65 ;
    const uint32_t u    =v66 ;
    const uint32_t v    =v67 ;
    const uint32_t batch=v68 ;
    const uint32_t lcell=v69 ;
    const uint32_t celly=v70 ;
    const uint32_t cellx=v71 ;
    const uint32_t sst  =v72 ;
    const uint32_t x    =v73 ;
    const uint32_t y    =v74 ;
    const uint32_t sld  =v112;
    const uint32_t tidx =v120;

    metadata_start();
    {
        metadata_set_lds_size(0x4100);
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(76);
        metadata_set_group_size(64);
        metadata_set_sgprcnt(51);
        metadata_set_vgprcnt(121);
        metadata_set_arg(8,0x00,arg_kind_globuf,arg_type_f32);
        metadata_set_arg(4,0x08,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x0c,arg_kind_direct,arg_type_u32);
        metadata_set_arg(8,0x10,arg_kind_direct,arg_type_u64);
        metadata_set_arg(8,0x18,arg_kind_direct,arg_type_u64);
        metadata_set_arg(8,0x20,arg_kind_direct,arg_type_u64);
        metadata_set_arg(4,0x28,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x2c,arg_kind_direct,arg_type_u32);
        metadata_set_arg(8,0x30,arg_kind_globuf,arg_type_f32);
        metadata_set_arg(4,0x38,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x3c,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x40,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x44,arg_kind_direct,arg_type_u32);
        metadata_set_arg(4,0x48,arg_kind_direct,arg_type_u32);
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
    s_shl_b32(gidz,s4,2);
    s_shl_b32(gidy,s3,2);
    s_lda_b256(s4,argptr,0x10);
    s_movk_i32(s12,260);
    v_shr_b32(v,v0,3);
    v_and_b32(u,ic(7),v0);
    v_shl_or_b32(tidx,gidx,6,v0);
    v_shl_or_b32(gcell,gidx,6,v);
    v_mul_u24(v1,s12,v);
    v_mul_u24(sld,s12,v0);
    v_shl_add_u32(sst,u,2,v1);
    s_sync(lgkmcnt(0));

    s_lda_b128(s12,argptr,0x30);
    s_mul_i32(gridy,gridy,gridx);
    V_MDM_U32(batch,gcell,gridy,pmag);
    V_MDM_U32(celly,lcell,gridx,qmag);
    S_MUL_U64_U32(s16,gidy,ldy);
    S_MUL_U64_U32(s18,gidz,ags);
    S_ADD_U64(s16,s16,s18);
    v_mad_u24(x,ic(6),cellx,u);
    v_mul_u24(y,ic(6),celly);
    s_sync(lgkmcnt(0));
    s_lda_b64(s34,argptr,0x40);
    s_lda_b32(pad,argptr,0x48);
    S_ADD_U64(abase,abase,s16);
    v_mul_lo_u32(v76,ldx,batch);
    s_shl_b32(s44,nx,2);
    v_mov_b32(c[0][0],zero);
    v_mov_b32(c[0][1],zero);
    v_mov_b32(c[0][2],zero);
    v_mov_b32(c[0][3],zero);
    v_mov_b32(c[0][4],zero);
    v_mov_b32(c[0][5],zero);
    v_mov_b32(c[0][6],zero);
    v_mov_b32(c[0][7],zero);
    s_sync(lgkmcnt(0));
    s_mov_b32(bs,s35);
    s_and_b32(padx,pad,ic(3));
    s_shr_b32(pady,pad,2);
    v_sub_i32(x,x,padx);
    v_sub_i32(y,y,pady);
    v_cmp_u32(zero,celly,ne);
    v_cmov_b32(v78,zero,y);
    v_mad_u24(v77,nx,v78,x);
    v_add_i32(y+1,ic(1),y);
    v_add_shl_u32(ao,v76,v77,2);
    s_sub_i32(ny+1,ny,ic(2));
    s_sub_i32(ny+2,ny,ic(3));
    s_sub_i32(ny+3,ny,ic(4));
    s_sub_i32(ny+4,ny,ic(5));
    s_sub_i32(ny+5,ny,ic(6));
    s_sub_i32(ny+6,ny,ic(7));
    v_cmp_u32(s16,batch,bs,lt);
    v_cmp_i32(s18,y+0,ny,lt);
    v_cmp_i32(s20,y+1,ny,lt);
    v_cmp_i32(s22,y,ny+1,lt);
    v_cmp_i32(s24,y,ny+2,lt);
    v_cmp_i32(s26,y,ny+3,lt);
    v_cmp_i32(s28,y,ny+4,lt);
    v_cmp_i32(s30,y,ny+5,lt);
    v_cmp_i32(s32,y,ny+6,lt);
    v_cmp_i32(nx  ,x  ,gt); s_and_b64(s16,s16,vcc);
    v_cmp_i32(zero,x  ,le); s_and_b64(s16,s16,vcc);
    v_cmp_i32(zero,y+0,le); s_and_b64(s18,s18,vcc);
    v_cmp_i32(zero,y+1,le); s_and_b64(s20,s20,vcc);
    s_mov_b64(s2,exec);

    for( int i=0; i<8; ++i ){
        s_and_b64(exec,s16,s18); ldg_b32(c[i][0],abase,ao,0x0); v_add_u32(ao,s44,ao);
        s_and_b64(exec,s16,s20); ldg_b32(c[i][1],abase,ao,0x0); v_add_u32(ao,s44,ao);
        s_and_b64(exec,s16,s22); ldg_b32(c[i][2],abase,ao,0x0); v_add_u32(ao,s44,ao);
        s_and_b64(exec,s16,s24); ldg_b32(c[i][3],abase,ao,0x0); v_add_u32(ao,s44,ao);
        s_and_b64(exec,s16,s26); ldg_b32(c[i][4],abase,ao,0x0); v_add_u32(ao,s44,ao);
        s_and_b64(exec,s16,s28); ldg_b32(c[i][5],abase,ao,0x0); v_add_u32(ao,s44,ao);
        s_and_b64(exec,s16,s30); ldg_b32(c[i][6],abase,ao,0x0); v_add_u32(ao,s44,ao);
        s_and_b64(exec,s16,s32); ldg_b32(c[i][7],abase,ao,0x0);
        s_mov_b64(exec,s2);
        if(i<7){
            v_mov_b32(c[i+1][0],zero);
            v_mov_b32(c[i+1][1],zero);
            v_mov_b32(c[i+1][2],zero);
            v_mov_b32(c[i+1][3],zero);
            v_mov_b32(c[i+1][4],zero);
            v_mov_b32(c[i+1][5],zero);
            v_mov_b32(c[i+1][6],zero);
            v_mov_b32(c[i+1][7],zero);
            v_add_u32(gcell,ic(8),gcell);
            V_MDM_U32(batch,gcell,gridy,pmag);
            V_MDM_U32(celly,lcell,gridx,qmag);
            v_mul_lo_u32(v76,ldx,batch);
            v_mad_u24(x,ic(6),cellx,u);
            v_mul_u24(y,ic(6),celly);
            v_sub_i32(x,x,padx);
            v_sub_i32(y,y,pady);
            v_cmp_u32(zero,celly,ne);
            v_cmov_b32(v78,zero,y);
            v_mad_u24(v77,nx,v78,x);
            v_add_i32(y+1,ic(1),y);
            v_add_shl_u32(ao,v76,v77,2);
            v_cmp_u32(s16,batch,bs,lt);
            v_cmp_i32(s18,y+0,ny,lt);
            v_cmp_i32(s20,y+1,ny,lt);
            v_cmp_i32(s22,y,ny+1,lt);
            v_cmp_i32(s24,y,ny+2,lt);
            v_cmp_i32(s26,y,ny+3,lt);
            v_cmp_i32(s28,y,ny+4,lt);
            v_cmp_i32(s30,y,ny+5,lt);
            v_cmp_i32(s32,y,ny+6,lt);
            v_cmp_i32(nx  ,x  ,gt); s_and_b64(s16,s16,vcc);
            v_cmp_i32(zero,x  ,le); s_and_b64(s16,s16,vcc);
            v_cmp_i32(zero,y+0,le); s_and_b64(s18,s18,vcc);
            v_cmp_i32(zero,y+1,le); s_and_b64(s20,s20,vcc);
        }
    }
    s_mul_i32(ncells,gridy,bs);
    s_movk_i32(s2,0x820);
    for( int i=0; i<8; ++i ){
        s_sync(vmcnt(56-i*8));
        lsst_b32x2(sst,0*8,c[i][0],1*8,c[i][1]);
        lsst_b32x2(sst,2*8,c[i][2],3*8,c[i][3]);
        lsst_b32x2(sst,4*8,c[i][4],5*8,c[i][5]);
        lsst_b32x2(sst,6*8,c[i][6],7*8,c[i][7]);
        if(i<7){ v_add_u32(sst,s2,sst); }
    }
    s_movk_b32(kcof0,float_as_uint( 0.25f));
    s_movk_b32(kcof1,float_as_uint( 5.25f));
    s_movk_b32(kcof2,float_as_uint(-1.25f));
    s_movk_b32(kcof3,float_as_uint(-2.50f));
    s_movk_b32(kcof4,float_as_uint(-4.25f));
    s_movk_b32(kcof5,float_as_uint(-5.00f));
    s_sync(lgkmcnt(0));

    for( int i=0; i<8; ++i ){ lsld_b32(a[2][i],sld,2*32+i*4); }
    for( int i=0; i<8; ++i ){ lsld_b32(a[6][i],sld,6*32+i*4); }
    for( int i=0; i<8; ++i ){ lsld_b32(a[1][i],sld,1*32+i*4); }
    for( int i=0; i<8; ++i ){ lsld_b32(a[5][i],sld,5*32+i*4); }
    for( int i=0; i<8; ++i ){ lsld_b32(a[4][i],sld,4*32+i*4); }
    for( int i=0; i<8; ++i ){ lsld_b32(a[3][i],sld,3*32+i*4); }
    for( int i=0; i<8; ++i ){ lsld_b32(a[0][i],sld,0*32+i*4); }
    for( int i=0; i<8; ++i ){ lsld_b32(a[7][i],sld,7*32+i*4); }

    s_sync(lgkmcnt(15));
    for( int i=0; i<8; ++i ){ ep[i]=b[2][i]; }
    for( int i=0; i<8; ++i ){ v_add_f32(ep[i],a[2][i],a[6][i]); }
    for( int i=0; i<8; ++i ){ v_add_f32(op[i],a[1][i],a[5][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(ep[i],kcof4,a[4][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(op[i],kcof4,a[3][i]); }
    for( int i=0; i<8; ++i ){ v_add_f32(b[1][i],ep[i],op[i]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(b[2][i],ep[i],op[i]); }

    for( int i=0; i<8; ++i ){ ep[i]=b[4][i]; }
    for( int i=0; i<8; ++i ){ v_fma_f32(ep[i],kcof0,a[2][i],a[6][i]); }
    for( int i=0; i<8; ++i ){ v_mul_f32(op[i],fhalf,a[1][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(ep[i],kcof2,a[4][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(op[i],kcof3,a[3][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(op[i],f2   ,a[5][i]); }
    for( int i=0; i<8; ++i ){ v_add_f32(b[3][i],ep[i],op[i]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(b[4][i],ep[i],op[i]); }

    for( int i=0; i<8; ++i ){ ep[i]=b[6][i]; }
    for( int i=0; i<8; ++i ){ v_fma_f32(ep[i],f4,a[2][i],a[6][i]); }
    for( int i=0; i<8; ++i ){ v_mul_f32(op[i],f2,a[1][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(ep[i],kcof5,a[4][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(op[i],kcof3,a[3][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(op[i],fhalf,a[5][i]); }
    for( int i=0; i<8; ++i ){ v_add_f32(b[5][i],ep[i],op[i]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(b[6][i],ep[i],op[i]); }

    s_sync(lgkmcnt(0));
    for( int i=0; i<8; ++i ){ ep[i]=op[i]; }
    for( int i=0; i<8; ++i ){ v_sub_f32(b[0][i],a[0][i],a[6][i]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(ep[i]  ,a[4][i],a[2][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(b[0][i],kcof1,ep[i]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(b[7][i],a[7][i],a[1][i]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(op[i]  ,a[3][i],a[5][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(b[7][i],kcof1,op[i]); }

    //=====================================================================================
    s_lda_b128(s0,argptr,0x0);
    //=====================================================================================

    for( int i=0; i<8; ++i ){ ep[i]=c[i][2]; }
    for( int i=0; i<8; ++i ){ v_add_f32(ep[i],b[i][2],b[i][6]); }
    for( int i=0; i<8; ++i ){ v_add_f32(op[i],b[i][1],b[i][5]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(ep[i],kcof4,b[i][4]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(op[i],kcof4,b[i][3]); }
    for( int i=0; i<8; ++i ){ v_add_f32(c[i][1],ep[i],op[i]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(c[i][2],ep[i],op[i]); }

    for( int i=0; i<8; ++i ){ ep[i]=c[i][4]; }
    for( int i=0; i<8; ++i ){ v_fma_f32(ep[i],kcof0,b[i][2],b[i][6]); }
    for( int i=0; i<8; ++i ){ v_mul_f32(op[i],fhalf,b[i][1]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(ep[i],kcof2,b[i][4]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(op[i],kcof3,b[i][3]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(op[i],f2   ,b[i][5]); }
    for( int i=0; i<8; ++i ){ v_add_f32(c[i][3],ep[i],op[i]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(c[i][4],ep[i],op[i]); }

    for( int i=0; i<8; ++i ){ ep[i]=c[i][6]; }
    for( int i=0; i<8; ++i ){ v_fma_f32(ep[i],f4,b[i][2],b[i][6]); }
    for( int i=0; i<8; ++i ){ v_mul_f32(op[i],f2,b[i][1]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(ep[i],kcof5,b[i][4]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(op[i],kcof3,b[i][3]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(op[i],fhalf,b[i][5]); }
    for( int i=0; i<8; ++i ){ v_add_f32(c[i][5],ep[i],op[i]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(c[i][6],ep[i],op[i]); }

    for( int i=0; i<8; ++i ){ ep[i]=op[i]; }
    for( int i=0; i<8; ++i ){ v_sub_f32(c[i][0],b[i][0],b[i][6]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(ep[i]  ,b[i][4],b[i][2]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(c[i][0],kcof1,ep[i]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(c[i][7],b[i][7],b[i][1]); }
    for( int i=0; i<8; ++i ){ v_sub_f32(op[i]  ,b[i][3],b[i][5]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(c[i][7],kcof1,op[i]); }

    //=====================================================================================
    //bbase+=gidz*64*bks+gidy*ldb+tidx
    v_shl_b32(bo,tidx,2);
    s_shl_b32(gidz,gidz,6);
    s_sync(lgkmcnt(0));
    S_MUL_U64_U32(s4,gidy,ldb);
    S_MUL_U64_U32(s6,gidz,bks);
    s_shl_b32(s16,bks,5);
    s_shl_b32(s17,bks,2);
    S_ADD_U64(bbase,bbase,s4);
    S_ADD_U64(bbase,bbase,s6);
    S_ADD_U64_U32(bbase+1*2,bbase+0*2,s16);
    S_ADD_U64_U32(bbase+2*2,bbase+1*2,s16);
    S_ADD_U64_U32(bbase+3*2,bbase+2*2,s16);
    S_ADD_U64_U32(bbase+4*2,bbase+3*2,s16);
    S_ADD_U64_U32(bbase+5*2,bbase+4*2,s16);
    S_ADD_U64_U32(bbase+6*2,bbase+5*2,s16);
    S_ADD_U64_U32(bbase+7*2,bbase+6*2,s16);
    v_add_u32(bo+1,s17,bo+0);
    v_add_u32(bo+2,s17,bo+1);
    v_add_u32(bo+3,s17,bo+2);
    v_add_u32(bo+4,s17,bo+3);
    v_add_u32(bo+5,s17,bo+4);
    v_add_u32(bo+6,s17,bo+5);
    v_add_u32(bo+7,s17,bo+6);
    v_cmpx_u32(ncells,tidx,gt);
    for( int i=0; i<8; ++i ){
        stg_b32(bbase+i*2,bo+0,0x0,c[i][0]);
        stg_b32(bbase+i*2,bo+1,0x0,c[i][1]);
        stg_b32(bbase+i*2,bo+2,0x0,c[i][2]);
        stg_b32(bbase+i*2,bo+3,0x0,c[i][3]);
        stg_b32(bbase+i*2,bo+4,0x0,c[i][4]);
        stg_b32(bbase+i*2,bo+5,0x0,c[i][5]);
        stg_b32(bbase+i*2,bo+6,0x0,c[i][6]);
        stg_b32(bbase+i*2,bo+7,0x0,c[i][7]);
    }
    s_endp();
}