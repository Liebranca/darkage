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
// get program clock

Clock& DARK::get_clock(void) {
  auto&  Chasm=CHASM::ice();
  return Chasm.win.clock();

};

// ---   *   ---   *   ---
// sin wrapper
//
// compiles params listed
// under this->programs

void DARK::load_shaders(void) {
//  auto& Sin=SIN::ice();
//  Sin.nit_programs(this->programs);

};

// ---   *   ---   *   ---
// creates window accto this->screen

void DARK::spawn_window(
  std::string name

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

  // set loop routines
  Chasm.draw  = DARK::draw;
  Chasm.logic = DARK::logic;

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

  auto&    Sin = SIN::ice();
  uint32_t ubo = Sin.program->get_ubo(0);

  Camera::Lens lens={
    .width  = float(this->screen.size.x),
    .height = float(this->screen.size.y),

    .scale  = this->screen.scale,
    .fov    = this->screen.fov,

    .near   = this->screen.znear,
    .far    = this->screen.zfar

  };

  cam.nit(pos,rot,lens,ubo);

  if(ortho) {
    cam.use_ortho();

  } else {
    cam.use_persp();

  };

  cam.get_view();

};

// ---   *   ---   *   ---
// create spacepart

void DARK::spawn_world(void) {
  uvec3 dim {1,1,1};
  world.nit(dim);

};

// ---   *   ---   *   ---
// push entity onto world

Node& DARK::spawn_object(

  uint32_t meshid,
  uint8_t  type,

  T3D      xform

) {

  auto&    Sin  = SIN::ice();
  uint32_t mesh = Sin.sprites.size();

  Sin.sprites.push_back(
    Sin.batch->ice_asset(meshid)

  );

  Node::Bld bld={

    .draw={
      .batch = Sin.batch_id,
      .mesh  = mesh,

      .type  = type

    },

    .xform=xform

  };

  return world.push_node(bld);

};

// ---   *   ---   *   ---
// runs application

void DARK::loop(void) {

  auto& Chasm = CHASM::ice();
  auto& Sin   = SIN::ice();

  Sin.unbind_batch();

  CHASM_RUN(
    (void*) &this->draw_data,
    (void*) &this->logic_data

  );

};

// ---   *   ---   *   ---
// draw prologue

void DARK::draw_prologue(void) {
  this->cam.get_view();
  this->cam.get_visible();

};

// ---   *   ---   *   ---
// ^epilogue

void DARK::draw_epilogue(void) {

  auto& Sin=SIN::ice();

  Sin.draw_enqueued();
  this->draw_ui();

};

// ---   *   ---   *   ---
// default drawing routine

int DARK::defdraw(void* data) {

  auto& Sin = SIN::ice();
  auto  bat = (Nodes*) data;

  // walk objects
  for(auto& node : *bat) {
    node.draw();

  };

  return bat->size();

};

// ---   *   ---   *   ---
// ^wrapper

int DARK::draw(void* data) {

  auto& Dark=DARK::ice();

  Dark.draw_prologue();
  int out=Dark.draw_f(data);

  Dark.draw_epilogue();

  return out;

};

// ---   *   ---   *   ---
// draw step for ui panels

void DARK::draw_ui(void) {

  for(auto& ref : m_ui) {
    auto& panel=ref.get();

    if(panel.enabled()) {
      panel.draw();

    };

  };

};

// ---   *   ---   *   ---
// ^TODO: same Fs for logic

void DARK::logic_prologue(void) {};
void DARK::logic_epilogue(void) {
  this->logic_ui();

};

int DARK::deflogic(void* data) {
  return 1;

};

// ---   *   ---   *   ---
// ^wrapper

int DARK::logic(void* data) {

  auto& Dark=DARK::ice();

  Dark.logic_prologue();
  int out=Dark.logic_f(data);

  Dark.logic_epilogue();

  return out;

};

// ---   *   ---   *   ---
// logic step for ui panels

void DARK::logic_ui(void) {

  for(auto& ref : m_ui) {
    auto& panel=ref.get();

    if(panel.enabled()) {
      panel.update();

    };

  };

};

// ---   *   ---   *   ---
// ui control

void DARK::register_panel(UI_Panel& panel) {
  m_ui.push_back(panel);

};

// ---   *   ---   *   ---
// get user-controlled node

Node& DARK::player(void) {
  auto& Dark=DARK::ice();
  return Dark.cam;

};

// ---   *   ---   *   ---
