#ifndef __7E_DA_DEFAULT_H__
#define __7E_DA_DEFAULT_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"

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

  static shader::List programs {};

};

// ---   *   ---   *   ---

#endif // __7E_DA_DEFAULT_H__
