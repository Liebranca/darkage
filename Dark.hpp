#ifndef __7E_DARK_H__
#define __7E_DARK_H__

// ---   *   ---   *   ---
// deps

  #include <functional>

  #include "bitter/kvrnel/GLM.hpp"
  #include "bitter/kvrnel/Clock.hpp"

  #include "chasm/Chasm.hpp"
  #include "sin/shader/Params.hpp"

  #include "world/Camera.hpp"
  #include "world/World.hpp"

  #include "ui/Panel.hpp"

// ---   *   ---   *   ---
// info

class DARK {

public:

  VERSION   "v0.00.3b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// helpers

  struct Screen {

    float    fov    = 45.0f;
    float    scale  = 0.0055f;

    float    znear  = 0.1f;
    float    zfar   = 100.0f;

    ivec2    size   = {640,480};
    uint64_t wflags = Win::DO_MOUSE_TRAP;

    bool     full   = false;

  };

// ---   *   ---   *   ---
// attrs

  Screen       screen;
  Camera       cam;

  World        world;

  Kbd::Keyset  keyset;
  shader::List programs;

  float        fps=60;

// ---   *   ---   *   ---
// default routines

  static int defdraw(void* data);
  static int deflogic(void* data);

  CHASM::Loop  draw_f  = &defdraw;
  CHASM::Loop  logic_f = &deflogic;

// ---   *   ---   *   ---
// guts

private:

  // ^wrap around draw step
  // with routines that run
  // before and after
  static int draw(void* data);
  void draw_prologue(void);
  void draw_epilogue(void);
  void draw_ui(void);

  // ^same for logic step
  static int logic(void* data);
  void logic_prologue(void);
  void logic_epilogue(void);
  void logic_ui(void);

  Nodes draw_data;
  Nodes logic_data;

  typedef std::vector<
    std::reference_wrapper<UI_Panel>

  > UI_Panels;

  UI_Panels m_ui;

  void load_shaders(void);

// ---   *   ---   *   ---
// iface

public:

  // cstruc
  DARK(void);
  ~DARK(void) {};

  SINGLETON(DARK);

// ---   *   ---   *   ---
// scene

  void spawn_window(
    std::string name="dark"

  );

  void spawn_camera(

    const vec3& pos={0,0,10},
    const quat& rot={1,0,0,0},

    bool ortho=false

  );

  void spawn_world(void);

  Node& spawn_object(

    uint32_t meshid,
    uint8_t  type,

    T3D      xform=T3D()

  );

  void loop(void);

// ---   *   ---   *   ---
// ui control

  void register_panel(UI_Panel& panel);

// ---   *   ---   *   ---
// getters

  static Node& player(void);

  inline Nodes& visible_objects(void) {
    return draw_data;

  };

// ---   *   ---   *   ---
// program clock wrappers

  Clock& get_clock(void);

  inline float fBy(void) {
    return this->get_clock().fBy();

  };

  inline void set_timescale(float x) {
    this->get_clock().set_scale(x);

  };

  inline float get_timescale(void) {
    return this->get_clock().get_scale();

  };

};

// ---   *   ---   *   ---

#endif // __7E_DARK_H__
