#ifndef __7E_DARK_H__
#define __7E_DARK_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/GLM.hpp"

  #include "chasm/Chasm.hpp"
  #include "sin/Sin.hpp"

// ---   *   ---   *   ---
// info

class DARK {

public:

  VERSION   "v0.00.1b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// helpers

  struct Screen {

    float      fov    = 45.0f;
    float      scale  = 0.0055f;

    float      znear  = 0.1f;
    float      zfar   = 100.0f;

    ivec2 size   = {640,480};
    uint64_t   wflags = Win::DO_MOUSE_TRAP;

    bool       full   = false;

  };

  typedef std::vector<uint32_t> Nodes;

// ---   *   ---   *   ---
// attrs

  Screen       screen;
  float        fps      = 60;

  Kbd::Keyset  keyset;
  shader::List programs;

  Nodes        draw_data;
  Nodes        logic_data;

// ---   *   ---   *   ---
// default routines

  static int defdraw(void* data);
  static int deflogic(void* data);

// ---   *   ---   *   ---
// guts

private:
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

    std::string name    = "dark",

    CHASM::Loop draw_f  = &defdraw,
    CHASM::Loop logic_f = &deflogic

  );

  void spawn_camera(

    const vec3& pos={0,0,10},
    const quat& rot={1,0,0,0},

    bool ortho=false

  );

  void loop(void);

// ---   *   ---   *   ---
// getters

  static Node& player(void);

};

// ---   *   ---   *   ---

#endif // __7E_DARK_H__
