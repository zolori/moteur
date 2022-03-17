#pragma once 
//Glew
#include <GL/glew.h>

//Windows
#ifdef _WIN32
#include <windows.h>
#endif

//SDL
#include <SDL.h>
#include <gl/GL.h>

//GLM
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Miscellaneous
#include <vector>
#include <chrono>

namespace GC_3D
{
  using namespace glm;

  template <typename T>
  using Vector = std::vector<T>;

  using Clock = std::chrono::high_resolution_clock;
  using Timestamp = Clock::time_point;
  using Duration = Clock::duration;

  inline float Seconds(Duration const& iDuration)
  {
    return std::chrono::duration_cast<std::chrono::duration<float>>(iDuration).count();
  }

  struct Geometry
  {
      //These arrays should all have the same size.
      //They can be empty as well
      Vector<vec3> m_Pos;
      Vector<vec3> m_Normals;
      Vector<vec2> m_TexCoord;

      Vector<uint32_t> m_Indices;

      void Bind() const;
      void Draw() const;
  };

  void Geometry::Bind() const
  {
      // Set each attribute pointer, if we have data for it.
      if (!m_Pos.empty())
      {
          glEnableClientState(GL_VERTEX_ARRAY);
          glVertexPointer(3, GL_FLOAT, sizeof(vec3), m_Pos.data());
          printf("m_Pos not empty\n");
      }
      else
      {
          glDisableClientState(GL_VERTEX_ARRAY);
      }
      if (!m_Normals.empty())
      {
          glEnableClientState(GL_NORMAL_ARRAY);
          glNormalPointer(GL_FLOAT, sizeof(vec3), m_Normals.data());
          printf("m_Normals not empty\n");
      }
      else
      {
          glDisableClientState(GL_NORMAL_ARRAY);
      }
      if (!m_TexCoord.empty())
      {
          glEnableClientState(GL_TEXTURE_COORD_ARRAY);
          glTexCoordPointer(2, GL_FLOAT, sizeof(vec2), m_TexCoord.data());
          printf("m_TexCoord not empty\n");
      }
      else
      {
          glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      }
  }

  void Geometry::Draw() const
  {
      if (!m_Indices.empty())
      {
          glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, m_Indices.data());
          printf("drawingElements\n");
      }
      else
      {
          glDrawArrays(GL_TRIANGLES, 0, m_Pos.size());
          printf("drawingArrays\n");
      }
  }


}