// ---   *   ---   *   ---
// deps

  #include "Dark.hpp"

  #include "logic/Move.hpp"
  #include "logic/View.hpp"

// ---   *   ---   *   ---
// spawn meshes

void load_resources(void) {

  auto& Sin=SIN::ice();

  Sin.new_batch(SIN::PROGRAM1);
  Sin.batch->new_edit();

};

// ---   *   ---   *   ---
// ^instance

void load_objects(void) {

  auto& Dark = DARK::ice();
  auto& Sin  = SIN::ice();

  Dark.draw_data.push_back(
    Sin.new_node(0,Node::STATIC)

  );

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

  Dark.spawn_window(

    "sined",

    &DARK::defdraw,
    &logic

  );

  load_resources();
  load_objects();

  Dark.spawn_camera();
  Dark.loop();

  return 0;

};

// ---   *   ---   *   ---
