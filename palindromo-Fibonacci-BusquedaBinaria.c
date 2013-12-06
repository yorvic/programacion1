#include <stdio.h>
#include <string.h>
#define MAX 100
/*========================<subProgramas>========================*/
int busquedaBinaria(int v[],int dato,int inf,int sup);
void leerVector(int v[],int *n);
int fibo(int n);
int palindromo (char palabra[MAX],int inf,int sup);
/*========================<Main>========================*/
int main(){
	char resp,palabra[MAX];
	int dato,n,pos,sup;
	int v [MAX];
	printf("\n lab00\n");
	printf("1- Busqueda Binaria\n");
	printf("2- Fibonacci\n");
	printf("3- palindromo\n");
	scanf("%c",&resp);
	switch (resp){
		case '1':
			printf("\n dato: ");
			scanf("%d",&dato);
			leerVector(v,&n);
			pos=busquedaBinaria(v,dato,0,n);
			if (pos==-1)
				printf("\n No encontrado");
			else
				printf("\n Encontrado el la posicion %d",pos);
			break;
		case '2':
			printf("\n dato: ");
			scanf("%d",&dato);
			printf("\n Fibonacci (%d)=%d",dato,fibo(dato));
			break;
		case '3':
			printf("\n palabra: ");
			scanf("%s",palabra);
			sup=strlen(palabra);
			if (palindromo(palabra,0,sup-1))
				printf("\n %s es PALINDROMO \n",palabra);
			else
				printf("\n %s NO es PALINDROMO \n",palabra);
			break;
		default:
			printf("Valor Invalido");
	}
	return 0;
}
/*========================<palindromo>========================*/
int palindromo (char palabra[],int inf,int sup){
	int resp=1,centro;
	centro=(inf+sup)/2;
	if (centro!=sup){
		if (palabra[inf]==palabra[sup]){
			resp=palindromo(palabra,inf+1,sup-1);
		}
		else
			resp=0;
	}
return resp;	
}
int fibo(int n){
	int resul;
	if (n==0)
		resul=0;
	else
		if (n==1)
			resul=1;
		else
			resul=fibo(n-1)+fibo(n-2);
	return resul;
}
int busquedaBinaria(int v[],int dato,int inf,int sup) {
	int centro,resp;
	if (inf<=sup){
		centro=(inf+sup)/2;
		if (dato==v[centro]){
			resp=centro;
		}
		else{
			if (dato<v[centro])
				resp=busquedaBinaria(v,dato,inf,centro-1);
			else
				resp=busquedaBinaria(v,dato,centro+1,sup);
		}
	}
	else
		resp=-1;
	return resp;
};
void leerVector(int v[],int *n){
	int i=0;
	FILE *in;
	in=fopen("vector.in","r");
	if (in!=NULL){
		while (!feof(in)){
			fscanf(in,"%d",&v[i]);
			i++;
		}
	*n=i-2;
	}
}
