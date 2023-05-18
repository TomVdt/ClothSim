#pragma once

#include <cmath>
#include <vector>

namespace Geometry {
    typedef std::vector<float> Vertices;
    typedef std::vector<unsigned int> Indices;

    // Will get overriden when line is drawn
    Vertices lineVertices = {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    };
    Indices lineIndices = {
        0, 1
    };

    // Each face is defined separately (could be used for different face normals)
    Vertices cubeVertices = {
        // Front
        -1.0, -1.0, -1.0, -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0, -1.0, -1.0,
        // Right
        1.0, -1.0, -1.0,  1.0,  1.0, -1.0,  1.0,  1.0,  1.0,  1.0, -1.0,  1.0,
        // Back
        1.0, -1.0,  1.0,  1.0,  1.0,  1.0, -1.0,  1.0,  1.0, -1.0, -1.0,  1.0,
        // Left
        -1.0, -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0, -1.0, -1.0, -1.0, -1.0,
        // Bottom
        -1.0, -1.0, -1.0,  1.0, -1.0, -1.0,  1.0, -1.0,  1.0, -1.0, -1.0,  1.0,
        // Top
        -1.0,  1.0, -1.0, -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
    };
    Indices cubeIndices = {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 3, 6, 7,
        8, 9, 10, 8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23
    };

    static Vertices UVSphereVertices(int meridians, int parallels) {
        Vertices vertices;
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
        for (int j = 0; j < parallels - 1; ++j) {
            double const polar = M_PI * double(j + 1) / double(parallels);
            double const sp = std::sin(polar);
            double const cp = std::cos(polar);
            for (int i = 0; i < meridians; ++i) {
                double const azimuth = 2.0 * M_PI * double(i) / double(meridians);
                double const sa = std::sin(azimuth);
                double const ca = std::cos(azimuth);
                double const x = sp * ca;
                double const y = cp;
                double const z = sp * sa;
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
        }
        vertices.push_back(0.0f);
        vertices.push_back(-1.0f);
        vertices.push_back(0.0f);
        return vertices;
    }

    static Indices UVSphereIndices(int meridians, int parallels, int vertexCount) {
        Indices indices;
        for (int i = 0; i < meridians; ++i) {
            int const a = i + 1;
            int const b = (i + 1) % meridians + 1;
            indices.push_back(0);
            indices.push_back(b);
            indices.push_back(a);
        }

        for (int j = 0; j < parallels - 2; ++j) {
            int aStart = j * meridians + 1;
            int bStart = (j + 1) * meridians + 1;
            for (int i = 0; i < meridians; ++i) {
                const int a = aStart + i;
                const int a1 = aStart + (i + 1) % meridians;
                const int b = bStart + i;
                const int b1 = bStart + (i + 1) % meridians;
                indices.push_back(a);
                indices.push_back(a1);
                indices.push_back(b1);

                indices.push_back(a);
                indices.push_back(b1);
                indices.push_back(b);
            }
        }

        for (int i = 0; i < meridians; ++i) {
            int const a = i + meridians * (parallels - 2) + 1;
            int const b = (i + 1) % meridians + meridians * (parallels - 2) + 1;
            // Divide by 3 because 3 values per vertex
            indices.push_back(vertexCount / 3 - 1);
            indices.push_back(a);
            indices.push_back(b);
        }

        return indices;
    }

    Vertices sphereVertices(UVSphereVertices(10, 10));
    Indices sphereIndices(UVSphereIndices(10, 10, sphereVertices.size()));
}