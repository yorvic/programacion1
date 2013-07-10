/* Ordenamiento Cedula de Personas
 * Ordenamiento Cedula de Hijo
 * Busqueda Binaria Cedula Persona
 * Busqueda Binaria Cedula Hijos
 *  
 */


#include <stdio.h>
#include <string.h>
#define K 100
typedef struct {
	char nombre [K];
	int ci;
}Thijos;
typedef struct {
	int ci;
	int papaCi;
	int mamaCi;
	int kHijos;
	Thijos hijos [K];
}Tpersonas;

typedef Tpersonas Poblacion[K];
void leerArchivo (Poblacion personas,int *nPersonas);
void menu (void);
void ordenarPersonas(Poblacion personas,int nPersonas);
void mostrarPoblacion(Poblacion vector, int nVector);
int main(){
	Poblacion personas;
	int nPersonas;
	
	leerArchivo (personas,&nPersonas);
	mostrarPoblacion(personas,nPersonas);
	ordenarPersonas(personas,nPersonas);
	printf("\n-----------------------------------------------------\n");
	mostrarPoblacion(personas,nPersonas);
	menu();
	return 0;
}

void leerArchivo (Poblacion personas,int *nPersonas){
	FILE *in;
	int i=0,j;
	in=fopen("Personas.txt","r");
	if (in!=NULL){
				
		while(!feof(in)){
			i++;
			fscanf(in,"%d %d %d %d",&personas[i].ci,&personas[i].papaCi,&personas[i].mamaCi,&personas[i].kHijos);
		
			for (j = 1; j <=personas[i].kHijos ; j++){
				fscanf(in,"%s %d",personas[i].hijos[j].nombre,&personas[i].hijos[j].ci);
			}
		};
		*nPersonas=i;
		fclose(in);
	}
};
void ordenarPersonas(Poblacion personas,int nPersonas){
	int i,j,r=0,e;
	Poblacion aux;
	for (i = 1; i <=nPersonas-1 ; i++){
		for (j = 1; j <=nPersonas-1 ; j++){
			if (personas[j].ci>personas[j+1].ci){
				strcpy(aux[r].hijos[e].nombre,"\0");
				r++;
				///Copia en Auxiliar el vector en pos j
				aux[r].ci=personas[j].ci;
				aux[r].mamaCi=personas[j].mamaCi;
				aux[r].papaCi=personas[j].papaCi;
				aux[r].kHijos=personas[j].kHijos;
				for (e = 1; e <=personas[j].kHijos ; e++){
					aux[r].hijos[e].ci=personas[j].hijos[e].ci;
					strcpy(aux[r].hijos[e].nombre,"\0");
					strcpy(aux[r].hijos[e].nombre,personas[r].hijos[e].nombre);
				}
				
				///al vector en j le asigno j+1
				personas[j].ci=personas[j+1].ci;
				personas[j].mamaCi=personas[j+1].mamaCi;
				personas[j].papaCi=personas[j+1].papaCi;
				personas[j].kHijos=personas[j+1].kHijos;
				for (e = 1; e <=personas[j+1].kHijos ; e++){
					personas[j].hijos[e].ci=personas[j+1].hijos[e].ci;
					strcpy(personas[j].hijos[e].nombre,"\0");
					strcpy(personas[j].hijos[e].nombre,personas[j+1].hijos[e].nombre);
					
				}
				///al vector en j+1 le asigno aux
				personas[j+1].ci=aux[r].ci;
				personas[j+1].mamaCi=aux[r].mamaCi;
				personas[j+1].papaCi=aux[r].papaCi;
				personas[j+1].kHijos=aux[r].kHijos;
				for (e = 1; e <=personas[j+1].kHijos ; e++){
					personas[j+1].hijos[e].ci=aux[r].hijos[e].ci;
					strcpy(personas[j+1].hijos[e].nombre,"\0");
					strcpy(personas[j+1].hijos[e].nombre,aux[r].hijos[e].nombre);
				}
			}
		}
	}
	
	
};
void menu (void){
	int op;
	do{
		printf("\n Ordenar \n");
		printf("-----> 1) Cedula Persona\n");
		printf("-----> 2) Cedula Hijo");
		printf("\n Busqueda Binaria \n");
		printf("-----> 3) Cedula Persona\n");
		printf("-----> 4) Cedula Hijo");
		printf("\n\n Opcion ----> ");
		scanf("%d",&op);
	}while(op!=1 && op!=2 && op!=3 && op!=4);
}

void mostrarPoblacion(Poblacion vector, int nVector){
	int i,j;
	
	for (i = 1; i <=nVector ; i++){
		printf("\nC.I: %d - mama: %d - papa: %d - numeroHijos: %d \n",vector[i].ci,vector[i].mamaCi,vector[i].papaCi,vector[i].kHijos);
		
		for (j = 1; j <=vector[i].kHijos ; j++){
			printf("\n hijo #%d : ci: %d - nombre: %s\n",j,vector[i].hijos[j].ci,vector[i].hijos[j].nombre);
		}
		
	}
	
	
}
