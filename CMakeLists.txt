# cmake最低版本
cmake_minimum_required(VERSION 4.1)

# 包含模塊
include(CMakePrintHelpers)

# 項目名
project(scope_exit)

find_package(spdlog REQUIRED)
find_package(Catch2 REQUIRED)

add_subdirectory(scope_exit)

add_executable(main)
target_sources(main
  PRIVATE
    src/main.cpp
)
target_link_libraries(main
  PRIVATE
    spdlog::spdlog
    scope_exit
)
target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(main PRIVATE Catch2::Catch2)
target_compile_features(main PRIVATE cxx_std_23)
