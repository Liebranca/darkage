#ifndef __7E_VIEW_H__
#define __7E_VIEW_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/GLM.hpp"

  #include "chasm/input/Rat.hpp"
  #include "logic/Move.hpp"

// ---   *   ---   *   ---
// info

class View {

public:

  VERSION   "v0.00.8b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// attrs

private:

  struct Cache {

    vec2  mouse_motion = {0,0};

    // screen/world cords
    vec2  mouse_pos_s  = {0,0};
    vec3  mouse_pos_w  = {0,0,0};

    vec3  cam_target   = {0,0,0};
    vec3  cam_to_vto   = {0,0,0};
    float cam_to_dist  = 10.0f;

    Move::Async_Smooth xition;
    Gaol::Line mouse_ray;

  };

  // private static nit in func
  static Cache& m_cache(void) {
    static Cache cache;
    return cache;

  };

  // cache-calc rat movement
  // times frame delta
  static void calc_mouse_motion(void);

  // cache-calc mouse position
  static void calc_mouse_pos(void);

  // cache-calc camera to mouse ray
  static void calc_mouse_ray(void);

  // cache-calc camera to origin
  static void calc_cam_to(void);

  // chk-run pending transition
  static void pending_xition(void);

// ---   *   ---   *   ---
// iface

public:

  // get rat movement times
  // frame delta from cache
  static inline vec2& mouse_motion(void) {
    return m_cache().mouse_motion;

  };

  // get rat position in screen cords
  static inline vec2& mouse_pos_s(void) {
    return m_cache().mouse_pos_s;

  };

  // ^world
  static inline vec3& mouse_pos_w(void) {
    return m_cache().mouse_pos_w;

  };

  // get camera to mouse ray
  static inline Gaol::Line& mouse_ray(void) {
    return m_cache().mouse_ray;

  };

  // get direction from camera to target
  static inline vec3& cam_to_vto(void) {
    return m_cache().cam_to_vto;

  };

  static inline float cam_to_dist(void) {
    return m_cache().cam_to_dist;

  };

  // ^selfex
  static inline vec3& cam_target(void) {
    return m_cache().cam_target;

  };

  // rotate camera around
  // itself by rat motion
  static void mouse_look(void);

  // ^rotate camera around point
  static void mouse_look_at(vec3& point);

  // ^drag camera around
  static void mouse_drag(void);

  // TODO: mouse_drag_object

  // ^move camera X away/closer to target
  static void mouse_zoom(float x);

  // mouse hover on specific object
  static Collision mouse_over(Node& node);

  // ^any visible object
  static Collision mouse_over_any(void);

  // ^ui element
  static bool mouse_over_ui(uint32_t idex);

  // common control scheme for
  // managing a 3D viewport
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
