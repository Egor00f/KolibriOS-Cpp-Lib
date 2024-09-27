#ifndef __ENUMBITFIELD_HPP__
#define __ENUMBITFIELD_HPP__

/*
	Кароч enumы как биовые поля
*/

#include <type_traits>

template<typename T, bool = std::is_enum<T>::value>
struct is_flag;

template<typename T>
struct is_flag<T, true> : std::false_type {};

template<typename T, typename std::enable_if<is_flag<T>::value>::type* = nullptr>
inline T operator | (T lhs, T rhs)
{
	using u_t = typename std::underlying_type<T>::type;
	return static_cast<T>(static_cast<u_t>(lhs) | static_cast<u_t>(rhs));
}

template<typename T, typename std::enable_if<is_flag<T>::value>::type* = nullptr>
inline T operator |= (T lhs, T rhs)
{
	return lhs | rhs;
}

template <typename T, typename std::enable_if<is_flag<T>::value>::type * = nullptr>
inline T operator&(T lhs, typename std::underlying_type<T>::type rhs)
{
	using u_t = typename std::underlying_type<T>::type;
	return static_cast<T>(static_cast<u_t>(lhs) & static_cast<u_t>(rhs));
}

template <typename T, typename std::enable_if<is_flag<T>::value>::type * = nullptr>
inline T operator<<(T lhs, typename std::underlying_type<T>::type rhs)
{
	using u_t = typename std::underlying_type<T>::type;
	return static_cast<T>(static_cast<u_t>(lhs) << rhs);
}

template <typename T, typename std::enable_if<is_flag<T>::value>::type * = nullptr>
inline T operator>>(T lhs, typename std::underlying_type<T>::type rhs)
{
	using u_t = typename std::underlying_type<T>::type;
	return static_cast<T>(static_cast<u_t>(lhs) >> rhs);
}

#endif // __ENUMBITFIELD_HPP__