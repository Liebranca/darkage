// ---   *   ---   *   ---
// MOVEMENT
// Gets you round
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include "DA.hpp"
  #include "logic/Movement.hpp"

// ---   *   ---   *   ---
// sugar

void Move::fwd(Node& dst,float mul) {
  dst.set_lindirn_ax(2,1);

};

void Move::back(Node& dst,float mul) {
  dst.set_lindirn_ax(2,-1);

};

void Move::left(Node& dst,float mul) {
  dst.set_lindirn_ax(0,1);

};

void Move::right(Node& dst,float mul) {
  dst.set_lindirn_ax(0,-1);

};

// ---   *   ---   *   ---
// ^iv

void Move::stop_z(Node& dst) {
  dst.set_lindirn_ax(2,0);

};

void Move::stop_x(Node& dst) {
  dst.set_lindirn_ax(0,0);

};

// ---   *   ---   *   ---
// ^inputless
// fetches dst from frame

void Move::player_fwd(void) {
  Move::fwd(DA::player());

};

void Move::player_left(void) {
  Move::left(DA::player());

};

void Move::player_back(void) {
  Move::back(DA::player());

};

void Move::player_right(void) {
  Move::right(DA::player());

};

// ---   *   ---   *   ---
// ^iv

void Move::player_stop_z(void) {
  Move::stop_z(DA::player());

};

void Move::player_stop_x(void) {
  Move::stop_x(DA::player());

};

// ---   *   ---   *   ---
