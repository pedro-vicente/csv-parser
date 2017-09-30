cmake_minimum_required(VERSION 2.8)
project(read_csv)

#/////////////////////////////////////////////////////////////////////////////////////
#general C/C++ build flags
#/////////////////////////////////////////////////////////////////////////////////////

set(CMAKE_BUILD_TYPE Debug)

if (MSVC)
  add_definitions( "/D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_DEPRECATE" )
endif()

#//////////////////////////
#sources 
#//////////////////////////

add_executable(read_test read_test.cc csv.cc csv.hh)
add_executable(read_dc311 read_dc311.cc csv.cc csv.hh)

