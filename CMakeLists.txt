cmake_minimum_required(VERSION 2.8)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif()

project(ErodeFilter)

# Find ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})



add_executable(ErodeFilter FilterErodeItk.cxx)

target_link_libraries(ErodeFilter  ${ITK_LIBRARIES})
