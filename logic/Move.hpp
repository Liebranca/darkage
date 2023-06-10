#ifndef __7E_MOVE_H__
#define __7E_MOVE_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/GLM.hpp"
  #include "world/Node.hpp"

// ---   *   ---   *   ---
// info

class Move {

public:

  VERSION   "v0.00.3b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// helpers

  struct Async_Smooth {

    // input
    vec3 m_beg;
    vec3 m_end;
    uint32_t  m_frames = 0;

    // handled
    uint32_t  m_cnt    = 0;
    float     m_step   = 0.0f;

    // xition ended
    bool valid(void) {
      return m_frames != 0;

    };

    // exec next step
    void run(Node& dst);

  };

// ---   *   ---   *   ---
// guts

private:

  // distance epsilon for
  // movement smoothing
  cxr32 SMEPS=0.16f;

// ---   *   ---   *   ---
// iface

public:

  // wipes all loaded velocities
  static void clear(Node& dst);

// ---   *   ---   *   ---
// quick mathutils

  static quat q_from_motion(
    vec3& n,
    vec2& motion

  );

  static vec3 n_by_motion(
    vec3& n,
    vec2& motion

  );

// ---   *   ---   *   ---
// angular motion

  static void look_around(

    Node&      dst,
    vec2& motion,

    float      mul=4.0f

  );

  static Async_Smooth look_around_point(

    Node&      dst,

    vec2& motion,
    vec3& point,

    float      distance,
    float      mul=4.0f

  );

// ---   *   ---   *   ---
// linear motion

  static void drag(

    Node&      dst,
    vec2& motion,

    float      mul=4.0f

  );

  static void smooth_to(

    Node&      dst,

    vec3& beg,
    vec3& end,

    float      step

  );

  static Async_Smooth async_smooth_to(

    Node&      dst,

    vec3& beg,
    vec3& end,

    uint32_t   frames=8

  );

  static void zoom(

    Node&      dst,
    vec3& point,

    float      x

  );

// ---   *   ---   *   ---
// one liners

  static void fwd(Node& dst,float mul=4.0f);
  static void left(Node& dst,float mul=4.0f);
  static void back(Node& dst,float mul=4.0f);
  static void right(Node& dst,float mul=4.0f);

  static void stop_z(Node& dst);
  static void stop_x(Node& dst);

// ---   *   ---   *   ---
// ^ice

  static void player_fwd(void);
  static void player_left(void);
  static void player_back(void);
  static void player_right(void);

  static void player_stop_z(void);
  static void player_stop_x(void);

};

// ---   *   ---   *   ---

#endif // __7E_MOVEMENT_H__
