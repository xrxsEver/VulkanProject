# Source files
set(SHADER_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADER_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

# Find glslangValidator
find_program(GLSLANG_VALIDATOR glslangValidator)

if (NOT GLSLANG_VALIDATOR)
    message(FATAL_ERROR "glslangValidator not found. Please install the Vulkan SDK.")
endif()

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${SHADER_SOURCE_DIR}/*.frag"
    "${SHADER_SOURCE_DIR}/*.vert"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${SHADER_BINARY_DIR}/${FILE_NAME}.spv")
    add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${GLSLANG_VALIDATOR} -V ${GLSL} -o ${SPIRV}
        DEPENDS ${GLSL}
        COMMENT "Compiling ${GLSL}"
        VERBATIM
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
)

set(SOURCES
    "main.cpp"
    "vulkanbase/VulkanBase.h" 
    "vulkanbase/VulkanUtil.h"
    "vulkanbase/VulkanUtil.cpp"
    "Command/CommandPool.h" 
    "Command/CommandBuffer.h"
    "Command/CommandPool.cpp"
    "Command/CommandBuffer.cpp"
    "xrxsPipeline.h"
    "xrxsPipeline.cpp" 
    "Vertex.h" 
    "DAEMesh.h"
    "DAEMesh.cpp"
    "DAEDescriptorPool.h"
    "DAEUniformBufferObject.h" 
    "DAEDataBuffer.h"
    "DAEDataBuffer.cpp"
    "DAEDescriptorPool.cpp" 
    "vulkanbase/VulkanBase.cpp"
    "SwapChainManager.h"
    "SwapChainManager.cpp"
    "Shader2D.h"
    "Shader2D.cpp"
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Ensure shaders are built before the main project
add_dependencies(${PROJECT_NAME} Shaders)

# Link libraries
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES} glfw)

# Set shader paths
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    VERT_SHADER_PATH="${CMAKE_BINARY_DIR}/shaders/Project/basic_shader.vert.spv"
    FRAG_SHADER_PATH="${CMAKE_BINARY_DIR}/shaders/basic_shader.frag.spv"
)
