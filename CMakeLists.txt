cmake_minimum_required(VERSION 3.19)

project(svz-data VERSION 0.1.0 DESCRIPTION "SvZ Data")

# Create shared library
add_library(svz-data INTERFACE)

# Include header files
target_include_directories(svz-data INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(svz-data PROPERTIES CXX_STANDARD 17)