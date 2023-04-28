#include "tree.hpp"

using namespace cgp;

mesh create_trunk(float r, float h) {
    mesh m;

    int n = 5;
    //Build points
    for (int k = 0; k < 2 * n; k++) {
        m.position.push_back(vec3(r * std::cos(k * Pi / n), r * std::sin(k * Pi / n), 0));
        m.position.push_back(vec3(r * std::cos((k + 1) * Pi / n), r * std::sin((k + 1) * Pi / n), h));
    }
    //Build triangles
    for (int k = 0; k < 2 * n; k++) {
        int p_index[] = { (2 * k - 1 + 4 * n) % (4 * n) ,2 * k ,(2 * k + 1) % (4 * n),(2 * k + 2) % (4 * n) };
        m.connectivity.push_back(uint3{ p_index[1] , p_index[3] , p_index[2] });
        m.connectivity.push_back(uint3{ p_index[1] , p_index[0] , p_index[2] });
    }
    m.fill_empty_field();

    return m;
}

mesh create_leaves(float r, float h, float z) {
    mesh m;

    int n = 5;
    //Build points
    m.position.push_back(vec3(0, 0, z)); //Base center
    m.position.push_back(vec3(0, 0, h + z)); //Tip
    for (int k = 0; k < 2 * n; k++) {
        m.position.push_back(vec3(r * std::cos(k * Pi / n), r * std::sin(k * Pi / n), z));
    }
    //Build triangles
    for (int k = 0; k < 2 * n; k++) {
        m.connectivity.push_back(uint3{ k + 2 , (k + 1) % (2 * n) + 2 ,1 });
        m.connectivity.push_back(uint3{ (k + 1) % (2 * n) + 2 , k + 2,0 });
    }

    m.fill_empty_field();
    return m;
}

mesh create_tree(float r , float h , float z)
{
    // Create a brown trunk
    mesh trunk = create_trunk(r, h);
    trunk.color.fill({ 0.4f, 0.3f, 0.3f });


    // Create a green foliage from 3 cones
    mesh foliage = create_leaves(4 * r, 6 * r, 0.0f);      // base-cone
    foliage.push_back(create_leaves(4 * r, 6 * r, 2 * r));   // middle-cone
    foliage.push_back(create_leaves(4 * r, 6 * r, 4 * r));   // top-cone
    foliage.apply_translation_to_position({ 0,0,h });       // place foliage at the top of the trunk
    foliage.color.fill({ 0.4f, 0.6f, 0.3f });

    // The tree is composed of the trunk and the foliage
    mesh tree = trunk;
    tree.push_back(foliage);

    return tree;
}