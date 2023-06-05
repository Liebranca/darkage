// ---   *   ---   *   ---
// DARKAGE
// Comin at cha
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include "chasm/Chasm.hpp"
  #include "sin/Sin.hpp"

  #include "DA_Default.hpp"
  #include "Dark.hpp"

// ---   *   ---   *   ---
// cstruc

DARK::DARK(void) {
  this->keyset   = DA_Default::keys;
  this->programs = DA_Default::programs;

};

// ---   *   ---   *   ---
// chasm wrapper
//
// circumvents needing a handle
// to the window within Sin

inline Clock& get_clock(void) {
  auto& Chasm=CHASM::ice();
  return Chasm.win.clock();

};

// ---   *   ---   *   ---
// sin wrapper
//
// compiles params listed
// under this->programs

void DARK::load_shaders(void) {
  auto& Sin=SIN::ice();
  Sin.nit_programs(this->programs);

};

// ---   *   ---   *   ---
// creates window accto this->screen

void DARK::spawn_window(

  std::string name,

  CHASM::Loop draw_f,
  CHASM::Loop logic_f

) {

  auto& Chasm=CHASM::ice();

  Win::Desc win_desc={

    .title      = name,

    .width      = this->screen.size.x,
    .height     = this->screen.size.y,

    .fullscreen = this->screen.full,
    .fps        = this->fps,

    .flags      = this->screen.wflags

  };

  Chasm.nit(win_desc,this->keyset);
  Chasm.win.set_ambient_color(8);

  Chasm.draw  = draw_f;
  Chasm.logic = logic_f;

  // get handle to program clock
  auto& Sin=SIN::ice();
  Sin.get_clock=&get_clock;

  // compile *.sg
  this->load_shaders();

};

// ---   *   ---   *   ---
// creates camera accto this->screen

void DARK::spawn_camera(

  const vec3& pos,
  const quat& rot,

  bool ortho

) {

  auto& Sin=SIN::ice();

  Camera::Lens lens={
    .width  = float(this->screen.size.x),
    .height = float(this->screen.size.y),

    .scale  = this->screen.scale,
    .fov    = this->screen.fov,

    .near   = this->screen.znear,
    .far    = this->screen.zfar

  };

  Sin.nit_camera(

    pos,rot,lens,

    Sin.program->get_ubo(0),
    ortho

  );

};

// ---   *   ---   *   ---
// runs application

void DARK::loop(void) {

  auto& Chasm=CHASM::ice();

  CHASM_RUN(
    (void*) &this->draw_data,
    (void*) &this->logic_data

  );

};

// ---   *   ---   *   ---
// default drawing routine

int DARK::defdraw(void* data) {

  auto& Sin = SIN::ice();
  auto  bat = (Nodes*) data;

  // trigger camera update
  Sin.cam.get_view();

  // walk objects
  for(auto& idex : *bat) {
    Sin.nodes[idex].draw();

  };

  Sin.draw_enqueued();

  return 0;

};

// ---   *   ---   *   ---
// ^selfex

int DARK::deflogic(void* data) {
  return 1;

};

// ---   *   ---   *   ---
// get user-controlled node

Node& DARK::player(void) {
  auto& Sin=SIN::ice();
  return Sin.cam;

};

// ---   *   ---   *   ---
