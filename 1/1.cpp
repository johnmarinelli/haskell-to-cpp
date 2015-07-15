#include <iostream>
// https://monoinfinito.wordpress.com/series/introduction-to-c-template-metaprogramming/

struct NIL {
  typedef NIL Head;
  typedef NIL Tail;
};

template <typename H, typename T = NIL>
struct List {
  typedef H Head;
  typedef T Tail;
};

template <int v>
struct Int {
  static const int Value = v;
};

template <typename List>
struct Length {
  // 'typename' tells compiler that List::Tail is a type, not a variable
  typedef typename List::Tail tail;

  enum { tailLength = Length<tail>::result };
  enum { result = tailLength + 1 };
};

template <>
struct Length<NIL> {
  enum { result = 0 };
};

template <typename H, typename T>
struct Last {
  typedef H Head;
  typedef T Tail;

  enum { Value = Last<Tail::Head, Tail::Tail>::Value };
};

template <typename H>
struct Last<H, NIL> {
  enum { Value = H::Value };
};
/*
template <typename lis>
struct Last {
  typedef typename list::Head Head;
  typedef typename list::Tail Tail;
  enum { Value = Last<Head, Tail>::Value };
};
*/

int main(int argc, char* args[]) {
  typedef List< Int<1>, List<Int<2>, List<Int<3>> > > list;
  std::cout << Length<list>::result << '\n';
  std::cout << Last<list::Head, list::Tail>::Value << '\n';
}
