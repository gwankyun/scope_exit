add_library(scope_exit)
target_sources(scope_exit
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src # 模塊根目錄
    FILES src/scope_exit.ixx                  # 模塊接口單元
  PRIVATE
    src/scope_exit_impl.hpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/scope_exit.h
    src/scope_exit.hpp
)
target_compile_features(scope_exit PRIVATE cxx_std_23)
