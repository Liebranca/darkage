#ifndef __7E_WASD_H__
#define __7E_WASD_H__

// ---   *   ---   *   ---
// deps

  #include "chasm/input/Kbd.hpp"
  #include "logic/Move.hpp"

// ---   *   ---   *   ---
// ROM

namespace Keysets {

  static Kbd::Key_Bind KB_W={

    w,{

      &Move::player_fwd,
      NULL,

      &Move::player_stop_z

    }

  };

  static Kbd::Key_Bind KB_A={

    a,{

      &Move::player_left,
      NULL,

      &Move::player_stop_x

    }

  };

  static Kbd::Key_Bind KB_S={

    s,{

      &Move::player_back,
      NULL,

      &Move::player_stop_z

    }

  };

  static Kbd::Key_Bind KB_D={

    d,{

      &Move::player_right,
      NULL,

      &Move::player_stop_x

    }

  };

};

// ---   *   ---   *   ---
// ^to paste within definition

#define KB_WASD  \
  Keysets::KB_W, \
  Keysets::KB_A, \
  Keysets::KB_S, \
  Keysets::KB_D

// ---   *   ---   *   ---

#endif // __7E_WASD_H__
