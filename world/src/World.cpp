// ---   *   ---   *   ---
// WORLD
// You can change it
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include "world/World.hpp"

// ---   *   ---   *   ---
// cstruc

void World::nit(uvec3& dim) {

  int32_t hx=dim.x/2;
  int32_t hy=dim.y/2;
  int32_t hz=dim.z/2;

  m_size=0;

  // triple crap!
  for(int32_t z=0;z<dim.z;z++) {
    m_cell.push_back(Map2D());

    for(int32_t y=0;y<dim.y;y++) {
      m_cell[z].push_back(Map1D());

      for(int32_t x=0;x<dim.x;x++) {
        ivec3 pos {x-hx,y-hy,z-hz};
        m_cell[z][y].push_back(Cell(pos));

        m_size++;

      };

    };

  };

};

// ---   *   ---   *   ---
// get id for new node

uint64_t World::pop_id(void) {

  static uint64_t top=0;

  uint64_t out;

  // use previously fred id
  if(m_free.size()) {
    out=m_free.back();
    m_free.pop_back();

  // ^make new
  } else {
    out=top++;
    m_nodes.push_back(Node());

  };

  return out;

};

// ---   *   ---   *   ---
// ^return fred id to stack

void World::push_id(uint64_t id) {
  m_free.push_back(id);

};

// ---   *   ---   *   ---
// TODO get cellref from position

Cell& World::cellof(vec3& pos) {
  return m_cell[0][0][0];

};

// ---   *   ---   *   ---
// create node at cell

Node& World::push_node(Node::Bld& bld) {

  uint64_t id   = this->pop_id();
  auto&    node = m_nodes[id];

  node.nit(bld);
  node.set_world_id(id);
  node.enable();

  auto& cell=this->cellof(node.get_pos());
  cell.enter(node);

  return node;

};

// ---   *   ---   *   ---
// ^remove

void World::pop_node(Node& node) {

  uint64_t id=node.get_world_id();
  this->push_id(id);

  node.disable();

};

// ---   *   ---   *   ---
// get visible cells

void World::cells_in_frustum(
  Map1D_Ref&     dst,
  Gaol::Frustum& frus

) {

  Map1D_Sort data(m_size);

  // get refpoint in near plane
  auto&  planes = frus.box().planes();
  data.m_origin = planes[
    Gaol::Box::FRONT

  ].centroid();

  // walk cells
  for(auto& col  : m_cell) {
  for(auto& row  : col   ) {
  for(auto& cell : row   ) {

    // store visible
    if(0 < frus.isect_bound(cell.bound())) {
      data.push(cell);

    };

  }}};

  // write sorted to dst
  data.sort(dst);

};

// ---   *   ---   *   ---
