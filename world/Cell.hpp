#ifndef __7E_CELL_H__
#define __7E_CELL_H__

// ---   *   ---   *   ---
// deps

  #include <functional>
  #include "world/Node.hpp"

// ---   *   ---   *   ---
// info

class Cell {

public:

  VERSION   "v0.00.2b";
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

  inline vec3& get_pos(bool rel=true) {
    return (rel) ? m_relpos : m_abspos;

  };

};

// ---   *   ---   *   ---
// sugar

typedef std::vector<Cell>  Map1D;

typedef std::vector<Map1D> Map2D;
typedef std::vector<Map2D> Map3D;

// jesus!
typedef std::vector<
  std::reference_wrapper<Cell>

>  Map1D_Ref;

// ---   *   ---   *   ---
// helpers

struct Map1D_Sort {

  Map1D_Ref m_unsorted;

  std::vector<float>    m_dist;
  std::vector<uint64_t> m_pending;

  vec3 m_origin;

  // cstruc
  Map1D_Sort(uint64_t size);

  // grow/solve
  void push(Cell& cell);
  void sort(Map1D_Ref& dst);

};

// ---   *   ---   *   ---

#endif // __7E_CELL_H__
