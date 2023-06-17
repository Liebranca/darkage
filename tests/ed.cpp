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

  Modeler Mod;

// ---   *   ---   *   ---
// spawn meshes

void load_resources(void) {

  auto& Sin=SIN::ice();

  Sin.new_batch(SIN::MESH);

  auto j0 = Mod.new_joint();
  auto j1 = Mod.new_joint();

  vec3 p0 = {0, 0.5f,0};
  vec3 p1 = {0,-0.5f,0};

  Mod.joint(j0).get_xform().move(p0);
  Mod.joint(j1).get_xform().move(p1);

  Mod.joint(j0).set_base(0);
  Mod.joint(j0).set_profile(11);

  Mod.joint(j1).set_base(11);
  Mod.joint(j1).set_profile(11);

  Mod.join(j0,j1);
  Mod.cap(j0,false);
  Mod.cap(j1,true);

  uint32_t me0=Sin.batch->new_edit();
  Sin.batch->repl(me0,Mod.get_packed());

};

// ---   *   ---   *   ---
// ^instance

void load_objects(void) {
  auto& Dark=DARK::ice();
  Dark.spawn_object(0,Node::STATIC);

};

// ---   *   ---   *   ---
// debug draw for vertex ring

void draw_joint(

  uint16_t joint_id,

  uint8_t  point_color = 0xF9,
  uint8_t  line_color  = 0x4D

) {

  auto& Sin   = SIN::ice();

  auto& pts   = Mod.get_deformed();
  auto  range = Mod.get_joint_dverts(joint_id);

  for(auto i=range[0];i<range[1];i++) {
    Sin.draw_point(pts[i].co,point_color,8.0f);

  };

  for(auto i=range[0];i<range[1]-1;i++) {

    auto& a=pts[i+0].co;
    auto& b=pts[i+1].co;

    Sin.draw_line(a,b,line_color,1.0f);

  };

  Sin.draw_line(

    pts[range[1]-1].co,
    pts[range[0]].co,

    line_color,
    0.75f

  );

};

// ---   *   ---   *   ---
// ^draw triangles of modeler mesh

void draw_mod_tris(
  uint8_t line_color=0x8A

) {

  auto& Sin   = SIN::ice();

  auto& pts   = Mod.get_deformed();
  auto& faces = Mod.get_faces();

  for(auto& face : faces) {

    for(uint16_t i=0;i<face.size()-2;i+=2) {

      auto& a=pts[face[i+0].get().idex].co;
      auto& b=pts[face[i+1].get().idex].co;
      auto& c=pts[face[i+2].get().idex].co;

      Sin.draw_line(a,b,line_color,0.3f);
      Sin.draw_line(b,c,line_color,0.3f);
      Sin.draw_line(c,a,line_color,0.3f);

    };

  };

};

// ---   *   ---   *   ---
// selfex

int logic(void* data) {

  View::load_cache();
  View::mouse_3D();

//  draw_joint(0);
//  draw_joint(1);
//
//  draw_mod_tris();

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
//  Test_Panel.enable();

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
