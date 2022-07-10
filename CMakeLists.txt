# 注意
# CMakeではソースコードのディレクトリとは別にビルド専用のディレクトリが作成される
# ビルド結果は全てビルド専用のディレクトリに出力される
# これによりソースコードのメンテナンス性が向上される

# 以下のコマンドは非推奨であることに注意
# include_directories
# add_definitions, add_compile_definitions, add_compile_options
# link_directories
# link_libraries

# 参考URL
# https://kamino.hatenablog.com/entry/cmake_tutorial1
# https://qiita.com/shohirose/items/45fb49c6b429e8b204ac

# message:デバッグ用途のためコンソールに出力する
message("Start Root/CMake.")

# ${CMAKE_SOURCE_DIR}:CMakeLists.txtのルートのパスを表す
message("DEBUG: CMAKE_SOURCE_DIR is ${CMAKE_SOURCE_DIR}")

# 対応するcmakeの最小バージョンを指定する
# 指定を満たさない場合はエラーで終了する
# これはルートのCMakeListsにのみ記載する
cmake_minimum_required(VERSION 3.17)

# プロジェクト名とプログラム言語を指定
# これはルートのCMakeListsにのみ記載する
PROJECT(PracticePathTracing CXX)

# コンパイラオプションの指定
# 最適化オプションを外す
# このやり方は非推奨の模様
# https://qiita.com/shohirose/items/5b406f060cd5557814e9
set(CMAKE_C_FLAGS "-O" )

enable_testing()
add_subdirectory(tests)
#add_subdirectory(src)

# そもそも論として各プログラムはオブジェクトファイル作成時には、独立してコンパイルがされる（必要なインタフェースは仮宣言してでも揃っていないといけない）

# そもそも論として「実行ファイルの作成」と「オブジェクトファイルの作成」と「静的ライブラリおよび共有ライブラリの作成」はすべて別
# そもそも論としてg++では「オブジェクトリファイル（XXX.o）を作成するコマンド」と、「ライブラリ（XXX.soおよびXXX.a）を作成するコマンド」は異なる
# そもそも論として「ヘッダファイルのXXX.hおよびXXX.hpp」等はコンパイルしても、ヘッダファイルのオブジェクトファイル(XXX.o)は作成されない
# そのため.hのみからなるディレクトリ内にCMakeLists.txtは存在しない
# そもそも論としてヘッダファイルにはインタフェースのみが定義されていて、実装は別のプログラムファイルに記載されている場合がある
# そもそも論として「プログラムファイル(XXX.cおよびXXX.cpp)」はコンパイルするとオブジェクトファイル(XXX.o)が作成される

# そもそも論として「includeディレクトリが別ディレクトリの場合」、g++ではオブジェクトファイルの作成時にincludeディレクトリのパスを指定する必要がある
# そもそも論として「libraryディレクトリの別ディレクトリの場合」、実行ファイルの生成時に「includeディレクトリ」と「libraryディレクトリ」のパスを指定する必要がある