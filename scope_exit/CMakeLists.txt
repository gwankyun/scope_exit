add_library(scope_exit)
target_sources(scope_exit
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src # 模塊根目錄
    FILES                                     # 模塊接口單元
      src/scope_exit.base.ixx
      src/scope_exit.ixx
      src/ref.ixx
      src/deleter.ixx
  PRIVATE
    src/scope_exit_impl.hpp
    src/scope_exit_base_impl.hpp
    src/ref_impl.hpp
    src/unique.h
    src/marco.h
    src/deleter_impl.hpp
  PUBLIC
    scope_exit.h       # 提供宏
    scope_exit.hpp     # 僅頭庫
    deleter.hpp        # 提供幾個內存刪除器
    ref.hpp            # 提供lite::ref和lite:cref
    local_function.hpp # 提供C++98可用的局部函數
)
target_compile_features(scope_exit PRIVATE cxx_std_23)
