#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define e 0.00005
#define BUF_SIZE 100

void pivot(double **a,double **c,int where,int n){
	int fabs_max=where;
	double num;

	//絶対値が一番大きいいところを探す
	for(int i=where;i<n;i++){
		if(fabs(a[i][where])>fabs(a[fabs_max][where])){
			fabs_max=i;
		}
	}

	if(where==fabs_max){//行列のランクが落ちた
		printf("行列式は存在しません");
		exit(0);
	}

	//whereの行とfabs_maxの行を入れ替え
	for(int i=0;i<n;i++){
		num=a[where][i];
		a[where][i]=a[fabs_max][i];
		a[fabs_max][i]=num;

		num=c[where][i];
		c[where][i]=c[fabs_max][i];
		c[fabs_max][i]=num;
	}

}

int main (void){
		system("chcp 65001");
	int i,j,k;
	double num;
	double **a;
	double b[4][4];
	double **c;

	FILE *fp;
	char buf[BUF_SIZE];
	int line = 0;
	char FILE_NAME[]="ginverse.txt";
	char FILE_NAME_DEBUG[]="test.txt";
	char ck[]="";
	char cd[]="K";

	if((fp=fopen(FILE_NAME,"r"))==NULL){
		printf("%sを開けませんでした",FILE_NAME);
		return 1;
	}

	while (fgets(buf, BUF_SIZE, fp) != NULL) {
		line++;
	}

	printf("現在のファイルの行数は「%d」です。\n",line);
	//ファイルポインタを先頭まで戻す
	
	rewind(fp);



	a=(double **)malloc(sizeof(double * )*line);
	for(i=0;i<line;i++)
	  a[i]=(double *)malloc(sizeof(double)*line);

	c=(double **)malloc(sizeof(double * )*line);
	for(i=0;i<line;i++)
	  c[i]=(double *)malloc(sizeof(double)*line);

	

	for(int i=0;i<line;i++){
		for(int j=0;j<line;j++){
			fscanf(fp,"%s",ck);
			if(strcmp(ck,cd)==0){
				printf("k?=");
				scanf("%lf",&a[i][j]);
				b[i][j]=a[i][j];
			}else{
				
			a[i][j]=atof(ck);	
			b[i][j]=a[i][j];
			}
		}
	}

	

	for(int i=0;i<line;i++)
		for(int j=0;j<line;j++){
			if(i==j){
				c[i][j]=1.0;
			}else{
				c[i][j]=0;
			}
		}
	


	for(k=0;k<line;k++){
		//pivot
		if(fabs(a[k][k])<=e){
			pivot(a,c,k,line);
		}
		num=a[k][k];
		for(j=0;j<line;j++){
			if(j>=k){
			a[k][j]=a[k][j]/num;
			}
			c[k][j]=c[k][j]/num;
		}

		for(i=0;i<line;i++){
			num=a[i][k];
			if(i!=k){
				for(j=0;j<line;j++){
					if(j>=k)
						a[i][j]=a[i][j]-a[k][j]*num;
					c[i][j]=c[i][j]-c[k][j]*num;
				}
			}
		}
	}

printf("A^-1=\n");
	for(i=0;i<line;i++){
		for(j=0;j<line;j++)
			printf("%f ",c[i][j]);
		printf("\n");
	}


	printf("\n");
	printf("A=\n");
		for(i=0;i<line;i++){
		for(j=0;j<line;j++)
			printf("%f ",b[i][j]);
		printf("\n");
	}

	printf("\n");
	printf("A*A^-1=\n");
	for(i=0;i<line;i++){
		for(j=0;j<line;j++){
			num=0;
			for(k=0;k<line;k++){
				num+=b[i][k]*c[k][j];
			}
			printf("%f ",num);
		}
		printf("\n");
	}
	

	return 0;
	}