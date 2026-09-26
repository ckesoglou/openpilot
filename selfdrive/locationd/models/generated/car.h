#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_4782419853829602388);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6507541307486986980);
void car_H_mod_fun(double *state, double *out_7245868377039428694);
void car_f_fun(double *state, double dt, double *out_7446431905340007511);
void car_F_fun(double *state, double dt, double *out_1288977979101878022);
void car_h_25(double *state, double *unused, double *out_6140538417752110073);
void car_H_25(double *state, double *unused, double *out_7677895046680631245);
void car_h_24(double *state, double *unused, double *out_4108860547315817589);
void car_H_24(double *state, double *unused, double *out_4119969447878308109);
void car_h_30(double *state, double *unused, double *out_226805391081361700);
void car_H_30(double *state, double *unused, double *out_761204705189014490);
void car_h_26(double *state, double *unused, double *out_8569504073184635440);
void car_H_26(double *state, double *unused, double *out_7027345708154864147);
void car_h_27(double *state, double *unused, double *out_6743854302428587590);
void car_H_27(double *state, double *unused, double *out_2935968016989439401);
void car_h_29(double *state, double *unused, double *out_716704461820300735);
void car_H_29(double *state, double *unused, double *out_250973360874622306);
void car_h_28(double *state, double *unused, double *out_344812785014738444);
void car_H_28(double *state, double *unused, double *out_8715014312781030608);
void car_h_31(double *state, double *unused, double *out_2503088889498087723);
void car_H_31(double *state, double *unused, double *out_7647249084803670817);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}