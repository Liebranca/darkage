// ---   *   ---   *   ---
// deps

  #include "Dark.hpp"
  #include "logic/Move.hpp"

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

  auto& Sin   = SIN::ice();
  auto& Chasm = CHASM::ice();

  auto& rat   = Chasm.ev.get_rat();
  auto  mo    = rat.get_motion(0.01f);

  auto& cam   = Sin.cam;

  bool dx = fabs(mo.y) > 0.0001f;
  bool dy = fabs(mo.x) > 0.0001f;

  if(dx || dy) {
    glm::vec3 origin {0,0,0};
    Move::look_around_point(cam,mo,origin);

  };

  auto lclick = rat.clicks(Rat::LEFT);
  auto rclick = rat.clicks(Rat::RIGHT);

  if(lclick || rclick) {

    float sign = (lclick) ? -1 : 1;

    cam.set_lindirn_ax(2,sign * 4);

  };

  cam.lin_fmotion();

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
