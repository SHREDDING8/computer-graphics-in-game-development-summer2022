#pragma once

#include "utils/error_handler.h"

#include <algorithm>
#include <linalg.h>
#include <vector>


using namespace linalg::aliases;

namespace cg
{
	// TODO: Lab 1.02. Implement `cg::resource` class
	template<typename T>
	class resource
	{
	public:
		resource(size_t size);
		resource(size_t x_size, size_t y_size);
		~resource();

		const T* get_data();
		T& item(size_t item);
		T& item(size_t x, size_t y);

		size_t get_size_in_bytes() const;
		size_t get_number_of_elements() const;
		size_t get_stride() const;

	private:
		std::vector<T> data;
		size_t item_size = sizeof(T);
		size_t stride;
	};
	template<typename T>
	inline resource<T>::resource(size_t size)
	{
	}
	template<typename T>
	inline resource<T>::resource(size_t x_size, size_t y_size)
	{
	}
	template<typename T>
	inline resource<T>::~resource()
	{
	}
	template<typename T>
	inline const T* resource<T>::get_data()
	{
	}
	template<typename T>
	inline T& resource<T>::item(size_t item)
	{
	}
	template<typename T>
	inline T& resource<T>::item(size_t x, size_t y)
	{
	}
	template<typename T>
	inline size_t resource<T>::get_size_in_bytes() const
	{
	}
	template<typename T>
	inline size_t resource<T>::get_number_of_elements() const
	{
	}

	template<typename T>
	inline size_t resource<T>::get_stride() const
	{
	}

	// TODO: Lab 1.02. Implement `cg::color` and `cg::unsigned_color` structs
	struct color
	{
		static color from_float3(const float3& in)
		{
		};
		float3 to_float3() const
		{
		}
		float r;
		float g;
		float b;
	};

	struct unsigned_color
	{
		static unsigned_color from_color(const color& color)
		{
		};
		static unsigned_color from_float3(const float3& color)
		{

		};
		float3 to_float3() const
		{

		};
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};


	// TODO: Lab 1.03. Implement `cg::vertex` struct
	struct vertex
	{
	};

}// namespace cg