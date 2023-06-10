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

  static vec3 zero {0,0,0};

  dst.set_linvel(zero);
  dst.set_angvel(zero);
  dst.set_lindirn(zero);
  dst.set_angdirn(zero);

};

// ---   *   ---   *   ---
// offset direction by motion

quat Move::q_from_motion(
  vec3& n,
  vec2& motion

) {

  auto base = n * motion.y;

  quat y = {1,-base.x,base.y,-base.z};
  quat x = {1,0,-motion.x,0};

  return x*y;

};

// ---   *   ---   *   ---
// ^gives unit n times q

vec3 Move::n_by_motion(
  vec3& n,
  vec2& motion

) {

  auto q=q_from_motion(n,motion);
  return glm::normalize(n*q);

};

// ---   *   ---   *   ---
// rotate around self

void Move::look_around(

  Node&      dst,
  vec2& motion,

  float      mul

) {

  quat r=Move::q_from_motion(
    dst.get_hax(),motion

  );

  vec3 v={r.x,r.y,r.z};
  v*=mul;

  dst.set_angvel(v);
  dst.ang_fmotion();

};

// ---   *   ---   *   ---
// ^rotate around other

Move::Async_Smooth Move::look_around_point(

  Node&      dst,

  vec2& motion,
  vec3& point,

  float      distance,
  float      mul

) {

  // return is xition
  Async_Smooth out;

  // starting position -> point
  vec3 beg=dst.get_pos();
  vec3 vto_beg=
    dst.get_fwd()
  * -distance
  ;

  // snap to point and rotate
  // around self
  dst.teleport(point);
  Move::look_around(dst,motion,mul);

  // point -> new orientation
  vec3 vto_end=
    dst.get_fwd()
  * -distance
  ;

  vec3 end=point+vto_end;

  // give anim if not centered on point
  if(

    glm::distance(beg-vto_beg,point)
  > Move::SMEPS

  ) {

    out=Move::async_smooth_to(dst,beg,end,8);

  // ^else we snap into place
  } else {
    dst.teleport(end);

  };

  return out;

};

// ---   *   ---   *   ---
// moves on two local axes

void Move::drag(

  Node&      dst,
  vec2& motion,

  float      mul

) {

  dst.set_lindirn_ax(0,motion.x * mul);
  dst.set_lindirn_ax(1,motion.y * mul);

  dst.lin_fmotion();

};

// ---   *   ---   *   ---
// eases STEP into position

void Move::smooth_to(

  Node&      dst,

  vec3& beg,
  vec3& end,

  float      step

) {

  vec3 vto=(
    (end-beg) * step

  ) + beg;

  dst.teleport(vto);

};

// ---   *   ---   *   ---
// ^enqueued

void Move::Async_Smooth::run(Node& dst) {

  Move::smooth_to(

    dst,

    m_beg,m_end,
    m_step * m_cnt

  );

  m_cnt++;
  m_frames--;

  if(! m_frames) {
    dst.teleport(m_end);
    m_cnt=0;

  };

};

// ---   *   ---   *   ---
// ^cstruc

Move::Async_Smooth Move::async_smooth_to(

  Node&      dst,

  vec3& beg,
  vec3& end,

  uint32_t   frames

) {

  Async_Smooth out={

    .m_beg    = beg,
    .m_end    = end,
    .m_frames = frames,

    .m_cnt    = 0,
    .m_step   = 1.0f/frames

  };

  out.run(dst);
  return out;

};

// ---   *   ---   *   ---
// get X close/farther from point

void Move::zoom(

  Node&      dst,
  vec3& point,

  float      x

) {

  auto vto=(point-dst.get_pos()) * x;

  dst.set_linvel(vto);
  dst.lin_fmotion();

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
