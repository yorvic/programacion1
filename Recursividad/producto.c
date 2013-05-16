///Yorvic Godoy

#include <stdio.h>
int producto(int a,int b);
int main(){
	
	int a,b;
	printf("\na: ");
	scanf("%d",&a);
	printf("\nb: ");
	scanf("%d",&b);
	
	printf("\n %dx%d=%d",a,b,producto(a,b));
	return 0;
}
int producto(int a,int b){
	int resul;
		if (b==0){
			resul=0;
		}
		else
			if (b>=1){
				resul=a+producto(a,b-1);
			}
	return resul;
	
}
