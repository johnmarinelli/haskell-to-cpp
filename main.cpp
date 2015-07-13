#include <iostream>
#include <string>

/*
 * add :: Int -> Int -> Int
 * add a b = a + b
 *
 */
template <int a, int b>
struct add {
  static constexpr int value = a + b;
};

/*
 * type Uri = String
 * type LocalName = String
 * type NameClass = AnyName
 *                | QName Uri LocalName
 *                | NsName Uri
 *                | NameClassChoice NameClass NameClass
 */

using String = const char*;
using Uri = String;
using LocalName = String;

constexpr char t[] = "http://google.com";
constexpr char q[] = "hello";

struct AnyName;

template <String U, String L>
struct QName {
  static constexpr String Uri = U;
  static constexpr String LocalName = L;
};

template <String U>
struct NsName {
  static constexpr String Uri = U;
};

template <typename NC1, typename NC2>
struct NameClassChoice {
  using NameClass1 = NC1;
  using NameClass2 = NC2;
};

/*
 * contains :: NameClass -> QName -> Bool
 *
 * contains AnyName _ = True
 * contains (QName ns1 ln1) (QName ns2 ln2) = (ns1 == ns2) && (ln1 == ln2)
 * contains (NsName ns1) (QName ns2 _) = (ns1 == ns2)
 * contains (NameClassChoice ns1 ns2) n = (contains ns1 n) || (contains ns2 n)
 */
template <typename NameClass, typename QName>
struct contains;

template <String U, String L>
struct contains<AnyName, QName<U, L>> { static constexpr bool value = true; };

template <String U1, String L1, String U2, String L2>
struct contains<QName<U1, L1>, QName<U2, L2>> {
  static constexpr bool value = (strcmp(U1, U2) == 0) && (strcmp(L1, L2) == 0);
};

template <String U1, String U2, String L2>
struct contains<NsName<U1>, QName<U2, L2>> {
  static constexpr bool value = strcmp(U1, U2) == 0;
};

template <typename NC1, typename NC2, String U2, String L2>
struct contains<NameClassChoice<NC1, NC2>, QName<U2, L2>> {
  static constexpr bool value = contains<NC1, QName<U2, L2>>::value ||
                                  contains<NC2, QName<U2, L2>>::value;
};

constexpr char c1[] = "http://google.com";
constexpr char c2[] = "div";

int main(int argc, char** args) {
  auto r = add<1,2>::value;
  std::cout << r << '\n';

  using ns1 = NsName<t>;
  using ns2 = NsName<q>;
  using ncc = NameClassChoice<ns1, ns2>;

  std::cout << ncc::NameClass1::Uri << '\n';

  using qn1 = QName<c1, c2>;
  std::cout << contains<AnyName, qn1>::value;
  static_assert(contains<AnyName, qn1>::value, "AnyName should match qn1");

  return 0;
}
