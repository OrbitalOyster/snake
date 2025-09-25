#ifndef NEW_SIZING_HPP_
#define NEW_SIZING_HPP_

#include <GUI/Alignment.hpp>

class Foo {
  private:
    GUIUnit s;
    GUIAlignment a1, a2;
  public:
    Foo();
    Foo(GUIUnit s, GUIAlignment a1);
    Foo(GUIAlignment a1, GUIAlignment a2);
    int get_l(int root_size);
    void calculate(int root_size, int *sp, int *l);
};

#endif
