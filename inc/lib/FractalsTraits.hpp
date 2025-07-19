#ifndef _FRACTALS_TRAITS_HPP
#define _FRACTALS_TRAITS_HPP
#include <cstdint>
#include <type_traits>
namespace fractals {
namespace traits {
namespace detail {
// catch-all
struct unsupported_tag {};

// primitives
struct int8_tag {};
struct uint8_tag {};
struct int16_tag {};
struct uint16_tag {};
struct int32_tag {};
struct uint32_tag {};
struct int64_tag {};
struct uint64_tag {};
struct longlong_tag {};
struct ulonglong_tag {};
struct bool_tag {};
struct char_tag {};

// special cases
struct const_char_tag {};
struct ptr_tag {};
struct nullptr_tag {};
struct void_ptr_tag {};
struct c_array_tag {};
struct enum_tag {};
struct union_tag {};

// primary template spec: the optional dummy param is
// for when partial spec SFINAE evaluates to void
// leaving the primary template a catch-all for unsupported types
template <typename T, typename = void>
struct classify {
  using type = unsupported_tag;
};

// tag classifier
template <>
struct classify<std::int8_t> {
  using type = int8_tag;
};

template <>
struct classify<std::uint8_t> {
  using type = uint8_tag;
};

template <>
struct classify<std::int16_t> {
  using type = int16_tag;
};

template <>
struct classify<std::uint16_t> {
  using type = uint16_tag;
};

// int32_t dispatches: handles `int` on most platforms
template <>
struct classify<int32_t> {
  using type = int32_tag;
};

template <>
struct classify<uint32_t> {
  using type = uint32_tag;
};

// int64_t dispatches: handles `long` on most platforms
template <>
struct classify<std::int64_t> {
  using type = int64_tag;
};

template <>
struct classify<std::uint64_t> {
  using type = uint64_tag;
};

// one-off primitives
template <>
struct classify<long long> {
  using type = longlong_tag;
};

template <>
struct classify<unsigned long long> {
  using type = ulonglong_tag;
};

template <>
struct classify<bool> {
  using type = bool_tag;
};

template <>
struct classify<char> {
  using type = char_tag;
};

template <>
struct classify<const char*> {
  using type = const_char_tag;
};

template <typename T>
struct classify<T, typename std::enable_if<std::is_pointer<T>::value && !std::is_same<T, const char*>::value &&
                                           !std::is_void<T>::value>::type> {
  using type = ptr_tag;
};

template <>
struct classify<std::nullptr_t> {
  using type = nullptr_tag;
};

template <>
struct classify<void*> {
  using type = void_ptr_tag;
};

template <typename T>
struct classify<T, typename std::enable_if<std::is_array<T>::value && (std::extent<T>::value != 0)  // non-zero carrays
                                                                                                    // are ill-formed
                                           >::type> {
  using type = c_array_tag;
};

template <typename T>
struct classify<T, typename std::enable_if<std::is_union<T>::value>::type> {
  using type = union_tag;
};

template <typename T>
struct classify<T, typename std::enable_if<std::is_enum<T>::value>::type> {
  using type = enum_tag;
};

};  // namespace detail

// expose public type
template <typename T>
using classify_t = typename detail::classify<T>::type;

};  // namespace traits
};  // namespace fractals
#endif
