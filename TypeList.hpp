#pragma once

namespace Jason {
template<typename... Ts>
struct TypeList {};

template<typename List> struct Front;
template<typename Head, typename ...Tail>
struct Front<TypeList<Head, Tail...>>
{
	using type = Head;
};

template<typename List> using Front_t = typename Front<List>::type;

} // Jason


