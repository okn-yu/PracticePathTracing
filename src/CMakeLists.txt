# message:デバッグ用途のためコンソールに出力する
message("Start src/CMake.")

# 対応するcmakeの最小バージョンを指定する
# 指定を満たさない場合はエラーで終了する
cmake_minimum_required(VERSION 3.17)

# プロジェクト名とプログラム言語を指定
project(PracticePathTracing CXX)
add_executable(main main.cpp)

target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/include/image")
target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/include/camera")
