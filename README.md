# PathTracerPractice
* パストレーシングの実装の練習用のリポジトリ
* 将来的には本リポジトリの実装をベースに、様々な微分可能なレンダラーを実装する予定

# 参考書籍
* https://booth.pm/ja/items/1159865
* https://booth.pm/ja/items/2186534

# 参考実装
* https://github.com/yumcyaWiz/Photorealism-Book
* https://github.com/kinakomoti-321/Raytracing_With_Embree

# 補足資料
## CMake
* https://qiita.com/shohirose/items/45fb49c6b429e8b204ac

## PPM形式
* 特別なツールがなくても読み書き編集ができるプレーンテキストの画像形式
* https://www.mm2d.net/main/prog/c/image_io-01.html

## PNG形式
* https://suzulang.com/libpng-try-filewrite/

## TODO:
* test_clolrでガンマ補正の修正後の値で試験を成功させること
* test_pinhole_cameraでカメラの視点がy軸に近い場合でも実行できるようにすること