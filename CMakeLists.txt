# 注意
# CMakeではソースコードのディレクトリとは別にビルド専用のディレクトリが作成される
# ビルド結果は全てビルド専用のディレクトリに出力される
# これによりソースコードのメンテナンス性が向上される

# 参考URL
# https://kamino.hatenablog.com/entry/cmake_tutorial1
# https://qiita.com/shohirose/items/45fb49c6b429e8b204ac

# message:デバッグ用途のためコンソールに出力する
message("Message: START CMAKE")

# 対応するcmakeの最小バージョンを指定する
# 指定を満たさない場合はエラーで終了する
cmake_minimum_required(VERSION 3.17)

# プロジェクト名とプログラム言語を指定
project(PracticePathTracing CXX)

# 変数を作成する
# 作成した変数は${}で出力ができる
set(TEST_VARIABLE foo)
message("TEST_VARIABLE: '${TEST_VARIABLE}'")

# find_packageは自身のプロジェクト（ソースコード）に属していないライブラリを自動的に検索する
# ただし全てのライブラリに対して本機能が使えるとは限らない
# 詳細は以下を参照
# https://qiita.com/shohirose/items/d9bda00a39a113965c5c
# REQUIREDを設定することで見つからなかった場合には意図的に失敗させる
# REQUIREDを設定して成功した場合は見つかったことになる
# 実行した結果は以下の変数に結果が格納される
# No matter which mode is used, if the package has been found, a set of variables will be defined:
#    _FOUND
#    _INCLUDE_DIRS or _INCLUDES
#    _LIBRARY or _LIBRARIES or _LIBS
#    _DEFINITIONS
# 詳細は以下を参照
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Find-Libraries

find_package(PNG REQUIRED)

# 目的のパッケージが見つかったかの確認
message("FOUND_PACKAGE?: '${PNG_FOUND}'")
message("PNG_INCLUDE_DIRS: '${PNG_INCLUDE_DIRS}'")
message("PNG_LIBRARY: '${PNG_LIBRARY}'")

# add_executable:指定したソースコードを元に実行ファイルを作成する
#add_executable(main src/main.cpp)
#add_executable(main tests/vec3_test.cpp)
#add_executable(main tests/ray_test.cpp)
#add_executable(main tests/ppm_test.cpp)
#add_executable(main tests/sphere_test.cpp)

add_executable(main tests/pinhole_camera_test.cpp)

# target_include_directories:指定した実行ファイルにinclude_directoriesを指定する
# つまり実行ファイルとヘッダーファイルの紐付けを行う
target_include_directories(main PRIVATE "include")
target_include_directories(main PRIVATE "include/camera")
target_include_directories(main PUBLIC ${PNG_INCLUDE_DIRS})

