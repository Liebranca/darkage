// ---   *   ---   *   ---
// deps

  #include "DA.hpp"

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

  auto& Dark = DA::ice();
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

    auto  hax = cam.get_hax() * mo.y;

    glm::quat y {1,-hax.x,hax.y,-hax.z};
    glm::quat x {1,0,-mo.x,0};

    glm::quat r=x*y;
    glm::vec3 v={r.x,r.y,r.z};

    v*=4;

    cam.set_angvel(v);
    cam.ang_fmotion();

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

  auto& Dark=DA::ice();

  Dark.spawn_window(

    "sined",

    &DA::defdraw,
    &logic

  );

  load_resources();
  load_objects();

  Dark.spawn_camera();
  Dark.loop();

  return 0;

};

// ---   *   ---   *   ---
