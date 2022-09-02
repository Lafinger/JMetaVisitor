#pragma once

#include "FuncTraits.hpp"
#include "UID.hpp"

#include <functional>
#include <unordered_map>
#include <queue>
#include <memory>

struct Triangle;
struct Sphere;

namespace Jason
{

class MetaVisitor
{
private:
    std::unordered_map<size_t, std::function<void(void*, void*&)>> behaviors_pool;
    std::queue<void*> results_queue;

public:
    MetaVisitor(/* args */) {}
    ~MetaVisitor() {}

    template<typename ...Fs>
    auto RegisterBehaviors(Fs&&... funcs) -> void
    {
        (RegisterBehavior(std::forward<Fs>(funcs)), ...);
    }

    template<typename F>
    auto RegisterBehavior(F&& func) -> void
    {
        using ReturnType = typename FuncTraits<F>::ResultType;
        using ArgsList = typename FuncTraits<F>::ArgsList;
        using FrontType = Front_t<ArgsList>;
        using Derived = std::remove_pointer_t<FrontType>;

        behaviors_pool[UID<Derived>::get()] =
            [func = std::forward<F>(func)](void* elem, void*& ret) -> void {
            ret = new ReturnType(func(reinterpret_cast<Derived*>(elem)));
        };
    }

    template<typename E>
    auto Visit(E* elem, void*& ret) -> void
    {
        using Derived = std::remove_pointer_t<E>;

        behaviors_pool[UID<Derived>::get()](elem, ret);
    }
};

}