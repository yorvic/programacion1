/*
 * =====================================================================================
 *
 *       Filename:  torreHanoi.c
 *
 *    Description:  ejercicio recursivo del juego torre de hanoi
 *
 *        Version:  1.0
 *        Created:  10/07/13 16:20:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YORVIC GODOY (), 
 *   Organization:  3Y
 *
 * =====================================================================================
 */


#include	<stdio.h>
#include	<stdlib.h>
void transferir (int,char,char,char);
/*=====================================================================================*/
int main (void){
	int n;
	printf ( "Bienvenidos a las Torres de HAnoi\n" );
	printf ( "Cuantos Discos?\n" );
	scanf ( "%d",&n );
	printf ( "\n" );
	transferir(n,'I','D','C');
		return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/* ===  FUNCTION  ======================================================================
 *         Name:  transferir
 * =====================================================================================*/
void transferir ( int n,char desde, char hacia,char temp ) {
  /* n= numero de discos
	* desde =origen
	* hacia=destino
	* temp=almacenamiento temporal*/

	if ( n>0 ) {
	  /* mover n-1 discos desde su origen hasta el pivote temporal*/
		transferir(n-1,desde,temp,hacia);
		/* mover el n-esimo disco desde su origen hasta su destino*/
		printf ( "mover disco %2d desde %c hasta %c\n",n,desde,hacia );	
		/* mover n-1 disco desde el pivote temporal hasta su destino*/
		transferir(n-1,temp,hacia,desde);
	}
}		/* -----  end of function transferir  ----- */
