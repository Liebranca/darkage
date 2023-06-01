#ifndef __5E_MOVEMENT_H__
#define __5E_MOVEMENT_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"
  #include "sin/world/Node.hpp"

// ---   *   ---   *   ---
// info

class Move {

public:

  VERSION   "v0.00.1b";
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

};

// ---   *   ---   *   ---

#endif // __5E_MOVEMENT_H__
