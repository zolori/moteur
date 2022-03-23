cmake_minimum_required(VERSION 3.23)


project(moteur)

include(bullet.cmake)

add_subdirectory(dep/SDL dep/SDL)
set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)

include(imgui.cmake)

set(ASSIMP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/dep/assimp)
add_subdirectory(${ASSIMP_ROOT} dep/assimp)

set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INCLUDE_DIR ${ASSIMP_ROOT}/include)

add_custom_target(copy_shaders 
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:moteur>/shader)


include(glew.cmake)

add_executable(moteur
    main.cpp 
    projet.h 
    gc_3d_defs.hpp
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
    Quick.cpp
)


# add_custom_target(copy_shaders COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:moteur>/shaders)
#add_custom_target(copy_ressources COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../Ressources $<TARGET_FILE_DIR:moteur>/../Ressources)

#add_dependencies(moteur copy_ressources)
set_property(TARGET moteur PROPERTY CXX_STANDARD 17)

#add_dependencies(moteur copy_shaders)

target_include_directories(moteur PRIVATE
    ${SDL_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${ASSIMP_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
    ${BULLET_INCLUDE_DIR}
)
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew assimp imgui LinearMath BulletCollision BulletDynamics)

set_property(TARGET moteur PROPERTY CXX_STANDARD 17)
