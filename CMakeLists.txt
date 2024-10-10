cmake_minimum_required(VERSION 3.20...3.28)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

if (NOT WIN32)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

# Project definition
project(kaiproc)

# Target to copy asset folder into binary folder
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

# Create core components
# add_subdirectory(external)

###################################Begin executable
set(KPG_SOURCES
   kpg/main.cpp)

add_executable(${PROJECT_NAME} ${KPG_SOURCES})

# Add dependency on assets
add_dependencies(${PROJECT_NAME} assets)
