#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(const char *path);
static void die(const char *s);

int
main(int argc, char *argv[])
{
    int i;

    if(argc < 2){
        fprintf(stderr, "%s: file name not given\n", argv[0])
    }
    for(i=1; i<argc; i++){
        do_cat(argv[i]); // コマンドライン引数に指定されたファイルを一つずつ処理
    }
    exit(0);
}

#define BUFFER_SIZE 2048

static void
do_cat(const char *path)
{
    int fd;
    unsigned char buf[BUFFER_SIZE];
    int n;

    fd = open(path, O_RDONLY); // ストリームを作成
    if(fd < 0) die(path); // 作成に失敗したらエラー終了
    for(;;){
        n = read(fd, buf, sizeof buf); // ストリームからバッファのサイズ分読み込む
        if(n < 0) die(path); // nが負（読み込み失敗）の場合は、エラー終了
        if(n == 0) break; // nが０の場合はストリームからの読み込みが終わったということ（この回のループで読み込んだバイト数が０）なので、抜ける
        if(write(STDOUT_FILENO, buf, n) < 0) die(path); // バッファの中身を標準出力に書き込み（書き込むのはバッファのサイズ分じゃなくて、読み込んだバイト数分　<=　そうしないとわけわからん値書き込んじゃう）
    }
    if(close(fd) < 0) die(path); // ストリームを破棄
}

static void
die(const char *s)
{
    perror(s); // エラー出力 perror()は、グローバル変数errnoの値（エラー発生時に自動で入る）を見て表示するエラーコードを決めている。そのエラーコードに加えてエラーを出したファイルパスなどを表示させたいとき、引数にその文字列を指定する
    exit(1);
}