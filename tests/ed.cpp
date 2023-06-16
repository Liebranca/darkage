// ---   *   ---   *   ---
// deps

  #include "gaoler/Box.hpp"

  #include "sin/mesh/Modeler.hpp"

  #include "sin/Sin.hpp"
  #include "Dark.hpp"

  #include "logic/Move.hpp"
  #include "logic/View.hpp"
  #include "ui/Panel.hpp"

// ---   *   ---   *   ---
// GBL

  UI_Panel Test_Panel(

    {-0.8f,0.8f},

    0.5f,
    0.5f

  );

// ---   *   ---   *   ---
// spawn meshes

void load_resources(void) {

  auto& Sin=SIN::ice();

  Sin.new_batch(SIN::MESH);

  Modeler sm;

  auto j0 = sm.new_joint();
  auto j1 = sm.new_joint();

  vec3 p0 = {0,0,0};
  vec3 p1 = {0,-2,0};

  sm.joint(j0).get_xform().move(p0);
  sm.joint(j1).get_xform().move(p1);

  sm.joint(j0).set_base(0);
  sm.joint(j0).set_profile(4);

  sm.joint(j1).set_base(4);
  sm.joint(j1).set_profile(4);

  sm.join(j0,j1);

  uint32_t me0=Sin.batch->new_edit();
  Sin.batch->repl(me0,sm.get_mesh());

};

// ---   *   ---   *   ---
// ^instance

void load_objects(void) {
  auto& Dark=DARK::ice();
  Dark.spawn_object(0,Node::STATIC);

};

// ---   *   ---   *   ---
// selfex

int logic(void* data) {
  View::load_cache();
  View::mouse_3D();

  auto& Sin=SIN::ice();

  Sin.draw_line(

    {0.5f,0.8f,0},
    {0.5f,-0.8f,0},

    0xF6,1.0f

  );

  return 1;

};

// ---   *   ---   *   ---
// "on-ui-click" test

void ui_elem_active(void) {
  printf("YOU CLICKED ME\n");

};

// ---   *   ---   *   ---
// makes ui elems

void load_ui(void) {

  auto& Dark=DARK::ice();

  auto& e0=Test_Panel.push();
  e0.ct="where the async at?";
  e0.on_active=ui_elem_active;

  auto& e1=Test_Panel.push();
  e1.ct="\x7F";

  e1.color_default = {.packed=0x00F1};
  e1.color_hover   = {.packed=0x00F9};

  Dark.register_panel(Test_Panel);
  Test_Panel.enable();

};

// ---   *   ---   *   ---
// the bit

int main(void) {

  auto& Dark=DARK::ice();

  Dark.logic_f=logic;

  Dark.spawn_window("sined");
  Dark.spawn_world();

  load_resources();
  load_objects();

  load_ui();

  Dark.spawn_camera();
  Dark.loop();

  return 0;

};

// ---   *   ---   *   ---
