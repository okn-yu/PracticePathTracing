if(CMAKE_DEBUG_OPT)
    message("Start /src/libcore/CMake.")
endif()

set(INC_DIR "../../include/futaba/core")

add_library(futaba-core SHARED
        ${INC_DIR}/vec3.h
        ${INC_DIR}/ray.h
        ${INC_DIR}/util.h
        util.cpp # 当然だがヘッダファイルutil.hだけでなく実装本体のutil.cppも指定しないと実行できない
        )

set_target_properties(futaba-core PROPERTIES LINKER_LANGUAGE CXX)
