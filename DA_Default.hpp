#ifndef __5E_DA_DEFAULT_H__
#define __5E_DA_DEFAULT_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"

  #include "sin/mesh/JOJ_Sprite.hpp_sg"
  #include "sin/mesh/M3D.hpp_sg"

  #include "input/Ctl.hpp"
  #include "input/WASD.hpp"

// ---   *   ---   *   ---
// info

namespace DA_Default {

  VERSION   "v0.00.1b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// ROM

  static Kbd::Keyset keys {
    KB_CTL,
    KB_WASD

  };

  static shader::List programs {
    &shader::mesh::JOJ_Sprite,
    &shader::mesh::M3D

  };

};

// ---   *   ---   *   ---

#endif // __5E_DA_DEFAULT_H__
