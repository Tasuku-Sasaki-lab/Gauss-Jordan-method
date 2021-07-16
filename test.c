#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>//malloc関数を使用するのに必要
#include <stdbool.h>

void pivot(double a[4][4], int p); /* ピボット処理用関数の定義 */
#define EPSIRON 0.00005 //丸め誤差対策


int main(void){

    double a[4][4], c[4][4];
    int m, n, i, j,k;
    FILE *fp; // FILE型構造体
    char fname[] = "ginverse.txt";
    bool isError;

// 一番目の初期設定

// aのファイル読み込みとコンソール入力からの初期設定

    fp = fopen(fname,"r"); // ファイルを開く。失敗するとNULLを返す。
    if ((fp = fopen("ginverse.txt","r")) == NULL)
    {
        printf("ファイルの読み込みに失敗しました\n");
    }
    for(n=0;n<4;n++)
    {
    for(m=0;m<4;m++)
    {
        
        fscanf( fp,"%lf  ",&a[n][m]);
        
    }
    }
    fclose(fp);
    
    printf("K=");
    scanf("%lf",&a[1][2]);

// cの初期設定

  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      if(i==j){
        c[i][j]=1;
      }
      else{
        c[i][j]=0;
      }
    }
  }

// 二番目の操作

for(k=0;k<4;k++)
    {

// 二番目の1の操作(ピボット操作が必要かどうかを検討)

if(fabs(a[k][k]) < EPSIRON)
{

pivot(a,k);

}

// 二番目の2の操作(注目する対角要素を1とする)

n = a[k][k];

for(j=0;j<4;j++){
    a[k][j]=a[k][j]/n;
  c[k][j]=c[k][j]/n;
}

// 二番目の3の操作

for(i=0;i<4;i++){
  if(i!=k){
    n=a[i][k];
    for(j=0;j<4;j++){
        a[i][j]=a[i][j]-a[k][j]*n;
      c[i][j]=c[i][j]-c[k][j]*n;
    }
  }
}
    
    }

//  逆行列を出力(正則か判定)
 

for(i=0;i<4;i++){
  if(a[i][0]==0&&a[i][1]==0&&a[i][3]){
    printf("No Inverse Matrix!");
    exit(EXIT_SUCCESS);
  }
  }

printf("inverse A =\n");
for(i=0;i<4;i++){
  for(j=0;j<4;j++){
   printf("%.5f ",c[j][i]);
  }
  printf("\n");
}
    }
  


void pivot(double a[][4],int p)
{
    /* pivot変換用関数 */
    int i,pivot;
    double max_value; /* 最大の変数を格納 */
    double temp_value;
    int temp[4];

    max_value = 0; /* 必要な変数の初期化 */
    pivot = 0;
    

    /* どの係数a[i][p]が一番大きいかを確認 */
        max_value = fabs(a[0][p]);
        
    for(i=1;i<4;i++)
    {
    if (max_value < fabs(a[i][p]))
    {
        max_value = fabs(a[i][p]);
        pivot = i;
    }
        else continue;
    }

     
    /* 一番大きい係数だった行と入れ替える */
    for(i=0;i<4;i++)
    {
        temp_value = a[p][i];
        a[p][i] = a[pivot][i];
        a[pivot][i] = temp_value;/* この中でaの行の値を各列ごとに入れ替える */
    }
}