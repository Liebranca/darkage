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

  Sin.new_batch(SIN::MATBAKE,64);

  Mod.uv_cut(0.0f,0.0f,1.0f);

  auto r0=Mod.new_ring();
  Mod.ring(r0).set_base(0);
  Mod.ring(r0).set_radius(1.0f);
  Mod.ring(r0).set_profile(4);
  Mod.push_uv_row(r0);

  auto inset = Mod.inset(r0,2,0.5f);

  Mod.nrot(r0,-8);
  Mod.nrot(inset[0],-8);
  Mod.nrot(inset[1],-14);

//  auto inset_b=Mod.new_ring(inset.back());
  auto tube  = Mod.extrude(
    inset[1],1,1.0f,false

  );

  Mod.uv_cut(0.0f,0.0f,1.0f);

  auto r1=Mod.new_ring(r0);
  Mod.push_uv_row(r1);
  Mod.extrude(r1,1,0.2f,true);

  uint32_t me0=Sin.batch->new_edit();

  Sin.batch->repl(me0,Mod.get_packed());
  Sin.batch->set_texture(
    me0,"/home/lyeb/Cruelty/Chars/matmk/planks_a.png"

  );

};

// ---   *   ---   *   ---
// ^ice

void load_objects(void) {
  auto& Dark=DARK::ice();
  Dark.spawn_object(0,Node::STATIC);

};

// ---   *   ---   *   ---
// debug draw for vertex ring

void draw_ring(

  uint16_t ring_id,

  uint8_t  point_color = 0xF9,
  uint8_t  line_color  = 0x4D

) {

  auto& Sin   = SIN::ice();

  auto& pts   = Mod.get_deformed();
  auto  range = Mod.get_ring_dverts(ring_id);

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

      Sin.draw_line(a,b,line_color,0.5f);
      Sin.draw_line(b,c,line_color,0.5f);
      Sin.draw_line(c,a,line_color,0.5f);

    };

  };

};

// ---   *   ---   *   ---
// ^draw texcords

void draw_mod_uvs(
  uint8_t point_color = 0xFB,
  uint8_t line_color  = 0x87

) {

  auto& Sin   = SIN::ice();

  auto& pts   = Mod.get_deformed();
  auto& faces = Mod.get_faces();

  Sin.set_point_layer(1);

  for(uint16_t i=0;i<pts.size()-1;i++) {

    auto a=pts[i+0].uv * 0.5f;
    auto b=pts[i+1].uv * 0.5f;

    Sin.draw_line(a,b,line_color,2.0f);
    Sin.draw_point(a,point_color,8.0f);

  };

  auto a=pts.back().uv * 0.5f;
  Sin.draw_point(a,point_color,8.0f);

};

// ---   *   ---   *   ---
// selfex

int logic(void* data) {

  View::load_cache();
  View::mouse_3D();

//  draw_mod_uvs();

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
