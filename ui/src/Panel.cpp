// ---   *   ---   *   ---
// UI PANEL
// Sticks to the screen
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include "chasm/Chasm.hpp"
  #include "sin/Sin.hpp"

  #include "logic/View.hpp"
  #include "ui/Panel.hpp"

// ---   *   ---   *   ---
// cstruc

UI_Panel::UI_Panel(

  vec2  pos,

  float cent_x,
  float cent_y

) {

  this->nit(pos,cent_x,cent_y);

};

void UI_Panel::nit(

  vec2  pos,

  float cent_x,
  float cent_y

) {

  m_pos=pos;

  m_dim={
    cent_x * UI::SIZE_X,
    cent_y * UI::SIZE_Y

  };

  m_offset={0,0};

};

// ---   *   ---   *   ---
// add elem to panel

uint32_t UI_Panel::draw_elem(
  UI_Panel::Elem& e

) {

  vec2 pos=m_pos+m_offset;

  vec3 dim={

    (m_dim.x-m_offset.x)
  / e.scale,

    (m_dim.y-m_offset.y)
  / e.scale,

    e.scale

  };

  auto&    Sin = SIN::ice();
  uint32_t id  = Sin.draw_text(

    e.ct,

    pos,
    dim,

    e.get_color(),
    e.show_ctl

  );

  m_offset+=Sin.ui_elem(id).get_rdim();

  return id;

};

// ---   *   ---   *   ---
// ^bat

void UI_Panel::draw(void) {

  m_offset={0,0};

  vec2 dim={
    m_dim.x * UI::CENT_X,
    m_dim.y * UI::CENT_Y

  };

  auto& Sin=SIN::ice();
  Sin.draw_rect(m_pos,dim,0x8000);

  for(auto& e : m_elems) {
    if(e.enabled) {
      e.sin_id=this->draw_elem(e);

    };

  };

};

// ---   *   ---   *   ---
// run logic step

void UI_Panel::update_elem(
  UI_Panel::Elem& e

) {

  auto& rat   = CHASM::ice().ev.get_rat();

  bool  hover = View::mouse_over_ui(e.sin_id);
  bool  click = rat.clicks(Rat::LEFT);

  e.state=ELEM_DEFAULT;

  e.state|=
    (ELEM_HOVER  * hover)
  | (ELEM_ACTIVE * click * hover)
  ;

  if(e.state & ELEM_ACTIVE) {
    e.on_active();

  };

};

// ---   *   ---   *   ---
// ^bat

void UI_Panel::update(void) {

  for(auto& e : m_elems) {
    if(e.enabled) {
      this->update_elem(e);

    };

  };

};

// ---   *   ---   *   ---
// create new element

UI_Panel::Elem& UI_Panel::push(void) {

  uint32_t id=m_elems.size();
  m_elems.push_back(Elem());

  auto& e  = m_elems.back();
  e.own_id = id;

  return e;

};

// ---   *   ---   *   ---
// ^remove

void UI_Panel::pop(UI_Panel::Elem& e) {
  this->pop(e.own_id);

};

void UI_Panel::pop(uint32_t id) {

  for(uint32_t i=id;i<m_elems.size();i++) {
    m_elems[i].own_id--;

  };

  m_elems.erase(m_elems.begin()+id);

};

// ---   *   ---   *   ---
// get packed 16-bit color value
// accto current state of elem

uint16_t UI_Panel::Elem::get_color(void) {

  switch(state) {

  case ELEM_HOVER:
    return color_hover.packed;

  case ELEM_ACTIVE:
  case ELEM_HOVER|ELEM_ACTIVE:
    return color_active.packed;

  case ELEM_DEFAULT:
  default:
    return color_default.packed;

  };

};

// ---   *   ---   *   ---
