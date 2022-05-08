# 注意
# CMakeではソースコードのディレクトリとは別にビルド専用のディレクトリが作成される
# ビルド結果は全てビルド専用のディレクトリに出力される
# これによりソースコードのメンテナンス性が向上される

# 参考URL
# https://kamino.hatenablog.com/entry/cmake_tutorial1
# https://qiita.com/shohirose/items/45fb49c6b429e8b204ac

# message:デバッグ用途のためコンソールに出力する
message("Start Root/CMake.")

# 対応するcmakeの最小バージョンを指定する
# 指定を満たさない場合はエラーで終了する
cmake_minimum_required(VERSION 3.17)

# プロジェクト名とプログラム言語を指定
project(PracticePathTracing CXX)

add_subdirectory(include)
add_subdirectory(tests)
enable_testing()

add_test(NAME MyTest COMMAND Test)


