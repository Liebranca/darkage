#ifndef __7E_UI_PANEL_H__
#define __7E_UI_PANEL_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/GLM.hpp"

// ---   *   ---   *   ---
// info

class UI_Panel {

public:

  VERSION   "v0.00.1b";
  AUTHOR    "IBN-3DILA";

  cx8 ELEM_DEFAULT = 0b00;
  cx8 ELEM_HOVER   = 0b01;
  cx8 ELEM_ACTIVE  = 0b10;

// ---   *   ---   *   ---
// helpers

  struct Color {

    union {

      struct {
        uint8_t fg_i:4;
        uint8_t fg_a:4;
        uint8_t bg_i:4;
        uint8_t bg_a:4;

      };

      uint16_t packed;

    };

  };

  struct Elem {

    std::string ct;

    float    scale     = 4.0f;
    uint32_t state     = 0b0000;

    nihil    on_active = noop;

    uint32_t own_id;
    uint32_t sin_id;

    Color color_default = {.packed=0x00F7};
    Color color_hover   = {.packed=0xF8F2};
    Color color_active  = {.packed=0xF1F3};

    uint16_t get_color(void);

    bool show_ctl = false;
    bool enabled  = true;

  };

  typedef std::vector<Elem> Elems;
  typedef std::vector<uint32_t> Elem_IDs;

// ---   *   ---   *   ---
// attrs

private:

  vec2  m_pos;
  vec2  m_dim;

  vec2  m_offset;
  Elems m_elems;

  bool  m_enabled = false;

// ---   *   ---   *   ---
// guts

  uint32_t draw_elem(Elem& e);
  void update_elem(Elem& e);

// ---   *   ---   *   ---
// iface

public:

  // cstruc
  UI_Panel(

    vec2  pos,

    float cent_x,
    float cent_y

  );

  void nit(

    vec2  pos,

    float cent_x,
    float cent_y

  );

  // ^ctrash
  UI_Panel(void) {};

  // create new element
  Elem& push(void);

  // ^remove
  void pop(Elem& e);
  void pop(uint32_t id);

  // draw all elements
  void draw(void);

  // run logic step
  void update(void);

  // do not draw/update
  inline void disable(void) {
    m_enabled=false;

  };

  // ^undo
  inline void enable(void) {
    m_enabled=true;

  };

  // ^check
  inline bool enabled(void) {
    return m_enabled;

  };

};

// ---   *   ---   *   ---

#endif // __7E_UI_PANEL_H__
