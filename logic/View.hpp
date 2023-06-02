#ifndef __7E_VIEW_H__
#define __7E_VIEW_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"

  #include "chasm/input/Rat.hpp"
  #include "logic/Move.hpp"

// ---   *   ---   *   ---
// info

class View {

public:

  VERSION   "v0.00.2b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// attrs

private:

  struct Cache {

    glm::vec2 mouse_motion = {0,0};

    glm::vec3 cam_target   = {0,0,0};
    glm::vec3 cam_to_vto   = {0,0,0};
    float     cam_to_dist  = 10.0f;

    Move::Async_Smooth xition;

  };

  // private static nit in func
  static Cache& m_cache(void) {
    static Cache cache;
    return cache;

  };

  // cache-calc rat movement
  // times frame delta
  static void get_mouse_motion(void);

  // cache-calc camera to origin
  static void get_cam_to(void);

// ---   *   ---   *   ---
// iface

public:

  // get rat movement times
  // frame delta from cache
  static inline glm::vec2& mouse_motion(void) {
    return m_cache().mouse_motion;

  };

  // get direction from camera to target
  static inline glm::vec3& cam_to_vto(void) {
    return m_cache().cam_to_vto;

  };

  static inline float cam_to_dist(void) {
    return m_cache().cam_to_dist;

  };

  // ^selfex
  static inline glm::vec3& cam_target(void) {
    return m_cache().cam_target;

  };

  // rotate camera around
  // itself by rat motion
  static void mouse_look(void);

  // ^rotate camera around point
  static void mouse_look_at(glm::vec3& point);

  // ^drag camera around
  static void mouse_drag(void);

  // TODO: mouse_drag_object

  // ^move camera X away/closer to target
  static void mouse_zoom(float x);

  // common control scheme for
  // controling a 3D viewport
  static void mouse_3D(
    uint8_t drag_b=Rat::RIGHT,
    uint8_t view_b=Rat::LEFT

  );

  // book-keeping
  static void clear_cache(void);
  static void load_cache(void);

};

// ---   *   ---   *   ---

#endif // __7E_VIEW_H__
