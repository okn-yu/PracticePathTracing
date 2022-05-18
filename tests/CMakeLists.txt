# TODO: src直下と同じ形式の以下のMakefileでは二重定義で失敗するため調査が必要
#[[
# message:デバッグ用途のためコンソールに出力する
message("Start tests/CMake.")

find_package(GTest REQUIRED)

message("FOUND_GTest_PACKAGE?: '${GTest_FOUND}'")

add_executable(my_test test_main.cpp test_pixel.cpp)

add_library(lib_image SHARED "${CMAKE_SOURCE_DIR}/include/image/pixel.hpp")
set_target_properties(lib_image PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(my_test PUBLIC "${CMAKE_SOURCE_DIR}/include/image/")
target_link_libraries(my_test gtest gtest_main pthread)
gtest_add_tests(TARGET my_test)
]]

# message:デバッグ用途のためコンソールに出力する
message("Start tests/CMake.")

# 対応するcmakeの最小バージョンを指定する
# 指定を満たさない場合はエラーで終了する
cmake_minimum_required(VERSION 3.17)

# プロジェクト名とプログラム言語を指定
project(PracticePathTracing CXX)

find_package(GTest REQUIRED)

# 目的のパッケージが見つかったかの確認
message("FOUND_GTest_PACKAGE?: '${GTest_FOUND}'")

add_executable(my_test test_main.cpp test_pixel.h test_ray.h test_vec3.h test_sphere.h test_image.h)

# target_include_directories:指定した実行ファイルにinclude_directoriesを指定する
# つまり実行ファイルとヘッダーファイルの紐付けを行う
target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include/image")
target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include/camera")
target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/extern/stb")
#target_include_directories(my_test PUBLIC ${PNG_INCLUDE_DIRS})

# コメントを書く
target_link_libraries(my_test gtest gtest_main pthread)

# コメントを書く
gtest_add_tests(TARGET my_test)
