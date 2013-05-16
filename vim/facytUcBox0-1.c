#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define VERDADERO 1
#define FALSO 0
typedef int logico;
typedef char TcadenaCorta[20];
///·····································································
typedef struct{
   char nombre [21];
   int tamanio;
   char servidor [41];
   int visibilidad;
}Tficheros;
///·····································································
typedef struct{
   char cedula [12];
   char contrasena [16];
   char correo [41];
   char fechaReg [11];
   int status ;
   int tamanoCasillero;
   Tficheros ficheros[500];
   int cantFichero;
}Tusuario;
///·····································································
void bienv(int *p);
void registrarUser(Tusuario usuarios [],int *nUsuarios);
void leeCI(char CedulaCompleta[]);
void cargarCiEstudiantes(TcadenaCorta[],int *aux);	///Vector de Cedulas de Estudiantes.txt
void cargarUsuarios(Tusuario usuarios[],int *nUsuarios);	///Vector de Usuarios.txt
int validaEstudiante(char[],TcadenaCorta[],int);///Valida que sea Estudiante de Facyt
int validaRegistrado(char[],Tusuario[],int);	///Valida que no este registrado

///·····································································
int main(void){
   int opcion;
   Tusuario usuarios[100];
   int nUsuarios;
   cargarUsuarios(usuarios,&nUsuarios);
   bienv(&opcion);
   if (opcion==1){
      printf("\n Ingresar: ");
   }
   else{
      printf("\nRegistrando\n");
      registrarUser(usuarios,&nUsuarios);

   }
   return 0;
}
///·····································································
void bienv(int *p){
   int op;
   do{
      printf("\n\t\t\tBienvenidos a FacytUcBox \n\n");
      printf("1) Ingresar \n");
      printf("2) Registrarse \n\n");
      printf("Opcion-> ");
      scanf("%d",&op);
      system( "clear" );
      if (op!=1 && op!=2)
         printf("\n\t\t\tOpcion Invalida\n");
   }while(op!=1 && op!=2);
   *p=op;
}
///·····································································
void registrarUser(Tusuario usuarios [],int *nUsuarios){
   char cedula[22]="\0";
   TcadenaCorta vectorCedula[100];	///Vector de Cedulas Estudiantes.txt
   int nCedula=0;///Numero de Cedulas en el vector

   cargarCiEstudiantes(vectorCedula,&nCedula);	///Copiar del archivo al Vector de Cedulas

   if (nCedula==0){ 
      printf("\nNo hay Cedulas en Estudiantes.txt Contacte al Admin\n");
   }
   else{
      leeCI(cedula);
      if (validaEstudiante(cedula,vectorCedula,nCedula)){
         if (!validaRegistrado(cedula,usuarios,*nUsuarios)){

         }
         else
            printf("\n Ya esta Registrado\n");
      }
      else{
         printf("\n NO ES ESTUDIANTE\n");
      }
      printf("Cedula: %s\n ",cedula);///policia

   }

}
///·····································································
void leeCI(char CedulaCompleta[]){
   char cedula[100]="\0";	///longitud 100 porque si la cedula es invalida(mayor a 9) se desborda
   char nacionalidad[3]="\0";	
   int r;
   do{
      //system("clear");
      printf("\n Datos de Identificacion \n");
      printf("\n 1- Venezolan@");
      printf("\n 2- Extrangero\n");
      printf("\n Opcion----> ");
      scanf("%d",&r);

   } while (r!=1 && r!=2);

   do{
      printf("\nCedula de Identidad (solo numeros);");
      scanf("%s",cedula);
   } while (strlen(cedula)>9);

   if (r==1)
      strcpy(nacionalidad,"V-");
   else
      strcpy(nacionalidad,"E-");

   strcat(CedulaCompleta,nacionalidad);
   strcat(CedulaCompleta,cedula);
}// FIN LEECI
///·····································································
void cargarCiEstudiantes(TcadenaCorta Vcedula[],int *aux){
   FILE *estudiantes;
   int i=0;
   char ci[14];
   estudiantes=fopen("estudiantes.txt","r");
   if (estudiantes!=NULL){
      while (!feof(estudiantes)){
         fscanf(estudiantes,"%s",ci);
         if ((ci[0]=='V' || ci[0]=='E')&&ci[1]=='-'){
            i++;
            strcpy(Vcedula[i],ci);
         }
      }
      fclose(estudiantes);
      *aux=i;
      printf("\nAux: %d",*aux);
   }
   else
      printf("\nError Estudiantes.txt Contacte al Admin");

   ///Probando
   ///policia
   for (i = 1; i <=*aux ; i++){
      printf("\n%s",Vcedula[i]);
   }

}
///·····································································
void cargarUsuarios(Tusuario usuarios[],int *nUsuarios){
   FILE *ArchUsuario;	
   int i=0;
   ArchUsuario=fopen("usuarios.txt","r");
   if (ArchUsuario!=NULL){

      while (!feof(ArchUsuario)){
         i++;
         fscanf(ArchUsuario,"%s",usuarios[i].correo);
         fscanf(ArchUsuario,"%s",usuarios[i].contrasena);
         fscanf(ArchUsuario,"%s",usuarios[i].cedula);
         fscanf(ArchUsuario,"%d",&usuarios[i].tamanoCasillero);
         fscanf(ArchUsuario,"%s",usuarios[i].fechaReg);
         fscanf(ArchUsuario,"%d",&usuarios[i].status);
      }

      *nUsuarios=i-1;																///Pendiente
      for (i = 1; i <=*nUsuarios ; i++){
         printf("%s\n",usuarios[i].correo);
         printf("%s\n",usuarios[i].contrasena);
         printf("%s\n",usuarios[i].cedula);
         printf("%d\n",usuarios[i].tamanoCasillero);
         printf("%s\n",usuarios[i].fechaReg);
         printf("%d\n",usuarios[i].status);
      }
      printf("\nNUSUARIO %d",*nUsuarios);			

   }

   else{
      printf("\nError Archivo usuarios.txt Contacte al Admin");
   }

}
///·····································································
int validaEstudiante(char cedula[],TcadenaCorta vectorCedula[],int nCedula){
   int esEstudiante=FALSO;
   int i=0;
   while((i<=nCedula) && (!esEstudiante)){
      i++;
      if (strcmp(vectorCedula[i],cedula)==0){
         esEstudiante=VERDADERO;
      }
   }
   return esEstudiante;
}

///·····································································
int validaRegistrado(char cedula[],Tusuario usuarios[],int nUsuarios){
   int registrado=0;
   int i=0;
   while((i<=nUsuarios) && (!registrado)){
      i++;
      if (strcmp(usuarios[i].cedula,cedula)==0){
         registrado=1;
      }
   }
   return registrado;
}
