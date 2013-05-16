#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define VERDADERO 1
#define FALSO 0
# define MAX_CLAVE 16
# define MAX_USUARIOS 200
typedef int logico;
typedef char TcadenaCorta[20];
///·····································································
typedef struct{
	char nombre [21];
	double tamanio;
	char servidor [30];
	char visibilidad[10];
}Tficheros;
///·····································································
typedef struct{
	char nombre [46];
}Tservidor;
///·····································································
typedef struct{
	char cedula [12];
	char contrasena [16];
	char correo [41];
	char fechaReg [11];
	int status ;
	float tamanoCasillero;
	Tficheros ficheros[500];
	int cantFichero;
}Tusuario;
///·····································································
void bienv(char *p);
void registrarUser(Tusuario usuarios [],int *nUsuarios);
void leeCI(char CedulaCompleta[]);
void cargarCiEstudiantes(TcadenaCorta[],int *aux);	///Vector de Cedulas de Estudiantes.txt
void cargarUsuarios(Tusuario usuarios[],int *nUsuarios);	///Vector de Usuarios.txt
int validaEstudiante(char[],TcadenaCorta[],int);///Valida que sea Estudiante de Facyt
int validaCedulaRegistrada(char[],Tusuario[],int);	///Valida que no este registrado
void validaCI(Tusuario usuarios [],int *nUsuarios,char cedula[]);		///Validacion Completa de la cedula (Registrado,Estudiante,longitud,etc)
void leeCorreo(char correo[]);	///correo debe tener arroba punto y max 40 caracteres
int validaCorreoRegistrado(char[],Tusuario[],int);	///Valida que no este registrado
void validaCorreo(Tusuario usuarios [],int *nUsuarios,char correo[]);
void obtener_clave(char pass[],int modo);	///obtiene la clave y muestra *** ///modo: Admin o Usuario
void fechaA(char fecha []);		///Fech actual al registrarse directo del Sistema
void invitacionUsuario(Tusuario usuarios[],int *nUsuarios,char cedula[],char fecha[]);	///Pregunta al usuario y ha sido referido y se encargar de verificar y guardarlo en bonos.txt
int buscarUsuario(Tusuario usuarios[],int *nUsuarios,char cedula[]);///Retorna la posicion en el vector de el usuario
void actualizarArchivoUsuarios(Tusuario usuarios[],int nUsuarios);	///Actualizar Archivo Usuarios despues de Registrar uno Nuevo
void iniciaSeccion(Tusuario usuarios[],int nUsuarios);	///Inicia Seccion e Identifica si es Usuario o Administrador
void panelUsuario(Tusuario usuarios[],int nUsuarios,int ID_usuario,Tservidor servidores[],int nServidor);///Panel Principal de Usuario
void	menuUsuario(char *op);///Menu de Usuario (Subir Archivo, Mostrar Archivos)
void tamano2Byte(double *tamanio);	///Convertidor a Bytes
void cargarVectorServidores(Tservidor[],int *nServidor);
void leeValidaAgregaFicheros(Tusuario usuarios[],int nUsuarios,int ID_usuario,Tservidor servidores[],int nServidor);
void mostrarArchivosUsuario(Tusuario usuarios[],int nUsuarios,int ID_usuario);
void visibilidadArchivo(char visibilidad[]);
void actualizarArchivoFicheros(Tusuario usuarios[],int nUsuarios);
void agregarServidor();
void bonosReporte();
void cargarVectorFichero(Tusuario usuarios [],int nUsuarios);
void panelAdmin(Tusuario usuarios[],int *nUsuarios,Tservidor servidores[],int *nServidor);
void menuAdmin(char *opcion);
void reporteUsuarios(Tusuario[],int);
void eliminarUsuario(Tusuario usuarios[],int nUsuario);
void cambiarContrasenha(Tusuario usuarios[],int nUsuarios,int ID_usuario);
void reporteBonos(Tusuario usuarios[],int nUsuarios);
int tieneExtension(char[]);
///·····································································
int main(void){;
	char opcion;
	Tusuario usuarios[MAX_USUARIOS];
	int nUsuarios;
	do{
		system("clear");
		cargarUsuarios(usuarios,&nUsuarios);//Cargar el vector 'ususarios' con usuarios.txt
		cargarVectorFichero(usuarios,nUsuarios);//Carga Los Archivos de los usuarios de ficheros.txt
		system("clear");
		bienv(&opcion);
		if (opcion=='1'){		//Ingresar al sistema
			iniciaSeccion(usuarios,nUsuarios);	//inicia sesion
			actualizarArchivoUsuarios(usuarios,nUsuarios);	//actualiza los archivos que fueron modificados
			actualizarArchivoFicheros(usuarios,nUsuarios);
		}
		///Proceso de Registro
		else{
			if (nUsuarios<MAX_USUARIOS){///MAX_USUARIOS ES 200
				printf("","REGISTRANDO");
				registrarUser(usuarios,&nUsuarios);	//procedimiento se encarga de validar y guardar los datos en el vector usuarios[]
				actualizarArchivoUsuarios(usuarios,nUsuarios);
				printf("");
			}
			else
				printf("");
		}
	} while (1);//Siempre el programa se va a repetir
	return 0;
}
///·····································································
void bienv(char *p){
	char op;
	do{
		printf("\n\n\t\t\tBienvenidos a FacytUcBox \n\n");
		printf("1) Ingresar \n");
		printf("2) Registrarse \n\n");
		printf("Opcion-> ");
		scanf("%c",&op);
		while(getchar()!='\n');
	}while(op!='1' && op!='2');
	*p=op;	
}
///·····································································
void registrarUser(Tusuario usuarios [],int *nUsuarios){//Registrando al nuevo usuario
	char cedula[13]="\0";
	char correo[41]="\0";
	char contrasena[16]="\0";
	char fecha[11]="\0";
	int i;
	*nUsuarios+=1;		//al vector le sumamos una posicion
	i=*nUsuarios;
	validaCI(usuarios,&*nUsuarios,cedula);	//validar cedula
	validaCorreo(usuarios,&*nUsuarios,correo);
	obtener_clave(contrasena,0);
	fechaA(fecha);
	strcpy(usuarios[i].cedula,cedula);
	strcpy(usuarios[i].correo,correo);
	strcpy(usuarios[i].contrasena,contrasena);
	strcpy(usuarios[i].fechaReg,fecha);
	usuarios[i].status=1;
	usuarios[i].tamanoCasillero=100;
	usuarios[i].cantFichero=0;
	invitacionUsuario(usuarios,&*nUsuarios,cedula,fecha);
}
///·····································································
void leeCI(char CedulaCompleta[]){
	char cedula[100]="\0";	///longitud 100 porque si la cedula es invalida(mayor a 9) se desborda
	char nacionalidad[3]="\0";	
	int r;
	do{
		printf("\n Datos de Identificacion \n");
		printf("\n 1- Venezolan@");
		printf("\n 2- Extranjero\n");
		printf("\n Opcion----> ");
		scanf("%d",&r);
		while(getchar()!='\n');
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
	}
	else
		printf("\nError Estudiantes.txt Contacte al Admin");
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
			fscanf(ArchUsuario,"%f",&usuarios[i].tamanoCasillero);
			fscanf(ArchUsuario,"%s",usuarios[i].fechaReg);
			fscanf(ArchUsuario,"%d",&usuarios[i].status);
			fscanf(ArchUsuario,"\n");
		}
		*nUsuarios=i;	
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
int validaCedulaRegistrada(char cedula[],Tusuario usuarios[],int nUsuarios){
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
///·····································································
void validaCI(Tusuario usuarios[],int *nUsuarios,char cedula[]){
	logico bandera=FALSO;
	TcadenaCorta vectorCedula[100];	///Vector de Cedulas Estudiantes.txt
	int nCedula=0;///Numero de Cedulas en el vector
	cargarCiEstudiantes(vectorCedula,&nCedula);	///Copiar del archivo al Vector de Cedulas
	if (nCedula==0){ 
		printf("\nNo hay Cedulas en Estudiantes.txt Contacte al Admin\n");
	}
	else{
		do{
			strcpy(cedula,"\0");	///IMPORTANTEEE ("limpiar la cadena por que al volver a leer queda guardada la informacion anterior ")
			leeCI(cedula);//Leer cedula con nacionalizacion y la devuelve en una cadena
			if (validaEstudiante(cedula,vectorCedula,nCedula)){//valida que sea estudiante de facyt
				if (!validaCedulaRegistrada(cedula,usuarios,*nUsuarios)){//Si no esta registrada entoces se puede registrar
					bandera=VERDADERO;																	//cumple con que es estudiante y no esta registrado
				}
				else
					printf("\n Ya estas Registrado\n");
			}
			else{
				printf("\n NO ES ESTUDIANTE\n");
			}
		}while(!bandera);//Se repite hasta que ingrese una cedula valida
	}
}

///·····································································
///Lee  el correo no debe exceder 40 caracteres y debe tener '.' y '@'
void leeCorreo(char correo[]){
	int i,verifArroba=0,verifPt=0;
	do{
		do{
			printf("\n\nCorreo: ");
			scanf("%s",correo);
			if (strlen(correo)>40)
				printf("\n El correo no debe exceder los 40 caracteres");
		}while(strlen(correo)>40);
		for (i = 0; i <=strlen(correo) ; i++){//verifica que tenga un arroba
			if (correo[i]=='@'){
				verifArroba=1;
			}
			else
			if (correo[i]=='.'){//verifica que tenga un punto '.'
				verifPt=1;
			}
		}
		if (!(verifArroba && verifPt)){//si no cumple con los dos no es valido 
			printf("\n El Correo debe tener este formato 'ejemplo@facyt.com' \n");
		}
	}while(!(verifArroba && verifPt));//vuelve  leer el correo
}// FIN LeeValidaCorreo

///·····································································
int validaCorreoRegistrado(char correo[],Tusuario usuarios[],int nUsuarios){//retorna si el correo est registrado y en que posicion
	int registrado=0;
	int i=0;
	while((i<=nUsuarios) && (!registrado)){
		i++;
		if (strcmp(usuarios[i].correo,correo)==0){
			registrado=i;
		}
	}
	return registrado;
}
///····································································
void validaCorreo(Tusuario usuarios [],int *nUsuarios,char correo[]){//Valida que cumpla
	int bandera=0;																										//con que el correo tiene pts y arroba
	do{																																//y que no este registrado
		leeCorreo(correo);
		if (!validaCorreoRegistrado(correo,usuarios,*nUsuarios)){
			bandera=1;		//cumple con los dos entonces es un correo valido
		}
		else
			printf("\n Correo Registrado intente nuevamente");
	} while (!bandera);
}
///····································································
void obtener_clave(char pass[],int modo){
	int maxClave=16;///Modo Usuario longitud maxima de la cadena = 15
	if (modo==1){///Modo Admin longitud maxima de la cadena = 30
		maxClave=31;
	}
	int verifM=0,verifS=0,verifN=0;
	do{
		printf("\n Contrasena: ");
		char caracter;{
		int i = 0;
		do {
			system("stty cbreak -echo"); /* deshabilita la salida por teclado */
			fflush(stdout);
			caracter = getchar(); /* espera por un caracter */
			system("stty cooked echo"); /* habilita la salida por teclado */
			if( caracter == '\n' ) /* validando el final de la clave */
				break;
			else
				if (((caracter >= 'A') && (caracter <= 'Z')) || (caracter=='_') || (caracter=='@') || (caracter=='#')|| ((caracter >= 'a') && (caracter <= 'z')) || ((caracter >= '0') && (caracter <= '9' ))) /* Define una restriccion para la clave*/{
					putchar('*'); /* Muestra un caracter por caracter ingresado por el usuario */
					pass[i] = caracter; /* Añade el caracter a la clave */
					i++; /* incremento del indice de la clave */
				}
		} while ( i < maxClave - 1 );
		pass[i] = '\0';
		putchar('\n');
				for (i = 0; i <=strlen(pass) ; i++){
				if (pass[i]=='@' ||pass[i]=='$'||pass[i]=='_'||pass[i]=='#'){
					verifS=1;
				}
					else{
						if ((pass[i]>='A') && (pass[i]<='Z')){
							verifM=1;
						}
						else
							if (pass[i]>='0' && pass[i]<='9'){
								verifN=1;
							}
					}
			}
				if (!(verifM && verifN && verifS))
					printf("\n Recuerde que la Contrasenha debe cumplir con: \n*Al menos una letra Mayuscula.\n*Al menos un Caracter Especial( @ $ _ # ).\n*Al menos un numero entero.\n");
				}
	}while(!(verifM && verifN && verifS));
}
///····································································
///Fecha Al momento de Registrarse
void fechaA(char fecha []){
	time_t tiempo;
  char cad[80];
  struct tm *tmPtr;
  tiempo = time(NULL);
  tmPtr = localtime(&tiempo);
  strftime( cad, 80, "%d-%m-20%y", tmPtr );
  strcpy(fecha,cad);
}//FIN fecha Actual
///····································································
void invitacionUsuario(Tusuario usuarios[],int *nUsuarios,char cedula[],char fecha[]){
	FILE *bonos;
	char resp='\0';
	char cedulaAmigo[13]="\0";
	int i;
	
	bonos=fopen("bonos.txt","a");
	if (bonos!=NULL){
		do{
		printf("\n\t\t ¿Ha sido invitado por un Estudiante?\n");
		printf("1) Si\n");
		printf("2) No\n");
		scanf("%c",&resp);
		while(getchar()!='\n');
		}while (resp!='1' && resp!='2');
		if (resp=='1'){
			printf("\n\n\tINFORMACION DEL ESTUDIANTE QUE TE INVITO \n");
			leeCI(cedulaAmigo);															//obtenemos la ci con nacionalida en una cadena
			if (validaCedulaRegistrada(cedulaAmigo,usuarios,*nUsuarios)){//debe estar registrada para poder aumentarle el espacio
				i=buscarUsuario(usuarios,&*nUsuarios,cedulaAmigo);//funcion busca usuario por la cedula y retorna la posicion en el vector usuarios[]
				if (usuarios[i].tamanoCasillero<=780){//el tamaño de casillero maximo es 800gb
					usuarios[i].tamanoCasillero+=20;//le incrementa 20gb
					fprintf(bonos,"\n%s\t%s\t%s",cedula,cedulaAmigo,fecha);//guarda en archivo bonos.txt la cedula del nuevo
				}																											//cedula de el que lo refirio y la fecha actual
				fclose(bonos);
			}
			else{
				printf("\n Tu Amigo no esta Registrado.\n");
			}
		}
	}
}
///····································································
int buscarUsuario(Tusuario usuarios[],int *nUsuarios,char cedula[]){//retorna la posicio9n en el vector donde consigue la cedula
	int pos=0;
	int i=1;
	while (i<=*nUsuarios && pos==0){
		if (strcmp(usuarios[i].cedula,cedula)==0){
			pos=i;
		}
		i++;
	}
	return pos;
}
///····································································
void actualizarArchivoUsuarios(Tusuario usuarios[],int nUsuarios){//actualiza archivo usuarios.txt con el nuevo usuario 
	FILE *ArchUsuarios;																						
	int i;
	char viejo[18] = "usuarios.txt";
	char nuevo[18] = "usuarios.bank";
	rename(viejo, nuevo);/* Copia de Seguridad de Usuarios.txt*/
	ArchUsuarios=fopen("usuarios.txt","w");	
	for (i = 1; i <=nUsuarios ; i++){
		fprintf(ArchUsuarios,"\n%s",usuarios[i].correo);
		fprintf(ArchUsuarios,"\n%s",usuarios[i].contrasena);
		fprintf(ArchUsuarios,"\n%s",usuarios[i].cedula);
		fprintf(ArchUsuarios,"\n%.2f",usuarios[i].tamanoCasillero);
		fprintf(ArchUsuarios,"\n%s",usuarios[i].fechaReg);
		fprintf(ArchUsuarios,"\n%d",usuarios[i].status);
		fprintf(ArchUsuarios,"\n");
	}
	fclose(ArchUsuarios);
}
///····································································
void iniciaSeccion(Tusuario usuarios[],int nUsuarios){//inicia seccion verifica si es usuario o administrador
	Tservidor servidores[100];
	int nServidor;
	char correo[42]="\0";
	char contrasena[16]="\0";
	int i=0;
	
	printf("\n\n\t\t\tFacytUCBox");
	printf("\n\n\t\t\tAREA DE INGRESO\n");
	leeCorreo(correo);												//leer correo con las limitaciones validaciones
	i=validaCorreoRegistrado(correo,usuarios,nUsuarios);	//valida que este registrado y retorna la posicion en el vector usuarios[]
	cargarVectorServidores(servidores,&nServidor);				//Carga los serivores
	if (i){	//si esta registrado es un usuario normal
		if(usuarios[i].status==1){//valida que este activos
			scanf("%*c");
			obtener_clave(contrasena,0);	//obtiene la clave y la retorna en una  cadena 
			if (strcmp(usuarios[i].contrasena,contrasena)==0){		//verifica que la clave sea igual a la de el usuario en la posicion donde consiguio el correo
				panelUsuario(usuarios,nUsuarios,i,servidores,nServidor);//Panel de Usuario donde muestra un menu con todas las opciones disponibles
			}
		}
		else
			printf("\n El usuario ha sido eliminado");
	}
	else{//si no lo consiguio en el vector prueba si es el administrador	
		if ((strcmp("admin@facytucbox.uc.edu.ve",correo)==0)){//si es el correo de el admin
			scanf("%*c");
			obtener_clave(contrasena,1);////obtenemos la clave de el admin en modo=1 permite introducir una clave mas larga que a los usuarios comunes
			if ((strcmp("Admin@_facyt2013",contrasena)==0)){	//verifica si la clave es igual a la de el admin
				panelAdmin(usuarios,&nUsuarios,servidores,&nServidor);//Panel de el Administrador con Todas las Opciones
				getchar();
			}
		}
	}
}

///····································································
void panelUsuario(Tusuario usuarios[],int nUsuarios,int ID_usuario,Tservidor servidores[],int nServidor){
	char op;
	char resp;
	
	do{
		system("clear");
		printf("\n\n\n\t\t\t\tCasillero Digital FacytUCBox\n");
		printf("\t\t\t\tTus Archivos\n");
		mostrarArchivosUsuario(usuarios,nUsuarios,ID_usuario);	//Al ingresar muestra los archivos de el usuario
		scanf("%*c");
		menuUsuario(&op);		//luego un menu con opciones de subir archivo y cambiar contraseña
		if (op=='1'){//1=subir archivo
			do{
				leeValidaAgregaFicheros(usuarios,nUsuarios,ID_usuario,servidores,nServidor); //lee valida agrega el archivo a ficheros.txt
				printf("\n¿Desea agregar otro archivo?(s/n)");
				scanf("%c",&resp);
				while(getchar()!='\n');
			}while(resp=='s' ||resp=='S');
		}
		else{
			if (op=='2'){//cambiar contrasenha
				scanf("%*c");
				cambiarContrasenha(usuarios,nUsuarios,ID_usuario);
				actualizarArchivoUsuarios(usuarios,nUsuarios);
				cargarUsuarios(usuarios,&nUsuarios);
			}
		}
		
	}while(op=='1' || op=='2');
}
///····································································
void menuUsuario(char *op){
	do{
		printf("\n---------------------------------------------------------------------------\n");
		printf("\n%-30s","1) Subir Archivo");
		printf("%-30s","\t2) Cambiar Contrasenha");
		printf("%-30s","\t3) Salir");
		printf("\n---------------------------------------------------------------------------\n");
		printf("\n\nOpcion-->  ");
		*op=getchar();
		while(getchar()!='\n');
	}while(*op!='1' && *op!='2'&&*op!='3');
}
///····································································
void tamano2Byte(double *tamanio){
	char op;
	do{
		scanf("%*c");
		//////system("clear");
		printf("\nSeleccione la Unidad de Almacenamiento ");
		printf("\n1) Byte      (B )");
		printf("\n2) KyloByte  (KB)");
		printf("\n3) MegaByte  (MB)");
		printf("\n4) GigaBytes (GB)");
		printf("\nOpcion-------->");
		op=getchar();
		while(getchar()!='\n');
	}while(op!='1' && op!='3' && op!='2'&& op!='4');
	printf("\nTamaño: ");
	scanf("%lf",&*tamanio);
	switch (op){
		case '1':
			break;
		case '2':
			*tamanio*=1024;
			break;
		case '3':
			*tamanio*=1048576;
			break;
		case '4':
			*tamanio*=1073741824;
			break;
		default:
		;
	}
}
///····································································
void cargarVectorServidores(Tservidor servidores[],int *nServidor){
	FILE *server;
	int i=0;
	server=fopen("server.txt","r");
	if (server!=NULL){
		while(!feof(server)){
			i++;
			fscanf(server,"%s",servidores[i].nombre);
			fscanf(server,"\n");
		}
		*nServidor=i;
	}
	fclose(server);
}
///····································································
void leeValidaAgregaFicheros(Tusuario usuarios[],int nUsuarios,int ID_usuario,Tservidor servidores[],int nServidor){
	int i,j,h;
	char nombreArch[31]="\0";
	double tamanio;
	i=ID_usuario;
	j=usuarios[i].cantFichero;
	do{
		
		printf("\n\t\t Subiendo Archivo.!!\n");
		do{
			printf("\n Nombre del Archivo: ");
			scanf("%s",nombreArch);
			if (!tieneExtension(nombreArch))
				printf("\nDebe tener extension ej: program.exe,code.c,foto.jpg,etc..");
		}while(!tieneExtension(nombreArch));
	}while(strlen(nombreArch)>30);
	tamano2Byte(&tamanio);
	if (usuarios[i].tamanoCasillero>=tamanio/1073741824){
		do{
			///Listar Servidores
			printf("\nSeleccione un Servidor\n");
			for (h = 1; h <=nServidor ; h++){
				printf("%d)%s\n",h,servidores[h].nombre);
			}
			scanf("%d",&h);
			while(getchar()!='\n');
		}while(!(h>=1 && h<=nServidor));
		j++;
		visibilidadArchivo(usuarios[i].ficheros[j].visibilidad);///procedimiento devuelve cadena Publico Privado
		strcpy(usuarios[i].ficheros[j].servidor,servidores[h].nombre);
		usuarios[i].tamanoCasillero-=(tamanio/1073741824);
		usuarios[i].cantFichero=j;
		usuarios[i].ficheros[j].tamanio=tamanio;
		strcpy(usuarios[i].ficheros[j].nombre,nombreArch);
		actualizarArchivoUsuarios(usuarios,nUsuarios);
		actualizarArchivoFicheros(usuarios,nUsuarios);
		cargarUsuarios(usuarios,&nUsuarios);
		cargarVectorFichero(usuarios,nUsuarios);
	}
	else{
		printf("\nNo Tiene Suficiente Espacio \n");
	}
}
///····································································
void mostrarArchivosUsuario(Tusuario usuarios[],int nUsuarios,int ID_usuario){
	int i,j;
	double bono,espacioUtilizado,espacioDisponible,espacioUtilizadoGB;
	i=ID_usuario;
	espacioUtilizado=0;
	
	printf("\nUSUARIO--------> %-30s",usuarios[i].correo);
	printf("\n---------------------------------------------------------------------------\n");
	printf(" %-25s %-15s %-15s %-15s","Archivo","Tamanio MB","Servidor","Visibilidad");
	printf("\n---------------------------------------------------------------------------");

	for (j = 1; j <= usuarios[i].cantFichero; j++){
		printf("\n %-25s %-15.0lf %-15s %-15s",usuarios[i].ficheros[j].nombre,usuarios[i].ficheros[j].tamanio/1048576,usuarios[i].ficheros[j].servidor,usuarios[i].ficheros[j].visibilidad);
		espacioUtilizado+=usuarios[i].ficheros[j].tamanio;
	}
	espacioDisponible=usuarios[i].tamanoCasillero;
	espacioUtilizadoGB=espacioUtilizado/1073741824;
	bono=(espacioDisponible+espacioUtilizadoGB-100);
	printf("\n---------------------------------------------------------------------------\n");
	printf(" %-25s %-25s %-25s ","Espacio Usado","Espacio Disponible","Total de Bonos");
	printf("\n %-25.2lf %-25.2lf %-25.2lf ",espacioUtilizadoGB,espacioDisponible,bono);
}
///····································································
void visibilidadArchivo(char visibilidad[]){
	strcpy(visibilidad,"\0");
	char op;
	do{
		printf("\n\t¡Desea Hacerlo Publico?");
		printf("\n1)Si");
		printf("\n2)No");
		printf("\nOpcion---> ");
		scanf("%c",&op);
		while(getchar()!='\n');
	}while(op!='1' && op!='2');	
	if (op=='1'){
		strcpy(visibilidad,"publico");
	}
	else{
		strcpy(visibilidad,"privado");
	}
}
///····································································
void actualizarArchivoFicheros(Tusuario usuarios[],int nUsuarios){
	FILE *ArchFicheros;
	int i;
	int j;
	char viejo[18] = "ficheros.txt";
	char nuevo[18] = "ficheros.bank";
	rename(viejo, nuevo);/* Copia de Seguridad de Usuarios.txt*/
	ArchFicheros=fopen("ficheros.txt","a");	
	for (i = 1; i <=nUsuarios ; i++){
		if (usuarios[i].cantFichero>0){
			fprintf(ArchFicheros,"\n%s",usuarios[i].cedula);
			fprintf(ArchFicheros,"\n%d",usuarios[i].cantFichero);
			for (j = 1; j <=usuarios[i].cantFichero ; j++){
				fprintf(ArchFicheros,"\n%s",usuarios[i].ficheros[j].nombre);
				fprintf(ArchFicheros,"\t%.0lf",usuarios[i].ficheros[j].tamanio);
				fprintf(ArchFicheros,"\t%s",usuarios[i].ficheros[j].servidor);
				fprintf(ArchFicheros,"\t%s",usuarios[i].ficheros[j].visibilidad);
			}
		}
	}
	fclose(ArchFicheros);
}
///********************************************************************
void agregarServidor(){
	FILE *servidor;
	char nombre[50]="\0";	
	servidor=fopen("server.txt","a");
	printf("\n%40s","AGREGAR SERVIDOR");
	if (servidor!=NULL){
		do{
			printf("\nNombre: ");
			scanf("%s",nombre);
		}while(strlen(nombre)>49);
		fprintf(servidor,"\n%s",nombre);
		fclose(servidor);
	}
}
///********************************************************************
void cargarVectorFichero(Tusuario usuarios [],int nUsuarios) {
	FILE *in;
	int i=0,j,n=nUsuarios;
	char cedula[15];
	in=fopen("ficheros.txt","r");
	if (in!=NULL){
		do{
			
			fscanf(in,"%s",cedula);
			i=buscarUsuario(usuarios,&n,cedula);
			fscanf(in,"%d",&usuarios[i].cantFichero);
			if (strcmp(usuarios[i].cedula,"\n")!=0){
				for (j = 1; j <=usuarios[i].cantFichero ; j++){
					fscanf(in,"%s",usuarios[i].ficheros[j].nombre);
					fscanf(in,"%lf",&usuarios[i].ficheros[j].tamanio);
					fscanf(in,"%s",usuarios[i].ficheros[j].servidor);
					fscanf(in,"%s",usuarios[i].ficheros[j].visibilidad);
				}
			}
		}while(!feof(in));
	}
}

///********************************************************************
void panelAdmin(Tusuario usuarios[],int *nUsuarios,Tservidor servidores[],int *nServidor){
	char opcion;
	do{
		menuAdmin(&opcion);
		switch (opcion){
			case '1':
				agregarServidor();
				break;
			case '2':
				eliminarUsuario(usuarios,*nUsuarios);
				break;
			case '3':
				reporteUsuarios(usuarios,*nUsuarios);
				break;
			case '4':
				reporteBonos(usuarios,*nUsuarios);
				break;
			case '5':
				opcion='5';
				break;
		}
	}while(opcion!='5');
	
}

///********************************************************************
void menuAdmin(char *opcion){
	do{	
		while(getchar()!='\n');
		printf("\n%40s","PANEL DE ADMINISTRADOR");
		printf("\n1) Agregar Servidor");
		printf("\n2) Eliminar Usuario");
		printf("\n3) Reporte Usuarios");
		printf("\n4) Bonos Usuarios");
		printf("\n5) Salir");
		printf("\nOpcion-------> ");
		scanf("%c",&*opcion);
	}while((*opcion!='5' && *opcion!='2' && *opcion!='3' && *opcion!='4'&& *opcion!='1'));
}

///********************************************************************
void reporteUsuarios(Tusuario usuarios[],int nUsuarios){
	int i,j;
	double totalEspacio;

	printf("\n%40s","REPORTE DE USUARIOS");
	for (i = 1; i <=nUsuarios ; i++){
		totalEspacio=0;
		if (usuarios[i].cantFichero>0 && usuarios[i].status==1){
			printf("\n\n\nUsuario-------> %-30s",usuarios[i].correo);
			printf("\n-----------------------------------------------------------------------\n");
			printf(" %-15s %-15s %-15s %-15s","Archivo","Tamanio (B)","Servidor","Visibilidad");
			printf("\n-----------------------------------------------------------------------\n");
			for (j = 1;  j<=usuarios[i].cantFichero ; j++){
				printf("\n %-15s %-15.0lf %-15s %-15s",usuarios[i].ficheros[j].nombre,usuarios[i].ficheros[j].tamanio,usuarios[i].ficheros[j].servidor,usuarios[i].ficheros[j].visibilidad);
				totalEspacio+=usuarios[i].ficheros[j].tamanio;
			}
			totalEspacio=totalEspacio/1073741824;
			printf("\n\n%60s %.2lfGB","Espacio Utilizado: ",totalEspacio);
		}
	}
}
///********************************************************************
void eliminarUsuario(Tusuario usuarios[],int nUsuarios){
	char cedula[20]="\0";
	int resp,n,i;
	
	n=nUsuarios;
	printf("\n%40s","ELIMINAR USUARIO");
	leeCI(cedula);
	resp=validaCedulaRegistrada(cedula,usuarios,n);
	if (resp){
		i=buscarUsuario(usuarios,&n,cedula);
		if (usuarios[i].status==2){
			printf("\n Ya estaba eliminado");
		}
		else{
			usuarios[i].status=2;
			actualizarArchivoUsuarios(usuarios,n);
			cargarUsuarios(usuarios,&n);
			printf("\nEliminado!");
			getchar();
		}
	}
	else{
		printf("\n NO REGISTRADO\n");
	}
}
///********************************************************************

void cambiarContrasenha(Tusuario usuarios[],int nUsuarios,int ID_usuario){
	char ci[16]="\0";
	int i;
	i=ID_usuario;
	printf("\n%40s","CAMBIANDO CONTRASENHA");
	obtener_clave(ci,0);
	strcpy(usuarios[i].contrasena,ci);
	printf("\n Contrasenha Cambiada!");
	getchar();
	
}
///********************************************************************
void reporteBonos(Tusuario usuarios[],int nUsuarios){
	
	int i,j;
	double bono,espacioUtilizado,espacioDisponible,espacioUtilizadoGB;
	printf("\n%40s","REPORTE DE BONOS");
	for (i = 1; i <=nUsuarios ; i++){
		espacioUtilizado=0;
		for (j = 1;  j<=usuarios[i].cantFichero ; j++){
			espacioUtilizado+=usuarios[i].ficheros[j].tamanio;
		}
		espacioDisponible=usuarios[i].tamanoCasillero;
		espacioUtilizadoGB=espacioUtilizado/1073741824;
		bono=(espacioDisponible+espacioUtilizadoGB-100);
		if (bono>=1&& usuarios[i].status==1){
			printf("\n\n\nUsuario-------> %-30s",usuarios[i].correo);
			printf("\n-----------------------------------------------------------------------\n");
			printf(" %-25s %-25s %-25s ","Espacio Usado (GB)","Espacio Disponible (GB)","Total de Bonos (GB)");
			printf("\n-----------------------------------------------------------------------\n");
			printf(" %-25.2lf %-25.2lf %-25.2lf ",espacioUtilizadoGB,espacioDisponible,bono);
		}
	}
}
///********************************************************************
int tieneExtension(char nombreArch[]){
	int i;
	int resp=0;
	for (i = 1; i <=strlen(nombreArch) ; i++){
		if (nombreArch[i]=='.'){
			resp=1;
		}
	}
	return resp;
	
}
