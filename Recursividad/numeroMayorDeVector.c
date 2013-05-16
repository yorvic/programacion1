///Yorvic Godoy

#include <stdio.h>
#define N 100
typedef int vector[N];
void leerVector(vector v,int *n);
int elementoMayorDelVector(vector v, int n);
int main(){
	int n;
	vector v;
	leerVector(v,&n);
	
	printf("\n \n\nel mayor es %d",elementoMayorDelVector(v,n));
	return 0;
}
int elementoMayorDelVector(vector v, int n){
	int aux,resul;
	if (n==0){
		resul=v[0];
	}
	else{
		aux=elementoMayorDelVector(v,n-1);
		if (v[n]>aux){
			resul=v[n];
		}
		else
			resul=aux;
	}
	return resul;
	
}

void leerVector(vector v,int *n){
	int i;
	printf("\n n: ");
	scanf("%d",n);
	printf("\nAsignando valores al Vector");
	for (i = 0; i <*n ; i++){
		printf("\n v[%d]= ",i);
		scanf("%d",&v[i]);
	}
	printf("\n Mostrando el Vector para Comprobar los elementos ingresados");
	for (i = 0; i <*n ; i++){
		printf("v[%d]=%d   ",i,v[i]);
	}
	
}
