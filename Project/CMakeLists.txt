cmake_minimum_required(VERSION 3.10)

# Project Name
project(VulkanProject)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include FetchContent module for GLFW
include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.8 # Specify the version you need
)

FetchContent_MakeAvailable(glfw)

# Find the required packages
find_package(Vulkan REQUIRED)

# Include Directories
include_directories(${Vulkan_INCLUDE_DIRS} include ${glfw_INCLUDE_DIRS} Lib)

# Add subdirectories
add_subdirectory(shaders)
add_subdirectory(Command)

# Set source files
set(SOURCES
    main.cpp
    VulkanBase.cpp
    include/VulkanUtil.cpp
    xrxsPipeline.cpp 
    DAEMesh.cpp
    DAEDataBuffer.cpp
    SwapChainManager.cpp
    Shader2D.cpp
    ModelLoader.cpp
    Lib/stb_image.h
)

# Set header files
set(HEADERS
    include/VulkanBase.h
    include/VulkanUtil.h
    include/xrxsPipeline.h
    include/Vertex.h 
    include/DAEMesh.h
    include/DAEDescriptorPool.h
    include/DAEUniformBufferObject.h 
    include/DAEDataBuffer.h
    include/DAEDescriptorPool.inl 
    include/SwapChainManager.h
    include/Shader2D.h
    include/ModelLoader.h
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} "include/Camera.h" "include/Camera.cpp" "include/Shader3D.h" "Shader3D.cpp")

# Link libraries
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include ${glfw_INCLUDE_DIRS} Lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES} glfw CommandLib)

# Ensure shaders are built before the main project
add_dependencies(${PROJECT_NAME} shaders)
