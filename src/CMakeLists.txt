# TODO: testsで同様の書き方では失敗するため調査が必要

# message:デバッグ用途のためコンソールに出力する
message("Start src/CMake.")

# 実行ファイルのビルド
add_executable(main main.cpp)
