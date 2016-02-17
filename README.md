# Practice
## 概要
ファイルから文字列を取得し、構造体に格納する。
出力先を指定されていないので、標準出力で行う。
## コンパイル方法
gcc -Wall -o tcusers tcusers.c

## 実行方法
事前にCSV形式で「氏名」「かな」「電話番号」の構成であるuser.txtを同じフォルダにおく。
最終行は改行が1回だけ入っていてもよい。

##コマンドライン
tcusers

##テストスクリプト
コンパイル後test.shを実行すると

test/test1
test/test2
test/test3

にtcusersをコピーする。
各testフォルダのtest.shを実行するとそれぞれ、

user.txtが空テキストの場合
user.txtが100行の場合
user.txtが100行を超える場合

のテストを行う。