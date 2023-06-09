#ifndef __7E_CAMERA_H__
#define __7E_CAMERA_H__

// ---   *   ---   *   ---
// deps

  #include <cmath>

  #include "bitter/kvrnel/GLM.hpp"
  #include "gaoler/Frustum.hpp"

  #include "sin/mesh/GBuff.hpp"
  #include "world/World.hpp"

// ---   *   ---   *   ---
// info

class Camera : public Node {

public:

  VERSION   "v2.00.9";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// helpers

  typedef struct {

    float width;
    float height;

    float scale;
    float fov;

    float near;
    float far;

// ---   *   ---   *   ---

    mat4 ortho(void) {

      float w=width;
      float h=height;

      w *= 0.5f;
      w *= scale;

      h *= 0.5f;
      h *= -scale;

      return glm::ortho(
        -w,w,-h,h,
        near,far

      );

    };

    mat4 persp(void) {

      float w=width;
      float h=height;

      w *= scale;
      h *= -scale;

      return glm::perspective(

        glm::radians(-fov),w/h,
        near,far

      );

    };

  } Lens;

// ---   *   ---   *   ---
// attrs

private:

  Camera::Lens  m_lens;

  Gaol::Frustum m_frustum;
  Map1D_Ref     m_cells;

  GBuff m_ubo;

  mat4  m_view;
  mat4  m_proj;
  mat4  m_stow;

  bool  m_ortho=false;

// ---   *   ---   *   ---
// guts

  // for VP to shader
  void nit_ubo(uint32_t loc);
  void update_ubo(bool which);

  // regenerate view matrix
  inline mat4 calc_view(void) {
    return glm::lookAt(

      this->get_pos(),

      this->get_pos()
    + this->get_fwd(),

      Y_AXIS

    );

  };

  // ^get screen-to-world matrix
  inline mat4 calc_stow(void) {

    return
      glm::inverse(m_view)
    * glm::inverse(m_proj)
    ;

  };

  // build prism from current view
  inline void update_frustum(void) {
    m_frustum.calc_box(

      this->get_pos(),

      this->get_fwd(),
      this->get_up()

    );

  };

  // frustum checks list of cells
  // from world, sorts by distance
  void calc_visible_cells(void);

// ---   *   ---   *   ---
// iface

public:

  // cstruc
  void nit(
    const vec3& pos,
    const quat& rot,

    Camera::Lens&    lens,

    uint32_t         bind_idex

  );

  // ctrash
  Camera(void) {};

  // get closest cord to self
  uint16_t closest(svec<vec3>& pts);

  // ^sort cords by distance to self
  svec<vec3> sort_closest(svec<vec3> pts);

// ---   *   ---   *   ---

  // frustum wrappers
  // used for visibility checks
  inline int sphere_in_frustum(
    Gaol::Sphere& sphere

  ) {

    return m_frustum.isect_sphere(sphere);

  };

  inline bool point_in_frustum(
    vec3& p

  ) {

    return m_frustum.isect_point(p);

  };

  inline bool points_in_frustum(
    Gaol::Points& pts

  ) {

    return m_frustum.isect_points(pts);

  };

  inline int bound_in_frustum(
    Gaol::Bound& b

  ) {

    return m_frustum.isect_bound(b);

  };

  inline bool box_in_frustum(Gaol::Box& box) {
    return m_frustum.isect_box(box);

  };

  inline int isect_frustum(Gaol::Frustum& other) {
    return m_frustum.isect_frustum(other);

  };

// ---   *   ---   *   ---
// get per-cell object visibility

  void get_visible(void);

// ---   *   ---   *   ---

  inline void use_ortho(void) {

    m_ortho = true;
    m_proj  = m_lens.ortho();

    m_updated.visibility = true;

    this->update_ubo(0);

  };

  inline void use_persp(void) {

    m_ortho  = false;
    m_proj   = m_lens.persp();

    m_updated.visibility = true;

    this->update_ubo(0);

  };

  inline bool is_ortho(void) {
    return m_ortho;

  };

// ---   *   ---   *   ---
// getters

  inline Camera::Lens& get_lens(void) {
    return m_lens;

  };

  inline float get_zfar(void) {
    return m_lens.far;

  };

  inline Gaol::Frustum& get_frustum(void) {
    return m_frustum;

  };

  mat4& get_view(void);

  inline mat4& get_stow(void) {
    return m_stow;

  };

  inline mat4& get_proj(void) {
    return m_proj;

  };

  inline vec3 get_eye(void) {

    return glm::normalize(
      this->get_pos()
    + this->get_fwd()

    );

  };

// ---   *   ---   *   ---
// space transforms

  inline vec3 screen_to_world(vec3& co) {
    return vec3(m_stow * vec4(co,1));

  };

  inline vec4 screen_to_world(vec4& co) {
    return m_stow * co;

  };

  vec3 world_to_screen(vec3& co) {
    return vec3(m_view * vec4(co,1));

  };

  vec4 world_to_screen(vec4& co) {
    return m_view * co;

  };

};

// ---   *   ---   *   ---

#endif // __7E_CAMERA_H__
