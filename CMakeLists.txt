cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(reset-after-percentage)

add_library(reset-after-percentage SHARED src/reset-after-percentage.cpp)

target_include_directories(reset-after-percentage PRIVATE
  libraries/minhook/include
  libraries/cocos-headers/cocos2dx/
  libraries/cocos-headers/cocos2dx/include
  libraries/cocos-headers/cocos2dx/kazmath/include
  libraries/cocos-headers/cocos2dx/platform/win32
  libraries/cocos-headers/cocos2dx/platform/third_party/win32
  libraries/cocos-headers/cocos2dx/platform/third_party/win32/OGLES
  libraries/gd.h
  libraries/gd.h/include
  libraries/Mega-Hack-Extensions/include
)

add_subdirectory(libraries/minhook)
add_subdirectory(libraries/cocos-headers)
target_link_libraries(reset-after-percentage
  ${CMAKE_SOURCE_DIR}/libraries/cocos-headers/cocos2dx/libcocos2d.lib
  minhook
  cocos2d
  ${CMAKE_SOURCE_DIR}/libraries/Mega-Hack-Extensions/bin/hackpro.lib
)