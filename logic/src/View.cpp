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

void View::calc_mouse_motion(void) {

  auto& Chasm = CHASM::ice();
  auto& Sin   = SIN::ice();

  auto& rat   = Chasm.ev.get_rat();

  m_cache().mouse_motion=
    rat.get_motion(Sin.fBy());

};

// ---   *   ---   *   ---
// cache-calc mouse position

void View::calc_mouse_pos(void) {

  auto& Chasm = CHASM::ice();

  auto& rat   = Chasm.ev.get_rat();
  auto& size  = Chasm.win.size();

  auto& pos   = rat.get_position();

  m_cache().mouse_pos={
    -((float(pos.x)/size.x) - 0.5 ),
    -((float(pos.y)/size.y) - 0.5 )

  };

};

// ---   *   ---   *   ---
// cache-calc camera to origin

// TODO: movable camera target

void View::calc_cam_to(void) {

  auto& Sin    = SIN::ice();
  auto& cam    = Sin.cam;

  auto& target = View::cam_target();

  m_cache().cam_to_vto  = cam.get_pos()-target;
  m_cache().cam_to_dist = glm::length(
    m_cache().cam_to_vto

  );

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

  // no transition in Q
  if(! m_cache().xition.valid()) {

    m_cache().xition=Move::look_around_point(

      cam,mo,

      point,
      View::cam_to_dist()

    );

  // ^finish transition in Q
  } else {
    m_cache().xition.run(cam);

  };

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
// ^move camera away/closer to target

void View::mouse_zoom(float x) {

  auto& Sin = SIN::ice();
  auto& cam = Sin.cam;

  Move::zoom(cam,View::cam_target(),x);

};

// ---   *   ---   *   ---
// cast ray from camera to cursor

void View::mouse_over(void) {

  auto& Sin = SIN::ice();
  auto& cam = Sin.cam;

  auto& pos = View::mouse_pos();

  printf("%f %f\n",pos.x,pos.y);

//  // face camera towards mouse
//  auto fwd=Move::n_by_motion(
//    cam.get_fwd(),pos
//
//  ) * m_cache().cam_to_dist;

  auto rot=Move::q_from_motion(
    cam.get_hax(),pos

  );

  auto fwd=glm::normalize(
    cam.get_fwd()
  * rot

  ) * View::cam_to_dist();

  auto& plane=Sin.nodes[0];
  plane.teleport(fwd);

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
  auto  do_zoom = rat.wheel() * 4;

  if(do_view) {
    View::mouse_look_at(View::cam_target());

  } else if(do_drag) {
    View::mouse_drag();

  } else {
    Chasm.win.disable_mouse_trap();
    Move::clear(cam);

  };

  if(do_zoom) {
    View::mouse_zoom(do_zoom);

  };

  View::mouse_over();

};

// ---   *   ---   *   ---
// book-keeping

void View::clear_cache(void) {
  m_cache()=Cache();

};

void View::load_cache(void) {
  View::calc_mouse_motion();
  View::calc_mouse_pos();
  View::calc_cam_to();

};

// ---   *   ---   *   ---
