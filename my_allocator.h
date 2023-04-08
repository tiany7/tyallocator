//
// Created by tiany on 2023/4/6.
// This is a simple allocator, which is referred to the Zhihu article:
// https://zhuanlan.zhihu.com/p/405934264
// Citation:
// https://zhuanlan.zhihu.com/p/405934264
// Experimental use only, not for commercial use.

#ifndef META_PROGRAMMING_MY_ALLOCATOR_H
#define META_PROGRAMMING_MY_ALLOCATOR_H
#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>
namespace tyalloc{
	template <typename T>
	inline T * allocate(std::ptrdiff_t alloc_size) {
		auto ptr = static_cast<T*>(::operator new(static_cast<size_t>(alloc_size * sizeof(T))));
		if (ptr == nullptr){
			std::cerr<<"failed to allocate memory"<<std::endl;
		}
		return ptr;
	}

	template <typename T>
	inline void release(T * ptr){
		::operator delete(ptr);
	}

	template <typename T, typename V>
	inline void construct(T * ptr, const V & value){
		new(ptr) T(value);
	}

	template <typename T>
	inline void destruct(T * ptr){
		ptr->~T();
	}
}

template <typename T>
class ty_allocator{
public:
	using value_type = T;
	using pointer = std::add_pointer_t<T>;
	using const_pointer = std::add_const_t<pointer>;
	using reference = std::add_lvalue_reference_t<T>;
	using const_reference = std::add_const_t<reference>;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

	template <typename U>
	struct rebind{
		using other = ty_allocator<U>;
	};

	pointer allocate(size_type n, const void * hint = 0){
		return tyalloc::allocate<T>(n);
	}

	void deallocate(pointer p, size_type n){
		tyalloc::release(p);
	}

	void construct(pointer p, const_reference value){
		tyalloc::construct(p, value);
	}

	void destroy(pointer p){
		tyalloc::destruct(p);
	}

	pointer address(reference x) const{
		return &x;
	}


	const_pointer address(const_reference x) {
		return &x;
	}

	size_type max_size() const{
		return static_cast<size_type>(-1) / sizeof(T);
	}



};


#endif //META_PROGRAMMING_MY_ALLOCATOR_H
