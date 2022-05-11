# message:デバッグ用途のためコンソールに出力する
message("Start include/CMake.")

# 対応するcmakeの最小バージョンを指定する
# 指定を満たさない場合はエラーで終了する
cmake_minimum_required(VERSION 3.17)

# プロジェクト名とプログラム言語を指定
project(PracticePathTracing CXX)

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
message("FOUND_PNG_PACKAGE?: '${PNG_FOUND}'")
message("PNG_INCLUDE_DIRS: '${PNG_INCLUDE_DIRS}'")
message("PNG_LIBRARY: '${PNG_LIBRARY}'")

add_subdirectory(camera)
add_subdirectory(image)

