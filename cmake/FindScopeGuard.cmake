if(ScopeGuard_ROOT)
    set(ScopeGuard_INCLUDE_DIRS
      ${ScopeGuard_ROOT}/include
      ${ScopeGuard_ROOT}/include/ScopeGuard)
    set(ScopeGuard_FOUND TRUE)
      if(NOT TARGET ScopeGuard::ScopeGuard)
      add_library(ScopeGuard_header_only INTERFACE)
      add_library(ScopeGuard::ScopeGuard ALIAS ScopeGuard_header_only)
      set_target_properties(ScopeGuard_header_only PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${ScopeGuard_INCLUDE_DIRS}"
      )
    endif()
endif()
