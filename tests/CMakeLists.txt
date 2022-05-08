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

add_executable(Test test_pixel.cpp)

# target_include_directories:指定した実行ファイルにinclude_directoriesを指定する
# つまり実行ファイルとヘッダーファイルの紐付けを行う
target_include_directories(Test PRIVATE "../include")
target_include_directories(Test PRIVATE "../include/image")
target_include_directories(Test PRIVATE "../include/camera")
target_include_directories(Test PUBLIC ${PNG_INCLUDE_DIRS})
target_link_libraries(Test gtest gtest_main pthread)