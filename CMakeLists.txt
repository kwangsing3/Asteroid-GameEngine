﻿# CMakeList.txt: CMakeProject1 的 CMake 專案，在此包含來源及定義
# 專案專屬邏輯。
#
cmake_minimum_required (VERSION 3.10)


project(Asteroid-GameEngine VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)

#--------------------------------------------------------------------
# Add Library
#--------------------------------------------------------------------

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glm)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)

#add_subdirectory(${CMAKE_SOURCE_DIR}/lib/bullet3)
#add_subdirectory(${CMAKE_SOURCE_DIR}/lib/assimp)
#add_subdirectory(${CMAKE_SOURCE_DIR}/lib/openal-soft)


##設定頭文件(.h)位置

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/lib/glm)
#include_directories(${CMAKE_SOURCE_DIR}/lib/bullet3/src)
#include_directories(${CMAKE_SOURCE_DIR}/lib/bullet3/examples)
#include_directories(${CMAKE_SOURCE_DIR}/lib/openal-soft/include)
#include_directories(${CMAKE_SOURCE_DIR}/lib/assimp/include)
#link_directories(${CMAKE_SOURCE_DIR}/lib)

# 添加目錄下所有的來源檔(.Cpp)並新增至DIR_SRCS變量

aux_source_directory(${CMAKE_SOURCE_DIR}/src MAIN_SRCS) 
aux_source_directory(${CMAKE_SOURCE_DIR}/src/GraphicEngine GRAPHICENGINE_SRCS)
#aux_source_directory(${CMAKE_SOURCE_DIR}/src/Component COMPONENT_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/RuntimeCompiler RC_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/RuntimeObjectSystem RCSYSTEM_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/System SYSTEM_SRCS)

LIST (APPEND ALL_SRC          #每次新增資料夾時都要記得增加資料夾列表
${MAIN_SRCS}
${GRAPHICENGINE_SRCS}
#${COMPONENT_SRCS}
${RC_SRCS}  
${RCSYSTEM_SRCS}  
${SYSTEM_SRCS}
)
#link_directories(${PROJECT_NAME} ${BULLET_LIBRARY_DIRS})

# 將來源新增到此專案的可執行檔。
add_executable (${PROJECT_NAME} ${ALL_SRC})

##OpenAL


#list (APPEND BULLET_LIBRARIES LinearMath)
#list (APPEND BULLET_LIBRARIES Bullet3Common)
#list (APPEND BULLET_LIBRARIES BulletInverseDynamics)
#list (APPEND BULLET_LIBRARIES BulletCollision)
#list (APPEND BULLET_LIBRARIES BulletDynamics)
#list (APPEND BULLET_LIBRARIES BulletSoftBody)
#--------------------------------------------------------------------
# Add GLFW-Lib
#--------------------------------------------------------------------

target_link_libraries(${PROJECT_NAME} glfw)
#target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} assimp)
#target_link_libraries(${PROJECT_NAME} ${BULLET_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} OpenAL)
#target_link_libraries(${PROJECT_NAME} ${BULLET_COLLISION_LIBRARY})
#target_link_libraries(${PROJECT_NAME} ${BULLET_DYNAMICS_LIBRARY})
#target_link_libraries(${PROJECT_NAME} ${BULLET_MATH_LIBRARY})


#--------------------------------------------------------------------
# Copy Folder
#--------------------------------------------------------------------
add_custom_command(
         TARGET ${PROJECT_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/Shader $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shader
         COMMENT "Copying Shader" VERBATIM
         )
add_custom_command(
         TARGET ${PROJECT_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/src/Texture $<TARGET_FILE_DIR:${PROJECT_NAME}>/Texture
         COMMENT "Copying Texture" VERBATIM
         )
add_custom_command(
         TARGET ${PROJECT_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/src/ExampleProject $<TARGET_FILE_DIR:${PROJECT_NAME}>/ExampleProject
         COMMENT "Copying ExampleProject" VERBATIM
         )
add_custom_command(
         TARGET ${PROJECT_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/src/ExampleModel $<TARGET_FILE_DIR:${PROJECT_NAME}>/ExampleModel
         COMMENT "Copying ExampleModel" VERBATIM
         )

