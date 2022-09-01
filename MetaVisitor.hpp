#pragma once

#include "FuncTraits.hpp"
#include "UID.hpp"

#include <functional>
#include <unordered_map>

struct Triangle;
struct Sphere;

namespace Jason
{

class MetaVisitor
{
private:
    std::unordered_map<size_t, std::function<void(void*)> > behaviors_pool;

public:
    MetaVisitor(/* args */) {}
    ~MetaVisitor() {}

    template<typename ...Fs>
    void RegisterBehaviors(Fs&&... funcs)
    {
        (RegisterBehavior(std::forward<Fs>(funcs)), ...);
    }

    template<typename F>
    void RegisterBehavior(F&& func)
    {
        using ResultType = typename FuncTraits<F>::ResultType;
        using ArgTypeTuple = typename FuncTraits<F>::ArgTuple;
        using ArgsFrontType = Front_t<ArgTypeTuple>;
        using Derived = std::remove_pointer_t<ArgsFrontType>;

        behaviors_pool[UID<Derived>::get()] =
            [func = std::forward<F>(func)](void* p) -> void {
            func(reinterpret_cast<Derived*>(p));
        };
    }

    template<typename E>
    void Visit(E* elem)
    {
        using Derived = std::remove_pointer_t<E>;

        behaviors_pool[UID<Derived>::get()](elem);
    }
};

}