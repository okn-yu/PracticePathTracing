if(CMAKE_DEBUG_OPT)
    message("Start /src/CMake.")
endif()

# futaba support libraries
add_subdirectory(libcore)

# futaba executables
add_subdirectory(futaba)

