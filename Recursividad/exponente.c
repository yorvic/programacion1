#include <stdio.h>
int expo(int x,int n);
int main(){
	int x,n;
	printf("\n base: ");
	scanf("%d",&x);
	printf("\n exponente: ");
	scanf("%d",&n);
	
	printf("\n resultado de %d elevado a la %d es igual a %d ",x,n,expo(x,n));
	return 0;
}

int expo(int x,int n){
	int resul;
	
	if (n==0){
		resul=1;
	}
	else
		resul=x*expo(x,n-1);
		
	return resul;
}
