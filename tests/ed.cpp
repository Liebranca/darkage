// ---   *   ---   *   ---
// deps

  #include "gaoler/Box.hpp"

  #include "Dark.hpp"

  #include "logic/Move.hpp"
  #include "logic/View.hpp"

// ---   *   ---   *   ---
// spawn meshes

void load_resources(void) {

  auto& Sin=SIN::ice();

  Sin.new_batch(SIN::PROGRAM2);

  uint32_t me0=Sin.batch->new_edit();
  uint32_t me1=Sin.batch->new_edit();

  CRK::Prim p0;
  CRK::Prim p1;

  Gaol::Box box0;
  Gaol::Box box1;

  vec3 origin {0,0,0};

  // target
  box0.set(origin,0.5f,0.5f,0.5f);
  box0.to_mesh(p0);
  p0.tris_to_lines();

  Sin.batch->repl(me0,p0,GL_LINES);

  // pointer
  box1.set(origin,0.1f,0.1f,0.1f);
  box1.to_mesh(p1);
  p1.tris_to_lines();

  Sin.batch->repl(me1,p1,GL_LINES);

};

// ---   *   ---   *   ---
// ^instance

void load_objects(void) {

  auto& Dark = DARK::ice();

  Dark.spawn_object(0,Node::STATIC);
  Dark.spawn_object(1,Node::STATIC);

};

// ---   *   ---   *   ---
// selfex

int logic(void* data) {

  View::load_cache();
  View::mouse_3D();

  return 1;

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

  Dark.spawn_camera();
  Dark.loop();

  return 0;

};

// ---   *   ---   *   ---
