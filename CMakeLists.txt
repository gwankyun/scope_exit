# cmake最低版本
cmake_minimum_required(VERSION 3.19)

# 啟用IDE目錄功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 包括模板
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
include(CMakePrintHelpers)

# 輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 項目名
project(ScopeGuard)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W4;/MP;/Zc:__cplusplus;>")
add_compile_definitions("SCOPE_GUARD_HAS_CXX_11=1")

set(ScopeGuard_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
find_package(ScopeGuard REQUIRED)

# 生成執行文件
set(ScopeGuard ScopeGuard)
add_executable(${ScopeGuard})

target_sources(${ScopeGuard}
  PRIVATE
    src/main.cpp
    include/ScopeGuard.hpp
    cmake/FindScopeGuard.cmake
)

# 引用庫
target_link_libraries(${ScopeGuard}
  PUBLIC
    ScopeGuard::ScopeGuard
)

target_compile_features(${ScopeGuard} PRIVATE cxx_std_17)

# 如果找到Catch2就添加測試
find_package(Catch2 CONFIG)
cmake_print_variables(Catch2_FOUND)

if(Catch2_FOUND)
  set(test test)
  add_executable(${test})
  target_sources(${test}
    PRIVATE src/test.cpp)
  target_link_libraries(${test}
    PUBLIC
      ScopeGuard::ScopeGuard Catch2::Catch2)
  target_compile_features(${test} PRIVATE cxx_std_17)
endif()
