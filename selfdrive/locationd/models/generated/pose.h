#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8106364195173448064);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1999187208436778161);
void pose_H_mod_fun(double *state, double *out_1403646606661394698);
void pose_f_fun(double *state, double dt, double *out_6156776826239606646);
void pose_F_fun(double *state, double dt, double *out_8191179680785695057);
void pose_h_4(double *state, double *unused, double *out_2559071891163856095);
void pose_H_4(double *state, double *unused, double *out_1870575472129554555);
void pose_h_10(double *state, double *unused, double *out_5996958394693935648);
void pose_H_10(double *state, double *unused, double *out_1808127169918867388);
void pose_h_13(double *state, double *unused, double *out_986663360582551760);
void pose_H_13(double *state, double *unused, double *out_1341698353202778246);
void pose_h_14(double *state, double *unused, double *out_3738680306552072346);
void pose_H_14(double *state, double *unused, double *out_2092665384209929974);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}