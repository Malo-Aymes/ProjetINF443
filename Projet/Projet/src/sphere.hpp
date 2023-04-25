#pragma once


#include "cgp/cgp.hpp"
#include "environment.hpp"

using cgp::mesh;
using cgp::mesh_drawable;
using cgp::vec3;

struct perlin_noise_parameters
{
	float persistency = 0.35f;
	float frequency_gain = 2.0f;
	int octave = 6;
	float terrain_height = 0.5f;
};

cgp::mesh create_sphere(cgp::vec3 center,float radius);
void update_terrain(mesh& terrain, cgp::vec3 center, float radius, mesh_drawable& terrain_visual, perlin_noise_parameters const& parameters);