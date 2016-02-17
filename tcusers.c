#include <stdio.h>
#include <string.h>

/*
C言語学習用課題
ファイルから文字列を取得し、構造体に格納する。

ファイル名	user.txt

ファイル内容の並びは「氏名」「かな」「電話番号」で構成。ファイルフォーマットは CSV.
1ファイル最大100名まで格納されている。

内容例
木村拓哉,きむらたくや,075-111-2221
稲垣五郎,いながきごろう,075-111-2222
香取慎吾,かとりしんご,075-111-2223

エラーチェック
ファイルが見つからない
ファイルフォーマットエラー
その他のエラー

コマンドライン
tcusers

*/
#define DATA_NUM 100
#define FILENAME "user.txt"

#define NO_ERROR 0
#define FILE_ERROR 1
#define FILETYPE_ERROR -1

typedef struct _user user_t;
struct _user{
	char name[50];
	char ruby[50];
	char phone[20];
};

void struct_init(user_t *p);
int struct_load(user_t *p ,char *file);
void struct_print(user_t *p);
void error_msg(int err);

//main関数-----------------------------------------------------------------------
int main(){
	int err = 0;
	char file[] = FILENAME;

	user_t data[DATA_NUM];
	user_t *data_ptr;
	data_ptr = data;
	struct_init(data_ptr);

	err = struct_load(data_ptr , file);
	if (err != NO_ERROR){
		error_msg(err);
		return FILE_ERROR;
	}

	struct_print(data_ptr);				//構造体の内容を表示する
	return 0 ;
}
//mainここまで--------------------------------------------------------------------

//構造体pをDATA_NUM分NULLで埋める---------------------------------------------------
void struct_init(user_t *p){
	for(int i = 0; i < DATA_NUM ; i++){
		strcpy( (p+i)->name,"\0" );
		strcpy( (p+i)->ruby,"\0" );
		strcpy( (p+i)->phone,"\0" );
	}
}

//FILENAMEのファイルを構造体pに読み込む----------------------------------------------
int struct_load(user_t *p ,char *file ) {
	char buf[120];
	memset( buf , '\0' , 120 );					//buf[119]まで'\0'埋め
	char *buf_p;
	FILE *fp;
	fp = fopen(file,"r");
	if (fp == NULL){
		printf("%s:ファイルが開けませんでした。\n", file);
		return FILE_ERROR;
	}
	int i=0;
	while( fgets(buf , 119 , fp) != NULL ){		//NULLまで1行ごとに読み込む(最大119バイト
											//120バイト目は必ず'\0'になっている→strtokでバッファオーバーフローする心配はない)
		if ( (memchr(buf, '\n', 119) == 0) && (memchr(buf, '\0', 119) == 0) ){
			return FILETYPE_ERROR;				//bufの120バイト目までに改行コードまたはNULLがない場合エラー
		}

		buf_p = strtok( buf , "," );				//もし","がいなくても119バイトで止まる
		if (buf_p != 0) {						//","が見つかっていた場合
			strncpy( (p+i)->name , buf_p ,49 );	//buf_pが示す値を49バイトまでコピー(50バイトまで初期化してある)
		} else {								//見つからないならファイル形式エラー
			return FILETYPE_ERROR;
		}

		buf_p = strtok(NULL,",");
		if (buf_p != 0) {
			(p+i)->name[49] = '\0';
			strncpy( (p+i)->ruby , buf_p ,49);
		} else {
			return FILETYPE_ERROR;
		}

		buf_p=strtok(NULL,"\n");				//構造体の3つ目の区切り文字は改行コード
		if (buf_p != 0){
			(p+i)->name[49] = '\0';
			strncpy( (p+i)->phone , buf_p ,19 );
		} else {
			return FILETYPE_ERROR;
		}
		i++;
		if ( i >= DATA_NUM ){
			break;								//DATA＿NUM個受け取ったら終わり
		}

		memset( buf , '\0' , 120 );				//一周ごとに再度'\0'で埋める
	}

	fclose(fp);
	return NO_ERROR;
}

//構造体の内容を表示する------------------------------------------------------------
void struct_print(user_t *p){
	int i=0;
	printf( "構造体の内容を表示します。\n" );
	while(strcmp((p+i)->name,"\0") != 0){
		printf("氏名:%s\nかな:%s\nTEL :%s\n" , (p+i)->name , (p+i)->ruby , (p+i)->phone);
		i++;
		if (i >= DATA_NUM){
			break;
		}
	}

}
//エラーメッセージ-----------------------------------------------------------------
void error_msg(int err){
	switch (err){
	  case NO_ERROR:
		break;

	  case FILE_ERROR:
		printf("ファイル読み込みに失敗しました。\n");
		break;

	  case FILETYPE_ERROR:
		printf("ファイル形式に問題があります。\n");
		break;

	  default:
		printf("不明なエラーが発生しました。\n");
		break;
	}
}