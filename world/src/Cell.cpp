// ---   *   ---   *   ---
// CELL
// A single unit of mass
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include "world/Cell.hpp"

// ---   *   ---   *   ---
// cstruc

Cell::Cell(ivec3& pos) {

  m_abspos  = {pos.x,pos.y,pos.z};
  m_abspos *= Cell::SIZE;

  // TODO: calc position relative
  //       to moving world origin
  m_relpos  = m_abspos;

  float h   = Cell::SIZE/2.0f;

  // TODO: set/reset from relative
  vec3 dim {h,h,h};
  mat4 model = IDENTITY;

  m_bound.set(model,m_abspos,dim);

};

// ---   *   ---   *   ---
// object enters area

void Cell::enter(Node& node) {

  static uint64_t top=0;

  uint64_t i;

  // use previously fred slot
  if(m_free.size()) {
    i=m_free.back();
    m_free.pop_back();

  // ^make new
  } else {
    i=top++;
    m_slot.push_back(0x00);

  };

  m_slot[i]=node.get_world_id()+1;
  node.set_cell_id(i);

  printf("NODE %u entered cell\n",i);

  m_updated=true;

};

// ---   *   ---   *   ---
// ^object leaves area

void Cell::leave(uint64_t i) {
  m_free.push_back(i);
  m_slot[i]=0x00;

  m_updated=true;

};

// ---   *   ---   *   ---
// filters m_slot for non-zero ids

void Cell::filter_nodes(void) {

  m_nodes.clear();
  for(auto& id : m_slot) { if(id) {
    m_nodes.push_back(id-1);

  }};

};

// ---   *   ---   *   ---
// gets list of node ids in cell

Cell::Slots& Cell::get_nodes(void) {

  if(m_updated) {
    this->filter_nodes();
    m_updated=false;

  };

  return m_nodes;

};

// ---   *   ---   *   ---
// reserves memory for N cells
// *should* make pushing more
// efficient

Map1D_Sort::Map1D_Sort(uint64_t size) {

  m_unsorted.reserve(size);
  m_pending.reserve(size);
  m_dist.reserve(size);

};

// ---   *   ---   *   ---
// add reference and distance
// to unsorted list

void Map1D_Sort::push(Cell& cell) {

  // get distance to near plane
  float distance=glm::distance(
    cell.get_pos(),
    m_origin

  );

  // save unsorted elem
  m_pending.push_back(
    m_unsorted.size()

  );

  m_unsorted.push_back(cell);
  m_dist.push_back(distance);

};

// ---   *   ---   *   ---
// ^use saved distances to
// write sorted list

void Map1D_Sort::sort(Map1D_Ref& dst) {

  while(m_pending.size()) {

    uint64_t near_i = 0;
    float    near_d = 9999.99f;

    // find closest out of remaining
    for(auto i : m_pending) {

      float dist=m_dist[i];

      if(dist < near_d) {
        near_i=i;
        near_d=dist;

      };

    };

    // remove found and push to dst
    m_pending.erase(
      m_pending.begin()+near_i

    );

    dst.push_back(m_unsorted[near_i]);

  };

};

// ---   *   ---   *   ---
