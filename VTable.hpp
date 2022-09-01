#pragma once

#include <type_traits>
#include <iostream>
#include <cassert>

namespace Jason {

    namespace detail::vtable_ {
        template<typename Base>
        struct Derived : Base {
            Derived() {}
            ~Derived() {}
            Base t;
        };
    }

	inline static const void* vtable(const void* ptr) noexcept {
		assert(ptr != nullptr);
		return *reinterpret_cast<void const* const*>(ptr);
	}
	inline static const void* vtable(void* ptr) noexcept {
		return vtable(static_cast<const void*>(ptr));
	}

	template<typename T>
	inline static const void* vtable(T* ptr) noexcept {
		static_assert(std::is_polymorphic_v<T>, "vtable: T isn't polymorphic");
		return vtable(reinterpret_cast<const void*>(ptr));
	}

	template<typename T>
	struct vtable_of {
		static_assert(std::is_polymorphic_v<T>);

		inline static void regist(const T* ptr) noexcept { value = vtable(ptr); }

		inline static const void* get() noexcept {
            if (!value) {
                if constexpr (std::is_constructible_v<T>) {
                    T tmp;
                    regist(&tmp);
                }
                // else if constexpr (is_derived_constructible_v<T>) {
                //     detail::vtable_::Derived<T> tmp{};
                //     regist(&tmp.t);
                // }
                else
                    assert("vtable_of::get: vtable regist fail");
            }
            return value;
        }
		
	private:
		inline static const void* value{ nullptr };
	};

	template<typename Derived, typename Base>
	inline static bool vtable_is(Base* ptr) noexcept {
		static_assert(std::is_polymorphic_v<Base>);
		static_assert(std::is_polymorphic_v<Derived>);
		static_assert(std::is_base_of_v<Base, Derived>);
		assert(ptr != nullptr);
		return vtable(ptr) == vtable_of<Derived>::get();
	}
}
