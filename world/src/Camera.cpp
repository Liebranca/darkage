// ---   *   ---   *   ---
// CAMERA
// Looks your way
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTOS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include <numeric>
  #include <GL/glew.h>

  #include "Dark.hpp"
  #include "world/Camera.hpp"

// ---   *   ---   *   ---
// fetch or regenerate view matrix

mat4& Camera::get_view(void) {

  if(m_updated.movement) {

    m_view  = this->calc_view();
    m_stow  = this->calc_stow();

    m_updated.movement = false;

    this->update_frustum();
    this->update_ubo(1);

    this->calc_visible_cells();

  };

  return m_view;

};

// ---   *   ---   *   ---
// frustum checks list of cells
// from world, sorts by distance

void Camera::calc_visible_cells(void) {

  auto& Dark=DARK::ice();
  m_cells.clear();

  // get list
  Dark.world.cells_in_frustum(
    m_cells,
    m_frustum

  );

};

// ---   *   ---   *   ---
// for uploading mats to shader

void Camera::nit_ubo(uint32_t idex) {

  m_ubo.nit(

    GBuff::D_UNIFORM,

    sizeof(mat4),
    2

  );

  m_ubo.bind_base(idex);

};

// ---   *   ---   *   ---
// ^send

void Camera::update_ubo(bool which) {

  auto& data=(which)
    ? m_view
    : m_proj
    ;

  m_ubo.sub_data((void*) &data[0][0],which,1);

};

// ---   *   ---   *   ---
// cstruc

void Camera::nit(

  const vec3& pos,
  const quat& rot,

  Camera::Lens&    lens,

  uint32_t         bind_idex

) {

  m_lens=lens;

  vec3 npos=pos;
  quat nrot=rot;

  this->move(npos);
  this->rotate(nrot);

  this->nit_ubo(bind_idex);

  m_frustum.set(

    lens.width,
    lens.height,

    lens.fov,
    lens.near,
    lens.far

  );

};

// ---   *   ---   *   ---
// get closest cord to self

uint16_t Camera::closest(svec<vec3>& pts) {

  uint16_t out  = 0;
  uint16_t i    = 0;

  float    near = 9999.9f;

  // walk list of cords
  for(auto& p : pts) {

    // get distance to self
    float dist=glm::distance(
      p,this->get_pos()

    );

    // ^is *closer* than previous
    if(dist < near) {
      near = dist;
      out  = i;

    };

    i++;

  };

  return out;

};

// ---   *   ---   *   ---
// sort cords by distance to self

svec<vec3> Camera::sort_closest(
  svec<vec3> pts

) {

  svec<vec3> out;
  out.resize(pts.size());

  for(auto& p : out) {

    uint16_t idex=this->closest(pts);

    p=pts[idex];
    pts.erase(pts.begin()+idex);

  };

  return out;

};

// ---   *   ---   *   ---
// TODO: culling from occluders

// ---   *   ---   *   ---
// get per-cell object visibility

void Camera::get_visible(void) {

  auto& Dark = DARK::ice();
  auto& dst  = Dark.visible_objects();

  dst.clear();
  for(auto& cell : m_cells) {
  for(auto& id   : cell.get().get_nodes()) {

    auto& node=Dark.world.get_node(id);
    if(this->bound_in_frustum(node.bound())) {
      dst.push_back(node);

    };

  }};

};

// ---   *   ---   *   ---
