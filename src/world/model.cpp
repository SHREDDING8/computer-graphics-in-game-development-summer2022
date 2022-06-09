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
	tinyobj::ObjReaderConfig reader_config;
	// Path to material files
	reader_config.mtl_search_path = model_path.parent_path().string();
	reader_config.triangulate = true;

	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(model_path.string(), reader_config)) {
		if (!reader.Error().empty()) {
			THROW_ERROR(reader.Error());
		}
		exit(1);
	}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();

	// Loop 1
	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		unsigned int vertex_buffer_size = 0;
		unsigned int index_buffer_size = 0;
		std::map<std::tuple<int, int, int>, unsigned int> index_map;
		const auto& mesh = shapes[s].mesh;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = mesh.num_face_vertices[f];
			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = mesh.indices[index_offset + v];
				auto idx_tuple = std::make_tuple(idx.vertex_index,
												 idx.normal_index,
												 idx.texcoord_index);
				if (index_map.count(idx_tuple) == 0) {
					index_map[idx_tuple] = vertex_buffer_size;
					vertex_buffer_size++;
				}
				index_buffer_size++;
			}
			index_offset += fv;
		}

		vertex_buffers.push_back(std::make_shared<cg::resource<cg ::vertex>>(vertex_buffer_size));
		index_buffers.push_back(std::make_shared<cg::resource<unsigned int>>(index_buffer_size));
	}

	// Loop 2
	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		unsigned int vertex_buffer_id = 0;
		unsigned int index_buffer_id = 0;
		auto vertex_buffer = vertex_buffers[s];
		auto index_buffer = index_buffers[s];
		std::map<std::tuple<int, int, int>, unsigned int> index_map;
		const auto& mesh = shapes[s].mesh;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = mesh.num_face_vertices[f];
			// Loop over vertices in the face.
			float3 normal;
			if (mesh.indices[index_offset].normal_index < 0) {
				auto a_id = mesh.indices[index_offset];
				auto b_id = mesh.indices[index_offset + 1];
				auto c_id = mesh.indices[index_offset + 2];

				float3 a{
						attrib.vertices[3 * a_id.vertex_index],
						attrib.vertices[3 * a_id.vertex_index + 1],
						attrib.vertices[3 * a_id.vertex_index + 2]};
				float3 b{
						attrib.vertices[3 * b_id.vertex_index],
						attrib.vertices[3 * b_id.vertex_index + 1],
						attrib.vertices[3 * b_id.vertex_index + 2]};
				float3 c{
						attrib.vertices[3 * c_id.vertex_index],
						attrib.vertices[3 * c_id.vertex_index + 1],
						attrib.vertices[3 * c_id.vertex_index + 2]};
				normal = normalize(cross(b - a, c - a));
			}
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = mesh.indices[index_offset + v];
				auto idx_tuple = std::make_tuple(idx.vertex_index,
												 idx.normal_index,
												 idx.texcoord_index);
				if (index_map.count(idx_tuple) == 0) {
					cg::vertex& vertex = vertex_buffer->item(vertex_buffer_id);

					vertex.x = attrib.vertices[3 * idx.vertex_index + 0];
					vertex.y = attrib.vertices[3 * idx.vertex_index + 1];
					vertex.z = attrib.vertices[3 * idx.vertex_index + 2];

					if (idx.normal_index > -1) {
						vertex.nx = attrib.normals[3 * idx.normal_index + 0];
						vertex.ny = attrib.normals[3 * idx.normal_index + 1];
						vertex.nz = attrib.normals[3 * idx.normal_index + 2];
					}
					else {
						vertex.nx = normal.x;
						vertex.ny = normal.y;
						vertex.nz = normal.z;
					}

					if (idx.texcoord_index > -1) {
						vertex.u = attrib.texcoords[2 * idx.texcoord_index + 0];
						vertex.v = attrib.texcoords[2 * idx.texcoord_index + 1];
					}
					else {
						vertex.u = 0.f;
						vertex.v = 0.f;
					}

					if (materials.size() > 0) {
						const auto& material = materials[mesh.material_ids[f]];
						vertex.ambient_r = material.ambient[0];
						vertex.ambient_g = material.ambient[1];
						vertex.ambient_b = material.ambient[2];

						vertex.diffuse_r = material.diffuse[0];
						vertex.diffuse_g = material.diffuse[1];
						vertex.diffuse_b = material.diffuse[2];

						vertex.emissive_r = material.emission[0];
						vertex.emissive_g = material.emission[1];
						vertex.emissive_b = material.emission[2];
					}

					index_map[idx_tuple] = vertex_buffer_id;
					vertex_buffer_id++;
				}
				index_buffer->item(index_buffer_id) = index_map[idx_tuple];
				index_buffer_id++;
			}
			index_offset += fv;
		}
	}
}


const std::vector<std::shared_ptr<cg::resource<cg::vertex>>>&
cg::world::model::get_vertex_buffers() const
{
	return vertex_buffers;
}


const std::vector<std::shared_ptr<cg::resource<unsigned int>>>&
cg::world::model::get_index_buffers() const
{
	return index_buffers;
}

std::vector<std::filesystem::path>
cg::world::model::get_per_shape_texture_files() const
{
	THROW_ERROR("Not implemented yet");
}


const float4x4 cg::world::model::get_world_matrix() const
{
	return float4x4{
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}};
}