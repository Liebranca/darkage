#ifndef __7E_CELL_H__
#define __7E_CELL_H__

// ---   *   ---   *   ---
// deps

  #include "world/Node.hpp"

// ---   *   ---   *   ---
// info

class Cell {

public:

  VERSION   "v0.00.1b";
  AUTHOR    "IBN-3DILA";

  cxr32 SIZE=4.0f;

// ---   *   ---   *   ---
// sugar

  typedef std::vector<uint16_t> Slots;

// ---   *   ---   *   ---
// attrs

private:

  Gaol::Bound m_bound;

  Slots m_slot;
  Slots m_free;
  Slots m_nodes;

  vec3  m_relpos;
  vec3  m_abspos;

  bool  m_updated;

// ---   *   ---   *   ---
// guts

  void filter_nodes(void);

// ---   *   ---   *   ---
// iface

public:

  // cstruc
  Cell(ivec3& pos);

  // book-keep objects in area
  void enter(Node& node);
  void leave(uint64_t i);

  // getters
  Gaol::Bound& bound(void) {
    return m_bound;

  };

  Slots& get_nodes(void);

};

// ---   *   ---   *   ---
// sugar

typedef std::vector<Cell>  Map1D;

typedef std::vector<Map1D> Map2D;
typedef std::vector<Map2D> Map3D;

// ---   *   ---   *   ---

#endif // __7E_CELL_H__
