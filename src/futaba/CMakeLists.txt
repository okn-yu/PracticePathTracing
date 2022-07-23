if(CMAKE_DEBUG_OPT)
    message("Start /src/futaba/CMake.")
endif()

add_executable(futaba futaba.cpp)
target_link_libraries(futaba PRIVATE futaba-core)


