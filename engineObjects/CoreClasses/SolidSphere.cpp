#include "SolidSphere.h"

SolidSphere::SolidSphere(float radius, unsigned int rings, unsigned int sectors)
{
    float const R = 1. / (float)(rings - 1);
    float const S = 1. / (float)(sectors - 1);
    int r, s;

    vertices.resize(rings * sectors * 3);
    normals.resize(rings * sectors * 3);
    texcoords.resize(rings * sectors * 2);
std::vector<GLfloat>::iterator v = vertices.begin();
        std::vector<GLfloat>::iterator n = normals.begin();
        std::vector<GLfloat>::iterator t = texcoords.begin();
        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
                float const y = sin( -M_PI_2 + M_PI * r * R );
                float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
                float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

                *t++ = s*S;
                *t++ = r*R;

                *v++ = x * radius;
                *v++ = y * radius;
                *v++ = z * radius;

                *n++ = x;
                *n++ = y;
                *n++ = z;
        }

    indices.resize(rings * sectors * 4);
    std::vector<unsigned int>::iterator i = indices.begin();
    for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
        *i++ = r * sectors + s;
        *i++ = r * sectors + (s + 1);
        *i++ = (r + 1) * sectors + s;
        *i++ = (r + 1) * sectors + (s + 1);
    }
}

void SolidSphere::Draw()
{
    Buffer* VerticesBuffer = new Buffer(vertices, 0, 4);
    VerticesBuffer->BindBuffer();
    Buffer* NormalBuffer = new Buffer(normals, 1, 3);
    NormalBuffer->BindBuffer();
    Buffer* TexCoordBuffer = new Buffer(texcoords, 2, 2);
    TexCoordBuffer->BindBuffer();
    Buffer* ColorBuffer = new Buffer(vertices, 3, 3);
    ColorBuffer->BindBuffer();

    IndicesBuffer* indicesBuffer = new IndicesBuffer(indices);

    glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_INT, 0);
}
