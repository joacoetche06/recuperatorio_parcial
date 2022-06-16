#include <stdio.h>
#include <stdlib.h>
#include "Biblioteca.h"
#include "Inputs.h"
#define T 10
void HarcodearListaServicios(eServicio listaServicios[]);

void HarcodearListaServicios(eServicio listaServicios[]){
	eServicio auxiliar[8] = {{1, "Joaquin", 21, 11, 2022, MOTOR, 14499.99, 3, ACTIVO, 2,1},
							{2, "Pia", 24, 3, 2022, ACEITE, 10000, 3, ACTIVO, 2,2},
							{3, "Lucas", 20, 10, 2021, SINDIAGNOSTICO, 0, 1, ACTIVO, 1,3},
							{4, "Roberto", 10, 10, 2022, ACEITE, 12500, 2, ACTIVO, 1,3},
							{5, "Juan", 11, 5, 2019, SINDIAGNOSTICO, 0, 3, ACTIVO, 3,1},
							{6, "Valentin", 10, 4, 2022, SUSPENSION, 10000, 1, ACTIVO, 3,3},
							{7, "Valentin", 10, 10, 2015, SINDIAGNOSTICO, 0, 2, ACTIVO, 2,2},
							{8, "Valentin", 10, 10, 2022, SINDIAGNOSTICO, 0, 3, ACTIVO, 2,1}};


	for(int i = 0; i < 8; i++){
		listaServicios[i] = auxiliar[i];
	}
}
int main(void)
{
	setbuf(stdout,NULL);

	int opcion;
	int bandera;
	int retorno;
	eServicio listaServicios[T];
	eMecanico listaMecanicos[M] = {{1, "Jose Luis", 1},{2, "Juan Jose", 2},{3, "Alberto", 4},
									{4, "Julio", 4},{5, "Abelardo", 2},{6, "Patricio", 2}};
	eAuxiliar auxiliar[10];
	sEspecialidad listaEspecialidades[E] = {{1, "Aceite"},{2, "Motor"},{3, "Suspension"},{4, "Ejes"},{5, "Bujias"}};
	eRecepcionista listaRecepcionistas[R] = {{1, "Maria Pilar", MANANA},{2, "Vanina", MANANA},{3, "Pia", TARDE}};

	opcion = 0;
	bandera = 0;
	retorno = 0;
    retorno = InicializarServicios(listaServicios, T);
    HarcodearListaServicios(listaServicios);

	do{

		opcion = PedirNumeroMenu();

		switch(opcion){
		case 1:
			CargarListaServicios(listaServicios, T);

			bandera = 1;
		break;

		case 2:
			if(bandera == 1){
				retorno = ModificarServicio(listaServicios, T, listaMecanicos);
				switch(retorno){
				case -1:
					printf("\nNo se encontró el id.\n\n");
				break;
				default:
					printf("Servicio modificado\n");
				break;
				}
			}
			else{
				printf("Debe cargar al menos un servicio\n");
			}
		break;

		case 3:
			if(bandera == 1){
				retorno = EliminarServicio(listaServicios, T);
				switch(retorno){
				case -1:
					printf("\nNo se encontró el id.\n\n");
				break;
				default:
					printf("Servicio eliminado\n");
				break;
				}
			}
			else{
				printf("Debe cargar al menos un servicio\n");
			}
		break;

		case 4:
			if(bandera == 1){
				retorno = DiagnosticarServicio(listaServicios, T, listaMecanicos,M, listaEspecialidades);
				switch(retorno){
				case -1:
					printf("\nNo se encontró el id.\n\n");
				break;
				default:
					printf("Servicio diagnosticado\n");
				break;
				}
			}
			else{
				printf("Debe cargar al menos un servicio\n");
			}
		break;

		case 5:
			if(bandera == 1){
				Listar(listaServicios, T, listaMecanicos, auxiliar, listaEspecialidades, listaRecepcionistas);
			}
			else{
				printf("Debe cargar al menos un servicio\n");
			}
		break;

		}
	}while(opcion != 6);


	return EXIT_SUCCESS;
}


