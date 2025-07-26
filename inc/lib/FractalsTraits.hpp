#ifndef _FRACTALS_TRAITS_HPP
#define _FRAGGLE_TRAITS_HPP
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <wchar.h>
#include <cstdint>
#include <type_traits>
namespace fractals {
namespace traits {
namespace detail {
// catch-all for unsupported or unclassified types
struct unsupported_tag {};
// std type tags
struct int8_tag {};
struct uint8_tag {};
struct int16_tag {};
struct uint16_tag {};
struct int32_tag {};
struct uint32_tag {};
struct int64_tag {};
struct uint64_tag {};
// tags for types that might be distinct from std types
// (e.g., 'long long' on Linux might be distinct from 'long' even if same size)
struct longlong_tag {};
struct ulonglong_tag {};
struct long_double_tag {};
// platform-specific/compiler-specific type tags
struct long_tag {};
struct ulong_tag {};
struct wchar_tag {};
struct ptrdiff_t_tag {};
struct size_t_tag {};
// distinct type tags
struct bool_tag {};
struct char_tag {};
struct const_char_tag {};
struct float_tag {};
struct double_tag {};
// pointer type tags
struct void_ptr_tag {};
struct ptr_tag {};
struct func_ptr_tag {};
// special type tags
struct c_array_tag {};
struct enum_tag {};
struct union_tag {};
// primary spec
template <typename T, typename = void> struct classify {
  using type = unsupported_tag;
};
// std types
template <> struct classify<int8_t> {
  using type = int8_tag;
};
template <> struct classify<uint8_t> {
  using type = uint8_tag;
};
template <> struct classify<int16_t> {
  using type = int16_tag;
};
template <> struct classify<uint16_t> {
  using type = uint16_tag;
};
template <> struct classify<int32_t> {
  using type = int32_tag;
};
template <> struct classify<uint32_t> {
  using type = uint32_tag;
};
template <> struct classify<int64_t> {
  using type = int64_tag;
};
template <> struct classify<uint64_t> {
  using type = uint64_tag;
};
// platform-specifc tags that overlap
#ifdef _WIN32 // --- Windows (MSVC / MinGW)
template <> struct classify<long> {
  using type = long_tag;
};
template <> struct classify<unsigned long> {
  using type = ulong_tag;
};
template <typename T>
struct classify<T,
                typename std::enable_if<std::is_same_v<T, long double> && !std::is_same_v<long double, double>>::type> {
  using type = long_double_tag;
};
template <> struct classify<wchar_t> {
  using type = wchar_tag;
};
// 'size_t' is typically 64-bit on 64-bit Linux/Windows.
template <typename T>
struct classify<T, typename std::enable_if<std::is_same_v<T, size_t> && !std::is_same_v<size_t, uint64_t>>::type> {
  using type = size_t_tag;
};
// 'ptrdiff_t' is typically 64-bit on 64-bit Linux/Windows
template <typename T>
struct classify<T, typename std::enable_if<std::is_same_v<T, ptrdiff_t> && !std::is_same_v<ptrdiff_t, int64_t>>::type> {
  using type = ptrdiff_t_tag;
};
#elif defined(__linux__) // --- Linux (GCC / Clang)
template <> struct classify<long long> {
  using type = longlong_tag;
};
template <> struct classify<unsigned long long> {
  using type = ulonglong_tag;
};
template <> struct classify<long double> {
  using type = long_double_tag;
};
template <> struct classify<wchar_t> {
  using type = wchar_tag;
};
template <typename T>
struct classify<T, typename std::enable_if<std::is_same_v<T, size_t> && !std::is_same_v<size_t, uint64_t>>::type> {
  using type = size_t_tag;
};
template <typename T>
struct classify<T, typename std::enable_if<std::is_same_v<T, ptrdiff_t> && !std::is_same_v<ptrdiff_t, int64_t>>::type> {
  using type = ptrdiff_t_tag;
};
#else  // unsupported platforms or compilers fallback (size comparisons)
template <> struct classify<long> {
  using type = typename std::conditional_t<
      sizeof(long) == sizeof(int32_t), int32_tag,
      typename std::conditional_t<sizeof(long) == sizeof(int64_t), int64_tag, unsupported_tag>>;
};
template <> struct classify<unsigned long> {
  using type = typename std::conditional_t<
      sizeof(unsigned long) == sizeof(uint32_t), uint32_tag,
      typename std::conditional_t<sizeof(unsigned long) == sizeof(uint64_t), uint64_tag, unsupported_tag>>;
};
template <typename T>
struct classify<T, typename std::enable_if<std::is_same_v<T, long long> && !std::is_same_v<long long, int64_t>>::type> {
  using type = longlong_tag;
};
template <typename T>
struct classify<T, typename std::enable_if<std::is_same_v<T, unsigned long long> &&
                                           !std::is_same_v<unsigned long long, uint64_t>>::type> {
  using type = ulonglong_tag;
};
template <typename T>
struct classify<T,
                typename std::enable_if<std::is_same_v<T, long double> && !std::is_same_v<long double, double>>::type> {
  using type = long_double_tag;
};
template <typename T>
struct classify<
    T, typename std::enable_if<std::is_same_v<T, wchar_t> && !std::is_same_v<wchar_t, uint16_t> && // Common on Windows
                               !std::is_same_v<wchar_t, uint32_t>                                  // Common on Linux
                               >::type> {
  using type = wchar_tag;
};
template <typename T>
struct classify<T,
                typename std::enable_if<std::is_same_v<T, size_t> && !std::is_same_v<size_t, unsigned int> &&
                                        !std::is_same_v<size_t, unsigned long> && !std::is_same_v<size_t, uint32_t> &&
                                        !std::is_same_v<size_t, uint64_t>>::type> {
  using type = size_t_tag;
};
template <typename T>
struct classify<T, typename std::enable_if<std::is_same_v<T, ptrdiff_t> && !std::is_same_v<ptrdiff_t, int> &&
                                           !std::is_same_v<ptrdiff_t, long> && !std::is_same_v<ptrdiff_t, int32_t> &&
                                           !std::is_same_v<ptrdiff_t, int64_t>>::type> {
  using type = ptrdiff_t_tag;
};
#endif // platform-specific guards
// generally distinct tags
template <> struct classify<bool> {
  using type = bool_tag;
};
template <> struct classify<char> {
  using type = char_tag;
};
template <> struct classify<const char*> {
  using type = const_char_tag;
};
template <> struct classify<float> {
  using type = float_tag;
};
template <> struct classify<double> {
  using type = double_tag;
};
// ptr handling: void ptr, data ptr, func ptr
// -> do we also spec `void` (?)
template <> struct classify<void*> {
  using type = void_ptr_tag;
};
template <typename T>
struct classify<T, typename std::enable_if<std::is_pointer_v<T> && !std::is_same_v<T, const char*> &&
                                           !std::is_void_v<T> && !std::is_function_v<std::remove_pointer_t<T>>>::type> {
  using type = ptr_tag;
};
template <typename T>
struct classify<T,
                typename std::enable_if<std::is_pointer_v<T> && std::is_function_v<std::remove_pointer_t<T>>>::type> {
  using type = func_ptr_tag;
};
// special cases/user-defined types
template <typename T>
struct classify<T, typename std::enable_if<std::is_array_v<T> && (std::extent_v<T> != 0) // non-zero c-arrays are
                                                                                         // ill-formed
                                           >::type> {
  using type = c_array_tag;
};
template <typename T> struct classify<T, typename std::enable_if<std::is_union_v<T>>::type> {
  using type = union_tag;
};
template <typename T> struct classify<T, typename std::enable_if<std::is_enum_v<T>>::type> {
  using type = enum_tag;
};

} // namespace detail
// Public type alias for convenience
template <typename T> using classify_t = typename detail::classify<T>::type;
}; // namespace traits
}; // namespace fractals
#endif
