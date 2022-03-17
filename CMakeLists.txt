project(moteur)

add_subdirectory(dep/SDL dep/SDL)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)

include(glew.cmake)

add_executable(moteur
	main.cpp 
	projet.h 
	gc_3d_defs.hpp
	geometry-snippet.cpp
	jour1.cpp
	jour2.cpp
	jour3.cpp
	jour4.cpp
	jour5.cpp
	SimpleFragmentShader.fragmentshader
	SimpleVertexShader.vertexshader
	Quick.cpp
	Buffer.h
	Buffer.cpp
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
)

target_include_directories(moteur PRIVATE
	${SDL_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
)
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew)