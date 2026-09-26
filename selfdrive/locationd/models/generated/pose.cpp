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
void err_fun(double *nom_x, double *delta_x, double *out_8106364195173448064) {
   out_8106364195173448064[0] = delta_x[0] + nom_x[0];
   out_8106364195173448064[1] = delta_x[1] + nom_x[1];
   out_8106364195173448064[2] = delta_x[2] + nom_x[2];
   out_8106364195173448064[3] = delta_x[3] + nom_x[3];
   out_8106364195173448064[4] = delta_x[4] + nom_x[4];
   out_8106364195173448064[5] = delta_x[5] + nom_x[5];
   out_8106364195173448064[6] = delta_x[6] + nom_x[6];
   out_8106364195173448064[7] = delta_x[7] + nom_x[7];
   out_8106364195173448064[8] = delta_x[8] + nom_x[8];
   out_8106364195173448064[9] = delta_x[9] + nom_x[9];
   out_8106364195173448064[10] = delta_x[10] + nom_x[10];
   out_8106364195173448064[11] = delta_x[11] + nom_x[11];
   out_8106364195173448064[12] = delta_x[12] + nom_x[12];
   out_8106364195173448064[13] = delta_x[13] + nom_x[13];
   out_8106364195173448064[14] = delta_x[14] + nom_x[14];
   out_8106364195173448064[15] = delta_x[15] + nom_x[15];
   out_8106364195173448064[16] = delta_x[16] + nom_x[16];
   out_8106364195173448064[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1999187208436778161) {
   out_1999187208436778161[0] = -nom_x[0] + true_x[0];
   out_1999187208436778161[1] = -nom_x[1] + true_x[1];
   out_1999187208436778161[2] = -nom_x[2] + true_x[2];
   out_1999187208436778161[3] = -nom_x[3] + true_x[3];
   out_1999187208436778161[4] = -nom_x[4] + true_x[4];
   out_1999187208436778161[5] = -nom_x[5] + true_x[5];
   out_1999187208436778161[6] = -nom_x[6] + true_x[6];
   out_1999187208436778161[7] = -nom_x[7] + true_x[7];
   out_1999187208436778161[8] = -nom_x[8] + true_x[8];
   out_1999187208436778161[9] = -nom_x[9] + true_x[9];
   out_1999187208436778161[10] = -nom_x[10] + true_x[10];
   out_1999187208436778161[11] = -nom_x[11] + true_x[11];
   out_1999187208436778161[12] = -nom_x[12] + true_x[12];
   out_1999187208436778161[13] = -nom_x[13] + true_x[13];
   out_1999187208436778161[14] = -nom_x[14] + true_x[14];
   out_1999187208436778161[15] = -nom_x[15] + true_x[15];
   out_1999187208436778161[16] = -nom_x[16] + true_x[16];
   out_1999187208436778161[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1403646606661394698) {
   out_1403646606661394698[0] = 1.0;
   out_1403646606661394698[1] = 0.0;
   out_1403646606661394698[2] = 0.0;
   out_1403646606661394698[3] = 0.0;
   out_1403646606661394698[4] = 0.0;
   out_1403646606661394698[5] = 0.0;
   out_1403646606661394698[6] = 0.0;
   out_1403646606661394698[7] = 0.0;
   out_1403646606661394698[8] = 0.0;
   out_1403646606661394698[9] = 0.0;
   out_1403646606661394698[10] = 0.0;
   out_1403646606661394698[11] = 0.0;
   out_1403646606661394698[12] = 0.0;
   out_1403646606661394698[13] = 0.0;
   out_1403646606661394698[14] = 0.0;
   out_1403646606661394698[15] = 0.0;
   out_1403646606661394698[16] = 0.0;
   out_1403646606661394698[17] = 0.0;
   out_1403646606661394698[18] = 0.0;
   out_1403646606661394698[19] = 1.0;
   out_1403646606661394698[20] = 0.0;
   out_1403646606661394698[21] = 0.0;
   out_1403646606661394698[22] = 0.0;
   out_1403646606661394698[23] = 0.0;
   out_1403646606661394698[24] = 0.0;
   out_1403646606661394698[25] = 0.0;
   out_1403646606661394698[26] = 0.0;
   out_1403646606661394698[27] = 0.0;
   out_1403646606661394698[28] = 0.0;
   out_1403646606661394698[29] = 0.0;
   out_1403646606661394698[30] = 0.0;
   out_1403646606661394698[31] = 0.0;
   out_1403646606661394698[32] = 0.0;
   out_1403646606661394698[33] = 0.0;
   out_1403646606661394698[34] = 0.0;
   out_1403646606661394698[35] = 0.0;
   out_1403646606661394698[36] = 0.0;
   out_1403646606661394698[37] = 0.0;
   out_1403646606661394698[38] = 1.0;
   out_1403646606661394698[39] = 0.0;
   out_1403646606661394698[40] = 0.0;
   out_1403646606661394698[41] = 0.0;
   out_1403646606661394698[42] = 0.0;
   out_1403646606661394698[43] = 0.0;
   out_1403646606661394698[44] = 0.0;
   out_1403646606661394698[45] = 0.0;
   out_1403646606661394698[46] = 0.0;
   out_1403646606661394698[47] = 0.0;
   out_1403646606661394698[48] = 0.0;
   out_1403646606661394698[49] = 0.0;
   out_1403646606661394698[50] = 0.0;
   out_1403646606661394698[51] = 0.0;
   out_1403646606661394698[52] = 0.0;
   out_1403646606661394698[53] = 0.0;
   out_1403646606661394698[54] = 0.0;
   out_1403646606661394698[55] = 0.0;
   out_1403646606661394698[56] = 0.0;
   out_1403646606661394698[57] = 1.0;
   out_1403646606661394698[58] = 0.0;
   out_1403646606661394698[59] = 0.0;
   out_1403646606661394698[60] = 0.0;
   out_1403646606661394698[61] = 0.0;
   out_1403646606661394698[62] = 0.0;
   out_1403646606661394698[63] = 0.0;
   out_1403646606661394698[64] = 0.0;
   out_1403646606661394698[65] = 0.0;
   out_1403646606661394698[66] = 0.0;
   out_1403646606661394698[67] = 0.0;
   out_1403646606661394698[68] = 0.0;
   out_1403646606661394698[69] = 0.0;
   out_1403646606661394698[70] = 0.0;
   out_1403646606661394698[71] = 0.0;
   out_1403646606661394698[72] = 0.0;
   out_1403646606661394698[73] = 0.0;
   out_1403646606661394698[74] = 0.0;
   out_1403646606661394698[75] = 0.0;
   out_1403646606661394698[76] = 1.0;
   out_1403646606661394698[77] = 0.0;
   out_1403646606661394698[78] = 0.0;
   out_1403646606661394698[79] = 0.0;
   out_1403646606661394698[80] = 0.0;
   out_1403646606661394698[81] = 0.0;
   out_1403646606661394698[82] = 0.0;
   out_1403646606661394698[83] = 0.0;
   out_1403646606661394698[84] = 0.0;
   out_1403646606661394698[85] = 0.0;
   out_1403646606661394698[86] = 0.0;
   out_1403646606661394698[87] = 0.0;
   out_1403646606661394698[88] = 0.0;
   out_1403646606661394698[89] = 0.0;
   out_1403646606661394698[90] = 0.0;
   out_1403646606661394698[91] = 0.0;
   out_1403646606661394698[92] = 0.0;
   out_1403646606661394698[93] = 0.0;
   out_1403646606661394698[94] = 0.0;
   out_1403646606661394698[95] = 1.0;
   out_1403646606661394698[96] = 0.0;
   out_1403646606661394698[97] = 0.0;
   out_1403646606661394698[98] = 0.0;
   out_1403646606661394698[99] = 0.0;
   out_1403646606661394698[100] = 0.0;
   out_1403646606661394698[101] = 0.0;
   out_1403646606661394698[102] = 0.0;
   out_1403646606661394698[103] = 0.0;
   out_1403646606661394698[104] = 0.0;
   out_1403646606661394698[105] = 0.0;
   out_1403646606661394698[106] = 0.0;
   out_1403646606661394698[107] = 0.0;
   out_1403646606661394698[108] = 0.0;
   out_1403646606661394698[109] = 0.0;
   out_1403646606661394698[110] = 0.0;
   out_1403646606661394698[111] = 0.0;
   out_1403646606661394698[112] = 0.0;
   out_1403646606661394698[113] = 0.0;
   out_1403646606661394698[114] = 1.0;
   out_1403646606661394698[115] = 0.0;
   out_1403646606661394698[116] = 0.0;
   out_1403646606661394698[117] = 0.0;
   out_1403646606661394698[118] = 0.0;
   out_1403646606661394698[119] = 0.0;
   out_1403646606661394698[120] = 0.0;
   out_1403646606661394698[121] = 0.0;
   out_1403646606661394698[122] = 0.0;
   out_1403646606661394698[123] = 0.0;
   out_1403646606661394698[124] = 0.0;
   out_1403646606661394698[125] = 0.0;
   out_1403646606661394698[126] = 0.0;
   out_1403646606661394698[127] = 0.0;
   out_1403646606661394698[128] = 0.0;
   out_1403646606661394698[129] = 0.0;
   out_1403646606661394698[130] = 0.0;
   out_1403646606661394698[131] = 0.0;
   out_1403646606661394698[132] = 0.0;
   out_1403646606661394698[133] = 1.0;
   out_1403646606661394698[134] = 0.0;
   out_1403646606661394698[135] = 0.0;
   out_1403646606661394698[136] = 0.0;
   out_1403646606661394698[137] = 0.0;
   out_1403646606661394698[138] = 0.0;
   out_1403646606661394698[139] = 0.0;
   out_1403646606661394698[140] = 0.0;
   out_1403646606661394698[141] = 0.0;
   out_1403646606661394698[142] = 0.0;
   out_1403646606661394698[143] = 0.0;
   out_1403646606661394698[144] = 0.0;
   out_1403646606661394698[145] = 0.0;
   out_1403646606661394698[146] = 0.0;
   out_1403646606661394698[147] = 0.0;
   out_1403646606661394698[148] = 0.0;
   out_1403646606661394698[149] = 0.0;
   out_1403646606661394698[150] = 0.0;
   out_1403646606661394698[151] = 0.0;
   out_1403646606661394698[152] = 1.0;
   out_1403646606661394698[153] = 0.0;
   out_1403646606661394698[154] = 0.0;
   out_1403646606661394698[155] = 0.0;
   out_1403646606661394698[156] = 0.0;
   out_1403646606661394698[157] = 0.0;
   out_1403646606661394698[158] = 0.0;
   out_1403646606661394698[159] = 0.0;
   out_1403646606661394698[160] = 0.0;
   out_1403646606661394698[161] = 0.0;
   out_1403646606661394698[162] = 0.0;
   out_1403646606661394698[163] = 0.0;
   out_1403646606661394698[164] = 0.0;
   out_1403646606661394698[165] = 0.0;
   out_1403646606661394698[166] = 0.0;
   out_1403646606661394698[167] = 0.0;
   out_1403646606661394698[168] = 0.0;
   out_1403646606661394698[169] = 0.0;
   out_1403646606661394698[170] = 0.0;
   out_1403646606661394698[171] = 1.0;
   out_1403646606661394698[172] = 0.0;
   out_1403646606661394698[173] = 0.0;
   out_1403646606661394698[174] = 0.0;
   out_1403646606661394698[175] = 0.0;
   out_1403646606661394698[176] = 0.0;
   out_1403646606661394698[177] = 0.0;
   out_1403646606661394698[178] = 0.0;
   out_1403646606661394698[179] = 0.0;
   out_1403646606661394698[180] = 0.0;
   out_1403646606661394698[181] = 0.0;
   out_1403646606661394698[182] = 0.0;
   out_1403646606661394698[183] = 0.0;
   out_1403646606661394698[184] = 0.0;
   out_1403646606661394698[185] = 0.0;
   out_1403646606661394698[186] = 0.0;
   out_1403646606661394698[187] = 0.0;
   out_1403646606661394698[188] = 0.0;
   out_1403646606661394698[189] = 0.0;
   out_1403646606661394698[190] = 1.0;
   out_1403646606661394698[191] = 0.0;
   out_1403646606661394698[192] = 0.0;
   out_1403646606661394698[193] = 0.0;
   out_1403646606661394698[194] = 0.0;
   out_1403646606661394698[195] = 0.0;
   out_1403646606661394698[196] = 0.0;
   out_1403646606661394698[197] = 0.0;
   out_1403646606661394698[198] = 0.0;
   out_1403646606661394698[199] = 0.0;
   out_1403646606661394698[200] = 0.0;
   out_1403646606661394698[201] = 0.0;
   out_1403646606661394698[202] = 0.0;
   out_1403646606661394698[203] = 0.0;
   out_1403646606661394698[204] = 0.0;
   out_1403646606661394698[205] = 0.0;
   out_1403646606661394698[206] = 0.0;
   out_1403646606661394698[207] = 0.0;
   out_1403646606661394698[208] = 0.0;
   out_1403646606661394698[209] = 1.0;
   out_1403646606661394698[210] = 0.0;
   out_1403646606661394698[211] = 0.0;
   out_1403646606661394698[212] = 0.0;
   out_1403646606661394698[213] = 0.0;
   out_1403646606661394698[214] = 0.0;
   out_1403646606661394698[215] = 0.0;
   out_1403646606661394698[216] = 0.0;
   out_1403646606661394698[217] = 0.0;
   out_1403646606661394698[218] = 0.0;
   out_1403646606661394698[219] = 0.0;
   out_1403646606661394698[220] = 0.0;
   out_1403646606661394698[221] = 0.0;
   out_1403646606661394698[222] = 0.0;
   out_1403646606661394698[223] = 0.0;
   out_1403646606661394698[224] = 0.0;
   out_1403646606661394698[225] = 0.0;
   out_1403646606661394698[226] = 0.0;
   out_1403646606661394698[227] = 0.0;
   out_1403646606661394698[228] = 1.0;
   out_1403646606661394698[229] = 0.0;
   out_1403646606661394698[230] = 0.0;
   out_1403646606661394698[231] = 0.0;
   out_1403646606661394698[232] = 0.0;
   out_1403646606661394698[233] = 0.0;
   out_1403646606661394698[234] = 0.0;
   out_1403646606661394698[235] = 0.0;
   out_1403646606661394698[236] = 0.0;
   out_1403646606661394698[237] = 0.0;
   out_1403646606661394698[238] = 0.0;
   out_1403646606661394698[239] = 0.0;
   out_1403646606661394698[240] = 0.0;
   out_1403646606661394698[241] = 0.0;
   out_1403646606661394698[242] = 0.0;
   out_1403646606661394698[243] = 0.0;
   out_1403646606661394698[244] = 0.0;
   out_1403646606661394698[245] = 0.0;
   out_1403646606661394698[246] = 0.0;
   out_1403646606661394698[247] = 1.0;
   out_1403646606661394698[248] = 0.0;
   out_1403646606661394698[249] = 0.0;
   out_1403646606661394698[250] = 0.0;
   out_1403646606661394698[251] = 0.0;
   out_1403646606661394698[252] = 0.0;
   out_1403646606661394698[253] = 0.0;
   out_1403646606661394698[254] = 0.0;
   out_1403646606661394698[255] = 0.0;
   out_1403646606661394698[256] = 0.0;
   out_1403646606661394698[257] = 0.0;
   out_1403646606661394698[258] = 0.0;
   out_1403646606661394698[259] = 0.0;
   out_1403646606661394698[260] = 0.0;
   out_1403646606661394698[261] = 0.0;
   out_1403646606661394698[262] = 0.0;
   out_1403646606661394698[263] = 0.0;
   out_1403646606661394698[264] = 0.0;
   out_1403646606661394698[265] = 0.0;
   out_1403646606661394698[266] = 1.0;
   out_1403646606661394698[267] = 0.0;
   out_1403646606661394698[268] = 0.0;
   out_1403646606661394698[269] = 0.0;
   out_1403646606661394698[270] = 0.0;
   out_1403646606661394698[271] = 0.0;
   out_1403646606661394698[272] = 0.0;
   out_1403646606661394698[273] = 0.0;
   out_1403646606661394698[274] = 0.0;
   out_1403646606661394698[275] = 0.0;
   out_1403646606661394698[276] = 0.0;
   out_1403646606661394698[277] = 0.0;
   out_1403646606661394698[278] = 0.0;
   out_1403646606661394698[279] = 0.0;
   out_1403646606661394698[280] = 0.0;
   out_1403646606661394698[281] = 0.0;
   out_1403646606661394698[282] = 0.0;
   out_1403646606661394698[283] = 0.0;
   out_1403646606661394698[284] = 0.0;
   out_1403646606661394698[285] = 1.0;
   out_1403646606661394698[286] = 0.0;
   out_1403646606661394698[287] = 0.0;
   out_1403646606661394698[288] = 0.0;
   out_1403646606661394698[289] = 0.0;
   out_1403646606661394698[290] = 0.0;
   out_1403646606661394698[291] = 0.0;
   out_1403646606661394698[292] = 0.0;
   out_1403646606661394698[293] = 0.0;
   out_1403646606661394698[294] = 0.0;
   out_1403646606661394698[295] = 0.0;
   out_1403646606661394698[296] = 0.0;
   out_1403646606661394698[297] = 0.0;
   out_1403646606661394698[298] = 0.0;
   out_1403646606661394698[299] = 0.0;
   out_1403646606661394698[300] = 0.0;
   out_1403646606661394698[301] = 0.0;
   out_1403646606661394698[302] = 0.0;
   out_1403646606661394698[303] = 0.0;
   out_1403646606661394698[304] = 1.0;
   out_1403646606661394698[305] = 0.0;
   out_1403646606661394698[306] = 0.0;
   out_1403646606661394698[307] = 0.0;
   out_1403646606661394698[308] = 0.0;
   out_1403646606661394698[309] = 0.0;
   out_1403646606661394698[310] = 0.0;
   out_1403646606661394698[311] = 0.0;
   out_1403646606661394698[312] = 0.0;
   out_1403646606661394698[313] = 0.0;
   out_1403646606661394698[314] = 0.0;
   out_1403646606661394698[315] = 0.0;
   out_1403646606661394698[316] = 0.0;
   out_1403646606661394698[317] = 0.0;
   out_1403646606661394698[318] = 0.0;
   out_1403646606661394698[319] = 0.0;
   out_1403646606661394698[320] = 0.0;
   out_1403646606661394698[321] = 0.0;
   out_1403646606661394698[322] = 0.0;
   out_1403646606661394698[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6156776826239606646) {
   out_6156776826239606646[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6156776826239606646[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6156776826239606646[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6156776826239606646[3] = dt*state[12] + state[3];
   out_6156776826239606646[4] = dt*state[13] + state[4];
   out_6156776826239606646[5] = dt*state[14] + state[5];
   out_6156776826239606646[6] = state[6];
   out_6156776826239606646[7] = state[7];
   out_6156776826239606646[8] = state[8];
   out_6156776826239606646[9] = state[9];
   out_6156776826239606646[10] = state[10];
   out_6156776826239606646[11] = state[11];
   out_6156776826239606646[12] = state[12];
   out_6156776826239606646[13] = state[13];
   out_6156776826239606646[14] = state[14];
   out_6156776826239606646[15] = state[15];
   out_6156776826239606646[16] = state[16];
   out_6156776826239606646[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8191179680785695057) {
   out_8191179680785695057[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8191179680785695057[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8191179680785695057[2] = 0;
   out_8191179680785695057[3] = 0;
   out_8191179680785695057[4] = 0;
   out_8191179680785695057[5] = 0;
   out_8191179680785695057[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8191179680785695057[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8191179680785695057[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8191179680785695057[9] = 0;
   out_8191179680785695057[10] = 0;
   out_8191179680785695057[11] = 0;
   out_8191179680785695057[12] = 0;
   out_8191179680785695057[13] = 0;
   out_8191179680785695057[14] = 0;
   out_8191179680785695057[15] = 0;
   out_8191179680785695057[16] = 0;
   out_8191179680785695057[17] = 0;
   out_8191179680785695057[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8191179680785695057[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8191179680785695057[20] = 0;
   out_8191179680785695057[21] = 0;
   out_8191179680785695057[22] = 0;
   out_8191179680785695057[23] = 0;
   out_8191179680785695057[24] = 0;
   out_8191179680785695057[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8191179680785695057[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8191179680785695057[27] = 0;
   out_8191179680785695057[28] = 0;
   out_8191179680785695057[29] = 0;
   out_8191179680785695057[30] = 0;
   out_8191179680785695057[31] = 0;
   out_8191179680785695057[32] = 0;
   out_8191179680785695057[33] = 0;
   out_8191179680785695057[34] = 0;
   out_8191179680785695057[35] = 0;
   out_8191179680785695057[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8191179680785695057[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8191179680785695057[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8191179680785695057[39] = 0;
   out_8191179680785695057[40] = 0;
   out_8191179680785695057[41] = 0;
   out_8191179680785695057[42] = 0;
   out_8191179680785695057[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8191179680785695057[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8191179680785695057[45] = 0;
   out_8191179680785695057[46] = 0;
   out_8191179680785695057[47] = 0;
   out_8191179680785695057[48] = 0;
   out_8191179680785695057[49] = 0;
   out_8191179680785695057[50] = 0;
   out_8191179680785695057[51] = 0;
   out_8191179680785695057[52] = 0;
   out_8191179680785695057[53] = 0;
   out_8191179680785695057[54] = 0;
   out_8191179680785695057[55] = 0;
   out_8191179680785695057[56] = 0;
   out_8191179680785695057[57] = 1;
   out_8191179680785695057[58] = 0;
   out_8191179680785695057[59] = 0;
   out_8191179680785695057[60] = 0;
   out_8191179680785695057[61] = 0;
   out_8191179680785695057[62] = 0;
   out_8191179680785695057[63] = 0;
   out_8191179680785695057[64] = 0;
   out_8191179680785695057[65] = 0;
   out_8191179680785695057[66] = dt;
   out_8191179680785695057[67] = 0;
   out_8191179680785695057[68] = 0;
   out_8191179680785695057[69] = 0;
   out_8191179680785695057[70] = 0;
   out_8191179680785695057[71] = 0;
   out_8191179680785695057[72] = 0;
   out_8191179680785695057[73] = 0;
   out_8191179680785695057[74] = 0;
   out_8191179680785695057[75] = 0;
   out_8191179680785695057[76] = 1;
   out_8191179680785695057[77] = 0;
   out_8191179680785695057[78] = 0;
   out_8191179680785695057[79] = 0;
   out_8191179680785695057[80] = 0;
   out_8191179680785695057[81] = 0;
   out_8191179680785695057[82] = 0;
   out_8191179680785695057[83] = 0;
   out_8191179680785695057[84] = 0;
   out_8191179680785695057[85] = dt;
   out_8191179680785695057[86] = 0;
   out_8191179680785695057[87] = 0;
   out_8191179680785695057[88] = 0;
   out_8191179680785695057[89] = 0;
   out_8191179680785695057[90] = 0;
   out_8191179680785695057[91] = 0;
   out_8191179680785695057[92] = 0;
   out_8191179680785695057[93] = 0;
   out_8191179680785695057[94] = 0;
   out_8191179680785695057[95] = 1;
   out_8191179680785695057[96] = 0;
   out_8191179680785695057[97] = 0;
   out_8191179680785695057[98] = 0;
   out_8191179680785695057[99] = 0;
   out_8191179680785695057[100] = 0;
   out_8191179680785695057[101] = 0;
   out_8191179680785695057[102] = 0;
   out_8191179680785695057[103] = 0;
   out_8191179680785695057[104] = dt;
   out_8191179680785695057[105] = 0;
   out_8191179680785695057[106] = 0;
   out_8191179680785695057[107] = 0;
   out_8191179680785695057[108] = 0;
   out_8191179680785695057[109] = 0;
   out_8191179680785695057[110] = 0;
   out_8191179680785695057[111] = 0;
   out_8191179680785695057[112] = 0;
   out_8191179680785695057[113] = 0;
   out_8191179680785695057[114] = 1;
   out_8191179680785695057[115] = 0;
   out_8191179680785695057[116] = 0;
   out_8191179680785695057[117] = 0;
   out_8191179680785695057[118] = 0;
   out_8191179680785695057[119] = 0;
   out_8191179680785695057[120] = 0;
   out_8191179680785695057[121] = 0;
   out_8191179680785695057[122] = 0;
   out_8191179680785695057[123] = 0;
   out_8191179680785695057[124] = 0;
   out_8191179680785695057[125] = 0;
   out_8191179680785695057[126] = 0;
   out_8191179680785695057[127] = 0;
   out_8191179680785695057[128] = 0;
   out_8191179680785695057[129] = 0;
   out_8191179680785695057[130] = 0;
   out_8191179680785695057[131] = 0;
   out_8191179680785695057[132] = 0;
   out_8191179680785695057[133] = 1;
   out_8191179680785695057[134] = 0;
   out_8191179680785695057[135] = 0;
   out_8191179680785695057[136] = 0;
   out_8191179680785695057[137] = 0;
   out_8191179680785695057[138] = 0;
   out_8191179680785695057[139] = 0;
   out_8191179680785695057[140] = 0;
   out_8191179680785695057[141] = 0;
   out_8191179680785695057[142] = 0;
   out_8191179680785695057[143] = 0;
   out_8191179680785695057[144] = 0;
   out_8191179680785695057[145] = 0;
   out_8191179680785695057[146] = 0;
   out_8191179680785695057[147] = 0;
   out_8191179680785695057[148] = 0;
   out_8191179680785695057[149] = 0;
   out_8191179680785695057[150] = 0;
   out_8191179680785695057[151] = 0;
   out_8191179680785695057[152] = 1;
   out_8191179680785695057[153] = 0;
   out_8191179680785695057[154] = 0;
   out_8191179680785695057[155] = 0;
   out_8191179680785695057[156] = 0;
   out_8191179680785695057[157] = 0;
   out_8191179680785695057[158] = 0;
   out_8191179680785695057[159] = 0;
   out_8191179680785695057[160] = 0;
   out_8191179680785695057[161] = 0;
   out_8191179680785695057[162] = 0;
   out_8191179680785695057[163] = 0;
   out_8191179680785695057[164] = 0;
   out_8191179680785695057[165] = 0;
   out_8191179680785695057[166] = 0;
   out_8191179680785695057[167] = 0;
   out_8191179680785695057[168] = 0;
   out_8191179680785695057[169] = 0;
   out_8191179680785695057[170] = 0;
   out_8191179680785695057[171] = 1;
   out_8191179680785695057[172] = 0;
   out_8191179680785695057[173] = 0;
   out_8191179680785695057[174] = 0;
   out_8191179680785695057[175] = 0;
   out_8191179680785695057[176] = 0;
   out_8191179680785695057[177] = 0;
   out_8191179680785695057[178] = 0;
   out_8191179680785695057[179] = 0;
   out_8191179680785695057[180] = 0;
   out_8191179680785695057[181] = 0;
   out_8191179680785695057[182] = 0;
   out_8191179680785695057[183] = 0;
   out_8191179680785695057[184] = 0;
   out_8191179680785695057[185] = 0;
   out_8191179680785695057[186] = 0;
   out_8191179680785695057[187] = 0;
   out_8191179680785695057[188] = 0;
   out_8191179680785695057[189] = 0;
   out_8191179680785695057[190] = 1;
   out_8191179680785695057[191] = 0;
   out_8191179680785695057[192] = 0;
   out_8191179680785695057[193] = 0;
   out_8191179680785695057[194] = 0;
   out_8191179680785695057[195] = 0;
   out_8191179680785695057[196] = 0;
   out_8191179680785695057[197] = 0;
   out_8191179680785695057[198] = 0;
   out_8191179680785695057[199] = 0;
   out_8191179680785695057[200] = 0;
   out_8191179680785695057[201] = 0;
   out_8191179680785695057[202] = 0;
   out_8191179680785695057[203] = 0;
   out_8191179680785695057[204] = 0;
   out_8191179680785695057[205] = 0;
   out_8191179680785695057[206] = 0;
   out_8191179680785695057[207] = 0;
   out_8191179680785695057[208] = 0;
   out_8191179680785695057[209] = 1;
   out_8191179680785695057[210] = 0;
   out_8191179680785695057[211] = 0;
   out_8191179680785695057[212] = 0;
   out_8191179680785695057[213] = 0;
   out_8191179680785695057[214] = 0;
   out_8191179680785695057[215] = 0;
   out_8191179680785695057[216] = 0;
   out_8191179680785695057[217] = 0;
   out_8191179680785695057[218] = 0;
   out_8191179680785695057[219] = 0;
   out_8191179680785695057[220] = 0;
   out_8191179680785695057[221] = 0;
   out_8191179680785695057[222] = 0;
   out_8191179680785695057[223] = 0;
   out_8191179680785695057[224] = 0;
   out_8191179680785695057[225] = 0;
   out_8191179680785695057[226] = 0;
   out_8191179680785695057[227] = 0;
   out_8191179680785695057[228] = 1;
   out_8191179680785695057[229] = 0;
   out_8191179680785695057[230] = 0;
   out_8191179680785695057[231] = 0;
   out_8191179680785695057[232] = 0;
   out_8191179680785695057[233] = 0;
   out_8191179680785695057[234] = 0;
   out_8191179680785695057[235] = 0;
   out_8191179680785695057[236] = 0;
   out_8191179680785695057[237] = 0;
   out_8191179680785695057[238] = 0;
   out_8191179680785695057[239] = 0;
   out_8191179680785695057[240] = 0;
   out_8191179680785695057[241] = 0;
   out_8191179680785695057[242] = 0;
   out_8191179680785695057[243] = 0;
   out_8191179680785695057[244] = 0;
   out_8191179680785695057[245] = 0;
   out_8191179680785695057[246] = 0;
   out_8191179680785695057[247] = 1;
   out_8191179680785695057[248] = 0;
   out_8191179680785695057[249] = 0;
   out_8191179680785695057[250] = 0;
   out_8191179680785695057[251] = 0;
   out_8191179680785695057[252] = 0;
   out_8191179680785695057[253] = 0;
   out_8191179680785695057[254] = 0;
   out_8191179680785695057[255] = 0;
   out_8191179680785695057[256] = 0;
   out_8191179680785695057[257] = 0;
   out_8191179680785695057[258] = 0;
   out_8191179680785695057[259] = 0;
   out_8191179680785695057[260] = 0;
   out_8191179680785695057[261] = 0;
   out_8191179680785695057[262] = 0;
   out_8191179680785695057[263] = 0;
   out_8191179680785695057[264] = 0;
   out_8191179680785695057[265] = 0;
   out_8191179680785695057[266] = 1;
   out_8191179680785695057[267] = 0;
   out_8191179680785695057[268] = 0;
   out_8191179680785695057[269] = 0;
   out_8191179680785695057[270] = 0;
   out_8191179680785695057[271] = 0;
   out_8191179680785695057[272] = 0;
   out_8191179680785695057[273] = 0;
   out_8191179680785695057[274] = 0;
   out_8191179680785695057[275] = 0;
   out_8191179680785695057[276] = 0;
   out_8191179680785695057[277] = 0;
   out_8191179680785695057[278] = 0;
   out_8191179680785695057[279] = 0;
   out_8191179680785695057[280] = 0;
   out_8191179680785695057[281] = 0;
   out_8191179680785695057[282] = 0;
   out_8191179680785695057[283] = 0;
   out_8191179680785695057[284] = 0;
   out_8191179680785695057[285] = 1;
   out_8191179680785695057[286] = 0;
   out_8191179680785695057[287] = 0;
   out_8191179680785695057[288] = 0;
   out_8191179680785695057[289] = 0;
   out_8191179680785695057[290] = 0;
   out_8191179680785695057[291] = 0;
   out_8191179680785695057[292] = 0;
   out_8191179680785695057[293] = 0;
   out_8191179680785695057[294] = 0;
   out_8191179680785695057[295] = 0;
   out_8191179680785695057[296] = 0;
   out_8191179680785695057[297] = 0;
   out_8191179680785695057[298] = 0;
   out_8191179680785695057[299] = 0;
   out_8191179680785695057[300] = 0;
   out_8191179680785695057[301] = 0;
   out_8191179680785695057[302] = 0;
   out_8191179680785695057[303] = 0;
   out_8191179680785695057[304] = 1;
   out_8191179680785695057[305] = 0;
   out_8191179680785695057[306] = 0;
   out_8191179680785695057[307] = 0;
   out_8191179680785695057[308] = 0;
   out_8191179680785695057[309] = 0;
   out_8191179680785695057[310] = 0;
   out_8191179680785695057[311] = 0;
   out_8191179680785695057[312] = 0;
   out_8191179680785695057[313] = 0;
   out_8191179680785695057[314] = 0;
   out_8191179680785695057[315] = 0;
   out_8191179680785695057[316] = 0;
   out_8191179680785695057[317] = 0;
   out_8191179680785695057[318] = 0;
   out_8191179680785695057[319] = 0;
   out_8191179680785695057[320] = 0;
   out_8191179680785695057[321] = 0;
   out_8191179680785695057[322] = 0;
   out_8191179680785695057[323] = 1;
}
void h_4(double *state, double *unused, double *out_2559071891163856095) {
   out_2559071891163856095[0] = state[6] + state[9];
   out_2559071891163856095[1] = state[7] + state[10];
   out_2559071891163856095[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1870575472129554555) {
   out_1870575472129554555[0] = 0;
   out_1870575472129554555[1] = 0;
   out_1870575472129554555[2] = 0;
   out_1870575472129554555[3] = 0;
   out_1870575472129554555[4] = 0;
   out_1870575472129554555[5] = 0;
   out_1870575472129554555[6] = 1;
   out_1870575472129554555[7] = 0;
   out_1870575472129554555[8] = 0;
   out_1870575472129554555[9] = 1;
   out_1870575472129554555[10] = 0;
   out_1870575472129554555[11] = 0;
   out_1870575472129554555[12] = 0;
   out_1870575472129554555[13] = 0;
   out_1870575472129554555[14] = 0;
   out_1870575472129554555[15] = 0;
   out_1870575472129554555[16] = 0;
   out_1870575472129554555[17] = 0;
   out_1870575472129554555[18] = 0;
   out_1870575472129554555[19] = 0;
   out_1870575472129554555[20] = 0;
   out_1870575472129554555[21] = 0;
   out_1870575472129554555[22] = 0;
   out_1870575472129554555[23] = 0;
   out_1870575472129554555[24] = 0;
   out_1870575472129554555[25] = 1;
   out_1870575472129554555[26] = 0;
   out_1870575472129554555[27] = 0;
   out_1870575472129554555[28] = 1;
   out_1870575472129554555[29] = 0;
   out_1870575472129554555[30] = 0;
   out_1870575472129554555[31] = 0;
   out_1870575472129554555[32] = 0;
   out_1870575472129554555[33] = 0;
   out_1870575472129554555[34] = 0;
   out_1870575472129554555[35] = 0;
   out_1870575472129554555[36] = 0;
   out_1870575472129554555[37] = 0;
   out_1870575472129554555[38] = 0;
   out_1870575472129554555[39] = 0;
   out_1870575472129554555[40] = 0;
   out_1870575472129554555[41] = 0;
   out_1870575472129554555[42] = 0;
   out_1870575472129554555[43] = 0;
   out_1870575472129554555[44] = 1;
   out_1870575472129554555[45] = 0;
   out_1870575472129554555[46] = 0;
   out_1870575472129554555[47] = 1;
   out_1870575472129554555[48] = 0;
   out_1870575472129554555[49] = 0;
   out_1870575472129554555[50] = 0;
   out_1870575472129554555[51] = 0;
   out_1870575472129554555[52] = 0;
   out_1870575472129554555[53] = 0;
}
void h_10(double *state, double *unused, double *out_5996958394693935648) {
   out_5996958394693935648[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5996958394693935648[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5996958394693935648[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1808127169918867388) {
   out_1808127169918867388[0] = 0;
   out_1808127169918867388[1] = 9.8100000000000005*cos(state[1]);
   out_1808127169918867388[2] = 0;
   out_1808127169918867388[3] = 0;
   out_1808127169918867388[4] = -state[8];
   out_1808127169918867388[5] = state[7];
   out_1808127169918867388[6] = 0;
   out_1808127169918867388[7] = state[5];
   out_1808127169918867388[8] = -state[4];
   out_1808127169918867388[9] = 0;
   out_1808127169918867388[10] = 0;
   out_1808127169918867388[11] = 0;
   out_1808127169918867388[12] = 1;
   out_1808127169918867388[13] = 0;
   out_1808127169918867388[14] = 0;
   out_1808127169918867388[15] = 1;
   out_1808127169918867388[16] = 0;
   out_1808127169918867388[17] = 0;
   out_1808127169918867388[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1808127169918867388[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1808127169918867388[20] = 0;
   out_1808127169918867388[21] = state[8];
   out_1808127169918867388[22] = 0;
   out_1808127169918867388[23] = -state[6];
   out_1808127169918867388[24] = -state[5];
   out_1808127169918867388[25] = 0;
   out_1808127169918867388[26] = state[3];
   out_1808127169918867388[27] = 0;
   out_1808127169918867388[28] = 0;
   out_1808127169918867388[29] = 0;
   out_1808127169918867388[30] = 0;
   out_1808127169918867388[31] = 1;
   out_1808127169918867388[32] = 0;
   out_1808127169918867388[33] = 0;
   out_1808127169918867388[34] = 1;
   out_1808127169918867388[35] = 0;
   out_1808127169918867388[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1808127169918867388[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1808127169918867388[38] = 0;
   out_1808127169918867388[39] = -state[7];
   out_1808127169918867388[40] = state[6];
   out_1808127169918867388[41] = 0;
   out_1808127169918867388[42] = state[4];
   out_1808127169918867388[43] = -state[3];
   out_1808127169918867388[44] = 0;
   out_1808127169918867388[45] = 0;
   out_1808127169918867388[46] = 0;
   out_1808127169918867388[47] = 0;
   out_1808127169918867388[48] = 0;
   out_1808127169918867388[49] = 0;
   out_1808127169918867388[50] = 1;
   out_1808127169918867388[51] = 0;
   out_1808127169918867388[52] = 0;
   out_1808127169918867388[53] = 1;
}
void h_13(double *state, double *unused, double *out_986663360582551760) {
   out_986663360582551760[0] = state[3];
   out_986663360582551760[1] = state[4];
   out_986663360582551760[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1341698353202778246) {
   out_1341698353202778246[0] = 0;
   out_1341698353202778246[1] = 0;
   out_1341698353202778246[2] = 0;
   out_1341698353202778246[3] = 1;
   out_1341698353202778246[4] = 0;
   out_1341698353202778246[5] = 0;
   out_1341698353202778246[6] = 0;
   out_1341698353202778246[7] = 0;
   out_1341698353202778246[8] = 0;
   out_1341698353202778246[9] = 0;
   out_1341698353202778246[10] = 0;
   out_1341698353202778246[11] = 0;
   out_1341698353202778246[12] = 0;
   out_1341698353202778246[13] = 0;
   out_1341698353202778246[14] = 0;
   out_1341698353202778246[15] = 0;
   out_1341698353202778246[16] = 0;
   out_1341698353202778246[17] = 0;
   out_1341698353202778246[18] = 0;
   out_1341698353202778246[19] = 0;
   out_1341698353202778246[20] = 0;
   out_1341698353202778246[21] = 0;
   out_1341698353202778246[22] = 1;
   out_1341698353202778246[23] = 0;
   out_1341698353202778246[24] = 0;
   out_1341698353202778246[25] = 0;
   out_1341698353202778246[26] = 0;
   out_1341698353202778246[27] = 0;
   out_1341698353202778246[28] = 0;
   out_1341698353202778246[29] = 0;
   out_1341698353202778246[30] = 0;
   out_1341698353202778246[31] = 0;
   out_1341698353202778246[32] = 0;
   out_1341698353202778246[33] = 0;
   out_1341698353202778246[34] = 0;
   out_1341698353202778246[35] = 0;
   out_1341698353202778246[36] = 0;
   out_1341698353202778246[37] = 0;
   out_1341698353202778246[38] = 0;
   out_1341698353202778246[39] = 0;
   out_1341698353202778246[40] = 0;
   out_1341698353202778246[41] = 1;
   out_1341698353202778246[42] = 0;
   out_1341698353202778246[43] = 0;
   out_1341698353202778246[44] = 0;
   out_1341698353202778246[45] = 0;
   out_1341698353202778246[46] = 0;
   out_1341698353202778246[47] = 0;
   out_1341698353202778246[48] = 0;
   out_1341698353202778246[49] = 0;
   out_1341698353202778246[50] = 0;
   out_1341698353202778246[51] = 0;
   out_1341698353202778246[52] = 0;
   out_1341698353202778246[53] = 0;
}
void h_14(double *state, double *unused, double *out_3738680306552072346) {
   out_3738680306552072346[0] = state[6];
   out_3738680306552072346[1] = state[7];
   out_3738680306552072346[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2092665384209929974) {
   out_2092665384209929974[0] = 0;
   out_2092665384209929974[1] = 0;
   out_2092665384209929974[2] = 0;
   out_2092665384209929974[3] = 0;
   out_2092665384209929974[4] = 0;
   out_2092665384209929974[5] = 0;
   out_2092665384209929974[6] = 1;
   out_2092665384209929974[7] = 0;
   out_2092665384209929974[8] = 0;
   out_2092665384209929974[9] = 0;
   out_2092665384209929974[10] = 0;
   out_2092665384209929974[11] = 0;
   out_2092665384209929974[12] = 0;
   out_2092665384209929974[13] = 0;
   out_2092665384209929974[14] = 0;
   out_2092665384209929974[15] = 0;
   out_2092665384209929974[16] = 0;
   out_2092665384209929974[17] = 0;
   out_2092665384209929974[18] = 0;
   out_2092665384209929974[19] = 0;
   out_2092665384209929974[20] = 0;
   out_2092665384209929974[21] = 0;
   out_2092665384209929974[22] = 0;
   out_2092665384209929974[23] = 0;
   out_2092665384209929974[24] = 0;
   out_2092665384209929974[25] = 1;
   out_2092665384209929974[26] = 0;
   out_2092665384209929974[27] = 0;
   out_2092665384209929974[28] = 0;
   out_2092665384209929974[29] = 0;
   out_2092665384209929974[30] = 0;
   out_2092665384209929974[31] = 0;
   out_2092665384209929974[32] = 0;
   out_2092665384209929974[33] = 0;
   out_2092665384209929974[34] = 0;
   out_2092665384209929974[35] = 0;
   out_2092665384209929974[36] = 0;
   out_2092665384209929974[37] = 0;
   out_2092665384209929974[38] = 0;
   out_2092665384209929974[39] = 0;
   out_2092665384209929974[40] = 0;
   out_2092665384209929974[41] = 0;
   out_2092665384209929974[42] = 0;
   out_2092665384209929974[43] = 0;
   out_2092665384209929974[44] = 1;
   out_2092665384209929974[45] = 0;
   out_2092665384209929974[46] = 0;
   out_2092665384209929974[47] = 0;
   out_2092665384209929974[48] = 0;
   out_2092665384209929974[49] = 0;
   out_2092665384209929974[50] = 0;
   out_2092665384209929974[51] = 0;
   out_2092665384209929974[52] = 0;
   out_2092665384209929974[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8106364195173448064) {
  err_fun(nom_x, delta_x, out_8106364195173448064);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1999187208436778161) {
  inv_err_fun(nom_x, true_x, out_1999187208436778161);
}
void pose_H_mod_fun(double *state, double *out_1403646606661394698) {
  H_mod_fun(state, out_1403646606661394698);
}
void pose_f_fun(double *state, double dt, double *out_6156776826239606646) {
  f_fun(state,  dt, out_6156776826239606646);
}
void pose_F_fun(double *state, double dt, double *out_8191179680785695057) {
  F_fun(state,  dt, out_8191179680785695057);
}
void pose_h_4(double *state, double *unused, double *out_2559071891163856095) {
  h_4(state, unused, out_2559071891163856095);
}
void pose_H_4(double *state, double *unused, double *out_1870575472129554555) {
  H_4(state, unused, out_1870575472129554555);
}
void pose_h_10(double *state, double *unused, double *out_5996958394693935648) {
  h_10(state, unused, out_5996958394693935648);
}
void pose_H_10(double *state, double *unused, double *out_1808127169918867388) {
  H_10(state, unused, out_1808127169918867388);
}
void pose_h_13(double *state, double *unused, double *out_986663360582551760) {
  h_13(state, unused, out_986663360582551760);
}
void pose_H_13(double *state, double *unused, double *out_1341698353202778246) {
  H_13(state, unused, out_1341698353202778246);
}
void pose_h_14(double *state, double *unused, double *out_3738680306552072346) {
  h_14(state, unused, out_3738680306552072346);
}
void pose_H_14(double *state, double *unused, double *out_2092665384209929974) {
  H_14(state, unused, out_2092665384209929974);
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
