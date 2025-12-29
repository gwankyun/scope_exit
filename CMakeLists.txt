# cmake最低版本
cmake_minimum_required(VERSION 3.30)

# 包含模塊
include(CMakePrintHelpers)

# get_import_std enable_module_std target_enable_module_std
include(cmake/cxx_module.cmake)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # CMake對Clang的import std;支持還在試驗階段
  # 需要設置此UUID
  get_import_std(import_std_uuid)
  cmake_print_variables(import_std_uuid)

  set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD ${import_std_uuid}
    CACHE STRING "UUID for import std")

  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# 項目名
project(scope_exit)

include(cmake/cxx_module.cmake)

enable_module_std(ON)

find_package(Catch2 CONFIG REQUIRED)

add_subdirectory(scope_exit)

#[[

include(GNUInstallDirs)

# 添加安裝
install(
  TARGETS scope_exit
  EXPORT scope_exitTargets
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
  EXPORT scope_exitTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/scope_exit
  NAMESPACE scope_exit::
)

install(
  FILES
    cmake/scope_exitConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/scope_exit
)

#]]

# 添加測試

add_library(test_interface INTERFACE)
target_sources(test_interface
  INTERFACE
    src/main_decl.hpp
    src/main_impl.hpp
)
target_link_libraries(test_interface
  INTERFACE
    Catch2::Catch2
    # scope_exit
)
target_include_directories(test_interface INTERFACE ${PROJECT_SOURCE_DIR})
target_compile_features(test_interface INTERFACE cxx_std_23)

add_executable(test_module)
target_sources(test_module
  PRIVATE
    src/main.cpp
)
target_link_libraries(test_module
  PRIVATE
    test_interface
    scope_exit::module
    # scope_exit_base
)

add_executable(test_header)
target_sources(test_header
  PRIVATE
    src/main_header.cpp
)
target_link_libraries(test_header
  PRIVATE
    test_interface
    scope_exit::header_only
)

include(CTest)
include(Catch)

catch_discover_tests(test_module)
catch_discover_tests(test_header)

# 生成.clangd配置文件
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_custom_target(generate_clangd
    COMMAND ${CMAKE_COMMAND}
      -D SOURCE_DIR=${CMAKE_SOURCE_DIR}
      -D BINARY_DIR=${CMAKE_BINARY_DIR}
      -D CONFIG=$<CONFIG>
      -P ${CMAKE_SOURCE_DIR}/cmake/generate_clangd.cmake
    COMMENT "生成.clangd配置文件"
  )
endif()
