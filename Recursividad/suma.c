#include <stdio.h>
int suma(int a,int b);
int main(){
	int a,b;
	printf("\na: ");
	scanf("%d",&a);
	printf("\nb: ");
	scanf("%d",&b);
	
	printf("\n %d+%d=%d",a,b,suma(a,b));
	return 0;
}

int suma(int a,int b){
	int resul;
	
	if (b==0){
		resul=a;
	}
	else
		if (b>0){
			resul=1+suma(a,b-1);
		}
		else
			resul=suma(a,b+1)-1;
	return resul;
			
}
