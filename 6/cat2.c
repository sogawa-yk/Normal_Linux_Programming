#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int i;

    if(argc == 1){ // 標準入力から受け取る場合 
        int c;

        while((c = getchar()) != EOF){ // この部分の条件は本当にこれでいいのかはわからない
            if(putchar(c) < 0) exit(1);
        }
    }else{
        for(i=1; i<argc; i++){ // 引数に指定されたファイル数分だけ繰り返す
            FILE *f; // FILE型のポインタ
            int c;
            
            f = fopen(argv[i], "r"); // ファイルを開く（ファイルにつながるストリームを取得し、それにつながるFILE型のポインタを得る）
            if(!f){ // 得られなかったとき
                perror(argv[i]);
                exit(1);
            }
            
            while((c = fgetc(f)) != EOF){ // FILE型のポインタfを用いてファイルの内容を読み込み（バイト単位）バイト単位で読み取っているのに戻り値がint型になるのは、EOFを表すため
                if(putchar(c) < 0) exit(1); // 読み込んだバイトを標準出力に書き込み　putchar()の返り値が負になるときは書き込めていないとき（書き込んだバイト数が本来返るため）
            }

            fclose(f); // ストリームを破棄（シェルがしてくれるので書かなくてもいいが、プロセスごとに確保できるストリームの数が決まっているので、使い終わったら開放するのが良い
        }
    }

    exit(0);
}