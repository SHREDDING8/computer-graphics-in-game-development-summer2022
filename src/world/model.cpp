#define TINYOBJLOADER_IMPLEMENTATION

#include "model.h"

#include "utils/error_handler.h"

#include <linalg.h>


using namespace linalg::aliases;
using namespace cg::world;

cg::world::model::model() {}

cg::world::model::~model() {}

void cg::world::model::load_obj(const std::filesystem::path& model_path)
{
	// TODO: Lab 1.03. Using `tinyobjloader` implement `load_obj`, `get_vertex_buffers`, `get_index_buffers` methods of `cg::world::model` class
}


const std::vector<std::shared_ptr<cg::resource<cg::vertex>>>&
cg::world::model::get_vertex_buffers() const
{
	// TODO: Lab 1.03. Using `tinyobjloader` implement `load_obj`, `get_vertex_buffers`, `get_index_buffers` methods of `cg::world::model` class
}


const std::vector<std::shared_ptr<cg::resource<unsigned int>>>&
cg::world::model::get_index_buffers() const
{
	// TODO: Lab 1.03. Using `tinyobjloader` implement `load_obj`, `get_vertex_buffers`, `get_index_buffers` methods of `cg::world::model` class
}

std::vector<std::filesystem::path>
cg::world::model::get_per_shape_texture_files() const
{
	return textures;
}


const float4x4 cg::world::model::get_world_matrix() const
{
	return float4x4{
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}};
}
