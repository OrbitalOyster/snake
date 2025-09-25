#include <GUI/Foo.hpp>
#include <stdexcept>

Foo::Foo() {
  a1 = GUIUnit(0u);
  s = GUIUnit();
  a2 = GUIUnit(0u);
}

Foo::Foo(GUIUnit s, GUIAlignment a1) : s(s), a1(a1) {
  if (s.is_unset())
    throw std::runtime_error("GUI error");
}

Foo::Foo(GUIAlignment a1, GUIAlignment a2) : a1(a1), a2(a2) {
  // if (a1.depends_on_s() || a2.depends_on_s())
  //   throw Error


}

int Foo::get_l(int root_size) {
  if (!s.is_static())
    throw std::runtime_error("GUI Error");

  int result;
  a1.calculate(root_size, s.to_pixels(root_size), &result);
  return result;
}

void Foo::calculate(int root_size, int *sp, int *l) {
  /* Width is auto */
  if (s.is_unset()) {

  } else {
    //a1.calculate(root_size, sp, l);
  }

  /*
  if (u1.is_unset())
    *l = root_size - u2.to_pixels(root_size) - u3.to_pixels(root_size);
  else
    *l = u1.to_pixels(root_size);

  if (u2.is_unset())
    *s = root_size - u1.to_pixels(root_size) - u3.to_pixels(root_size);
  else
    *s = u2.to_pixels(root_size);

  if (u1.is_unset())
    *l -= offset.to_pixels(*s);
  else
    *l += offset.to_pixels(*s);

  if (*l < 0)
    *l = 0;
  if (*s < 0)
    *s = 0;
  */
}
