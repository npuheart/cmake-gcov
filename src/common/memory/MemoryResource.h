/// @date 2024-08-14
/// @file MemoryResource.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
/// 
/// @brief 
/// 
///
#pragma once
#include "Singleton.h"

template <typename derived_t>
struct MemoryResource
{
	using pointer_t = void *;

	pointer_t allocate(std::size_t bytes, std::size_t alignment = alignof(max_align_t))
	{
		return static_cast<derived_t &>(*this).do_allocate(bytes, alignment);
	}

	void deallocate(pointer_t ptr, std::size_t bytes = 0, std::size_t alignment = alignof(max_align_t))
	{
		static_cast<derived_t &>(*this).do_deallocate(ptr, bytes, alignment);
	}

	bool is_equal(const MemoryResource &other) const noexcept
	{
		return (this == &other);
	}
};

struct HeapMemoryResource
	: Singleton<HeapMemoryResource>,
	  MemoryResource<HeapMemoryResource>
{
	void *do_allocate(std::size_t bytes, std::size_t align)
	{
		(void)align;
		(void)bytes;
		// return ::operator new(bytes, std::align_val_t(align));
		return ::operator new(bytes);
	}

	void do_deallocate(void *ptr, std::size_t bytes, std::size_t align)
	{
		(void)align;
		(void)bytes;
		//::operator delete(ptr, bytes, std::align_val_t(align));
		::operator delete(ptr);
	}
};

/// stateless allocator
struct HeapAllocator {
	using mr_type = MemoryResource<HeapMemoryResource>;

	HeapAllocator() = default;
	HeapAllocator(const HeapAllocator& o) noexcept {(void)o;}

	mr_type* resource() const {
		return &HeapMemoryResource::instance();
	}

	void* allocate(std::size_t bytes) {
		return resource()->allocate(bytes);
	}
	void deallocate(void* p, std::size_t bytes) {
		(void) bytes;

		resource()->deallocate(p);
	}
};
