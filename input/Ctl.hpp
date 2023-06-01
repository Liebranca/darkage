#ifndef __5E_CTL_H__
#define __5E_CTL_H__

// ---   *   ---   *   ---
// deps

  #include "chasm/input/Kbd.hpp"
  #include "chasm/Chasm.hpp"

// ---   *   ---   *   ---
// ROM

namespace Keysets {

  static Kbd::Key_Bind KB_ESC={

    escape,{

      NULL,
      NULL,

      &chasm_exit

    }

  };

};

// ---   *   ---   *   ---
// ^to paste within definition

#define KB_CTL Keysets::KB_ESC

// ---   *   ---   *   ---

#endif // __5E_CTL_H__
