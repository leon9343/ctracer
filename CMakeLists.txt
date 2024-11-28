cmake_minimum_required(VERSION 3.28)
project(ctracer C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(USE_SDL "Build with SDL2 for rendering (TODO)" OFF)
option(USE_IMAGE "Build with image writing" ON)

if(NOT USE_SDL AND NOT USE_IMAGE)
    message(FATAL_ERROR "You must enable at least one of USE_SDL or USE_IMAGE")
endif()

# libjpeg
find_package(JPEG REQUIRED)
if (JPEG_FOUND)
    message(STATUS "Found JPEG: ${JPEG_LIBRARIES}")
else()
    message(FATAL_ERROR "libjpeg not found")
endif()

# SDL2
if (USE_SDL)
    # Use the SDL2 CMake module or find it via pkg-config
    find_package(SDL2 REQUIRED)
    if (SDL2_FOUND)
        message(STATUS "Found SDL2: ${SDL2_LIBRARIES}")
    else()
        message(FATAL_ERROR "SDL2 not found")
    endif()
endif()

file(GLOB_RECURSE SRCS src/*.c)

include_directories(ctracer 
  src/
  ${JPEG_INCLUDE_DIR}
)

if (USE_SDL)
  include_directories(${SDL2_INCLUDE_DIRS})
endif()

add_executable(ctracer ${SRCS})

target_link_libraries(ctracer PRIVATE ${JPEG_LIBRARIES})
if (USE_SDL)
    target_link_libraries(ctracer PRIVATE ${SDL2_LIBRARIES})
endif()


