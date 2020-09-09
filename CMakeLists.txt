# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include(main/component.cmake)

foreach(dir IN LISTS CORE_DIRS CUSTOM_DIRS I2C_DIRS)
  message(STATUS "main/${dir}")
  add_subdirectory("main/${dir}")
endforeach(dir)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(firmware)
