#include "rasterizer_renderer.h"

#include "utils/resource_utils.h"


void cg::renderer::rasterization_renderer::init()
{
	// TODO: Lab 1.02. Implement image clearing & saving in `cg::renderer::rasterization_renderer` class
    render_target = std::make_shared<cg::resource<cg::unsigned_color>>(
            settings->width,settings->height
            );
    rasterizer = std::make_shared<cg::renderer::rasterizer<cg::vertex,cg::unsigned_color>>();
    rasterizer->set_viewport(settings->width,settings->height);
    rasterizer->set_render_target(render_target);

	// TODO: Lab 1.03. Adjust `cg::renderer::rasterization_renderer` class to consume `cg::world::model`
	// TODO: Lab 1.04. Setup an instance of camera `cg::world::camera` class in `cg::renderer::rasterization_renderer`

    camera = std::make_shared<cg::world::camera>();
    camera->set_height(static_cast<float>(settings->height));
    camera->set_width(static_cast<float>(settings->width));
    camera->set_position(
            float3{
                settings->camera_position[0],
                settings->camera_position[1],
                settings->camera_position[2]
            }
            );
    camera->set_phi((settings->camera_phi));
    camera->set_theta(settings->camera_theta);
    camera->set_angle_of_view(settings->camera_angle_of_view);
    camera->set_z_near(settings->camera_z_near);
    camera->set_z_far(settings->camera_z_far);

	// TODO: Lab 1.06. Add depth buffer in cg::renderer::rasterization_renderer
	
}
void cg::renderer::rasterization_renderer::render()
{
	// TODO: Lab 1.02. Implement image clearing & saving in `cg::renderer::rasterization_renderer` class
    rasterizer->clear_render_target({111,15,112});

    // TODO: Lab 1.04. Implement `vertex_shader` lambda for the instance of `cg::renderer::rasterizer`

    float4x4 matrix = mul(camera->get_projection_matrix(),
                          camera->get_view_matrix(),
                          model->get_world_matrix());
    rasterizer->vertex_shader = [&](float4 vertex,cg::vertex vertex_data){
        auto processed = mul(matrix,vertex);
        return std::make_pair(processed,vertex_data);
    };

    // TODO: Lab 1.05. Implement `pixel_shader` lambda for the instance of `cg::renderer::rasterizer`

    cg::utils::save_resource(*render_target,settings->result_path);

	// TODO: Lab 1.03. Adjust `cg::renderer::rasterization_renderer` class to consume `cg::world::model`

}

void cg::renderer::rasterization_renderer::destroy() {}

void cg::renderer::rasterization_renderer::update() {}