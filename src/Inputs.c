#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Inputs.h"
#include "Biblioteca.h"

int ValidateString (char *B){
        int i;
        for (i = 0; B[i] != '\0'; i++){
		   if (!(B[i] >= 65 && B[i] <= 90) && !(B[i] >= 97 && B[i] <= 122) && !(B[i] >= 48 && B[i] <= 57)){
				return 0;
		  }
       }
       return 1;
}



char* getString(char message[], int size){
	char* cadena[size];

	do{
		printf("%s", message);
		scanf("%s", *cadena);
	}
	while(ValidateString(*cadena) != 0);


	return *cadena;
}


int myGets(char* cadena, int longitud){
	fflush(stdin);
	fgets(cadena, longitud, stdin);
	cadena[strlen(cadena)-1] = '\0';
	return 0;

}


int getInt(int* pResultado){
	int retorno = -1;
	char bufferString[4096];

	if(myGets(bufferString, sizeof(bufferString)) == 0 && esNumerica(bufferString)){
		retorno = 0;
		*pResultado = atoi(bufferString);
	}

	return retorno;
}



int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
	int retorno = -1;
	int bufferInt;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0){
		do{
			printf("%s", mensaje);
				if(getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo){
					*pResultado = bufferInt;
					retorno = 0;
					break;
				}
			reintentos--;
			printf("%s", mensajeError);
		}while(reintentos >= 0);
	}
	return retorno;
}



int esNumerica(char* cadena){
	int retorno = 1;
	int i=0;

		if(cadena[0] == '-'){
			i = 1;
		}

		for( ; cadena[i] != '\0'; i++){
			if(cadena[i] > '9' || cadena[i] < '0'){
				retorno = 0;
				break;
			}
		}
	return retorno;
}



int validarFloat(const char* fm, void* var){
    int ch;

    if(!scanf(fm, var)) {
        while((ch = getchar()) != '\n' && ch != EOF);
        return 1;
    }

    if(getchar() != '\n'){
        while((ch = getchar()) != '\n' && ch != EOF);
        return 1;
    }
    return 0;
}



int validarAlfanumerico(char variable[]){
	int retorno = 1;
	int i;

		for(i=0 ; i<strlen(variable); i++){
			if(!((variable[i]>=65 && variable[i]<=90)||	(variable[i]>=97 && variable[i]<=122)||
				(variable[i]>='0' && variable[i]<='9'))){
				printf("\nError ingrese un codigo de vuelo valido");
				retorno = 0;
				break;
			}
		}
	return retorno;
}



void PedirAlfanumerico(char nombre[], char mensaje[]){
	int retorno;

		do{
	         printf("\n%s", mensaje);
	         scanf("%s",nombre);
	         retorno = validarAlfanumerico(nombre);

	     }while(retorno == 0);
}

int PedirDia(int mes, int dia){
	switch(mes){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			utn_getNumero(&dia, "Ingrese el dia que se realizo el servicio: \n","ERROR dia invalido\n", 1, 31, 50);
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			utn_getNumero(&dia, "Ingrese el dia que se realizo el servicio: \n","ERROR dia invalido\n", 1, 30, 50);
			break;

		case 2:
			utn_getNumero(&dia, "Ingrese el dia que se realizo el servicio: \n","ERROR dia invalido\n", 1, 28, 50);
			break;
		}
	return dia;
}


