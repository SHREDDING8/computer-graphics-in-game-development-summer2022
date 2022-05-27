#define _USE_MATH_DEFINES

#include "camera.h"

#include "utils/error_handler.h"

#include <math.h>


using namespace cg::world;

cg::world::camera::camera() : theta(0.f), phi(0.f), height(1080.f), width(1920.f),
							  aspect_ratio(1920.f / 1080.f), angle_of_view(1.04719f),
							  z_near(0.001f), z_far(100.f), position(float3{0.f, 0.f, 0.f})
{
}

cg::world::camera::~camera() {}

void cg::world::camera::set_position(float3 in_position)
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
}

void cg::world::camera::set_theta(float in_theta)
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
}

void cg::world::camera::set_phi(float in_phi)
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
}

void cg::world::camera::set_angle_of_view(float in_aov)
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
}

void cg::world::camera::set_height(float in_height)
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    height = in_height;
}

void cg::world::camera::set_width(float in_width)
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    width = in_width;
    aspect_ratio = width/height;


}

void cg::world::camera::set_z_near(float in_z_near)
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    z_near = in_z_near
}

void cg::world::camera::set_z_far(float in_z_far)
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    z_far = in_z_far;
}

const float4x4 cg::world::camera::get_view_matrix() const
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    float3 up{0.f,1.f,0.f};
    float3  eye = position+get_direction();

    float3 z_axis = normalize(position-eye);
    float3 x_axis = normalize(cross(up,z_axis));
    float3 y_axis = cross(z_axis,x_axis);

    return float4x4{
            {x_axis.x,y_axis,z_axis,0},
            {x_axis.y,y_axis,z_axis,0},
            {x_axis.z,y_axis,z_axis,0},
            {x_axis,y_axis,z_axis,0},
    };
}

#ifdef DX12
const DirectX::XMMATRIX cg::world::camera::get_dxm_view_matrix() const
{
	// TODO Lab 3.08. Implement `get_dxm_view_matrix`, `get_dxm_projection_matrix`, and `get_dxm_mvp_matrix` methods of `camera`
}

const DirectX::XMMATRIX cg::world::camera::get_dxm_projection_matrix() const
{
	// TODO Lab 3.08. Implement `get_dxm_view_matrix`, `get_dxm_projection_matrix`, and `get_dxm_mvp_matrix` methods of `camera`
}

const DirectX::XMMATRIX camera::get_dxm_mvp_matrix() const
{
	// TODO Lab 3.08. Implement `get_dxm_view_matrix`, `get_dxm_projection_matrix`, and `get_dxm_mvp_matrix` methods of `camera`
}
#endif

const float4x4 cg::world::camera::get_projection_matrix() const
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    return float4x4{};
}

const float3 cg::world::camera::get_position() const
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    return float3{};
}

const float3 cg::world::camera::get_direction() const
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    return float3{};
}

const float3 cg::world::camera::get_right() const
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    return linalg::cross(get_direction(),float3{0,1,0});
}

const float3 cg::world::camera::get_up() const
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    return linalg::cross(get_right(),get_direction());
}
const float camera::get_theta() const
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    return theta;
}
const float camera::get_phi() const
{
	// TODO: Lab 1.04. Implement `cg::world::camera` class
    return phi;
}
