#ifndef __7E_MOVE_H__
#define __7E_MOVE_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"
  #include "sin/world/Node.hpp"

// ---   *   ---   *   ---
// info

class Move {

public:

  VERSION   "v0.00.3b";
  AUTHOR    "IBN-3DILA";

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
// angular motion
  static void look_around(

    Node&      dst,
    glm::vec2& motion,

    float      mul=4.0f

  );

  static void look_around_point(

    Node&      dst,

    glm::vec2& motion,
    glm::vec3& point,

    float      distance,
    float      mul=4.0f

  );

// ---   *   ---   *   ---
// linear motion

  static void drag(

    Node&      dst,
    glm::vec2& motion,

    float      mul=4.0f

  );

  static void smooth_to(

    Node&      dst,

    glm::vec3& beg,
    glm::vec3& end,

    float      step=SMEPS

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
