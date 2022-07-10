# message:デバッグ用途のためコンソールに出力する
message("Start tests/CMake.")

find_package(GTest REQUIRED)
find_package(OpenMP REQUIRED)

# 目的のパッケージが見つかったかの確認
message("FOUND_GTest_PACKAGE?: '${GTest_FOUND}'")
message("FOUND_OpenMP_PACKAGE?: '${OpenMP_FOUND}'")

if (OpenMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

# add_ececutable:実行ファイル（実行可能なファイルで実行するとプログラムが動作する）を作成する
# ただしこの実行ファイルはライブラリのリンクがなされていない
# ビルドする実行ファイルを定義する
# 下のようにadd_executableに追加すると宣言の重複となり失敗してしまう
# add_executable(my_test test_main.cpp test_pixel.cpp test_ray.cpp test_vec3.cpp test_sphere.cpp test_image.cpp)
add_executable(my_test test_main.cpp)

# Compile Option
# $ g++ -O3 -Wall ... (etc)
target_compile_options(my_test PUBLIC -O3 -Wall)

# target_include_directories:指定した実行ファイルにinclude_directoriesを指定する
# つまり実行ファイルとヘッダーファイルの紐付けを行う
# 下の書き方は不要かも（include1つのみで十分）
message("CMAKE_SOURCE_DIR: '${CMAKE_SOURCE_DIR}'")

# filesを使えば複数ディレクトリを一括で取得できる

# ここでtarget_include_directoriesにincludeのパスだけでは動作しないのはおかしい
# -> これは下のような書き方をすれば相対パスを#include camera/pinholecamera.hpp のような書き方をしないで済むから
# -> 動作から推察するに単にinclude先のルートのパスをコンパイラに伝えているだけである
# 各.hファイルの場所をフルパスで書けば不要だがそれでは管理という観点で不向きである
target_include_directories(my_test PRIVATE ${CMAKE_SOURCE_DIR}/include/)
target_include_directories(my_test PRIVATE ${CMAKE_SOURCE_DIR}/src/)


# 以下のように書くとincludeの際にファイル名のみで済むがフォルダ構成が見えなくなるので望ましくない
#target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include/background")
#target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include/image")
#target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include/camera")
#target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include/object")
#target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include/lights")
#target_include_directories(my_test PRIVATE "${CMAKE_SOURCE_DIR}/include/materials")

target_include_directories(my_test PUBLIC "${CMAKE_SOURCE_DIR}/extern/stb")


# exterのstb_image_write.hを共有ライブラリという形式で呼び出している
# このadd_libraryでライブラリ(XXX.soおよびXXX.a)を作成する
# ビルドするライブラリを定義する(add_executable <-> add_libraryで対になっていると考えればよい)
add_library(stb_image_write SHARED "${CMAKE_SOURCE_DIR}/extern/stb/stb_image_write.h")
add_library(stb_image SHARED "${CMAKE_SOURCE_DIR}/extern/stb/stb_image.h")

# 作成したライブラリのパスを取得する
target_include_directories(stb_image_write PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(stb_image PUBLIC "${PROJECT_SOURCE_DIR}/include/background")

# これがないとエラーが発生してしまう
# 複数指定可能
set_target_properties(stb_image stb_image_write PROPERTIES LINKER_LANGUAGE CXX)

# target_link_libraries:作成済みの実行ファイルにコンパイル済みのライブラリ(libXXX.soおよびlibXXX.a)のリンクを行う
# "実行ファイルの作成"という手続きと、"実行ファイルにライブラリのリンク"という手続きは別であることに注意
target_link_libraries(my_test gtest gtest_main pthread stb_image_write stb_image)

gtest_add_tests(TARGET my_test)