cmake_minimum_required(VERSION 3.23)

project(moteur)

add_subdirectory(dep/SDL dep/SDL)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)

include(glew.cmake)

set(IMGUI_USE_OGL3 true)
include(imgui.cmake)

include(assimp.cmake)

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
	jour6.cpp
	jour8.cpp
	SimpleFragmentShader.fragmentshader
	SimpleVertexShader.vertexshader
	Quick.cpp
	TextureFShader.fragmentshader
	j8Fshader.fragmentshader
	TextureVShader.vertexshader
	j8Vshader.vertexshader
)

# add_custom_target(copy_shaders COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:moteur>/shaders)
add_custom_target(copy_ressources COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../Ressources $<TARGET_FILE_DIR:moteur>/../Ressources)

add_dependencies(moteur copy_ressources)
set_property(TARGET moteur PROPERTY CXX_STANDARD 17)

target_include_directories(moteur PRIVATE
	${SDL_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
)
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew imgui assimp)