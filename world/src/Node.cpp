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
// calc bounding box from list of cords

void Node::calc_bounds_dim(svec<vec3>& pts) {

  float x=0.0f;
  float y=0.0f;
  float z=0.0f;

  for(auto& pt : pts) {

    float fx=fabs(pt.x);
    float fy=fabs(pt.y);
    float fz=fabs(pt.z);

    x=(fx > x) ? fx : x;
    y=(fx > y) ? fx : y;
    z=(fx > z) ? fx : z;

  };

  m_bounds_dim=vec3({x,y,z});

};

// ---   *   ---   *   ---
// regenerate physbody

void Node::calc_bounds(void) {

  m_bounds.set(

    m_xform.get_model(),
    m_xform.position(),

    m_bounds_dim

  );

  m_updated.bounds=false;

};

// ---   *   ---   *   ---
// ^test against other

bool Node::boundschk(Node& other) {

  auto& s0=m_bounds.sphere();
  auto& s1=other.m_bounds.sphere();

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
