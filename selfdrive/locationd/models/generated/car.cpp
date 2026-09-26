#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4782419853829602388) {
   out_4782419853829602388[0] = delta_x[0] + nom_x[0];
   out_4782419853829602388[1] = delta_x[1] + nom_x[1];
   out_4782419853829602388[2] = delta_x[2] + nom_x[2];
   out_4782419853829602388[3] = delta_x[3] + nom_x[3];
   out_4782419853829602388[4] = delta_x[4] + nom_x[4];
   out_4782419853829602388[5] = delta_x[5] + nom_x[5];
   out_4782419853829602388[6] = delta_x[6] + nom_x[6];
   out_4782419853829602388[7] = delta_x[7] + nom_x[7];
   out_4782419853829602388[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6507541307486986980) {
   out_6507541307486986980[0] = -nom_x[0] + true_x[0];
   out_6507541307486986980[1] = -nom_x[1] + true_x[1];
   out_6507541307486986980[2] = -nom_x[2] + true_x[2];
   out_6507541307486986980[3] = -nom_x[3] + true_x[3];
   out_6507541307486986980[4] = -nom_x[4] + true_x[4];
   out_6507541307486986980[5] = -nom_x[5] + true_x[5];
   out_6507541307486986980[6] = -nom_x[6] + true_x[6];
   out_6507541307486986980[7] = -nom_x[7] + true_x[7];
   out_6507541307486986980[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7245868377039428694) {
   out_7245868377039428694[0] = 1.0;
   out_7245868377039428694[1] = 0.0;
   out_7245868377039428694[2] = 0.0;
   out_7245868377039428694[3] = 0.0;
   out_7245868377039428694[4] = 0.0;
   out_7245868377039428694[5] = 0.0;
   out_7245868377039428694[6] = 0.0;
   out_7245868377039428694[7] = 0.0;
   out_7245868377039428694[8] = 0.0;
   out_7245868377039428694[9] = 0.0;
   out_7245868377039428694[10] = 1.0;
   out_7245868377039428694[11] = 0.0;
   out_7245868377039428694[12] = 0.0;
   out_7245868377039428694[13] = 0.0;
   out_7245868377039428694[14] = 0.0;
   out_7245868377039428694[15] = 0.0;
   out_7245868377039428694[16] = 0.0;
   out_7245868377039428694[17] = 0.0;
   out_7245868377039428694[18] = 0.0;
   out_7245868377039428694[19] = 0.0;
   out_7245868377039428694[20] = 1.0;
   out_7245868377039428694[21] = 0.0;
   out_7245868377039428694[22] = 0.0;
   out_7245868377039428694[23] = 0.0;
   out_7245868377039428694[24] = 0.0;
   out_7245868377039428694[25] = 0.0;
   out_7245868377039428694[26] = 0.0;
   out_7245868377039428694[27] = 0.0;
   out_7245868377039428694[28] = 0.0;
   out_7245868377039428694[29] = 0.0;
   out_7245868377039428694[30] = 1.0;
   out_7245868377039428694[31] = 0.0;
   out_7245868377039428694[32] = 0.0;
   out_7245868377039428694[33] = 0.0;
   out_7245868377039428694[34] = 0.0;
   out_7245868377039428694[35] = 0.0;
   out_7245868377039428694[36] = 0.0;
   out_7245868377039428694[37] = 0.0;
   out_7245868377039428694[38] = 0.0;
   out_7245868377039428694[39] = 0.0;
   out_7245868377039428694[40] = 1.0;
   out_7245868377039428694[41] = 0.0;
   out_7245868377039428694[42] = 0.0;
   out_7245868377039428694[43] = 0.0;
   out_7245868377039428694[44] = 0.0;
   out_7245868377039428694[45] = 0.0;
   out_7245868377039428694[46] = 0.0;
   out_7245868377039428694[47] = 0.0;
   out_7245868377039428694[48] = 0.0;
   out_7245868377039428694[49] = 0.0;
   out_7245868377039428694[50] = 1.0;
   out_7245868377039428694[51] = 0.0;
   out_7245868377039428694[52] = 0.0;
   out_7245868377039428694[53] = 0.0;
   out_7245868377039428694[54] = 0.0;
   out_7245868377039428694[55] = 0.0;
   out_7245868377039428694[56] = 0.0;
   out_7245868377039428694[57] = 0.0;
   out_7245868377039428694[58] = 0.0;
   out_7245868377039428694[59] = 0.0;
   out_7245868377039428694[60] = 1.0;
   out_7245868377039428694[61] = 0.0;
   out_7245868377039428694[62] = 0.0;
   out_7245868377039428694[63] = 0.0;
   out_7245868377039428694[64] = 0.0;
   out_7245868377039428694[65] = 0.0;
   out_7245868377039428694[66] = 0.0;
   out_7245868377039428694[67] = 0.0;
   out_7245868377039428694[68] = 0.0;
   out_7245868377039428694[69] = 0.0;
   out_7245868377039428694[70] = 1.0;
   out_7245868377039428694[71] = 0.0;
   out_7245868377039428694[72] = 0.0;
   out_7245868377039428694[73] = 0.0;
   out_7245868377039428694[74] = 0.0;
   out_7245868377039428694[75] = 0.0;
   out_7245868377039428694[76] = 0.0;
   out_7245868377039428694[77] = 0.0;
   out_7245868377039428694[78] = 0.0;
   out_7245868377039428694[79] = 0.0;
   out_7245868377039428694[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7446431905340007511) {
   out_7446431905340007511[0] = state[0];
   out_7446431905340007511[1] = state[1];
   out_7446431905340007511[2] = state[2];
   out_7446431905340007511[3] = state[3];
   out_7446431905340007511[4] = state[4];
   out_7446431905340007511[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7446431905340007511[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7446431905340007511[7] = state[7];
   out_7446431905340007511[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1288977979101878022) {
   out_1288977979101878022[0] = 1;
   out_1288977979101878022[1] = 0;
   out_1288977979101878022[2] = 0;
   out_1288977979101878022[3] = 0;
   out_1288977979101878022[4] = 0;
   out_1288977979101878022[5] = 0;
   out_1288977979101878022[6] = 0;
   out_1288977979101878022[7] = 0;
   out_1288977979101878022[8] = 0;
   out_1288977979101878022[9] = 0;
   out_1288977979101878022[10] = 1;
   out_1288977979101878022[11] = 0;
   out_1288977979101878022[12] = 0;
   out_1288977979101878022[13] = 0;
   out_1288977979101878022[14] = 0;
   out_1288977979101878022[15] = 0;
   out_1288977979101878022[16] = 0;
   out_1288977979101878022[17] = 0;
   out_1288977979101878022[18] = 0;
   out_1288977979101878022[19] = 0;
   out_1288977979101878022[20] = 1;
   out_1288977979101878022[21] = 0;
   out_1288977979101878022[22] = 0;
   out_1288977979101878022[23] = 0;
   out_1288977979101878022[24] = 0;
   out_1288977979101878022[25] = 0;
   out_1288977979101878022[26] = 0;
   out_1288977979101878022[27] = 0;
   out_1288977979101878022[28] = 0;
   out_1288977979101878022[29] = 0;
   out_1288977979101878022[30] = 1;
   out_1288977979101878022[31] = 0;
   out_1288977979101878022[32] = 0;
   out_1288977979101878022[33] = 0;
   out_1288977979101878022[34] = 0;
   out_1288977979101878022[35] = 0;
   out_1288977979101878022[36] = 0;
   out_1288977979101878022[37] = 0;
   out_1288977979101878022[38] = 0;
   out_1288977979101878022[39] = 0;
   out_1288977979101878022[40] = 1;
   out_1288977979101878022[41] = 0;
   out_1288977979101878022[42] = 0;
   out_1288977979101878022[43] = 0;
   out_1288977979101878022[44] = 0;
   out_1288977979101878022[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1288977979101878022[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1288977979101878022[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1288977979101878022[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1288977979101878022[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1288977979101878022[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1288977979101878022[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1288977979101878022[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1288977979101878022[53] = -9.8100000000000005*dt;
   out_1288977979101878022[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1288977979101878022[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1288977979101878022[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1288977979101878022[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1288977979101878022[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1288977979101878022[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1288977979101878022[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1288977979101878022[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1288977979101878022[62] = 0;
   out_1288977979101878022[63] = 0;
   out_1288977979101878022[64] = 0;
   out_1288977979101878022[65] = 0;
   out_1288977979101878022[66] = 0;
   out_1288977979101878022[67] = 0;
   out_1288977979101878022[68] = 0;
   out_1288977979101878022[69] = 0;
   out_1288977979101878022[70] = 1;
   out_1288977979101878022[71] = 0;
   out_1288977979101878022[72] = 0;
   out_1288977979101878022[73] = 0;
   out_1288977979101878022[74] = 0;
   out_1288977979101878022[75] = 0;
   out_1288977979101878022[76] = 0;
   out_1288977979101878022[77] = 0;
   out_1288977979101878022[78] = 0;
   out_1288977979101878022[79] = 0;
   out_1288977979101878022[80] = 1;
}
void h_25(double *state, double *unused, double *out_6140538417752110073) {
   out_6140538417752110073[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7677895046680631245) {
   out_7677895046680631245[0] = 0;
   out_7677895046680631245[1] = 0;
   out_7677895046680631245[2] = 0;
   out_7677895046680631245[3] = 0;
   out_7677895046680631245[4] = 0;
   out_7677895046680631245[5] = 0;
   out_7677895046680631245[6] = 1;
   out_7677895046680631245[7] = 0;
   out_7677895046680631245[8] = 0;
}
void h_24(double *state, double *unused, double *out_4108860547315817589) {
   out_4108860547315817589[0] = state[4];
   out_4108860547315817589[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4119969447878308109) {
   out_4119969447878308109[0] = 0;
   out_4119969447878308109[1] = 0;
   out_4119969447878308109[2] = 0;
   out_4119969447878308109[3] = 0;
   out_4119969447878308109[4] = 1;
   out_4119969447878308109[5] = 0;
   out_4119969447878308109[6] = 0;
   out_4119969447878308109[7] = 0;
   out_4119969447878308109[8] = 0;
   out_4119969447878308109[9] = 0;
   out_4119969447878308109[10] = 0;
   out_4119969447878308109[11] = 0;
   out_4119969447878308109[12] = 0;
   out_4119969447878308109[13] = 0;
   out_4119969447878308109[14] = 1;
   out_4119969447878308109[15] = 0;
   out_4119969447878308109[16] = 0;
   out_4119969447878308109[17] = 0;
}
void h_30(double *state, double *unused, double *out_226805391081361700) {
   out_226805391081361700[0] = state[4];
}
void H_30(double *state, double *unused, double *out_761204705189014490) {
   out_761204705189014490[0] = 0;
   out_761204705189014490[1] = 0;
   out_761204705189014490[2] = 0;
   out_761204705189014490[3] = 0;
   out_761204705189014490[4] = 1;
   out_761204705189014490[5] = 0;
   out_761204705189014490[6] = 0;
   out_761204705189014490[7] = 0;
   out_761204705189014490[8] = 0;
}
void h_26(double *state, double *unused, double *out_8569504073184635440) {
   out_8569504073184635440[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7027345708154864147) {
   out_7027345708154864147[0] = 0;
   out_7027345708154864147[1] = 0;
   out_7027345708154864147[2] = 0;
   out_7027345708154864147[3] = 0;
   out_7027345708154864147[4] = 0;
   out_7027345708154864147[5] = 0;
   out_7027345708154864147[6] = 0;
   out_7027345708154864147[7] = 1;
   out_7027345708154864147[8] = 0;
}
void h_27(double *state, double *unused, double *out_6743854302428587590) {
   out_6743854302428587590[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2935968016989439401) {
   out_2935968016989439401[0] = 0;
   out_2935968016989439401[1] = 0;
   out_2935968016989439401[2] = 0;
   out_2935968016989439401[3] = 1;
   out_2935968016989439401[4] = 0;
   out_2935968016989439401[5] = 0;
   out_2935968016989439401[6] = 0;
   out_2935968016989439401[7] = 0;
   out_2935968016989439401[8] = 0;
}
void h_29(double *state, double *unused, double *out_716704461820300735) {
   out_716704461820300735[0] = state[1];
}
void H_29(double *state, double *unused, double *out_250973360874622306) {
   out_250973360874622306[0] = 0;
   out_250973360874622306[1] = 1;
   out_250973360874622306[2] = 0;
   out_250973360874622306[3] = 0;
   out_250973360874622306[4] = 0;
   out_250973360874622306[5] = 0;
   out_250973360874622306[6] = 0;
   out_250973360874622306[7] = 0;
   out_250973360874622306[8] = 0;
}
void h_28(double *state, double *unused, double *out_344812785014738444) {
   out_344812785014738444[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8715014312781030608) {
   out_8715014312781030608[0] = 1;
   out_8715014312781030608[1] = 0;
   out_8715014312781030608[2] = 0;
   out_8715014312781030608[3] = 0;
   out_8715014312781030608[4] = 0;
   out_8715014312781030608[5] = 0;
   out_8715014312781030608[6] = 0;
   out_8715014312781030608[7] = 0;
   out_8715014312781030608[8] = 0;
}
void h_31(double *state, double *unused, double *out_2503088889498087723) {
   out_2503088889498087723[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7647249084803670817) {
   out_7647249084803670817[0] = 0;
   out_7647249084803670817[1] = 0;
   out_7647249084803670817[2] = 0;
   out_7647249084803670817[3] = 0;
   out_7647249084803670817[4] = 0;
   out_7647249084803670817[5] = 0;
   out_7647249084803670817[6] = 0;
   out_7647249084803670817[7] = 0;
   out_7647249084803670817[8] = 1;
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

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_4782419853829602388) {
  err_fun(nom_x, delta_x, out_4782419853829602388);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6507541307486986980) {
  inv_err_fun(nom_x, true_x, out_6507541307486986980);
}
void car_H_mod_fun(double *state, double *out_7245868377039428694) {
  H_mod_fun(state, out_7245868377039428694);
}
void car_f_fun(double *state, double dt, double *out_7446431905340007511) {
  f_fun(state,  dt, out_7446431905340007511);
}
void car_F_fun(double *state, double dt, double *out_1288977979101878022) {
  F_fun(state,  dt, out_1288977979101878022);
}
void car_h_25(double *state, double *unused, double *out_6140538417752110073) {
  h_25(state, unused, out_6140538417752110073);
}
void car_H_25(double *state, double *unused, double *out_7677895046680631245) {
  H_25(state, unused, out_7677895046680631245);
}
void car_h_24(double *state, double *unused, double *out_4108860547315817589) {
  h_24(state, unused, out_4108860547315817589);
}
void car_H_24(double *state, double *unused, double *out_4119969447878308109) {
  H_24(state, unused, out_4119969447878308109);
}
void car_h_30(double *state, double *unused, double *out_226805391081361700) {
  h_30(state, unused, out_226805391081361700);
}
void car_H_30(double *state, double *unused, double *out_761204705189014490) {
  H_30(state, unused, out_761204705189014490);
}
void car_h_26(double *state, double *unused, double *out_8569504073184635440) {
  h_26(state, unused, out_8569504073184635440);
}
void car_H_26(double *state, double *unused, double *out_7027345708154864147) {
  H_26(state, unused, out_7027345708154864147);
}
void car_h_27(double *state, double *unused, double *out_6743854302428587590) {
  h_27(state, unused, out_6743854302428587590);
}
void car_H_27(double *state, double *unused, double *out_2935968016989439401) {
  H_27(state, unused, out_2935968016989439401);
}
void car_h_29(double *state, double *unused, double *out_716704461820300735) {
  h_29(state, unused, out_716704461820300735);
}
void car_H_29(double *state, double *unused, double *out_250973360874622306) {
  H_29(state, unused, out_250973360874622306);
}
void car_h_28(double *state, double *unused, double *out_344812785014738444) {
  h_28(state, unused, out_344812785014738444);
}
void car_H_28(double *state, double *unused, double *out_8715014312781030608) {
  H_28(state, unused, out_8715014312781030608);
}
void car_h_31(double *state, double *unused, double *out_2503088889498087723) {
  h_31(state, unused, out_2503088889498087723);
}
void car_H_31(double *state, double *unused, double *out_7647249084803670817) {
  H_31(state, unused, out_7647249084803670817);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
