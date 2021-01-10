if(ScopeGuard_ROOT)
    set(ScopeGuard_INCLUDE_DIRS
      ${ScopeGuard_ROOT}/include
      ${ScopeGuard_ROOT}/include/ScopeGuard)
    if(NOT has_include_ROOT)
      message(FATAL_ERROR "must set has_include_ROOT")
    endif()
    find_package(has_include REQUIRED)
    if(NOT apply_ROOT)
      message(FATAL_ERROR "must set apply_ROOT")
    endif()
    find_package(apply REQUIRED)
	if(NOT preprocessor_ROOT)
      message(FATAL_ERROR "must set preprocessor_ROOT")
    endif()
    find_package(preprocessor REQUIRED)
    find_package(Boost REQUIRED)
    set(ScopeGuard_FOUND TRUE)
      if(NOT TARGET ScopeGuard::ScopeGuard)
      add_library(ScopeGuard_header_only INTERFACE)
      add_library(ScopeGuard::ScopeGuard ALIAS ScopeGuard_header_only)
      set(ScopeGuard_LIBRARIES
        ScopeGuard::ScopeGuard apply::apply preprocessor::preprocessor has_include::has_include Boost::headers)
      set_target_properties(ScopeGuard_header_only PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${ScopeGuard_INCLUDE_DIRS}"
        INTERFACE_LINK_LIBRARIES "${ScopeGuard_LIBRARIES}"
      )
    endif()
endif()
