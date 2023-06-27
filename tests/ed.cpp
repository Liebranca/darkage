// ---   *   ---   *   ---
// deps

  #include "gaoler/Box.hpp"

  #include "sin/mesh/Modeler.hpp"

  #include "sin/Sin.hpp"
  #include "Dark.hpp"

  #include "logic/Move.hpp"
  #include "logic/View.hpp"
  #include "ui/Panel.hpp"
  #include "ui/VLink.hpp"

// ---   *   ---   *   ---
// GBL

  UI_Panel Test_Panel(

    {-0.8f,0.8f},

    0.5f,
    0.5f

  );

  Modeler  Mod;

  uint16_t Sel_Ring=0xFFFF;

  uint32_t Edit_Mesh;
  uint32_t Edit_Batch;

  UI_VLink<Modeler::Ring,float> Link_Test;

// ---   *   ---   *   ---
// spawn meshes

void load_resources(void) {

  auto& Sin=SIN::ice();

  Edit_Batch=Sin.new_batch(SIN::MATBAKE,64);

  Mod.uv_cut(0.0f,0.0f,1.0f);

  auto r0=Mod.new_ring();
  Mod.ring(r0).set_base(0);
  Mod.ring(r0).set_radius(1.0f);
  Mod.ring(r0).set_profile(4);
  Mod.push_uv_row(r0);

  auto i0=Mod.inset(r0,2,0.5f);

  Mod.nrot(r0,16);
  Mod.nrot(i0[0],8);
  Mod.nrot(i0.back(),16);

  auto e0=Mod.extrude(
    i0.back(),1,1.0f,false

  );

  Mod.nrot(e0.back(),16);

  auto i1=Mod.inset(e0.back(),1,0.2f);
  Mod.uv_cut(0.0f,0.0f,1.0f);

  Mod.cap(i1.back());

  auto r1=Mod.new_ring(r0);
  Mod.push_uv_row(r1);
  auto e1=Mod.extrude(r1,1,0.2f,true);
  Mod.ring(e1.back()).occlude(0.0f);

  Edit_Mesh=Sin.batch->new_edit();

  Sin.batch->repl(Edit_Mesh,Mod.get_packed());

  Sin.batch->set_texture(
    Edit_Mesh,
    "/home/lyeb/Cruelty/Chars/matmk/planks_a.png"

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

  line_color=(ring_id==Sel_Ring)
    ? 0xF3
    : line_color
    ;

  auto& Sin  = SIN::ice();
  auto& pts  = Mod.get_deformed();
  auto& ring = Mod.ring(ring_id);

  uint16_t cnt  = 0;
  uint16_t prof = ring.get_profile();

  svec<uint16_t> vi;

  for(auto& vert : ring.get_verts()) {

    if(cnt==prof) {
      break;

    };

    uint16_t i=vert.idex;
    Sin.draw_point(pts[i].co,point_color,8.0f);

    vi.push_back(i);

    cnt++;

  };

  for(auto i=0;i<vi.size()-1;i++) {

    auto& a=pts[vi[i+0]].co;
    auto& b=pts[vi[i+1]].co;

    Sin.draw_line(a,b,line_color,1.0f);

  };

  Sin.draw_line(

    pts[vi.back()].co,
    pts[vi[0]].co,

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
// point selection test

void get_closest_point(void) {

  auto& Sin    = SIN::ice();
  auto& Chasm  = CHASM::ice();
  auto& Dark   = DARK::ice();

  auto& cam    = Dark.cam;
  auto& rat    = Chasm.ev.get_rat();

  auto  lclick = rat.clicks(Rat::LEFT);
  auto& pts    = Mod.get_deformed();

  for(uint16_t i=0;i<Mod.ring_cnt();i++) {

    auto& ring  = Mod.ring(i);
    auto& verts = ring.get_verts();

    svec<vec3> cords;
    cords.resize(verts.size());

    // map cords to pts.co
    uint16_t j=0;
    for(auto& co : cords) {
      co=pts[verts[j++].idex].co;

    };

    auto sorted = cam.sort_closest(cords);
    bool found  = false;

    for(auto p : cords) {

      auto col=View::mouse_over_point(p);

      if(col.hit()) {

        Sin.draw_point(p,0xF3,16.0f);
        found=true;

        break;

      };

    };

    if(found) {

      if(lclick) {
        Sel_Ring=i;
        Link_Test.set_object(0,ring);

      };

      break;

    };

  };

};

// ---   *   ---   *   ---
// selfex

int logic(void* data) {

  View::load_cache();
  View::mouse_3D();

  for(uint16_t i=0;i<Mod.ring_cnt();i++) {
    draw_ring(i);

  };

  draw_mod_tris();
  get_closest_point();

  if(Sel_Ring != 0xFFFF) {

    auto& e1=Test_Panel.elem(1);

    e1.ct=std::to_string(
      Link_Test.get_attr(0)

    );

  };

  return 1;

};

// ---   *   ---   *   ---
// "on-ui-click" test

void ui_elem_active(void) {

  auto& Sin=SIN::ice();

  if(Sel_Ring == 0xFFFF) {
    return;

  };

  auto& e1 = Test_Panel.elem(1);
  auto& v  = Link_Test.get_attr(0);

  v+=0.1f;

  Link_Test.set_attr(0,v);

  Sin.bind_batch(Edit_Batch);
  Sin.batch->repl(Edit_Mesh,Mod.get_packed());

};

// ---   *   ---   *   ---
// makes ui elems

void load_ui(void) {

  auto& Dark=DARK::ice();

  auto& e0=Test_Panel.push();
  e0.ct="Radius:";

  auto& e1=Test_Panel.push();
  e1.ct="0.5f";
  e1.ghost=false;
  e1.on_active=ui_elem_active;

  e1.color_default = {.packed=0xF8F7};
  e1.color_hover   = {.packed=0xF8F2};

  Link_Test.getset_procs(
    &Modeler::Ring::get_radius,
    &Modeler::Ring::set_radius

  );

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
