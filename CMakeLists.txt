project(moteur)

add_subdirectory(dep/SDL dep/SDL)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)

add_executable(moteur
	main.cpp 
	projet.h 
	gc_3d_defs.hpp 
	imgui-snippet.cpp
	imgui.cmake
	geometry-snippet.cpp
	glew.cmake
	
)
target_include_directories(moteur PRIVATE
	${SDL_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
)
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32)