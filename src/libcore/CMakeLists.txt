if(CMAKE_DEBUG_OPT)
    message("Start /src/libcore/CMake.")
endif()

set(INC_DIR "../../include/futaba/core")

add_library(futaba-core-obj SHARED
        ${INC_DIR}/vec3.h
        ${INC_DIR}/ray.h
        )

set_target_properties(futaba-core-obj PROPERTIES LINKER_LANGUAGE CXX)
