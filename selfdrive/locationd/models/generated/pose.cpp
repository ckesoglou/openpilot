#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_5742780909134961661) {
   out_5742780909134961661[0] = delta_x[0] + nom_x[0];
   out_5742780909134961661[1] = delta_x[1] + nom_x[1];
   out_5742780909134961661[2] = delta_x[2] + nom_x[2];
   out_5742780909134961661[3] = delta_x[3] + nom_x[3];
   out_5742780909134961661[4] = delta_x[4] + nom_x[4];
   out_5742780909134961661[5] = delta_x[5] + nom_x[5];
   out_5742780909134961661[6] = delta_x[6] + nom_x[6];
   out_5742780909134961661[7] = delta_x[7] + nom_x[7];
   out_5742780909134961661[8] = delta_x[8] + nom_x[8];
   out_5742780909134961661[9] = delta_x[9] + nom_x[9];
   out_5742780909134961661[10] = delta_x[10] + nom_x[10];
   out_5742780909134961661[11] = delta_x[11] + nom_x[11];
   out_5742780909134961661[12] = delta_x[12] + nom_x[12];
   out_5742780909134961661[13] = delta_x[13] + nom_x[13];
   out_5742780909134961661[14] = delta_x[14] + nom_x[14];
   out_5742780909134961661[15] = delta_x[15] + nom_x[15];
   out_5742780909134961661[16] = delta_x[16] + nom_x[16];
   out_5742780909134961661[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_90707900821457158) {
   out_90707900821457158[0] = -nom_x[0] + true_x[0];
   out_90707900821457158[1] = -nom_x[1] + true_x[1];
   out_90707900821457158[2] = -nom_x[2] + true_x[2];
   out_90707900821457158[3] = -nom_x[3] + true_x[3];
   out_90707900821457158[4] = -nom_x[4] + true_x[4];
   out_90707900821457158[5] = -nom_x[5] + true_x[5];
   out_90707900821457158[6] = -nom_x[6] + true_x[6];
   out_90707900821457158[7] = -nom_x[7] + true_x[7];
   out_90707900821457158[8] = -nom_x[8] + true_x[8];
   out_90707900821457158[9] = -nom_x[9] + true_x[9];
   out_90707900821457158[10] = -nom_x[10] + true_x[10];
   out_90707900821457158[11] = -nom_x[11] + true_x[11];
   out_90707900821457158[12] = -nom_x[12] + true_x[12];
   out_90707900821457158[13] = -nom_x[13] + true_x[13];
   out_90707900821457158[14] = -nom_x[14] + true_x[14];
   out_90707900821457158[15] = -nom_x[15] + true_x[15];
   out_90707900821457158[16] = -nom_x[16] + true_x[16];
   out_90707900821457158[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_9191020752603421382) {
   out_9191020752603421382[0] = 1.0;
   out_9191020752603421382[1] = 0.0;
   out_9191020752603421382[2] = 0.0;
   out_9191020752603421382[3] = 0.0;
   out_9191020752603421382[4] = 0.0;
   out_9191020752603421382[5] = 0.0;
   out_9191020752603421382[6] = 0.0;
   out_9191020752603421382[7] = 0.0;
   out_9191020752603421382[8] = 0.0;
   out_9191020752603421382[9] = 0.0;
   out_9191020752603421382[10] = 0.0;
   out_9191020752603421382[11] = 0.0;
   out_9191020752603421382[12] = 0.0;
   out_9191020752603421382[13] = 0.0;
   out_9191020752603421382[14] = 0.0;
   out_9191020752603421382[15] = 0.0;
   out_9191020752603421382[16] = 0.0;
   out_9191020752603421382[17] = 0.0;
   out_9191020752603421382[18] = 0.0;
   out_9191020752603421382[19] = 1.0;
   out_9191020752603421382[20] = 0.0;
   out_9191020752603421382[21] = 0.0;
   out_9191020752603421382[22] = 0.0;
   out_9191020752603421382[23] = 0.0;
   out_9191020752603421382[24] = 0.0;
   out_9191020752603421382[25] = 0.0;
   out_9191020752603421382[26] = 0.0;
   out_9191020752603421382[27] = 0.0;
   out_9191020752603421382[28] = 0.0;
   out_9191020752603421382[29] = 0.0;
   out_9191020752603421382[30] = 0.0;
   out_9191020752603421382[31] = 0.0;
   out_9191020752603421382[32] = 0.0;
   out_9191020752603421382[33] = 0.0;
   out_9191020752603421382[34] = 0.0;
   out_9191020752603421382[35] = 0.0;
   out_9191020752603421382[36] = 0.0;
   out_9191020752603421382[37] = 0.0;
   out_9191020752603421382[38] = 1.0;
   out_9191020752603421382[39] = 0.0;
   out_9191020752603421382[40] = 0.0;
   out_9191020752603421382[41] = 0.0;
   out_9191020752603421382[42] = 0.0;
   out_9191020752603421382[43] = 0.0;
   out_9191020752603421382[44] = 0.0;
   out_9191020752603421382[45] = 0.0;
   out_9191020752603421382[46] = 0.0;
   out_9191020752603421382[47] = 0.0;
   out_9191020752603421382[48] = 0.0;
   out_9191020752603421382[49] = 0.0;
   out_9191020752603421382[50] = 0.0;
   out_9191020752603421382[51] = 0.0;
   out_9191020752603421382[52] = 0.0;
   out_9191020752603421382[53] = 0.0;
   out_9191020752603421382[54] = 0.0;
   out_9191020752603421382[55] = 0.0;
   out_9191020752603421382[56] = 0.0;
   out_9191020752603421382[57] = 1.0;
   out_9191020752603421382[58] = 0.0;
   out_9191020752603421382[59] = 0.0;
   out_9191020752603421382[60] = 0.0;
   out_9191020752603421382[61] = 0.0;
   out_9191020752603421382[62] = 0.0;
   out_9191020752603421382[63] = 0.0;
   out_9191020752603421382[64] = 0.0;
   out_9191020752603421382[65] = 0.0;
   out_9191020752603421382[66] = 0.0;
   out_9191020752603421382[67] = 0.0;
   out_9191020752603421382[68] = 0.0;
   out_9191020752603421382[69] = 0.0;
   out_9191020752603421382[70] = 0.0;
   out_9191020752603421382[71] = 0.0;
   out_9191020752603421382[72] = 0.0;
   out_9191020752603421382[73] = 0.0;
   out_9191020752603421382[74] = 0.0;
   out_9191020752603421382[75] = 0.0;
   out_9191020752603421382[76] = 1.0;
   out_9191020752603421382[77] = 0.0;
   out_9191020752603421382[78] = 0.0;
   out_9191020752603421382[79] = 0.0;
   out_9191020752603421382[80] = 0.0;
   out_9191020752603421382[81] = 0.0;
   out_9191020752603421382[82] = 0.0;
   out_9191020752603421382[83] = 0.0;
   out_9191020752603421382[84] = 0.0;
   out_9191020752603421382[85] = 0.0;
   out_9191020752603421382[86] = 0.0;
   out_9191020752603421382[87] = 0.0;
   out_9191020752603421382[88] = 0.0;
   out_9191020752603421382[89] = 0.0;
   out_9191020752603421382[90] = 0.0;
   out_9191020752603421382[91] = 0.0;
   out_9191020752603421382[92] = 0.0;
   out_9191020752603421382[93] = 0.0;
   out_9191020752603421382[94] = 0.0;
   out_9191020752603421382[95] = 1.0;
   out_9191020752603421382[96] = 0.0;
   out_9191020752603421382[97] = 0.0;
   out_9191020752603421382[98] = 0.0;
   out_9191020752603421382[99] = 0.0;
   out_9191020752603421382[100] = 0.0;
   out_9191020752603421382[101] = 0.0;
   out_9191020752603421382[102] = 0.0;
   out_9191020752603421382[103] = 0.0;
   out_9191020752603421382[104] = 0.0;
   out_9191020752603421382[105] = 0.0;
   out_9191020752603421382[106] = 0.0;
   out_9191020752603421382[107] = 0.0;
   out_9191020752603421382[108] = 0.0;
   out_9191020752603421382[109] = 0.0;
   out_9191020752603421382[110] = 0.0;
   out_9191020752603421382[111] = 0.0;
   out_9191020752603421382[112] = 0.0;
   out_9191020752603421382[113] = 0.0;
   out_9191020752603421382[114] = 1.0;
   out_9191020752603421382[115] = 0.0;
   out_9191020752603421382[116] = 0.0;
   out_9191020752603421382[117] = 0.0;
   out_9191020752603421382[118] = 0.0;
   out_9191020752603421382[119] = 0.0;
   out_9191020752603421382[120] = 0.0;
   out_9191020752603421382[121] = 0.0;
   out_9191020752603421382[122] = 0.0;
   out_9191020752603421382[123] = 0.0;
   out_9191020752603421382[124] = 0.0;
   out_9191020752603421382[125] = 0.0;
   out_9191020752603421382[126] = 0.0;
   out_9191020752603421382[127] = 0.0;
   out_9191020752603421382[128] = 0.0;
   out_9191020752603421382[129] = 0.0;
   out_9191020752603421382[130] = 0.0;
   out_9191020752603421382[131] = 0.0;
   out_9191020752603421382[132] = 0.0;
   out_9191020752603421382[133] = 1.0;
   out_9191020752603421382[134] = 0.0;
   out_9191020752603421382[135] = 0.0;
   out_9191020752603421382[136] = 0.0;
   out_9191020752603421382[137] = 0.0;
   out_9191020752603421382[138] = 0.0;
   out_9191020752603421382[139] = 0.0;
   out_9191020752603421382[140] = 0.0;
   out_9191020752603421382[141] = 0.0;
   out_9191020752603421382[142] = 0.0;
   out_9191020752603421382[143] = 0.0;
   out_9191020752603421382[144] = 0.0;
   out_9191020752603421382[145] = 0.0;
   out_9191020752603421382[146] = 0.0;
   out_9191020752603421382[147] = 0.0;
   out_9191020752603421382[148] = 0.0;
   out_9191020752603421382[149] = 0.0;
   out_9191020752603421382[150] = 0.0;
   out_9191020752603421382[151] = 0.0;
   out_9191020752603421382[152] = 1.0;
   out_9191020752603421382[153] = 0.0;
   out_9191020752603421382[154] = 0.0;
   out_9191020752603421382[155] = 0.0;
   out_9191020752603421382[156] = 0.0;
   out_9191020752603421382[157] = 0.0;
   out_9191020752603421382[158] = 0.0;
   out_9191020752603421382[159] = 0.0;
   out_9191020752603421382[160] = 0.0;
   out_9191020752603421382[161] = 0.0;
   out_9191020752603421382[162] = 0.0;
   out_9191020752603421382[163] = 0.0;
   out_9191020752603421382[164] = 0.0;
   out_9191020752603421382[165] = 0.0;
   out_9191020752603421382[166] = 0.0;
   out_9191020752603421382[167] = 0.0;
   out_9191020752603421382[168] = 0.0;
   out_9191020752603421382[169] = 0.0;
   out_9191020752603421382[170] = 0.0;
   out_9191020752603421382[171] = 1.0;
   out_9191020752603421382[172] = 0.0;
   out_9191020752603421382[173] = 0.0;
   out_9191020752603421382[174] = 0.0;
   out_9191020752603421382[175] = 0.0;
   out_9191020752603421382[176] = 0.0;
   out_9191020752603421382[177] = 0.0;
   out_9191020752603421382[178] = 0.0;
   out_9191020752603421382[179] = 0.0;
   out_9191020752603421382[180] = 0.0;
   out_9191020752603421382[181] = 0.0;
   out_9191020752603421382[182] = 0.0;
   out_9191020752603421382[183] = 0.0;
   out_9191020752603421382[184] = 0.0;
   out_9191020752603421382[185] = 0.0;
   out_9191020752603421382[186] = 0.0;
   out_9191020752603421382[187] = 0.0;
   out_9191020752603421382[188] = 0.0;
   out_9191020752603421382[189] = 0.0;
   out_9191020752603421382[190] = 1.0;
   out_9191020752603421382[191] = 0.0;
   out_9191020752603421382[192] = 0.0;
   out_9191020752603421382[193] = 0.0;
   out_9191020752603421382[194] = 0.0;
   out_9191020752603421382[195] = 0.0;
   out_9191020752603421382[196] = 0.0;
   out_9191020752603421382[197] = 0.0;
   out_9191020752603421382[198] = 0.0;
   out_9191020752603421382[199] = 0.0;
   out_9191020752603421382[200] = 0.0;
   out_9191020752603421382[201] = 0.0;
   out_9191020752603421382[202] = 0.0;
   out_9191020752603421382[203] = 0.0;
   out_9191020752603421382[204] = 0.0;
   out_9191020752603421382[205] = 0.0;
   out_9191020752603421382[206] = 0.0;
   out_9191020752603421382[207] = 0.0;
   out_9191020752603421382[208] = 0.0;
   out_9191020752603421382[209] = 1.0;
   out_9191020752603421382[210] = 0.0;
   out_9191020752603421382[211] = 0.0;
   out_9191020752603421382[212] = 0.0;
   out_9191020752603421382[213] = 0.0;
   out_9191020752603421382[214] = 0.0;
   out_9191020752603421382[215] = 0.0;
   out_9191020752603421382[216] = 0.0;
   out_9191020752603421382[217] = 0.0;
   out_9191020752603421382[218] = 0.0;
   out_9191020752603421382[219] = 0.0;
   out_9191020752603421382[220] = 0.0;
   out_9191020752603421382[221] = 0.0;
   out_9191020752603421382[222] = 0.0;
   out_9191020752603421382[223] = 0.0;
   out_9191020752603421382[224] = 0.0;
   out_9191020752603421382[225] = 0.0;
   out_9191020752603421382[226] = 0.0;
   out_9191020752603421382[227] = 0.0;
   out_9191020752603421382[228] = 1.0;
   out_9191020752603421382[229] = 0.0;
   out_9191020752603421382[230] = 0.0;
   out_9191020752603421382[231] = 0.0;
   out_9191020752603421382[232] = 0.0;
   out_9191020752603421382[233] = 0.0;
   out_9191020752603421382[234] = 0.0;
   out_9191020752603421382[235] = 0.0;
   out_9191020752603421382[236] = 0.0;
   out_9191020752603421382[237] = 0.0;
   out_9191020752603421382[238] = 0.0;
   out_9191020752603421382[239] = 0.0;
   out_9191020752603421382[240] = 0.0;
   out_9191020752603421382[241] = 0.0;
   out_9191020752603421382[242] = 0.0;
   out_9191020752603421382[243] = 0.0;
   out_9191020752603421382[244] = 0.0;
   out_9191020752603421382[245] = 0.0;
   out_9191020752603421382[246] = 0.0;
   out_9191020752603421382[247] = 1.0;
   out_9191020752603421382[248] = 0.0;
   out_9191020752603421382[249] = 0.0;
   out_9191020752603421382[250] = 0.0;
   out_9191020752603421382[251] = 0.0;
   out_9191020752603421382[252] = 0.0;
   out_9191020752603421382[253] = 0.0;
   out_9191020752603421382[254] = 0.0;
   out_9191020752603421382[255] = 0.0;
   out_9191020752603421382[256] = 0.0;
   out_9191020752603421382[257] = 0.0;
   out_9191020752603421382[258] = 0.0;
   out_9191020752603421382[259] = 0.0;
   out_9191020752603421382[260] = 0.0;
   out_9191020752603421382[261] = 0.0;
   out_9191020752603421382[262] = 0.0;
   out_9191020752603421382[263] = 0.0;
   out_9191020752603421382[264] = 0.0;
   out_9191020752603421382[265] = 0.0;
   out_9191020752603421382[266] = 1.0;
   out_9191020752603421382[267] = 0.0;
   out_9191020752603421382[268] = 0.0;
   out_9191020752603421382[269] = 0.0;
   out_9191020752603421382[270] = 0.0;
   out_9191020752603421382[271] = 0.0;
   out_9191020752603421382[272] = 0.0;
   out_9191020752603421382[273] = 0.0;
   out_9191020752603421382[274] = 0.0;
   out_9191020752603421382[275] = 0.0;
   out_9191020752603421382[276] = 0.0;
   out_9191020752603421382[277] = 0.0;
   out_9191020752603421382[278] = 0.0;
   out_9191020752603421382[279] = 0.0;
   out_9191020752603421382[280] = 0.0;
   out_9191020752603421382[281] = 0.0;
   out_9191020752603421382[282] = 0.0;
   out_9191020752603421382[283] = 0.0;
   out_9191020752603421382[284] = 0.0;
   out_9191020752603421382[285] = 1.0;
   out_9191020752603421382[286] = 0.0;
   out_9191020752603421382[287] = 0.0;
   out_9191020752603421382[288] = 0.0;
   out_9191020752603421382[289] = 0.0;
   out_9191020752603421382[290] = 0.0;
   out_9191020752603421382[291] = 0.0;
   out_9191020752603421382[292] = 0.0;
   out_9191020752603421382[293] = 0.0;
   out_9191020752603421382[294] = 0.0;
   out_9191020752603421382[295] = 0.0;
   out_9191020752603421382[296] = 0.0;
   out_9191020752603421382[297] = 0.0;
   out_9191020752603421382[298] = 0.0;
   out_9191020752603421382[299] = 0.0;
   out_9191020752603421382[300] = 0.0;
   out_9191020752603421382[301] = 0.0;
   out_9191020752603421382[302] = 0.0;
   out_9191020752603421382[303] = 0.0;
   out_9191020752603421382[304] = 1.0;
   out_9191020752603421382[305] = 0.0;
   out_9191020752603421382[306] = 0.0;
   out_9191020752603421382[307] = 0.0;
   out_9191020752603421382[308] = 0.0;
   out_9191020752603421382[309] = 0.0;
   out_9191020752603421382[310] = 0.0;
   out_9191020752603421382[311] = 0.0;
   out_9191020752603421382[312] = 0.0;
   out_9191020752603421382[313] = 0.0;
   out_9191020752603421382[314] = 0.0;
   out_9191020752603421382[315] = 0.0;
   out_9191020752603421382[316] = 0.0;
   out_9191020752603421382[317] = 0.0;
   out_9191020752603421382[318] = 0.0;
   out_9191020752603421382[319] = 0.0;
   out_9191020752603421382[320] = 0.0;
   out_9191020752603421382[321] = 0.0;
   out_9191020752603421382[322] = 0.0;
   out_9191020752603421382[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3255491544958013680) {
   out_3255491544958013680[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3255491544958013680[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3255491544958013680[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3255491544958013680[3] = dt*state[12] + state[3];
   out_3255491544958013680[4] = dt*state[13] + state[4];
   out_3255491544958013680[5] = dt*state[14] + state[5];
   out_3255491544958013680[6] = state[6];
   out_3255491544958013680[7] = state[7];
   out_3255491544958013680[8] = state[8];
   out_3255491544958013680[9] = state[9];
   out_3255491544958013680[10] = state[10];
   out_3255491544958013680[11] = state[11];
   out_3255491544958013680[12] = state[12];
   out_3255491544958013680[13] = state[13];
   out_3255491544958013680[14] = state[14];
   out_3255491544958013680[15] = state[15];
   out_3255491544958013680[16] = state[16];
   out_3255491544958013680[17] = state[17];
}
void F_fun(double *state, double dt, double *out_72615651512449831) {
   out_72615651512449831[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_72615651512449831[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_72615651512449831[2] = 0;
   out_72615651512449831[3] = 0;
   out_72615651512449831[4] = 0;
   out_72615651512449831[5] = 0;
   out_72615651512449831[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_72615651512449831[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_72615651512449831[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_72615651512449831[9] = 0;
   out_72615651512449831[10] = 0;
   out_72615651512449831[11] = 0;
   out_72615651512449831[12] = 0;
   out_72615651512449831[13] = 0;
   out_72615651512449831[14] = 0;
   out_72615651512449831[15] = 0;
   out_72615651512449831[16] = 0;
   out_72615651512449831[17] = 0;
   out_72615651512449831[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_72615651512449831[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_72615651512449831[20] = 0;
   out_72615651512449831[21] = 0;
   out_72615651512449831[22] = 0;
   out_72615651512449831[23] = 0;
   out_72615651512449831[24] = 0;
   out_72615651512449831[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_72615651512449831[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_72615651512449831[27] = 0;
   out_72615651512449831[28] = 0;
   out_72615651512449831[29] = 0;
   out_72615651512449831[30] = 0;
   out_72615651512449831[31] = 0;
   out_72615651512449831[32] = 0;
   out_72615651512449831[33] = 0;
   out_72615651512449831[34] = 0;
   out_72615651512449831[35] = 0;
   out_72615651512449831[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_72615651512449831[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_72615651512449831[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_72615651512449831[39] = 0;
   out_72615651512449831[40] = 0;
   out_72615651512449831[41] = 0;
   out_72615651512449831[42] = 0;
   out_72615651512449831[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_72615651512449831[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_72615651512449831[45] = 0;
   out_72615651512449831[46] = 0;
   out_72615651512449831[47] = 0;
   out_72615651512449831[48] = 0;
   out_72615651512449831[49] = 0;
   out_72615651512449831[50] = 0;
   out_72615651512449831[51] = 0;
   out_72615651512449831[52] = 0;
   out_72615651512449831[53] = 0;
   out_72615651512449831[54] = 0;
   out_72615651512449831[55] = 0;
   out_72615651512449831[56] = 0;
   out_72615651512449831[57] = 1;
   out_72615651512449831[58] = 0;
   out_72615651512449831[59] = 0;
   out_72615651512449831[60] = 0;
   out_72615651512449831[61] = 0;
   out_72615651512449831[62] = 0;
   out_72615651512449831[63] = 0;
   out_72615651512449831[64] = 0;
   out_72615651512449831[65] = 0;
   out_72615651512449831[66] = dt;
   out_72615651512449831[67] = 0;
   out_72615651512449831[68] = 0;
   out_72615651512449831[69] = 0;
   out_72615651512449831[70] = 0;
   out_72615651512449831[71] = 0;
   out_72615651512449831[72] = 0;
   out_72615651512449831[73] = 0;
   out_72615651512449831[74] = 0;
   out_72615651512449831[75] = 0;
   out_72615651512449831[76] = 1;
   out_72615651512449831[77] = 0;
   out_72615651512449831[78] = 0;
   out_72615651512449831[79] = 0;
   out_72615651512449831[80] = 0;
   out_72615651512449831[81] = 0;
   out_72615651512449831[82] = 0;
   out_72615651512449831[83] = 0;
   out_72615651512449831[84] = 0;
   out_72615651512449831[85] = dt;
   out_72615651512449831[86] = 0;
   out_72615651512449831[87] = 0;
   out_72615651512449831[88] = 0;
   out_72615651512449831[89] = 0;
   out_72615651512449831[90] = 0;
   out_72615651512449831[91] = 0;
   out_72615651512449831[92] = 0;
   out_72615651512449831[93] = 0;
   out_72615651512449831[94] = 0;
   out_72615651512449831[95] = 1;
   out_72615651512449831[96] = 0;
   out_72615651512449831[97] = 0;
   out_72615651512449831[98] = 0;
   out_72615651512449831[99] = 0;
   out_72615651512449831[100] = 0;
   out_72615651512449831[101] = 0;
   out_72615651512449831[102] = 0;
   out_72615651512449831[103] = 0;
   out_72615651512449831[104] = dt;
   out_72615651512449831[105] = 0;
   out_72615651512449831[106] = 0;
   out_72615651512449831[107] = 0;
   out_72615651512449831[108] = 0;
   out_72615651512449831[109] = 0;
   out_72615651512449831[110] = 0;
   out_72615651512449831[111] = 0;
   out_72615651512449831[112] = 0;
   out_72615651512449831[113] = 0;
   out_72615651512449831[114] = 1;
   out_72615651512449831[115] = 0;
   out_72615651512449831[116] = 0;
   out_72615651512449831[117] = 0;
   out_72615651512449831[118] = 0;
   out_72615651512449831[119] = 0;
   out_72615651512449831[120] = 0;
   out_72615651512449831[121] = 0;
   out_72615651512449831[122] = 0;
   out_72615651512449831[123] = 0;
   out_72615651512449831[124] = 0;
   out_72615651512449831[125] = 0;
   out_72615651512449831[126] = 0;
   out_72615651512449831[127] = 0;
   out_72615651512449831[128] = 0;
   out_72615651512449831[129] = 0;
   out_72615651512449831[130] = 0;
   out_72615651512449831[131] = 0;
   out_72615651512449831[132] = 0;
   out_72615651512449831[133] = 1;
   out_72615651512449831[134] = 0;
   out_72615651512449831[135] = 0;
   out_72615651512449831[136] = 0;
   out_72615651512449831[137] = 0;
   out_72615651512449831[138] = 0;
   out_72615651512449831[139] = 0;
   out_72615651512449831[140] = 0;
   out_72615651512449831[141] = 0;
   out_72615651512449831[142] = 0;
   out_72615651512449831[143] = 0;
   out_72615651512449831[144] = 0;
   out_72615651512449831[145] = 0;
   out_72615651512449831[146] = 0;
   out_72615651512449831[147] = 0;
   out_72615651512449831[148] = 0;
   out_72615651512449831[149] = 0;
   out_72615651512449831[150] = 0;
   out_72615651512449831[151] = 0;
   out_72615651512449831[152] = 1;
   out_72615651512449831[153] = 0;
   out_72615651512449831[154] = 0;
   out_72615651512449831[155] = 0;
   out_72615651512449831[156] = 0;
   out_72615651512449831[157] = 0;
   out_72615651512449831[158] = 0;
   out_72615651512449831[159] = 0;
   out_72615651512449831[160] = 0;
   out_72615651512449831[161] = 0;
   out_72615651512449831[162] = 0;
   out_72615651512449831[163] = 0;
   out_72615651512449831[164] = 0;
   out_72615651512449831[165] = 0;
   out_72615651512449831[166] = 0;
   out_72615651512449831[167] = 0;
   out_72615651512449831[168] = 0;
   out_72615651512449831[169] = 0;
   out_72615651512449831[170] = 0;
   out_72615651512449831[171] = 1;
   out_72615651512449831[172] = 0;
   out_72615651512449831[173] = 0;
   out_72615651512449831[174] = 0;
   out_72615651512449831[175] = 0;
   out_72615651512449831[176] = 0;
   out_72615651512449831[177] = 0;
   out_72615651512449831[178] = 0;
   out_72615651512449831[179] = 0;
   out_72615651512449831[180] = 0;
   out_72615651512449831[181] = 0;
   out_72615651512449831[182] = 0;
   out_72615651512449831[183] = 0;
   out_72615651512449831[184] = 0;
   out_72615651512449831[185] = 0;
   out_72615651512449831[186] = 0;
   out_72615651512449831[187] = 0;
   out_72615651512449831[188] = 0;
   out_72615651512449831[189] = 0;
   out_72615651512449831[190] = 1;
   out_72615651512449831[191] = 0;
   out_72615651512449831[192] = 0;
   out_72615651512449831[193] = 0;
   out_72615651512449831[194] = 0;
   out_72615651512449831[195] = 0;
   out_72615651512449831[196] = 0;
   out_72615651512449831[197] = 0;
   out_72615651512449831[198] = 0;
   out_72615651512449831[199] = 0;
   out_72615651512449831[200] = 0;
   out_72615651512449831[201] = 0;
   out_72615651512449831[202] = 0;
   out_72615651512449831[203] = 0;
   out_72615651512449831[204] = 0;
   out_72615651512449831[205] = 0;
   out_72615651512449831[206] = 0;
   out_72615651512449831[207] = 0;
   out_72615651512449831[208] = 0;
   out_72615651512449831[209] = 1;
   out_72615651512449831[210] = 0;
   out_72615651512449831[211] = 0;
   out_72615651512449831[212] = 0;
   out_72615651512449831[213] = 0;
   out_72615651512449831[214] = 0;
   out_72615651512449831[215] = 0;
   out_72615651512449831[216] = 0;
   out_72615651512449831[217] = 0;
   out_72615651512449831[218] = 0;
   out_72615651512449831[219] = 0;
   out_72615651512449831[220] = 0;
   out_72615651512449831[221] = 0;
   out_72615651512449831[222] = 0;
   out_72615651512449831[223] = 0;
   out_72615651512449831[224] = 0;
   out_72615651512449831[225] = 0;
   out_72615651512449831[226] = 0;
   out_72615651512449831[227] = 0;
   out_72615651512449831[228] = 1;
   out_72615651512449831[229] = 0;
   out_72615651512449831[230] = 0;
   out_72615651512449831[231] = 0;
   out_72615651512449831[232] = 0;
   out_72615651512449831[233] = 0;
   out_72615651512449831[234] = 0;
   out_72615651512449831[235] = 0;
   out_72615651512449831[236] = 0;
   out_72615651512449831[237] = 0;
   out_72615651512449831[238] = 0;
   out_72615651512449831[239] = 0;
   out_72615651512449831[240] = 0;
   out_72615651512449831[241] = 0;
   out_72615651512449831[242] = 0;
   out_72615651512449831[243] = 0;
   out_72615651512449831[244] = 0;
   out_72615651512449831[245] = 0;
   out_72615651512449831[246] = 0;
   out_72615651512449831[247] = 1;
   out_72615651512449831[248] = 0;
   out_72615651512449831[249] = 0;
   out_72615651512449831[250] = 0;
   out_72615651512449831[251] = 0;
   out_72615651512449831[252] = 0;
   out_72615651512449831[253] = 0;
   out_72615651512449831[254] = 0;
   out_72615651512449831[255] = 0;
   out_72615651512449831[256] = 0;
   out_72615651512449831[257] = 0;
   out_72615651512449831[258] = 0;
   out_72615651512449831[259] = 0;
   out_72615651512449831[260] = 0;
   out_72615651512449831[261] = 0;
   out_72615651512449831[262] = 0;
   out_72615651512449831[263] = 0;
   out_72615651512449831[264] = 0;
   out_72615651512449831[265] = 0;
   out_72615651512449831[266] = 1;
   out_72615651512449831[267] = 0;
   out_72615651512449831[268] = 0;
   out_72615651512449831[269] = 0;
   out_72615651512449831[270] = 0;
   out_72615651512449831[271] = 0;
   out_72615651512449831[272] = 0;
   out_72615651512449831[273] = 0;
   out_72615651512449831[274] = 0;
   out_72615651512449831[275] = 0;
   out_72615651512449831[276] = 0;
   out_72615651512449831[277] = 0;
   out_72615651512449831[278] = 0;
   out_72615651512449831[279] = 0;
   out_72615651512449831[280] = 0;
   out_72615651512449831[281] = 0;
   out_72615651512449831[282] = 0;
   out_72615651512449831[283] = 0;
   out_72615651512449831[284] = 0;
   out_72615651512449831[285] = 1;
   out_72615651512449831[286] = 0;
   out_72615651512449831[287] = 0;
   out_72615651512449831[288] = 0;
   out_72615651512449831[289] = 0;
   out_72615651512449831[290] = 0;
   out_72615651512449831[291] = 0;
   out_72615651512449831[292] = 0;
   out_72615651512449831[293] = 0;
   out_72615651512449831[294] = 0;
   out_72615651512449831[295] = 0;
   out_72615651512449831[296] = 0;
   out_72615651512449831[297] = 0;
   out_72615651512449831[298] = 0;
   out_72615651512449831[299] = 0;
   out_72615651512449831[300] = 0;
   out_72615651512449831[301] = 0;
   out_72615651512449831[302] = 0;
   out_72615651512449831[303] = 0;
   out_72615651512449831[304] = 1;
   out_72615651512449831[305] = 0;
   out_72615651512449831[306] = 0;
   out_72615651512449831[307] = 0;
   out_72615651512449831[308] = 0;
   out_72615651512449831[309] = 0;
   out_72615651512449831[310] = 0;
   out_72615651512449831[311] = 0;
   out_72615651512449831[312] = 0;
   out_72615651512449831[313] = 0;
   out_72615651512449831[314] = 0;
   out_72615651512449831[315] = 0;
   out_72615651512449831[316] = 0;
   out_72615651512449831[317] = 0;
   out_72615651512449831[318] = 0;
   out_72615651512449831[319] = 0;
   out_72615651512449831[320] = 0;
   out_72615651512449831[321] = 0;
   out_72615651512449831[322] = 0;
   out_72615651512449831[323] = 1;
}
void h_4(double *state, double *unused, double *out_5118220219965623011) {
   out_5118220219965623011[0] = state[6] + state[9];
   out_5118220219965623011[1] = state[7] + state[10];
   out_5118220219965623011[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5483916111262222662) {
   out_5483916111262222662[0] = 0;
   out_5483916111262222662[1] = 0;
   out_5483916111262222662[2] = 0;
   out_5483916111262222662[3] = 0;
   out_5483916111262222662[4] = 0;
   out_5483916111262222662[5] = 0;
   out_5483916111262222662[6] = 1;
   out_5483916111262222662[7] = 0;
   out_5483916111262222662[8] = 0;
   out_5483916111262222662[9] = 1;
   out_5483916111262222662[10] = 0;
   out_5483916111262222662[11] = 0;
   out_5483916111262222662[12] = 0;
   out_5483916111262222662[13] = 0;
   out_5483916111262222662[14] = 0;
   out_5483916111262222662[15] = 0;
   out_5483916111262222662[16] = 0;
   out_5483916111262222662[17] = 0;
   out_5483916111262222662[18] = 0;
   out_5483916111262222662[19] = 0;
   out_5483916111262222662[20] = 0;
   out_5483916111262222662[21] = 0;
   out_5483916111262222662[22] = 0;
   out_5483916111262222662[23] = 0;
   out_5483916111262222662[24] = 0;
   out_5483916111262222662[25] = 1;
   out_5483916111262222662[26] = 0;
   out_5483916111262222662[27] = 0;
   out_5483916111262222662[28] = 1;
   out_5483916111262222662[29] = 0;
   out_5483916111262222662[30] = 0;
   out_5483916111262222662[31] = 0;
   out_5483916111262222662[32] = 0;
   out_5483916111262222662[33] = 0;
   out_5483916111262222662[34] = 0;
   out_5483916111262222662[35] = 0;
   out_5483916111262222662[36] = 0;
   out_5483916111262222662[37] = 0;
   out_5483916111262222662[38] = 0;
   out_5483916111262222662[39] = 0;
   out_5483916111262222662[40] = 0;
   out_5483916111262222662[41] = 0;
   out_5483916111262222662[42] = 0;
   out_5483916111262222662[43] = 0;
   out_5483916111262222662[44] = 1;
   out_5483916111262222662[45] = 0;
   out_5483916111262222662[46] = 0;
   out_5483916111262222662[47] = 1;
   out_5483916111262222662[48] = 0;
   out_5483916111262222662[49] = 0;
   out_5483916111262222662[50] = 0;
   out_5483916111262222662[51] = 0;
   out_5483916111262222662[52] = 0;
   out_5483916111262222662[53] = 0;
}
void h_10(double *state, double *unused, double *out_3610281455795856596) {
   out_3610281455795856596[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3610281455795856596[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3610281455795856596[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4454049598256953673) {
   out_4454049598256953673[0] = 0;
   out_4454049598256953673[1] = 9.8100000000000005*cos(state[1]);
   out_4454049598256953673[2] = 0;
   out_4454049598256953673[3] = 0;
   out_4454049598256953673[4] = -state[8];
   out_4454049598256953673[5] = state[7];
   out_4454049598256953673[6] = 0;
   out_4454049598256953673[7] = state[5];
   out_4454049598256953673[8] = -state[4];
   out_4454049598256953673[9] = 0;
   out_4454049598256953673[10] = 0;
   out_4454049598256953673[11] = 0;
   out_4454049598256953673[12] = 1;
   out_4454049598256953673[13] = 0;
   out_4454049598256953673[14] = 0;
   out_4454049598256953673[15] = 1;
   out_4454049598256953673[16] = 0;
   out_4454049598256953673[17] = 0;
   out_4454049598256953673[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4454049598256953673[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4454049598256953673[20] = 0;
   out_4454049598256953673[21] = state[8];
   out_4454049598256953673[22] = 0;
   out_4454049598256953673[23] = -state[6];
   out_4454049598256953673[24] = -state[5];
   out_4454049598256953673[25] = 0;
   out_4454049598256953673[26] = state[3];
   out_4454049598256953673[27] = 0;
   out_4454049598256953673[28] = 0;
   out_4454049598256953673[29] = 0;
   out_4454049598256953673[30] = 0;
   out_4454049598256953673[31] = 1;
   out_4454049598256953673[32] = 0;
   out_4454049598256953673[33] = 0;
   out_4454049598256953673[34] = 1;
   out_4454049598256953673[35] = 0;
   out_4454049598256953673[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4454049598256953673[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4454049598256953673[38] = 0;
   out_4454049598256953673[39] = -state[7];
   out_4454049598256953673[40] = state[6];
   out_4454049598256953673[41] = 0;
   out_4454049598256953673[42] = state[4];
   out_4454049598256953673[43] = -state[3];
   out_4454049598256953673[44] = 0;
   out_4454049598256953673[45] = 0;
   out_4454049598256953673[46] = 0;
   out_4454049598256953673[47] = 0;
   out_4454049598256953673[48] = 0;
   out_4454049598256953673[49] = 0;
   out_4454049598256953673[50] = 1;
   out_4454049598256953673[51] = 0;
   out_4454049598256953673[52] = 0;
   out_4454049598256953673[53] = 1;
}
void h_13(double *state, double *unused, double *out_4072338729150022115) {
   out_4072338729150022115[0] = state[3];
   out_4072338729150022115[1] = state[4];
   out_4072338729150022115[2] = state[5];
}
void H_13(double *state, double *unused, double *out_9129072499144804930) {
   out_9129072499144804930[0] = 0;
   out_9129072499144804930[1] = 0;
   out_9129072499144804930[2] = 0;
   out_9129072499144804930[3] = 1;
   out_9129072499144804930[4] = 0;
   out_9129072499144804930[5] = 0;
   out_9129072499144804930[6] = 0;
   out_9129072499144804930[7] = 0;
   out_9129072499144804930[8] = 0;
   out_9129072499144804930[9] = 0;
   out_9129072499144804930[10] = 0;
   out_9129072499144804930[11] = 0;
   out_9129072499144804930[12] = 0;
   out_9129072499144804930[13] = 0;
   out_9129072499144804930[14] = 0;
   out_9129072499144804930[15] = 0;
   out_9129072499144804930[16] = 0;
   out_9129072499144804930[17] = 0;
   out_9129072499144804930[18] = 0;
   out_9129072499144804930[19] = 0;
   out_9129072499144804930[20] = 0;
   out_9129072499144804930[21] = 0;
   out_9129072499144804930[22] = 1;
   out_9129072499144804930[23] = 0;
   out_9129072499144804930[24] = 0;
   out_9129072499144804930[25] = 0;
   out_9129072499144804930[26] = 0;
   out_9129072499144804930[27] = 0;
   out_9129072499144804930[28] = 0;
   out_9129072499144804930[29] = 0;
   out_9129072499144804930[30] = 0;
   out_9129072499144804930[31] = 0;
   out_9129072499144804930[32] = 0;
   out_9129072499144804930[33] = 0;
   out_9129072499144804930[34] = 0;
   out_9129072499144804930[35] = 0;
   out_9129072499144804930[36] = 0;
   out_9129072499144804930[37] = 0;
   out_9129072499144804930[38] = 0;
   out_9129072499144804930[39] = 0;
   out_9129072499144804930[40] = 0;
   out_9129072499144804930[41] = 1;
   out_9129072499144804930[42] = 0;
   out_9129072499144804930[43] = 0;
   out_9129072499144804930[44] = 0;
   out_9129072499144804930[45] = 0;
   out_9129072499144804930[46] = 0;
   out_9129072499144804930[47] = 0;
   out_9129072499144804930[48] = 0;
   out_9129072499144804930[49] = 0;
   out_9129072499144804930[50] = 0;
   out_9129072499144804930[51] = 0;
   out_9129072499144804930[52] = 0;
   out_9129072499144804930[53] = 0;
}
void h_14(double *state, double *unused, double *out_8765973181652125668) {
   out_8765973181652125668[0] = state[6];
   out_8765973181652125668[1] = state[7];
   out_8765973181652125668[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8566704543557594958) {
   out_8566704543557594958[0] = 0;
   out_8566704543557594958[1] = 0;
   out_8566704543557594958[2] = 0;
   out_8566704543557594958[3] = 0;
   out_8566704543557594958[4] = 0;
   out_8566704543557594958[5] = 0;
   out_8566704543557594958[6] = 1;
   out_8566704543557594958[7] = 0;
   out_8566704543557594958[8] = 0;
   out_8566704543557594958[9] = 0;
   out_8566704543557594958[10] = 0;
   out_8566704543557594958[11] = 0;
   out_8566704543557594958[12] = 0;
   out_8566704543557594958[13] = 0;
   out_8566704543557594958[14] = 0;
   out_8566704543557594958[15] = 0;
   out_8566704543557594958[16] = 0;
   out_8566704543557594958[17] = 0;
   out_8566704543557594958[18] = 0;
   out_8566704543557594958[19] = 0;
   out_8566704543557594958[20] = 0;
   out_8566704543557594958[21] = 0;
   out_8566704543557594958[22] = 0;
   out_8566704543557594958[23] = 0;
   out_8566704543557594958[24] = 0;
   out_8566704543557594958[25] = 1;
   out_8566704543557594958[26] = 0;
   out_8566704543557594958[27] = 0;
   out_8566704543557594958[28] = 0;
   out_8566704543557594958[29] = 0;
   out_8566704543557594958[30] = 0;
   out_8566704543557594958[31] = 0;
   out_8566704543557594958[32] = 0;
   out_8566704543557594958[33] = 0;
   out_8566704543557594958[34] = 0;
   out_8566704543557594958[35] = 0;
   out_8566704543557594958[36] = 0;
   out_8566704543557594958[37] = 0;
   out_8566704543557594958[38] = 0;
   out_8566704543557594958[39] = 0;
   out_8566704543557594958[40] = 0;
   out_8566704543557594958[41] = 0;
   out_8566704543557594958[42] = 0;
   out_8566704543557594958[43] = 0;
   out_8566704543557594958[44] = 1;
   out_8566704543557594958[45] = 0;
   out_8566704543557594958[46] = 0;
   out_8566704543557594958[47] = 0;
   out_8566704543557594958[48] = 0;
   out_8566704543557594958[49] = 0;
   out_8566704543557594958[50] = 0;
   out_8566704543557594958[51] = 0;
   out_8566704543557594958[52] = 0;
   out_8566704543557594958[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_5742780909134961661) {
  err_fun(nom_x, delta_x, out_5742780909134961661);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_90707900821457158) {
  inv_err_fun(nom_x, true_x, out_90707900821457158);
}
void pose_H_mod_fun(double *state, double *out_9191020752603421382) {
  H_mod_fun(state, out_9191020752603421382);
}
void pose_f_fun(double *state, double dt, double *out_3255491544958013680) {
  f_fun(state,  dt, out_3255491544958013680);
}
void pose_F_fun(double *state, double dt, double *out_72615651512449831) {
  F_fun(state,  dt, out_72615651512449831);
}
void pose_h_4(double *state, double *unused, double *out_5118220219965623011) {
  h_4(state, unused, out_5118220219965623011);
}
void pose_H_4(double *state, double *unused, double *out_5483916111262222662) {
  H_4(state, unused, out_5483916111262222662);
}
void pose_h_10(double *state, double *unused, double *out_3610281455795856596) {
  h_10(state, unused, out_3610281455795856596);
}
void pose_H_10(double *state, double *unused, double *out_4454049598256953673) {
  H_10(state, unused, out_4454049598256953673);
}
void pose_h_13(double *state, double *unused, double *out_4072338729150022115) {
  h_13(state, unused, out_4072338729150022115);
}
void pose_H_13(double *state, double *unused, double *out_9129072499144804930) {
  H_13(state, unused, out_9129072499144804930);
}
void pose_h_14(double *state, double *unused, double *out_8765973181652125668) {
  h_14(state, unused, out_8765973181652125668);
}
void pose_H_14(double *state, double *unused, double *out_8566704543557594958) {
  H_14(state, unused, out_8566704543557594958);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
