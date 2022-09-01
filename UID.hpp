#pragma once

#include "VTable.hpp"
//#include <UTemplate/TypeID.h>

namespace Jason {
	template<typename T>
	struct UID {
		// return custom ID of T
		// if T is polymorphic, then return it's virtual table
		// * it will create a object of T, and get the virtual table from the object
		// * if T is not default constructable, you should call vtable_of<T>::regist(ptr) firstly
		// * or call get(ptr)
		// else return TypeID<T>
		static constexpr size_t get() noexcept
		{
			static_assert(!std::is_const_v<T> && !std::is_pointer_v<T>, "GetID: <T> must be non-const and non-pointer");
			if constexpr (std::is_polymorphic_v<T>)
				return reinterpret_cast<size_t>(vtable_of<T>::get());
			//else
			//	return Ubpa::TypeID<T>;
		}

		// return custom ID of T
		// if T is polymorphic, then return it's virtual table getting from ptr
		// else return TypeID<T>
		static constexpr size_t get(const T* ptr) noexcept 
		{
			assert(ptr != nullptr);
			if constexpr (std::is_void_v<T> || std::is_polymorphic_v<T>)
				return reinterpret_cast<size_t>(vtable(ptr));
			//else
			//	return Ubpa::TypeID<T>;
		}
	};

	template<typename T>
	constexpr size_t CustomIDof(const T* ptr) noexcept {
		return UID<T>::get(ptr);
	}
}
