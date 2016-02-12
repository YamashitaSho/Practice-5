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

typedef struct _user user_t;
struct _user{
	char name[50];
	char ruby[50];
	char phone[20];
};

void structinit(user_t *p);
int structload(user_t *p ,char *file);
void structprint(user_t *p);
void errmsg(int err);

//main関数-----------------------------------------------------------------------
int main(){
	int err = 0;
	char file[] = FILENAME;

	user_t data[DATA_NUM];
	user_t *data_ptr;
	data_ptr = data;
	structinit(data_ptr);
	
	err = structload(data_ptr , file);
	if (err!=0){errmsg(err);return -1;}
	structprint(data_ptr);				//構造体の内容を表示する
	return 0 ;
}
//mainここまで--------------------------------------------------------------------

//構造体pをDATA_NUM分NULLで埋める---------------------------------------------------
void structinit(user_t *p){
	for(int i=0; i<DATA_NUM-1 ;i++){
		strcpy((p+i)->name,"\0");
		strcpy((p+i)->ruby,"\0");
		strcpy((p+i)->phone,"\0");
	}
}

//FILENAMEのファイルを構造体pに読み込む----------------------------------------------
int structload(user_t *p ,char *file){
	char buf[120];
	char *buf_p;
	FILE *fp;
	fp = fopen(file,"r");
	if (fp == NULL){
		printf("%s:ファイルが開けませんでした。", file);
		return -1;
	}
	int i=0;
	while(fgets(buf,100,fp) != NULL){		//NULLまで1行ごとに読み込む
		buf_p=strtok(buf,",");
		if (buf_p != 0){
			strcpy((p+i)->name,buf_p);
		}else{ return -1;}
		buf_p=strtok(NULL,",");
		if (buf_p != 0){
			strcpy((p+i)->ruby,buf_p);
		}else{ return -1;}
		buf_p=strtok(NULL,"\n");
		if (buf_p != 0){
			strcpy((p+i)->phone,buf_p);
		}else{ return -1;}
		i++;
	}
	
	fclose(fp);
	return 0;
}

//構造体の内容を表示する------------------------------------------------------------
void structprint(user_t *p){
	int i=0;
	printf("構造体の内容を表示します。\n");
	while(strcmp((p+i)->name,"\0") != 0){
		printf("氏名:%s\nかな:%s\nTEL :%s\n",(p+i)->name,(p+i)->ruby,(p+i)->phone);
		i++;
		if (i > DATA_NUM){break;}
	}
}
//エラーメッセージ-----------------------------------------------------------------
void errmsg(int err){
	switch (err){
	  case 0:
		break;
	  case -1:
		printf("ファイル読み込みに失敗しました。\n");
		break;
	  default:
		printf("不明なエラーが発生しました。\n");
		break;
	}
}