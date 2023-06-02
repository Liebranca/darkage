// ---   *   ---   *   ---
// MOVE
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

  #include "Dark.hpp"
  #include "logic/Move.hpp"

// ---   *   ---   *   ---
// wipes all loaded velocities

void Move::clear(Node& dst) {

  static glm::vec3 zero {0,0,0};

  dst.set_linvel(zero);
  dst.set_angvel(zero);
  dst.set_lindirn(zero);
  dst.set_angdirn(zero);

};

// ---   *   ---   *   ---
// rotate around self

void Move::look_around(

  Node&      dst,
  glm::vec2& motion,

  float      mul

) {

  auto hax=dst.get_hax() * motion.y;

  glm::quat y={1,-hax.x,hax.y,-hax.z};
  glm::quat x={1,0,-motion.x,0};

  glm::quat r=x*y;
  glm::vec3 v={r.x,r.y,r.z};

  v*=mul;

  dst.set_angvel(v);
  dst.ang_fmotion();

};

// ---   *   ---   *   ---
// ^rotate around other

void Move::look_around_point(

  Node&      dst,

  glm::vec2& motion,
  glm::vec3& point,

  float      distance,
  float      mul

) {

  glm::vec3 beg=dst.get_pos();

  dst.teleport(point);
  Move::look_around(dst,motion,mul);

  glm::vec3 end=

    point + (

    dst.get_fwd()
  * -distance

  );

  glm::vec3 vel=Move::smooth_to(
    beg,end,0.16f

  );

  dst.teleport(beg);

  if(

    glm::distance(dst.get_pos(),end)
  > 0.001f

  ) {

    dst.move(vel);

  };

};

// ---   *   ---   *   ---
// moves on two local axes

void Move::drag(

  Node&      dst,
  glm::vec2& motion,

  float      mul

) {

  dst.set_lindirn_ax(0,motion.x * mul);
  dst.set_lindirn_ax(1,motion.y * mul);

  dst.lin_fmotion();

};

// ---   *   ---   *   ---
// eases into position

glm::vec3 Move::smooth_to(

  glm::vec3& beg,
  glm::vec3& end,

  float      step

) {

  glm::vec3 vto      = end-beg;
  float     distance = glm::length(vto);

  return vto*step;

};

// ---   *   ---   *   ---
// sugar

void Move::fwd(Node& dst,float mul) {
  dst.set_lindirn_ax(2,1 * mul);

};

void Move::back(Node& dst,float mul) {
  dst.set_lindirn_ax(2,-1 * mul);

};

void Move::left(Node& dst,float mul) {
  dst.set_lindirn_ax(0,1 * mul);

};

void Move::right(Node& dst,float mul) {
  dst.set_lindirn_ax(0,-1 * mul);

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
  Move::fwd(DARK::player());

};

void Move::player_left(void) {
  Move::left(DARK::player());

};

void Move::player_back(void) {
  Move::back(DARK::player());

};

void Move::player_right(void) {
  Move::right(DARK::player());

};

// ---   *   ---   *   ---
// ^iv

void Move::player_stop_z(void) {
  Move::stop_z(DARK::player());

};

void Move::player_stop_x(void) {
  Move::stop_x(DARK::player());

};

// ---   *   ---   *   ---
