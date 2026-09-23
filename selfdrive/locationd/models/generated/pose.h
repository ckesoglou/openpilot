#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5742780909134961661);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_90707900821457158);
void pose_H_mod_fun(double *state, double *out_9191020752603421382);
void pose_f_fun(double *state, double dt, double *out_3255491544958013680);
void pose_F_fun(double *state, double dt, double *out_72615651512449831);
void pose_h_4(double *state, double *unused, double *out_5118220219965623011);
void pose_H_4(double *state, double *unused, double *out_5483916111262222662);
void pose_h_10(double *state, double *unused, double *out_3610281455795856596);
void pose_H_10(double *state, double *unused, double *out_4454049598256953673);
void pose_h_13(double *state, double *unused, double *out_4072338729150022115);
void pose_H_13(double *state, double *unused, double *out_9129072499144804930);
void pose_h_14(double *state, double *unused, double *out_8765973181652125668);
void pose_H_14(double *state, double *unused, double *out_8566704543557594958);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}