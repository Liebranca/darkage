// ---   *   ---   *   ---
// NODE
// An abstract generality
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include "sin/Sin.hpp"
  #include "Dark.hpp"

  #include "world/Node.hpp"

// ---   *   ---   *   ---
// fetch noderef from
// collision handler

Node& Collision::node(void) {
  auto& Dark=DARK::ice();
  return Dark.world.get_node(this->id-1);

};

// ---   *   ---   *   ---
// cstruc

void Node::nit(Bld& bld) {

  m_xform     = bld.xform;
  m_draw_data = bld.draw;

  this->calc_bounds();

};

// ---   *   ---   *   ---
// keeps track of where the
// node is within spacepart

void Node::spacepart_track(
  vec3& co,
  bool  tele

) {

  auto& Dark     = DARK::ice();
  auto& world    = Dark.world;

  auto& old_cell = world.cellof(
    this->get_pos()

  );

  (tele)
    ? m_xform.teleport(co)
    : m_xform.move(co)
    ;

  m_updated.bounds   = true;
  m_updated.movement = true;

  auto& new_cell = world.cellof(
    this->get_pos()

  );

  if(&new_cell != &old_cell) {
    old_cell.leave(m_cell_id);
    new_cell.enter(*this);

  };

};

// ---   *   ---   *   ---
// regenerate physbody

void Node::calc_bounds(void) {

  vec3 dim(0.5f,0.5f,0.5f);

  m_bound.set(

    m_xform.get_model(),
    m_xform.position(),

    dim

  );

  m_updated.bounds=false;

};

// ---   *   ---   *   ---
// ^test against other

bool Node::boundschk(Node& other) {

  auto& s0=m_bound.sphere();
  auto& s1=other.m_bound.sphere();

  // get coldata
  auto col=s0.isect_sphere(s1);

  if(col.hit()) {
    vec3 n=col.normal()*0.05f;
    this->set_linvel(n);

  };

  return col.hit();

};

// ---   *   ---   *   ---
// push draw command to Q

void Node::draw(void) {

  auto& Sin    = SIN::ice();
  auto& data   = this->draw_data();

  auto  meshid = (data.type==ANIMATED)
    ? Sin.sprites[data.mesh].play()
    : Sin.sprites[data.mesh].get_cpose_abs()
    ;

  Sin.enqueue(

    data.batch,
    meshid,

    this->xform().get_model(),
    this->xform().get_nmat()

  );

};

// ---   *   ---   *   ---
// moves accto set direction
// and linear velocity

void Node::lin_fmotion(void) {

  auto& Dark=DARK::ice();

  vec3 mvec=((
    (this->get_hax() * m_lindirn.x)
  + (this->get_up()  * m_lindirn.y)
  + (this->get_fwd() * m_lindirn.z)

  ) + m_linvel) * Dark.fBy();

  this->move(mvec);

};

// ---   *   ---   *   ---
// ^rotates

void Node::ang_fmotion(void) {

  auto& Dark=DARK::ice();

  vec3 dirn=((
    (this->get_hax() * m_angdirn.x)
  + (this->get_up()  * m_angdirn.y)
  + (this->get_fwd() * m_angdirn.z)

  ) + m_angvel) * Dark.fBy();

  quat rvec={1,dirn.x,dirn.y,dirn.z};

  this->rotate(rvec);

};

// ---   *   ---   *   ---
