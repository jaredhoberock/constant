#pragma once

#include <concepts>
#include <iostream>

template<auto v>
struct constant
{
  using value_type = decltype(v);
  constexpr static value_type value = v;
  
  // conversion to value_type
  constexpr operator value_type () const noexcept
  {
    return value;
  }

  friend std::ostream& operator<<(std::ostream& os, constant self)
  {
    return os << value;
  }

  // unary operators
  constexpr constant<+v> operator+() const noexcept { return {}; }
  constexpr constant<-v> operator-() const noexcept { return {}; }
  constexpr constant<~v> operator~() const noexcept { return {}; }

  // binary operators against another constant
#define CONSTANT_BIN_OP_CONSTANT(OP)\
  template<auto other> requires requires { v OP other; }\
  constexpr constant<(v OP other)> operator OP (constant<other>) const noexcept { return {}; }

  // relational operators
  CONSTANT_BIN_OP_CONSTANT(==)
  CONSTANT_BIN_OP_CONSTANT(!=)
  CONSTANT_BIN_OP_CONSTANT(<)
  CONSTANT_BIN_OP_CONSTANT(<=)
  CONSTANT_BIN_OP_CONSTANT(>)
  CONSTANT_BIN_OP_CONSTANT(>=)

  // arithmetic operators
  CONSTANT_BIN_OP_CONSTANT(+)
  CONSTANT_BIN_OP_CONSTANT(-)
  CONSTANT_BIN_OP_CONSTANT(*)
  CONSTANT_BIN_OP_CONSTANT(/)
  CONSTANT_BIN_OP_CONSTANT(%)
  CONSTANT_BIN_OP_CONSTANT(&)
  CONSTANT_BIN_OP_CONSTANT(|)
  CONSTANT_BIN_OP_CONSTANT(^)
  CONSTANT_BIN_OP_CONSTANT(<<)
  CONSTANT_BIN_OP_CONSTANT(>>)

#undef CONSTANT_BIN_OP_CONSTANT

  // operators for dynamic values are handled via conversion to value_type
};


#if defined(__cpp_user_defined_literals)

namespace detail
{

// parse_int_digits takes a variadic number of digits and converts them into a 64b unsigned integer
template<std::same_as<int>... Ts>
constexpr uint64_t parse_int_digits(uint64_t result, int digit, Ts... digits) noexcept
{
  if constexpr (sizeof...(Ts) == 0)
  {
    return 10 * result + digit;
  }
  else
  {
    return parse_int_digits(10 * result + digit, digits...);
  }
}

} // end detail


// user-defined literal operator allows constant written as literals. For example,
//
//   auto var = 32_c;
//
// var has type constant<32ull>.
template<char... digits>
constexpr constant<detail::parse_int_digits(0, (digits - '0')...)> operator "" _c() noexcept
{
  static_assert((('0' <= digits) && ...) && ((digits <= '9') && ...),
              "Expected 0 <= digit <= 9 for each digit of the integer.");
  return {};
}

#endif // __cpp_user_defined_literals

#if __has_include(<fmt/format.h>)

#include <fmt/format.h>

template<auto v>
struct fmt::formatter<constant<v>>
{
  template<class ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template<class FormatContext>
  auto format(const constant<v>& c, FormatContext& ctx)
  {
    return fmt::format_to(ctx.out(), "{}", c.value);
  }
};

#endif // __has_include

