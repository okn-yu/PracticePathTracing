# TODO: testsで同様の書き方では失敗するため調査が必要

# message:デバッグ用途のためコンソールに出力する
message("Start src/CMake.")

# 実行ファイルのビルド
add_executable(main main.cpp)

# 静的ライブラリ（STATIC）/動的ライブラリ（SHARED）のビルド
add_library(lib_image SHARED "${CMAKE_SOURCE_DIR}/include/image/pixel.hpp")

# propertiesとしてCXXを指定しないと以下のエラーが発生してしまう
# CMake Error: CMake can not determine linker language for target:XXX
# CMake Error: Cannot determine link language for target "XXX".
set_target_properties(lib_image PROPERTIES LINKER_LANGUAGE CXX)

# includeディレクトリをtargetに追加する
# add_libraryでライブラリの作成後に実行する必要がある
target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/include/image/")

# 実行対象のターゲットとライブラリのリンクを行う
target_link_libraries(main lib_image)