cmake_minimum_required(VERSION 3.23)


project(moteur)

include(bullet.cmake)

add_subdirectory(dep/SDL dep/SDL)
set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)

set(IMGUI_USE_OGL3 true)
include(cmake/imgui.cmake)


set(ASSIMP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/dep/assimp)
add_subdirectory(${ASSIMP_ROOT} dep/assimp)

set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INCLUDE_DIR ${ASSIMP_ROOT}/include)

add_custom_target(copy_shaders 
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:moteur>/shader)

add_custom_target(copy_assets
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:moteur>/assets)


include(cmake/glew.cmake)

add_executable(moteur
	main.cpp 
	common/functions.hpp
	common/functions.cpp
	common/AssimpImporter.h
	common/AssimpImporter.cpp
	common/Header.h
	common/stb_image.h
	engineObjects/CoreClasses/Buffer.h
	engineObjects/CoreClasses/Buffer.cpp
	engineObjects/CoreClasses/IndicesBuffer.h
	engineObjects/CoreClasses/IndicesBuffer.cpp
	engineObjects/CoreClasses/VertexAssembly.h
	engineObjects/CoreClasses/VertexAssembly.cpp
	engineObjects/CoreClasses/Texture.h
	engineObjects/CoreClasses/Texture.cpp
	engineObjects/CoreClasses/BulletPhysics.h
	engineObjects/CoreClasses/BulletPhysics.cpp
	engineObjects/CoreClasses/SolidSphere.h
	engineObjects/CoreClasses/SolidSphere.cpp
	engineObjects/Component.h
	engineObjects/Component.cpp
	engineObjects/ComponentName.h
	engineObjects/Object.h
	engineObjects/Object.cpp
	engineObjects/Components/Transform.h
	engineObjects/Components/Transform.cpp
	engineObjects/Components/Mesh.h
	engineObjects/Components/Mesh.cpp
	engineObjects/Components/Camera.h
	engineObjects/Components/Camera.cpp
)

add_dependencies(moteur copy_shaders)
add_dependencies(moteur copy_assets)


target_include_directories(moteur PRIVATE
	${SDL_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${ASSIMP_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
    ${BULLET_INCLUDE_DIR}
)
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew assimp imgui LinearMath BulletCollision BulletDynamics)

set_property(TARGET moteur PROPERTY CXX_STANDARD 17)