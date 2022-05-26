#pragma once

#include "resource.h"

#include <filesystem>
#include <linalg.h>
#include <tiny_obj_loader.h>


using namespace linalg::aliases;

namespace cg::world
{
	class model
	{
	public:
		model();
		virtual ~model();

		void load_obj(const std::filesystem::path& model_path);

		const std::vector<std::shared_ptr<cg::resource<cg::vertex>>>& get_vertex_buffers() const;

		const std::vector<std::shared_ptr<cg::resource<unsigned int>>>& get_index_buffers() const;

		std::vector<std::filesystem::path> get_per_shape_texture_files() const;

		const float4x4 get_world_matrix() const;

	protected:
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::vector<std::shared_ptr<cg::resource<cg::vertex>>> vertex_buffers;

		std::vector<std::shared_ptr<cg::resource<unsigned int>>> index_buffers;

		std::vector<std::filesystem::path> textures;
	};
}// namespace cg::world