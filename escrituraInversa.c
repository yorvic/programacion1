/*
 * =====================================================================================
 *
 *       Filename:  escrituraInversa.c
 *
 *    Description:  Escritura Inversa Recursiva *
 *        Version:  1.0
 *        Created:  10/07/13 14:34:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YORVIC GODOY (), 
 *   Organization:  3Y
 *
 * =====================================================================================
 */
#include <stdio.h>
#define	EOLN '\n'			/* enter */
void inverso(void);
int main(){
	printf("\n Escritura Inversa ...\n");
	printf ( "Ingrese una cadena: " );
	inverso();
	return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  inverso
 *  Description:  
 * =====================================================================================
 */
	void inverso ( void)
{
char c;	
	if ((c=getchar())!=EOLN)
		inverso();
	putchar(c);
}		/* -----  end of function inverso  ----- */
