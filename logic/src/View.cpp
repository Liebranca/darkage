// ---   *   ---   *   ---
// VIEW
// What you see
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
  #include "logic/View.hpp"

// ---   *   ---   *   ---
// get rat movement times
// frame delta and store it

void View::get_mouse_motion(void) {

  auto& Chasm = CHASM::ice();
  auto& Sin   = SIN::ice();

  auto& rat   = Chasm.ev.get_rat();

  m_cache().mouse_motion=
    rat.get_motion(Sin.fBy());

};

// ---   *   ---   *   ---
// cache-calc camera to origin

// TODO: movable camera target

void View::get_cam_to(void) {

  auto& Sin    = SIN::ice();
  auto& cam    = Sin.cam;

  auto& target = View::cam_target();

  m_cache().cam_to_vto = cam.get_pos()-target;

};

// ---   *   ---   *   ---
// rotate camera around
// itself by rat motion

void View::mouse_look(void) {

  auto& Sin = SIN::ice();

  auto& mo  = View::mouse_motion();
  auto& cam = Sin.cam;

  Move::look_around(cam,mo);

};

// ---   *   ---   *   ---
// ^rotate camera around point

void View::mouse_look_at(glm::vec3& point) {

  auto& Sin   = SIN::ice();
  auto& Chasm = CHASM::ice();

  auto& mo    = View::mouse_motion();
  auto& cam   = Sin.cam;

  Chasm.win.enable_mouse_trap();

  Move::look_around_point(

    cam,mo,

    point,
    View::cam_to_dist()

  );

};

// ---   *   ---   *   ---
// ^drag camera around

void View::mouse_drag(void) {

  auto& Sin   = SIN::ice();
  auto& Chasm = CHASM::ice();

  auto  mo    = View::mouse_motion();
  auto& cam   = Sin.cam;

  mo.x *= Chasm.win.hsize().x/6;
  mo.y *= Chasm.win.hsize().y/6;
  mo.y *= -1;

  Chasm.win.disable_mouse_trap();
  Move::drag(cam,mo,1);

};

// ---   *   ---   *   ---
// common control scheme for
// controling a 3D viewport

void View::mouse_3D(
  uint8_t drag_b,
  uint8_t view_b

) {

  auto& Chasm   = CHASM::ice();
  auto& Sin     = SIN::ice();

  auto& rat     = Chasm.ev.get_rat();
  auto& cam     = Sin.cam;

  auto  do_drag = rat.clicks(drag_b);
  auto  do_view = rat.clicks(view_b);

  if(do_view) {
    View::mouse_look_at(View::cam_target());

  } else if(do_drag) {
    View::mouse_drag();

  } else {
    Chasm.win.disable_mouse_trap();
    Move::clear(cam);

  };

};

// ---   *   ---   *   ---
// book-keeping

void View::clear_cache(void) {
  m_cache()=Cache();

};

void View::load_cache(void) {
  View::get_mouse_motion();
  View::get_cam_to();

};

// ---   *   ---   *   ---
