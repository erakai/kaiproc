cmake_minimum_required(VERSION 3.20...3.28)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

if (NOT WIN32)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

# Project definition
project(kaiproc)

###################################Locate SDL
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
set(SDL_INCLUDE
  PUBLIC include/
  PUBLIC ${SDL2_INCLUDE_DIRS}
  PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
)
set(SDL_LINK
  PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}
)

###################################Add components

# Target to copy asset folder into binary folder
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

# Create dependencies
add_subdirectory(external)

###################################Begin executable
set(KPG_SOURCES
   kpg/src/main.cpp
   kpg/src/procgen/perlin.cpp
   kpg/src/procgen/noisemap.cpp
   kpg/src/procgen/debugwin.cpp
   kpg/src/gui/gui.cpp
   kpg/src/gui/input.cpp
   kpg/src/gui/display.cpp
   kpg/src/utils/logger.cpp)

add_executable(${PROJECT_NAME} ${KPG_SOURCES})

# Add include dir
target_include_directories(${PROJECT_NAME} PUBLIC kpg/include)

# Add dependency on assets
add_dependencies(${PROJECT_NAME} assets)

# Link to sdl
target_include_directories(${PROJECT_NAME} ${SDL_INCLUDE})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL_LINK})

# Link to ImGui for debugging ui
target_link_libraries(${PROJECT_NAME} PUBLIC ImGui)
