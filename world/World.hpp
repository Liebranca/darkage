#ifndef __7E_WORLD_H__
#define __7E_WORLD_H__

// ---   *   ---   *   ---
// deps

  #include "gaoler/Frustum.hpp"
  #include "world/Cell.hpp"

// ---   *   ---   *   ---
// info

class World {

public:

  VERSION   "v0.00.2b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// sugar

  typedef std::vector<uint64_t> Slots;

// ---   *   ---   *   ---
// attrs

private:

  Map3D m_cell;

  Nodes m_nodes;
  Slots m_free;

  uint64_t m_size;

// ---   *   ---   *   ---
// guts

  uint64_t pop_id(void);
  void push_id(uint64_t id);

// ---   *   ---   *   ---
// iface

public:

  // cstruc
  void nit(uvec3& dim);

  // ctrash
  World(void) {};

  // get cellref from position
  Cell& cellof(vec3& pos);

  // create node at cell
  Node& push_node(Node::Bld& bld);

  // ^remove
  void pop_node(Node& node);

  // get visible cells
  void cells_in_frustum(
    Map1D_Ref&     dst,
    Gaol::Frustum& frus

  );

  // get object from id
  Node& get_node(uint64_t id) {
    return m_nodes[id];

  };

  // get cell count
  uint64_t get_size(void) {
    return m_size;

  };

};

// ---   *   ---   *   ---

#endif // __7E_WORLD_H__
