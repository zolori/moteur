project(moteur)

add_subdirectory(dep/SDL dep/SDL)

set(ASSIMP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/dep/assimp)
add_subdirectory(${ASSIMP_ROOT} dep/assimp)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INCLUDE_DIR ${ASSIMP_ROOT}/include)

include(glew.cmake)

add_executable(moteur
	main.cpp 
	projet.h 
	gc_3d_defs.hpp
	SimpleFragmentShader.fragmentshader
	SimpleVertexShader.vertexshader
	shader/loadShader.hpp
	shader/loadShader.cpp
	Buffer.h
	Buffer.cpp
	IndicesBuffer.h
	IndicesBuffer.cpp
	Component.h
	Component.cpp
	ComponentName.h
	Object.h
	Object.cpp
	Transform.h
	Transform.cpp
	Mesh.h
	Mesh.cpp
	Texture.h
	Texture.cpp
	stb_image.h
	Header.h
	AssimpImporter.h
	AssimpImporter.cpp
	VertexAssembly.h
	VertexAssembly.cpp
)

target_include_directories(moteur PRIVATE
	${SDL_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${ASSIMP_INCLUDE_DIR}
)
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew assimp)