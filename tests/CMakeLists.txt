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

#下のようにadd_executableに追加すると宣言の重複となり失敗してしまう
#add_executable(my_test test_main.cpp test_pixel.cpp test_ray.cpp test_vec3.cpp test_sphere.cpp test_image.cpp)
add_executable(my_test test_main.cpp)

# target_include_directories:指定した実行ファイルにinclude_directoriesを指定する
# つまり実行ファイルとヘッダーファイルの紐付けを行う
target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include/image")
target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include/camera")
target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/extern/stb")

# コメントを書く
target_link_libraries(my_test gtest gtest_main pthread)

# コメントを書く
gtest_add_tests(TARGET my_test)