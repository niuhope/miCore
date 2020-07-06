﻿#include"../include/context.h"

static const uint8_t g_hsaco_gfx900[]=
{
#include"../hsaco/hsaco_gfx900.h"
};
static const uint8_t g_hsaco_gfx906[]=
{
#include"../hsaco/hsaco_gfx906.h"
};

static const struct{ const char* name; uint32_t info; } g_kprop[]=
{
    { "padding2d"        , ((36<<16)|256) },
    { "perm_flip"        , ((40<<16)| 64) },
    { "genidx_co2d"      , ((56<<16)| 64) },

    /*==================================================*/

    { "suffco7x4_om"     , ((64<<16)|128) },
    { "suffco7x4_om_relu", ((64<<16)|128) },
    { "suffco7x4_dm"     , ((64<<16)|128) },
    { "suffco7x4_dm_relu", ((64<<16)|128) },
    { "suffco7x4_qm"     , ((64<<16)|128) },
    { "suffco7x4_qm_relu", ((64<<16)|128) },
    { "suffco8x5_om"     , ((64<<16)|256) },
    { "suffco8x5_om_relu", ((64<<16)|256) },
    { "suffco8x5_dm"     , ((64<<16)|256) },
    { "suffco8x5_dm_relu", ((64<<16)|256) },
    { "suffco8x5_qm"     , ((64<<16)|256) },
    { "suffco8x5_qm_relu", ((64<<16)|256) },
    { "suffco8x6_om"     , ((64<<16)|256) },
    { "suffco8x6_om_relu", ((64<<16)|256) },
    { "suffco8x6_dm"     , ((64<<16)|256) },
    { "suffco8x6_dm_relu", ((64<<16)|256) },
    { "suffco8x6_qm"     , ((64<<16)|256) },
    { "suffco8x6_qm_relu", ((64<<16)|256) },
    { "suffco7x7_om"     , ((64<<16)|256) },
    { "suffco7x7_om_relu", ((64<<16)|256) },
    { "suffco7x7_dm"     , ((64<<16)|256) },
    { "suffco7x7_dm_relu", ((64<<16)|256) },
    { "suffco7x7_qm"     , ((64<<16)|256) },
    { "suffco7x7_qm_relu", ((64<<16)|256) },
    { "sufbco7x4_om"     , ((64<<16)|128) },
    { "sufbco7x4_dm"     , ((64<<16)|128) },
    { "sufbco7x4_qm"     , ((64<<16)|128) },
    { "sufbco8x5_om"     , ((64<<16)|256) },
    { "sufbco8x5_dm"     , ((64<<16)|256) },
    { "sufbco8x5_qm"     , ((64<<16)|256) },
    { "sufbco8x6_om"     , ((64<<16)|256) },
    { "sufbco8x6_dm"     , ((64<<16)|256) },
    { "sufbco8x6_qm"     , ((64<<16)|256) },
    { "sufbco7x7_om"     , ((64<<16)|256) },
    { "sufbco7x7_dm"     , ((64<<16)|256) },
    { "sufbco7x7_qm"     , ((64<<16)|256) },

    /*==================================================*/

    { "sfco"             , ((68<<16)|256) },
    { "sfco_relu"        , ((68<<16)|256) },
    { "sfco7x4"          , ((68<<16)|128) },
    { "sfco7x4_relu"     , ((68<<16)|128) },
    { "sfco8x5"          , ((68<<16)|256) },
    { "sfco8x5_relu"     , ((68<<16)|256) },
    { "sfco8x6"          , ((68<<16)|256) },
    { "sfco8x6_relu"     , ((68<<16)|256) },
    { "sfco7x7"          , ((68<<16)|256) },
    { "sfco7x7_relu"     , ((68<<16)|256) },
    { "sbco7x4"          , ((68<<16)|128) },
    { "sbco8x5"          , ((68<<16)|256) },
    { "sbco8x6"          , ((68<<16)|256) },
    { "sbco7x7"          , ((68<<16)|256) },

    /*==================================================*/

    { "sgemm6x5"         , ((64<<16)| 64) },
    { "sgemm7x5"         , ((64<<16)|128) },
    { "sgemm8x5"         , ((64<<16)|256) },
    { "sgemm6x6"         , ((64<<16)| 64) },
    { "sgemm7x6"         , ((64<<16)|128) },
    { "sgemm8x6"         , ((64<<16)|256) },
    { "sgemm7x7"         , ((64<<16)|256) },
    { "sco3x3q6_dta"     , ((72<<16)| 64) },
    { "sco3x3q6_dtx"     , ((72<<16)| 64) },
    { "sco3x3q6_dtp"     , ((76<<16)| 64) },
    { "sco3x3q6_fft"     , ((36<<16)| 64) },
    { "sco3x3q6_bft"     , ((36<<16)| 64) },
    { "sco3x3q6_ota"     , ((72<<16)| 64) },
    { "sco3x3q6_ota_relu", ((72<<16)| 64) },
    { "sco3x3q6_otx"     , ((72<<16)| 64) },
    { "sco3x3q6_otx_relu", ((72<<16)| 64) },

    /*==================================================*/

    { "scgemm5x4"   , ((64<<16)| 64) },
    { "scgemm5x4_ck", ((64<<16)| 64) },
    { "scgemm5x5"   , ((64<<16)| 64) },
    { "scgemm5x5_ck", ((64<<16)| 64) },
    { "scgemm5x6"   , ((64<<16)|128) },
    { "scgemm5x6_ck", ((64<<16)|128) },
    { "scgemm6x4"   , ((64<<16)| 64) },
    { "scgemm6x4_ck", ((64<<16)| 64) },
    { "scgemm6x5"   , ((64<<16)|128) },
    { "scgemm6x5_ck", ((64<<16)|128) },
    { "scgemm6x6"   , ((64<<16)|256) },
    { "scgemm6x6_ck", ((64<<16)|256) },

    { "sfft4x4_r2c_perm_s3x3", ((32<<16)|256) },
    { "sfft4x4_r2c_perm_s5x5", ((32<<16)|256) },
    { "sfft4x4_r2c_qerm_s3x3", ((32<<16)|256) },
    { "sfft4x4_r2c_qerm_s5x5", ((32<<16)|256) },
    { "sfft5x5_r2c_perm_s3x3", ((32<<16)|512) },
    { "sfft5x5_r2c_perm_s5x5", ((32<<16)|512) },
    { "sfft5x5_r2c_qerm_s3x3", ((32<<16)|512) },
    { "sfft5x5_r2c_qerm_s5x5", ((32<<16)|512) },

    { "sfft4x4_c2r_g3x1", ((32<<16)|256) },
    { "sfft4x4_c2r_g5x1", ((32<<16)|256) },
    { "sfft4x4_c2r_g7x1", ((32<<16)|256) },
    { "sfft4x4_c2r_g9x1", ((32<<16)|256) },
    { "sfft4x4_c2r_g1x3", ((32<<16)|256) },
    { "sfft4x4_c2r_g1x5", ((32<<16)|256) },
    { "sfft4x4_c2r_g1x7", ((32<<16)|256) },
    { "sfft4x4_c2r_g1x9", ((32<<16)|256) },
    { "sfft4x4_c2r_g3x3", ((32<<16)|256) },
    { "sfft4x4_c2r_g5x5", ((32<<16)|256) },
    { "sfft4x4_c2r_g7x7", ((32<<16)|256) },
    { "sfft5x5_c2r_g3x1", ((32<<16)|256) },
    { "sfft5x5_c2r_g5x1", ((32<<16)|256) },
    { "sfft5x5_c2r_g7x1", ((32<<16)|256) },
    { "sfft5x5_c2r_g9x1", ((32<<16)|256) },
    { "sfft5x5_c2r_g1x3", ((32<<16)|256) },
    { "sfft5x5_c2r_g1x5", ((32<<16)|256) },
    { "sfft5x5_c2r_g1x7", ((32<<16)|256) },
    { "sfft5x5_c2r_g1x9", ((32<<16)|256) },
    { "sfft5x5_c2r_g3x3", ((32<<16)|256) },
    { "sfft5x5_c2r_g5x5", ((32<<16)|256) },
    { "sfft5x5_c2r_g7x7", ((32<<16)|256) },

    { "sfft4x4_r2c_grid_perm"    , ((68<<16)|256) },
    { "sfft4x4_r2c_grid_perm_ex" , ((68<<16)|256) },
    { "sfft4x4_r2c_grid_perm_pad", ((72<<16)|256) },
    { "sfft5x5_r2c_grid_perm"    , ((68<<16)|512) },
    { "sfft5x5_r2c_grid_perm_ex" , ((68<<16)|512) },
    { "sfft5x5_r2c_grid_perm_pad", ((72<<16)|512) },

    { "sfft4x4_r2c_grad"    , ((68<<16)|256) },
    { "sfft4x4_r2c_grad_ex" , ((68<<16)|256) },
    { "sfft4x4_r2c_grad_pad", ((72<<16)|256) },
    { "sfft4x4_r2c_grad_nov", ((68<<16)|256) },
    { "sfft5x5_r2c_grad"    , ((68<<16)|512) },
    { "sfft5x5_r2c_grad_ex" , ((68<<16)|512) },
    { "sfft5x5_r2c_grad_pad", ((72<<16)|512) },
    { "sfft5x5_r2c_grad_nov", ((68<<16)|512) },

    { "sfft4x4_c2r_grid_perm"     , ((68<<16)|256) },
    { "sfft4x4_c2r_grid_perm_relu", ((68<<16)|256) },
    { "sfft5x5_c2r_grid_perm"     , ((68<<16)|256) },
    { "sfft5x5_c2r_grid_perm_relu", ((68<<16)|256) },

    { "sfft4x4_r2c_perm_v01", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v02", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v03", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v04", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v05", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v06", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v07", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v08", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v09", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v10", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v11", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v12", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v13", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v14", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v15", ((40<<16)|256) },
    { "sfft4x4_r2c_perm_v16", ((40<<16)|256) },
    { "sfft5x5_r2c_perm_v01", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v02", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v03", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v04", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v05", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v06", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v07", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v08", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v09", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v10", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v11", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v12", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v13", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v14", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v15", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v16", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v17", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v18", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v19", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v20", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v21", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v22", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v23", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v24", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v25", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v26", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v27", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v28", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v29", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v30", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v31", ((40<<16)|512) },
    { "sfft5x5_r2c_perm_v32", ((40<<16)|512) },
    
    { "sfft4x4_r2c_qerm_v01", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v02", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v03", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v04", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v05", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v06", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v07", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v08", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v09", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v10", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v11", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v12", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v13", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v14", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v15", ((40<<16)|256) },
    { "sfft4x4_r2c_qerm_v16", ((40<<16)|256) },
    { "sfft5x5_r2c_qerm_v01", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v02", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v03", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v04", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v05", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v06", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v07", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v08", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v09", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v10", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v11", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v12", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v13", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v14", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v15", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v16", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v17", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v18", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v19", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v20", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v21", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v22", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v23", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v24", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v25", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v26", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v27", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v28", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v29", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v30", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v31", ((40<<16)|512) },
    { "sfft5x5_r2c_qerm_v32", ((40<<16)|512) },
    
    { "sfft4x4_r2c_perm_p00", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p01", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p02", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p03", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p04", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p05", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p06", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p07", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p08", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p09", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p10", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p11", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p12", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p13", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p14", ((48<<16)|256) },
    { "sfft4x4_r2c_perm_p15", ((48<<16)|256) },
    { "sfft5x5_r2c_perm_p00", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p01", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p02", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p03", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p04", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p05", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p06", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p07", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p08", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p09", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p10", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p11", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p12", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p13", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p14", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p15", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p16", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p17", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p18", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p19", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p20", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p21", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p22", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p23", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p24", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p25", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p26", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p27", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p28", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p29", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p30", ((48<<16)|512) },
    { "sfft5x5_r2c_perm_p31", ((48<<16)|512) },

    { "sfft4x4_c2r_perm_v01"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v02"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v03"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v04"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v05"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v06"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v07"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v08"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v09"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v10"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v11"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v12"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v13"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v14"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v15"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_v16"     , ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v01", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v02", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v03", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v04", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v05", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v06", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v07", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v08", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v09", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v10", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v11", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v12", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v13", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v14", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v15", ((40<<16)|256) },
    { "sfft4x4_c2r_perm_relu_v16", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v01"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v02"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v03"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v04"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v05"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v06"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v07"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v08"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v09"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v10"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v11"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v12"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v13"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v14"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v15"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v16"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v17"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v18"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v19"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v20"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v21"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v22"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v23"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v24"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v25"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v26"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v27"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v28"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v29"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v30"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v31"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_v32"     , ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v01", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v02", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v03", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v04", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v05", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v06", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v07", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v08", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v09", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v10", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v11", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v12", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v13", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v14", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v15", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v16", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v17", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v18", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v19", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v20", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v21", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v22", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v23", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v24", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v25", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v26", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v27", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v28", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v29", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v30", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v31", ((40<<16)|256) },
    { "sfft5x5_c2r_perm_relu_v32", ((40<<16)|256) }
};

__local_func int context_init( context_t* p_ctx )
{
    hipDeviceProp_t dev_prop;
    uint8_t *p_hsaco;
    uint32_t i, nkern;
    hipDevice_t dev;

    hipGetDevice( &dev );
    hipGetDeviceProperties( &dev_prop, dev );
    if((dev_prop.gcnArch!=900)&&(dev_prop.gcnArch!=906))
        return istatus_invalid_device;

    switch(dev_prop.gcnArch){
    case 900 : p_hsaco=(uint8_t*)g_hsaco_gfx900; break;
    case 906 : p_hsaco=(uint8_t*)g_hsaco_gfx906; break;
    }

    p_ctx->device=dev;
    p_ctx->arch=dev_prop.gcnArch;
    p_ctx->ncu=dev_prop.multiProcessorCount;
    nkern=sizeof(g_kprop)/sizeof(g_kprop[0]);
    if((p_ctx->kern=(kernel_t*)malloc((nkern)*sizeof(kernel_t)))==NULL)
        return istatus_host_memory_alloc_failed;

    p_ctx->module=NULL;
    if(hipModuleLoadData( &p_ctx->module, (const void*)p_hsaco )!=hipSuccess){
        free(p_ctx->kern); p_ctx->kern=NULL;
        return istatus_invalid_binary;
    }

    p_ctx->kern_perm=&p_ctx->kern[1];
    p_ctx->kern_idx =&p_ctx->kern_perm[1];
    p_ctx->kern_ufco=&p_ctx->kern_idx[1];
    p_ctx->kern_fco =&p_ctx->kern_ufco[36];
    p_ctx->kern_bco =&p_ctx->kern_fco[10];
    p_ctx->kern_cell=&p_ctx->kern_bco[4];
    p_ctx->kern_fft =&p_ctx->kern_cell[16];
    
    for( i=0; i<nkern; ++i ){
        kernel_t* kern=&p_ctx->kern[i];
        hipModuleGetFunction( &kern->id, p_ctx->module, g_kprop[i].name );
        kern->block[0]=g_kprop[i].info&0xffff;
        kern->argsize=g_kprop[i].info>>16;
        init_kernel( kern );
    }
    return istatus_success;
}
__local_func void context_release( context_t* p_ctx )
{
    if(p_ctx!=NULL){
        if(p_ctx->module!=NULL){ hipModuleUnload(p_ctx->module); }
        if(p_ctx->kern!=NULL){ free(p_ctx->kern); }
    }
}