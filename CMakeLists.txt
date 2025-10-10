# cmake最低版本
cmake_minimum_required(VERSION 4.1)

# 包含模塊
include(CMakePrintHelpers)

# CMake對Clang的import std;支持還在試驗階段
# 需要設置此UUID，以下值衹保證在[4.1.0, 4.1.2]有效
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444"
  CACHE STRING "UUID for import std")

# 項目名
project(scope_exit)

# 為目標啟用標準庫模塊
function(target_enable_module_std tgt enable_std)
  # 檢查當前C++編譯器是否為Clang或GNU
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set_target_properties(${tgt}
      PROPERTIES
      CXX_MODULE_STD ${enable_std}
    )
  endif()
endfunction()

# 全局啟用標準庫模塊
function(enable_module_std enable_std)
  # 檢查當前C++編譯器是否為Clang或GNU
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(CMAKE_CXX_MODULE_STD ${enable_std} PARENT_SCOPE)
  endif()
endfunction()

enable_module_std(ON)

find_package(spdlog REQUIRED)
find_package(Catch2 REQUIRED)

add_subdirectory(scope_exit)

add_executable(test_example)
target_sources(test_example
  PRIVATE
    src/main.cpp
)
target_link_libraries(test_example
  PRIVATE
    spdlog::spdlog
    scope_exit
)
target_include_directories(test_example PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(test_example PRIVATE Catch2::Catch2)
target_compile_features(test_example PRIVATE cxx_std_23)


if(MSVC)
  include(CTest)
  include(Catch)
  catch_discover_tests(test_example)
endif()
