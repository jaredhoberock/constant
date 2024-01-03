// clang++ -std=c++20 test.cpp -lstdc++ -lfmt
#include "constant.hpp"
#include <concepts>
#include <fmt/core.h>
#include <iostream>

int main()
{
  constant<13> thirteen;

  // unary operators
  static_assert(std::same_as<constant<+13>, decltype(+thirteen)>);
  static_assert(std::same_as<constant<-13>, decltype(-thirteen)>);
  static_assert(std::same_as<constant<~13>, decltype(~thirteen)>);

  // relations against self
  static_assert(std::same_as<constant<true>,  decltype(thirteen == thirteen)>);
  static_assert(std::same_as<constant<false>, decltype(thirteen != thirteen)>);
  static_assert(std::same_as<constant<false>, decltype(thirteen < thirteen)>);
  static_assert(std::same_as<constant<true>, decltype(thirteen <= thirteen)>);
  static_assert(std::same_as<constant<false>, decltype(thirteen > thirteen)>);
  static_assert(std::same_as<constant<true>, decltype(thirteen >= thirteen)>);

  // arithmetic against self
  static_assert(std::same_as<constant<13+13>, decltype(thirteen + thirteen)>);
  static_assert(std::same_as<constant<13-13>, decltype(thirteen - thirteen)>);
  static_assert(std::same_as<constant<13*13>, decltype(thirteen * thirteen)>);
  static_assert(std::same_as<constant<13/13>, decltype(thirteen / thirteen)>);
  static_assert(std::same_as<constant<13%13>, decltype(thirteen % thirteen)>);
  static_assert(std::same_as<constant<13&13>, decltype(thirteen & thirteen)>);
  static_assert(std::same_as<constant<13|13>, decltype(thirteen | thirteen)>);
  static_assert(std::same_as<constant<13^13>, decltype(thirteen ^ thirteen)>);
  static_assert(std::same_as<constant<13<<13>, decltype(thirteen << thirteen)>);
  static_assert(std::same_as<constant<(13>>13)>, decltype(thirteen >> thirteen)>);

  constant<7> seven;

  // relation against another constant
  static_assert(std::same_as<constant<true>, decltype(seven != thirteen)>);
  static_assert(seven != thirteen);
  static_assert(std::same_as<constant<true>, decltype(seven < thirteen)>);
  static_assert(seven < thirteen);
  static_assert(std::same_as<constant<true>, decltype(seven <= thirteen)>);
  static_assert(seven <= thirteen);
  static_assert(std::same_as<constant<true>, decltype(thirteen > seven)>);
  static_assert(thirteen > seven);
  static_assert(std::same_as<constant<true>, decltype(thirteen >= seven)>);
  static_assert(thirteen >= seven);

  // arithmetic against another constant
  static_assert(std::same_as<constant<13+7>, decltype(thirteen + seven)>);
  static_assert(std::same_as<constant<13-7>, decltype(thirteen - seven)>);
  static_assert(std::same_as<constant<13*7>, decltype(thirteen * seven)>);
  static_assert(std::same_as<constant<13/7>, decltype(thirteen / seven)>);
  static_assert(std::same_as<constant<13%7>, decltype(thirteen % seven)>);
  static_assert(std::same_as<constant<13&7>, decltype(thirteen & seven)>);
  static_assert(std::same_as<constant<13|7>, decltype(thirteen | seven)>);
  static_assert(std::same_as<constant<13^7>, decltype(thirteen ^ seven)>);
  static_assert(std::same_as<constant<13<<7>, decltype(thirteen << seven)>);
  static_assert(std::same_as<constant<(13>>7)>, decltype(thirteen >> seven)>);

  // relation against another value, rhs
  static_assert(std::same_as<bool, decltype(thirteen == 13)>);
  static_assert(thirteen == 13);
  static_assert(std::same_as<bool, decltype(thirteen != 13)>);
  static_assert(not (thirteen != 13));
  static_assert(std::same_as<bool, decltype(thirteen < 13)>);
  static_assert(not (thirteen < 13));
  static_assert(std::same_as<bool, decltype(thirteen <= 13)>);
  static_assert(thirteen <= 13);
  static_assert(std::same_as<bool, decltype(thirteen > 13)>);
  static_assert(not (thirteen > 13));
  static_assert(std::same_as<bool, decltype(thirteen >= 13)>);
  static_assert(thirteen >= 13);

  // relation against another value, lhs
  static_assert(std::same_as<bool, decltype(13 == thirteen)>);
  static_assert(13 == thirteen);
  static_assert(std::same_as<bool, decltype(13 != thirteen)>);
  static_assert(not (13 != thirteen));
  static_assert(std::same_as<bool, decltype(13 < thirteen)>);
  static_assert(not (13 < thirteen));
  static_assert(std::same_as<bool, decltype(13 <= thirteen)>);
  static_assert(13 <= thirteen);
  static_assert(std::same_as<bool, decltype(13 > thirteen)>);
  static_assert(not (13 > thirteen));
  static_assert(std::same_as<bool, decltype(13 >= thirteen)>);
  static_assert(13 >= thirteen);

  // arithmetic against another value, rhs
  static_assert(std::same_as<int, decltype(thirteen + 7)>);
  static_assert(13+7 == thirteen + 7);
  static_assert(std::same_as<int, decltype(thirteen - 7)>);
  static_assert(13-7 == thirteen - 7);
  static_assert(std::same_as<int, decltype(thirteen * 7)>);
  static_assert(13*7 == thirteen * 7);
  static_assert(std::same_as<int, decltype(thirteen / 7)>);
  static_assert(13/7 == thirteen / 7);
  static_assert(std::same_as<int, decltype(thirteen % 7)>);
  static_assert(13%7 == thirteen % 7);
  static_assert(std::same_as<int, decltype(thirteen & 7)>);
  static_assert((13&7) == (thirteen & 7));
  static_assert(std::same_as<int, decltype(thirteen | 7)>);
  static_assert((13|7) == (thirteen | 7));
  static_assert(std::same_as<int, decltype(thirteen ^ 7)>);
  static_assert((13^7) == (thirteen ^ 7));
  static_assert(std::same_as<int, decltype(thirteen << 7)>);
  static_assert((13<<7) == (thirteen << 7));
  static_assert(std::same_as<int, decltype(thirteen >> 7)>);
  static_assert((13>>7) == (thirteen >> 7));

  // arithmetic against another value, lhs
  static_assert(std::same_as<int, decltype(13 + seven)>);
  static_assert(13+7 == 13 + seven);
  static_assert(std::same_as<int, decltype(13 - seven)>);
  static_assert(13-7 == 13 - seven);
  static_assert(std::same_as<int, decltype(13 * seven)>);
  static_assert(13*7 == 13 * seven);
  static_assert(std::same_as<int, decltype(13 / seven)>);
  static_assert(13/7 == 13 / seven);
  static_assert(std::same_as<int, decltype(13 % seven)>);
  static_assert(13%7 == 13 % seven);
  static_assert(std::same_as<int, decltype(13 & seven)>);
  static_assert((13&7) == (13 & seven));
  static_assert(std::same_as<int, decltype(13 | seven)>);
  static_assert((13|7) == (13 | seven));
  static_assert(std::same_as<int, decltype(13 ^ seven)>);
  static_assert((13^7) == (13 ^ seven));
  static_assert(std::same_as<int, decltype(13 << seven)>);
  static_assert((13<<7) == (13 << seven));
  static_assert(std::same_as<int, decltype(13 >> seven)>);
  static_assert((13>>7) == (13 >> seven));

  // this prints "13" to the terminal
  std::cout << thirteen << std::endl;

  // this prints "13" to the terminal
  std::cout << 13_c << std::endl;

  // this prints "13" to the terminal
  fmt::print("{}\n", thirteen);

  // this prints "13" to the terminal
  fmt::print("{}\n", 13_c);

  fmt::print("OK\n");

  return 0;
}

