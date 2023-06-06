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

  float h   = Cell::SIZE/2.0f;

  // TODO: set from relative
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
