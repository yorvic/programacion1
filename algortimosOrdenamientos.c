/* Yorvic Godoy
Descripcion:lab 03  */
/*========================<Bibliotecas>=========================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/*========================< Constantes >========================*/
 
/*========================< Declaraciones de Tipos >========================*/
 
/*========================< Prototipos >========================*/
void leeOrdenaExporta (); 
void mostrarVector (int v[],int m,int k);
void exportarVector (int v[],int m,int k);
void ordenamientoBurbuja (int a[],int m);
void shellSort (int a[],int n);
void ordenamientoIntercambio (int a[],int n);
void ordenamientoSeleccion (int a[],int n);
void ordenamientoInsercion (int a[],int n);
void vaciarArchivo ();
void menuOrdenamiento (int k,int v[],int m);
void id2Cadena (int k,char cadena[]);
/*========================<Funcion Main>========================*/
int main(){
	vaciarArchivo ();
	leeOrdenaExporta();
	return 0;
}

/*========================<Limpiar archivo de Salida>========================*/
void vaciarArchivo (){
	FILE *out;
	out=fopen("orden.out","w");
	fclose(out);
}
/*========================<menu de Ordenacion>========================*/
void menuOrdenamiento (int k,int v[],int m){
	switch (k){

		case 1 :
			ordenamientoIntercambio (v,m);
			exportarVector(v,m,k);
			break;
		case 2 :
			ordenamientoSeleccion(v,m);
			exportarVector(v,m,k);
			break;
		case 3 :
			ordenamientoInsercion(v,m);
			exportarVector(v,m,k);
			break;
		case 4 :
			ordenamientoBurbuja(v,m);
			exportarVector(v,m,k);
			break;
		case 5 :
			shellSort(v,m);
			exportarVector(v,m,k);
			break;
		default :
			break;
	}
}
/*========================<leer Ordena Exporta Vector>========================*/
void leeOrdenaExporta (){
	int i,n,v[30],m,k,j;
	FILE *in;

	in=fopen("orden.in","r");
	if( in!=NULL ){
		fscanf(in,"%d",&n);
		for( j=1 ; j<=n ; j++ ){
			fscanf(in,"%d",&m);
			for( i=0 ; i<m ; i++ ){
				fscanf(in,"%d",&v[i]);
			}
			fscanf(in,"%d",&k);
			menuOrdenamiento(k,v,m);
		}
		fclose(in);
	}
	else{
		printf("Error Archivo\n");
	}
}

/*========================<Ordenamiento por Metodo de la Burbuja>========================*/
void ordenamientoBurbuja (int a[],int m){
	int bandera,pasada,j,aux;

	pasada=0;
	bandera=1;
	while(pasada<m-1 && bandera){
		bandera=0;
		for( j=0 ; j<m-pasada-1 ; j++ ){
			if( a[j]>a[j+1] ){
				// Elementos desordenado, es necesario intercambiar
				bandera=1;
				aux=a[j];
				a[j]=a[j+1];
				a[j+1]=aux;
			}
		}
		pasada++;
	}
}
/*========================<Mostrar Vector>========================*/
void mostrarVector (int v[],int m,int k){
	int i;
	printf("\n");
	printf("m: %d",m);
	printf("\n");
	printf("k: %d",k);

	for( i=0 ; i<m ; i++ ){
		printf("v[%d]=%d ",i,v[i]);
	}
	printf("\n");

}

/*========================<Escribir en Archivo el Vector>========================*/
void exportarVector (int v[],int m,int k){
	int i;
	char metodo[60];
	FILE *out;
	out=fopen("orden.out","a");
	
	if( out!=NULL ){
		id2Cadena(k,metodo);
		fprintf(out,"\n Por el metodo \"%s\"\n",metodo);
		for( i=0 ; i<m ; i++ ){
			fprintf(out,"%d ",v[i]);
		}
		fprintf(out,"\n");
		fclose(out);
	}
	else{
		printf("Error Archivo\n");	
	}
}

/*========================<ShellSort>========================*/
void shellSort (int a[],int n){
	int i,j,k,intervalo;
	int temp;
	intervalo=n/2;
	while(intervalo>0){
		for( i=intervalo ; i<n ; i++ ){
			j=i-intervalo;
			while(j>=0){
				k=j+intervalo;
				if( a[j]<=a[k] ){
					j=-1;
				}
				else{
					temp=a[j];
					a[j]=a[k];
					a[k]=temp;
					j-=intervalo;	
				}
			}
		}
		intervalo=intervalo/2;
	}
}

/*========================<Ordenamiento por Intercambio>========================*/
void ordenamientoIntercambio (int a[],int n){
	int i,aux,j;
	for( i=0 ; i<=n-2 ; i++ ){
		for( j=i+1 ; j<=n-1 ; j++ ){
			if( a[i]>a[j] ){
				aux=a[i];
				a[i]=a[j];
				a[j]=aux;
			}
		}
		
	}
	
}

/*========================<Ordenamiento por Seleccion>========================*/
void ordenamientoSeleccion (int a[],int n){
	int indiceMenor,i,j,aux;
	for( i=0 ; i<=n-2 ; i++ ){
		indiceMenor=i;
		for( j=i+1 ; j<=n-1 ; j++ ){
			if( a[j]<a[indiceMenor] ){
				indiceMenor=j;
			}
		}
		if( i!=indiceMenor ){
			aux=a[i];
			a[i]=a[indiceMenor];
			a[indiceMenor]=aux;
		}
	}
}

void ordenamientoInsercion (int a[],int n){
	int i,j,aux;
	for( i=1 ; i<n ; i++ ){
		j=i;
		aux=a[i];
		while(j>0 && aux<a[j-1]){
			a[j]=a[j-1];
			j=j-1;
		}
		a[j]=aux;
	}
}

/*========================<Recibe el tipo el tipo de ordenamiento y devuelve la cadena con el nombre>========================*/
void id2Cadena (int k,char cadena[]){
	switch (k){
		
		case 1 :
			strcpy(cadena,"Intercambio");
			break;
		case 2:
			strcpy(cadena,"Seleccion");
			break;
		case 3 :
			strcpy(cadena,"Insercion");
			break;
		case 4 :
			strcpy(cadena,"Burbuja");
			break;
		case 5 :
			strcpy(cadena,"Shell Sort");
			break;
		default :
			strcpy(cadena,"Desconocido");
			break;
	}
}
