#pragma once

#include "TypeList.hpp"

#include <type_traits>
#include <tuple>
#include <functional>

namespace Jason {
namespace detail {
    template<typename Ret, typename ...Args>
    struct __FunctionTraitsBase {
        using ArgsList = TypeList<Args...>;
        using ResultType = Ret;
        using FuncType = std::function<Ret(Args...)>;
    };

    template<typename Func>
    struct __FunctionTraits;
    template<typename Func>
    struct __FunctionTraits<std::reference_wrapper<Func>> : public __FunctionTraits<Func> {};
    template<typename Ret, typename ...Args>
    struct __FunctionTraits<Ret(*)(Args...)> : public __FunctionTraitsBase<Ret, Args...> {};
    template<typename Ret, typename C, typename ...Args>
    struct __FunctionTraits<Ret(C::*)(Args...)> : public __FunctionTraitsBase<Ret, Args...> {};
    template<typename Ret, typename C, typename ...Args>
    struct __FunctionTraits<Ret(C::*)(Args...) const> : public __FunctionTraitsBase<Ret, Args...> {/*lambda*/};
    template<typename Func>
    struct __FunctionTraits : public __FunctionTraits<decltype(&Func::operator())> {/*lambda*/};

}

template<typename Func>
struct FuncTraits : public detail::__FunctionTraits<std::decay_t<Func>> {};

} // Jason
