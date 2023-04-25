#include "sphere.hpp"


using namespace cgp;

mesh create_sphere(cgp::vec3 center, float radius) {
	mesh m = mesh_primitive_sphere(radius, center,400,200);
	return m;
}

void update_terrain(mesh& terrain, cgp::vec3 center, float radius, mesh_drawable& terrain_visual, perlin_noise_parameters const& parameters)
{
	int const N = terrain.position.size();
	mesh m = mesh_primitive_sphere(radius, center, 400, 200);

	for (int i = 0; i < N; i++) {
		vec3 point = terrain.position[i];
		float const noise = noise_perlin(point, parameters.octave, parameters.persistency, parameters.frequency_gain);

		terrain.position[i] = m.position[i] + parameters.terrain_height * noise * normalize(point - center);
		terrain.color[i] = 0.3f * vec3(0, 0.5f, 0) + 0.7f * noise * vec3(1, 1, 1);
	}

	// Update the normal of the mesh structure
	terrain.normal_update();

	// Update step: Allows to update a mesh_drawable without creating a new one
	terrain_visual.vbo_position.update(terrain.position);
	terrain_visual.vbo_normal.update(terrain.normal);
	terrain_visual.vbo_color.update(terrain.color);

}