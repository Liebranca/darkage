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

  VERSION   "v0.00.2b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// guts

private:

// ---   *   ---   *   ---
// iface

public:

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

// ---   *   ---   *   ---
// angular control

  static void look_around(

    Node&      dst,
    glm::vec2& motion,

    float      mul=4.0f

  );

  static void look_around_point(

    Node&      dst,

    glm::vec2& motion,
    glm::vec3& point,

    float      mul=4.0f

  );

};

// ---   *   ---   *   ---

#endif // __7E_MOVEMENT_H__
