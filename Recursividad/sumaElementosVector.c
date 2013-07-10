///Yorvic Godoy
#include <stdio.h>
#define N 100
typedef int vector[N];
int sumaVector(vector v,int n);
int main(){
	vector v;
	int n,i;
	printf("\n n: ");
	scanf("%d",&n);
	printf("\nAsignando valores al Vector");
	for (i = 0; i <n ; i++){
		printf("\n v[%d]= ",i);
		scanf("%d",&v[i]);
	}
	printf("\n");
	for (i = 0; i <n ; i++){
		printf("v[%d]=%d   ",i,v[i]);
	}
	printf("\n la suma de los elementos del vector es %d",sumaVector(v,n));
	return 0;
}

int sumaVector(vector v,int n){
	int resul;
	
	if (n==0){
		resul=0;
	}
	else
		resul=v[n]+sumaVector(v,n-1);

	
	return resul;
	
};
