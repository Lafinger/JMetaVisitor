#pragma once

#include <functional>
#include <unordered_map>

namespace JMetaVisitor
{

class MetaVisitor
{
private:
    std::unordered_map< void*, std::function<void(void*)> > behaviors_pool;

public:
    MetaVisitor(/* args */) {}
    ~MetaVisitor() {}

    // template <typename ...Elems>
    // void PushElement(Elems&&...)
    // {
    //     // 1.lookup base class of element
    //     // 2.push base class to map_pool
    // }

    template <typename ...Fn>
    void RegisterBehavior(Fn&&... fns)
    {
        

        for(auto&& fn : fns...)
        {
            fn();
            // behaviors_pool[] = std::forward<Fn>(fn);
        }        

    }

    // template <typename Elem>
    // void execute(Elem&& elem)
};

}