#ifndef __7E_UI_VLINK_H__
#define __7E_UI_VLINK_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"

// ---   *   ---   *   ---
// info

template<typename K,typename T>
class UI_VLink {

public:

  VERSION   "v0.00.1b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// helpers

  typedef svec<sref<K>> Objects;

  typedef T&(K::*Getter)(void);
  typedef void(K::*Setter)(T);

// ---   *   ---   *   ---
// attrs

private:

  Objects m_objects;

  Getter  get;
  Setter  set;

// ---   *   ---   *   ---
// guts

// ---   *   ---   *   ---
// iface

public:

  // append object reference
  inline void push_object(K& x) {
    m_objects.push_back(x);

  };

  // ^overwrite
  inline void set_object(uint16_t i,K& x) {

    if(m_objects.size() <= i) {
      this->push_object(x);

    } else {
      m_objects[i]=x;

    };

  };

  // ^fetch
  inline K& get_object(uint16_t i) {
    return m_objects[i].get();

  };

  // use these fptrs for messing
  // with the linked attrs
  inline void getset_procs(
    Getter _get,
    Setter _set

  ) {

    this->get=_get;
    this->set=_set;

  };

  // ^get/set attr from object
  inline T& get_attr(uint16_t i) {
    K& o=this->get_object(i);
    return (o.*get)();

  };

  inline void set_attr(uint16_t i,T& x) {
    K& o=this->get_object(i);
    return (o.*set)(x);

  };

};

// ---   *   ---   *   ---

#endif // __7E_UI_VLINK_H__
