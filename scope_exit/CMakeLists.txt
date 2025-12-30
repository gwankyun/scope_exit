add_library(scope_exit_base INTERFACE)
target_sources(scope_exit_base
  INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
      scope_exit.h       # 提供宏
      local_function.hpp # 提供C++98可用的局部函數
      src/scope_exit_impl.hpp
      src/scope_exit_base_impl.hpp
      src/ref_impl.hpp
      src/unique.h
      src/marco.h
      src/deleter_impl.hpp
)
target_include_directories(scope_exit_base INTERFACE ${PROJECT_SOURCE_DIR})
add_library(scope_exit::base ALIAS scope_exit_base)

add_library(scope_exit_header_only INTERFACE)
target_sources(scope_exit_header_only
  INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
      scope_exit.hpp # 僅頭庫
      deleter.hpp    # 提供幾個內存刪除器
      ref.hpp        # 提供lite::ref和lite:cref
)
target_link_libraries(scope_exit_header_only INTERFACE scope_exit::base)
add_library(scope_exit::header_only ALIAS scope_exit_header_only)

add_library(scope_exit_module)
target_sources(scope_exit_module
  PUBLIC
    FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src # 模塊根目錄
    FILES                                     # 模塊接口單元
      src/scope_exit.base.ixx
      src/scope_exit.ixx
      src/ref.ixx
      src/deleter.ixx
)
target_link_libraries(scope_exit_module PUBLIC scope_exit::base)
target_compile_features(scope_exit_module PRIVATE cxx_std_23)
add_library(scope_exit::module ALIAS scope_exit_module)
