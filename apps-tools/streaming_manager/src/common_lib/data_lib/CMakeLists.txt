cmake_minimum_required(VERSION 3.18)

project(data_lib)


if(NOT DEFINED MODEL)
  set(MODEL Z10)
endif()

message(STATUS "Project=${PROJECT_NAME}")
message(STATUS "RedPitaya model=${MODEL}")
message(STATUS "RedPitaya platform=${RP_PLATFORM}")
message(STATUS "VERSION=${VERSION}")
message(STATUS "REVISION=${REVISION}")

message(STATUS "Compiler С path: ${CMAKE_C_COMPILER}")
message(STATUS "Compiler С ID: ${CMAKE_C_COMPILER_ID}")
message(STATUS "Compiler С version: ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "Compiler С is part: ${CMAKE_COMPILER_IS_GNUC}")

message(STATUS "Compiler С++ path: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler С++ ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler С++version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Compiler С++ is part: ${CMAKE_COMPILER_IS_GNUCXX}")


set(CMAKE_CXX_STANDARD 17)

FILE(GLOB_RECURSE INC_ALL "*.h")

FILE(GLOB_RECURSE INC_ALL2 "*.hpp")

add_library(${PROJECT_NAME} ${INC_ALL} ${INC_ALL2})

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    target_compile_options(${PROJECT_NAME}
        PRIVATE -mcpu=cortex-a9 -mfpu=neon-fp16 -fPIC -DARM_NEON)

    target_compile_definitions(${PROJECT_NAME}
        PRIVATE ARCH_ARM)
endif()

FILE(GLOB_RECURSE INC_ALL "*.h")

if (RP_PLATFORM)
    target_compile_options(${PROJECT_NAME} PRIVATE -DRP_PLATFORM)
endif()

target_compile_options(${PROJECT_NAME}
    PRIVATE -std=c++17 -Wall -pedantic -Wextra -fpermissive -D${MODEL} $<$<CONFIG:Debug>:-g3> $<$<CONFIG:Release>:-Os> -ffunction-sections -fdata-sections)


target_include_directories(${PROJECT_NAME}
    PUBLIC  ${PROJECT_SOURCE_DIR}
            ${COMMON_LIB_DIR}
    )

list(APPEND headers
            ${PROJECT_SOURCE_DIR}/buffer.h
            ${PROJECT_SOURCE_DIR}/buffers_pack.h
            ${PROJECT_SOURCE_DIR}/neon_asm.h
            ${PROJECT_SOURCE_DIR}/thread_cout.h
            ${PROJECT_SOURCE_DIR}/signal.hpp
        )

list(APPEND src
            ${PROJECT_SOURCE_DIR}/buffer.cpp
            ${PROJECT_SOURCE_DIR}/buffers_pack.cpp
            ${PROJECT_SOURCE_DIR}/neon_asm.cpp
            ${PROJECT_SOURCE_DIR}/thread_cout.cpp
        )

target_sources(${PROJECT_NAME} PRIVATE ${src})

target_link_libraries(${PROJECT_NAME}
    PRIVATE pthread stdc++)


file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/include/${PROJECT_NAME}")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${headers}
        "${CMAKE_BINARY_DIR}/bin/include/${PROJECT_NAME}"
    COMMENT "Copying ${PROJECT_NAME} public headers to ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}"
    VERBATIM)
