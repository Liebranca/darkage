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
  auto& Sin   = SIN::ice();

  auto& rat   = Chasm.ev.get_rat();
  auto& size  = Chasm.win.size();
  auto& cam   = Sin.cam;

  auto& pos   = rat.get_position();

  float x     = float(pos.x);
  float y     = float(pos.y);

  float sz_x  = float(size.x);
  float sz_y  = float(size.y);

  // screen cords
  vec4 cords {
      ( ((x/sz_x) * 2.0f ) - 1.0f),
     -( ((y/sz_y) * 2.0f ) - 1.0f),

    1.0f,1

  };

  m_cache().mouse_pos_s=vec2(cords);

  // ^xform to world coords
  cords=cam.get_stow() * cords;
  m_cache().mouse_pos_w=vec3(cords);

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

void View::mouse_look_at(vec3& point) {

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

  auto  pos = glm::normalize(
    View::mouse_pos_w()

  );

  auto a = cam.get_pos() + pos;
  auto b = a + pos * 100.0f;

  // test
  auto& cube  = Sin.nodes[0];
  auto& point = Sin.nodes[1];

  Gaol::Line ray;

  ray.set(a,b);

  auto& box=cube.bound().box();
  auto  col=box.isect_ray(ray);

  uint8_t line_color=SIN::RED;

  if(col.hit()) {
    line_color=SIN::GREEN;
    point.teleport(col.point());
    printf("HIT\n");

  } else {
    point.teleport(b);
    printf("NO HIT\n");

  };

  Sin.draw_line(a,b,line_color);

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
