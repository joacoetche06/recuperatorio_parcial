#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Biblioteca.h"
#include "Inputs.h"

int PedirNumeroMenu(){
	int opcion;
	printf("1.Alta de Servicio\n2.Modificar Servicio\n3.Cancelar Servicio\n4.Diagnosticar\n5.Listar\n6.Salir\n");
	scanf("%d", &opcion);

	return opcion;
}

eServicio PedirServicio(int i){
	eServicio miServicio;

	miServicio.idServicio = i + 1;
	printf("Id: %d\n", miServicio.idServicio);
	printf("Ingrese el nombre del cliente: \n");
	fflush(stdin);
	gets(miServicio.nombreCliente);

	utn_getNumero(&miServicio.anio, "Ingrese el año que se realizo el servicio: \n","Error, año invalido\n", 2005, 2022, 50);
	utn_getNumero(&miServicio.mes, "Ingrese el mes que se realizo el servicio:\n ","ERROR mes invalido\n", 1, 12, 50);


	miServicio.dia = PedirDia(miServicio.mes, miServicio.dia);

	miServicio.precio = 0;

	utn_getNumero(&miServicio.idMecanico, "Ingrese el id del mecanico a cargo:\n1.Jose Luis\n2.Juan Jose\n3.Alberto"
										  "\n4.Julio\n5.Abelardo\n6.Patricio","ERROR id invalido\n", 1, M, 50);

	switch(miServicio.idMecanico){
		case 1:
			miServicio.idEspecialidad = 1;
		break;

		case 2:
			miServicio.idEspecialidad = 2;
		break;

		case 3:
			miServicio.idEspecialidad = 3;
		break;
	}

	utn_getNumero(&miServicio.idMecanico, "Ingrese el id de la recepcionista que lo atendió:\n1.Maria Pilar\n2.Vanina\n3.Pia",
										  "\nERROR id invalido", 1, R, 50);

	miServicio.diagnostico = SINDIAGNOSTICO;
	miServicio.estado = ACTIVO;

	return miServicio;
}

int InicializarServicios(eServicio listaServicios[], int size){
	for (int i = 0; i < size; i++){
		listaServicios[i].estado = VACIO;
	}
	return 1;
}

int BuscarEspacioLibre(eServicio listaServicios[], int size){
	int index;
	index = -1;

	for(int i = 0; i < size; i++){
		if(listaServicios[i].estado == VACIO){
			index = i;
			break;
		}
	}
	return index;
}

void CargarListaServicios(eServicio listaServicios[], int size){
	int index;
	index = BuscarEspacioLibre(listaServicios, size);
	if(index != -1){
		listaServicios[index] = PedirServicio(index);
	}
}

int ModificarServicio(eServicio listaServicios[], int size, eMecanico listaMecanicos[]){
	int idAModificar;
	int modifico;
	int opcion;
	modifico = -1;
	printf("Ingrese el id a modificar");
	scanf("%d", &idAModificar);

	for(int i = 0; i < size; i++){
		if(listaServicios[i].estado == ACTIVO && listaServicios[i].idServicio == idAModificar){
			utn_getNumero(&opcion, "Ingrese el campo a modificar:\n1.Nombre del cliente\n2.Fecha del servicio\n3.Mecanico encargado\n",
								   "\nERROR numero invalido", 1, 3, 50);
			modifico = 1;
			switch(opcion){
				case 1:
					printf("Ingrese el nuevo nombre:");
					scanf("%s", listaServicios[i].nombreCliente);
				break;

				case 2:
					utn_getNumero(&listaServicios[i].anio, "Ingrese el año que se realizo el servicio: ","\nError, año invalido", 2005, 2022, 50);

					utn_getNumero(&listaServicios[i].mes, "Ingrese el mes que se realizo el servicio: ","\nERROR mes invalido", 1, 12, 50);

					listaServicios[i].dia = PedirDia(listaServicios[i].mes, listaServicios[i].dia);

				break;

				case 3:
					utn_getNumero(&listaServicios[i].idMecanico, "Ingrese el nuevo id del mecanico:\n1.Jose Luis\n2.Juan Jose\n3.Alberto",
																 "\nError, id invalido", 1, M, 50);
					}
				break;
			}
		}

	return modifico;

}

int DiagnosticarServicio(eServicio listaServicios[], int size, eMecanico listaMecanicos[], int sizeMecanicos, sEspecialidad listaespecialidades[]){
	int diagnostico;
	int idIngresado;
	int opcion;
	diagnostico = -1;

	utn_getNumero(&idIngresado, "Ingrese el id del mecanico:\n1.Jose Luis\n2.Juan Jose\n3.Alberto",
								"\nError, id invalido", 1, M, 50);

	for(int i = 0; i < sizeMecanicos; i++){
		if(listaMecanicos[i].idMecanico == idIngresado){
			for(int j = 0; j < size; j++){
				printf("Elija el servicio a diagnosticar:\n");
				for(int k = 0; k < size; k++){
					if(listaServicios[k].estado == ACTIVO && listaServicios[k].diagnostico == SINDIAGNOSTICO && listaServicios[k].idMecanico == idIngresado){
						printf("%5d %10d/%d/%d %10s $%.2f\n", listaServicios[k].idServicio, listaServicios[k].dia, listaServicios[k].mes,
						listaServicios[k].anio, listaServicios[k].nombreCliente, listaServicios[k].precio);
					}
					scanf("%d", &opcion);
				}

				for(int x = 0; x < size; x++){
					if(opcion == listaServicios[x].idServicio){
						printf("Elija un diagnostico:\n1.%s\n2.%s\n3.%s\n", listaespecialidades[0].descripcionEspecialidad,
						listaespecialidades[1].descripcionEspecialidad, listaespecialidades[2].descripcionEspecialidad);
						scanf("%d", &listaServicios[x].diagnostico);
						printf("Ingrese el precio del servicio:");
						scanf("%f", &listaServicios[x].precio);
						while(listaServicios[x].precio < 1){
							printf("Vuelva a ingresar el precio del servicio:");
							scanf("%f", &listaServicios[x].precio);
						}
						diagnostico = 1;
					}
				}
				break;
			}
		}
	}

	return diagnostico;
}

int EliminarServicio(eServicio listaServicios[], int size){
	int idAEliminar;
	int elimino;
	elimino = -1;

	printf("Ingrese el id a eliminar");
	scanf("%d", &idAEliminar);

	for(int i = 0; i < size; i++){
		if(listaServicios[i].estado == ACTIVO && listaServicios[i].idServicio == idAEliminar){
			listaServicios[i].estado = VACIO;
			elimino = 1;
			break;
		}
	}

	return elimino;
}

void Listar(eServicio listaServicios[], int size, eMecanico listaMecanicos[], eAuxiliar auxiliar[], sEspecialidad listaEspecialidades[],eRecepcionista listaRecepcionistas[]){
	int opcion;
	printf("Ingresar el numero del listado que quiere conocer\n"
			"1.Todos los mecánicos\n2. Todos los servicios.\n"
			"3.Todos los mecánicos a los cuales no se les haya asignado ningún servicio.\n"
			"4.Listado de servicios ordenados por fecha, desde el más antiguo hasta el más reciente.\n"
			"5.Para una fecha determinada se necesita saber cuál fue la suma de cotizaciones en concepto de cambio de aceite.\n"
			"6.Cotización promedio de cada uno de los mecánicos\n"
			"7.Determinar cuál/cuáles son los mecánicos que diagnosticaron más servicios.\n"
			"8.Listado de servicios ordenados por especialidad del mecánico alfabéticamente\n"
			"9.Listado de todos los servicios entre el mes de Marzo y Mayo del 2022 para una especialidad determinada.\n"
			"10.Porcentaje de servicio diagnosticados que atiende cada mecánico en función del total de diagnósticos.\n"
			"11.Top 3 de especialidades más estudiadas por los mecanicos\n"
			"12.Determinar la cantidad de clientes de una recepcionista determinada\n");

	scanf("%d", &opcion);

	switch(opcion){
	case 1:
		MostrarTodosLosMecanicos(listaMecanicos, M,listaEspecialidades, E);
	break;

	case 2:
		MostrarServicios(listaServicios, size, listaMecanicos, M, listaEspecialidades, E, listaRecepcionistas, R);
	break;

	case 3:
		MostrarMecanicosSinServicio(listaServicios, size, listaMecanicos, M, listaEspecialidades, E, auxiliar);
	break;

	case 4:
		MostrarServiciosPorFecha(listaServicios, size, listaMecanicos, listaEspecialidades,listaRecepcionistas);
	break;

	case 5:
		MostrarCotizacionPorDeterminadaFecha(listaServicios, size);
	break;

	case 6:
		MostrarCotizacionPromedio(listaServicios, size, listaMecanicos, M, listaEspecialidades, E, auxiliar);
	break;

	case 7:
		MostrarMecanicoConMasServicios(listaServicios, size, listaMecanicos, M,auxiliar);
	break;

	case 8:
		MostrarServiciosPorEspecialidadMecanico(listaServicios, size, listaMecanicos, listaEspecialidades,listaRecepcionistas);
	break;

	case 9:
		MostrarServiciosMarzoMayo(listaServicios, size, listaMecanicos);
	break;

	case 10:
		MostrarPorcentajeMecanicosDiagnosticados( listaServicios, size, listaMecanicos, M,auxiliar);
	break;

	case 11:
		MostrarTopEspecialidades(listaMecanicos, M,listaEspecialidades, E,auxiliar);
	break;

	case 12:
		MostrarCantidadClientesRecepcionistas(listaServicios,size, listaRecepcionistas, R, auxiliar);

	break;
	}
}

void MostrarTodosLosMecanicos(eMecanico listaMecanicos[], int sizeMecanicos, sEspecialidad listaEspecialidades[], int sizeEspecialidad){
	printf("+--+------------+--------------+\n");
	printf("|%s| %-10s | %-9s |\n", "ID", "Nombre", "Especialidad");
	printf("+--+------------+--------------+\n");
	for(int i = 0; i < sizeMecanicos; i++){
		for(int j = 0; j < sizeEspecialidad; j++){
			if(listaMecanicos[i].idEspecialidad == listaEspecialidades[j].idEspecialidad){
				printf("| %d| %-10s |  %-12s|\n", listaMecanicos[i].idMecanico, listaMecanicos[i].nombreMecanico, listaEspecialidades[j].descripcionEspecialidad);
				printf("+--+------------+--------------+\n");
			}
		}
	}
}

void MostrarServicios(eServicio listaServicios[], int size, eMecanico listaMecanicos[],int sizeMecanicos, sEspecialidad listaEspecialidades[], int sizeEspecialidades, eRecepcionista listaRecepcionistas[], int sizeRecepcionista){
	char aceite[20] = "Cambio de aceite";
	char motor[20] = "Reparacion de motor";
	char suspension[20] = "Suspension";
	char nulo[20] = "Sin diagnostico";
	char opcion[20];
	char nombreMecanico[20];
	char nombreRecepcionista[20];
	int numTurno;
	char turno[20];
	char especialidad[20];
	printf("+--+------------+-----------+------------+---------------------+-----------+--------------+---------------+---------+\n");
	printf("|%s| %-10s | %-9s | %-10s | %-19s | %-9s | %-13s| %-14s| %-8s|\n","ID", "Fecha","Nombre", "Precio", "Diagnóstico", "Mecanico", "Especialidad", "Recepcionista", "Turno");
	printf("+--+------------+-----------+------------+---------------------+-----------+--------------+---------------+---------+\n");
	for(int i = 0; i < size; i++){
		for(int j = 0; j < sizeMecanicos; j++){
			if(listaServicios[i].idMecanico == listaMecanicos[j].idMecanico){
				strcpy(nombreMecanico, listaMecanicos[j].nombreMecanico);
			}
			for(int k = 0; k < sizeEspecialidades; k++){
				if(listaServicios[i].idEspecialidad == listaEspecialidades[k].idEspecialidad){
					strcpy(especialidad, listaEspecialidades[k].descripcionEspecialidad);
				}
			}
			for(int x = 0; x < sizeRecepcionista; x++){
				if(listaServicios[i].idRecepcionista == listaRecepcionistas[x].idRecepcionista){
					strcpy(nombreRecepcionista, listaRecepcionistas[x].nombreRecepcionista);
					numTurno = listaRecepcionistas[x].turno;

				}
				switch(numTurno){
				case 1:
					strcpy(turno, "Mañana");
				break;

				case 2:
					strcpy(turno, "Tarde");
				break;
				}
			}

		}
		switch(listaServicios[i].diagnostico){
			case 0:
				strcpy(opcion, nulo);
			break;

			case 1:
				strcpy(opcion, aceite);
			break;

			case 2:
				strcpy(opcion, motor);
			break;

			case 3:
				strcpy(opcion, suspension);
			break;
		}

		if(listaServicios[i].estado == ACTIVO){
			printf("|%2d| %-2d/%-2d/%-5d| %-10s| $%-10.2f| %-20s| %-10s| %-13s| %-14s| %-8s|\n",
			listaServicios[i].idServicio, listaServicios[i].dia, listaServicios[i].mes,listaServicios[i].anio,
			listaServicios[i].nombreCliente, listaServicios[i].precio, opcion, nombreMecanico, especialidad,nombreRecepcionista, turno);
			printf("+--+------------+-----------+------------+---------------------+-----------+--------------+---------------+---------+\n");
		}
	}
}


void MostrarMecanicosSinServicio(eServicio listaServicios[], int size, eMecanico listaMecanicos[],  int sizeMecanicos, sEspecialidad listaEspecialidades[], int sizeEspecialidad,eAuxiliar auxiliar[]){
	int bandera;
	int pregunta;
	bandera = -1;
	pregunta = 0;

	InicializarAuxiliar(listaServicios, size, listaMecanicos, sizeMecanicos, auxiliar, pregunta);

	for(int i = 0; i < sizeMecanicos; i++){
		for(int j = 0; j < sizeEspecialidad; j++){
			if(auxiliar[i].contador == 0 && listaEspecialidades[j].idEspecialidad == listaMecanicos[i].idEspecialidad){
				bandera = 0;
				printf("\nEl mecanico sin servicio es %s y su especialidad es %s\n", listaMecanicos[i].nombreMecanico, listaEspecialidades[j].descripcionEspecialidad);
			}
			else{
				if(bandera == -1){
					bandera = 1;
				}
			}
		}
	}
	if(bandera == 1){
		printf("Todos los mecanicos tienen al menos un servicio\n\n");
	}
}

void MostrarServiciosPorFecha(eServicio listaServicios[], int size, eMecanico listaMecanicos[], sEspecialidad listaEspecialidades[],eRecepcionista listaRecepcionistas[]){
	eServicio auxiliar;
	for(int i = 0; i < size - 1; i++){
		for(int j = i + 1; j < size; j++){
			if(listaServicios[i].anio > listaServicios[j].anio){
				auxiliar = listaServicios[i];
				listaServicios[i] = listaServicios[j];
				listaServicios[j] = auxiliar;
			}
			else{
				if(listaServicios[i].anio == listaServicios[j].anio && listaServicios[i].mes > listaServicios[j].mes){
					auxiliar = listaServicios[i];
					listaServicios[i] = listaServicios[j];
					listaServicios[j] = auxiliar;
				}
				if(listaServicios[i].anio == listaServicios[j].anio && listaServicios[i].mes == listaServicios[j].mes && listaServicios[i].dia > listaServicios[j].dia){
					auxiliar = listaServicios[i];
					listaServicios[i] = listaServicios[j];
					listaServicios[j] = auxiliar;
				}
			}
		}
	}
	MostrarServicios(listaServicios, size, listaMecanicos, M,listaEspecialidades, E, listaRecepcionistas, R);
}

void MostrarCotizacionPorDeterminadaFecha(eServicio listaServicios[], int size){
	int diaIngresado;
	int mesIngresado;
	int anioIngresado;
	float cotizacionAceite;
	int bandera;
	cotizacionAceite = 0;
	bandera = 0;
	diaIngresado = 0;

	utn_getNumero(&anioIngresado, "Ingrese el año que se realizo el servicio: \n","Error, año invalido\n", 2005, 2022, 50);

	utn_getNumero(&mesIngresado, "Ingrese el mes que se realizo el servicio:\n ","ERROR mes invalido\n", 1, 12, 50);

	diaIngresado = PedirDia(mesIngresado, diaIngresado);

	for(int i = 0; i < size; i++){
		if(anioIngresado == listaServicios[i].anio && mesIngresado == listaServicios[i].mes &&
				diaIngresado == listaServicios[i].dia && listaServicios[i].diagnostico == ACEITE){
			cotizacionAceite += listaServicios[i].precio;
			bandera = 1;
		}
	}
	if(bandera == 1){
		printf("Para el dia %d/%d/%d la suma de cotizaciones para el cambio de aceite fue de $%.2f\n", diaIngresado, mesIngresado, anioIngresado, cotizacionAceite);
	}
	else{
		printf("En la fecha ingresada no se registraron cambios de aceite.\n");
	}

}


void MostrarCotizacionPromedio(eServicio listaServicios[], int size, eMecanico listaMecanicos[],  int sizeMecanicos, sEspecialidad listaEspecialidades[], int sizeEspecialidad, eAuxiliar auxiliar[]){
	int pregunta;
	pregunta = 1;

	InicializarAuxiliar(listaServicios, size, listaMecanicos, sizeMecanicos, auxiliar, pregunta);

	for(int i = 0; i < sizeMecanicos; i++){
		for(int j = 0; j < sizeEspecialidad; j++){
			if(listaEspecialidades[j].idEspecialidad == listaMecanicos[i].idEspecialidad && auxiliar[i].contador > 0){
				auxiliar[i].promedio =  auxiliar[i].suma/auxiliar[i].contador;
				printf("Promedio del mecanico especialista en %s, %s: $%.2f\n",listaEspecialidades[j].descripcionEspecialidad, listaMecanicos[i].nombreMecanico,auxiliar[i].promedio);
			}
		}
	}
}



void MostrarMecanicoConMasServicios(eServicio listaServicios[],int size, eMecanico listaMecanicos[], int sizeMecanicos,eAuxiliar auxiliar[]){
	int maximo;
	int pregunta;
	maximo = 0;
	pregunta = 0;

	InicializarAuxiliar(listaServicios, size, listaMecanicos, sizeMecanicos, auxiliar, pregunta);

	maximo = DeterminarMaximo(listaMecanicos, sizeMecanicos, auxiliar, maximo);

	for(int i = 0; i < sizeMecanicos; i++){
		if(maximo == auxiliar[i].contador){
			printf("El mecanico con mas servicios es: %s\n", listaMecanicos[i].nombreMecanico);
		}
	}
}


void MostrarServiciosPorEspecialidadMecanico(eServicio listaServicios[],int size, eMecanico listaMecanicos[],sEspecialidad listaEspecialidades[], eRecepcionista listaRecepcionistas[]){
	eServicio auxiliar;
		for(int i = 0; i < size - 1; i++){
			for (int j = i + 1; j < size; j++){
				if(listaServicios[i].idEspecialidad > listaServicios[j].idEspecialidad){
					auxiliar = listaServicios[i];
					listaServicios[i] = listaServicios[j];
					listaServicios[j] = auxiliar;
				}
				else{
					if(listaServicios[i].idEspecialidad == listaServicios[j].idEspecialidad){
						auxiliar = listaServicios[i];
						listaServicios[i] = listaServicios[j];
						listaServicios[j] = auxiliar;
					}
				}
			}
		}
		MostrarServicios(listaServicios, size, listaMecanicos, M,listaEspecialidades, E, listaRecepcionistas, R);
}


 void MostrarServiciosMarzoMayo(eServicio listaServicios[],int  size, eMecanico listaMecanicos[]){
	 int especialidad;
	 int bandera;
	 bandera = 0;
	 utn_getNumero(&especialidad, "Ingrese el id de la especialidad a buscar:\n1.Aceite\n2.Motor\n3.Suspension\n4.Ejes\n5.Bujias",
	 							  "\nERROR id invalido", 1, E, 50);

	 for(int i = 0; i < size; i++){
		 if(listaServicios[i].estado == ACTIVO && especialidad == listaServicios[i].diagnostico &&
			listaServicios[i].anio == 2022 && listaServicios[i].mes >= 3 && listaServicios[i].mes <= 5){
			 printf("%5d %10d/%d/%d %10s $%.2f %s\n", listaServicios[i].idServicio, listaServicios[i].dia,
			listaServicios[i].mes,listaServicios[i].anio, listaServicios[i].nombreCliente,listaServicios[i].precio, listaMecanicos[i].nombreMecanico);
			 bandera = 1;
		 }
	 }
	 if(bandera == 0){
		 printf("No hay servicios de esa especialidad entre marzo y mayo.\n");
	 }
}



void MostrarPorcentajeMecanicosDiagnosticados(eServicio listaServicios[],int size, eMecanico listaMecanicos[], int sizeMecanicos,eAuxiliar auxiliar[]){
 	int contadorTotal;
 	int pregunta;
 	contadorTotal = 0;
 	pregunta = 2;

 	InicializarAuxiliar(listaServicios, size, listaMecanicos, sizeMecanicos, auxiliar, pregunta);
 	contadorTotal = ContarTotalMecanicosConServiciosDiagnosticados(listaServicios, size, auxiliar, sizeMecanicos,contadorTotal);

 	if(contadorTotal > 0){
		for(int i = 0; i < sizeMecanicos; i++){
			auxiliar[i].porcentaje = (auxiliar[i].contador * 100) / contadorTotal;
			printf("\nPorcentaje: %s %.2f%s  \n", listaMecanicos[i].nombreMecanico, auxiliar[i].porcentaje, "%");
		}
 	}
 	else{
		printf("No hay servicios diagnosticados.\n");
	}

}



void MostrarTopEspecialidades(eMecanico listaMecanicos[], int sizeMecanicos,sEspecialidad listaEspecialidades[], int sizeEspecialidades,eAuxiliar auxiliar[]){
	InicializarAuxiliarEspecialidades(listaMecanicos, sizeMecanicos,listaEspecialidades, sizeEspecialidades, auxiliar);

	OrdenamientoEspecialidades(sizeEspecialidades, auxiliar);

	printf("El top 3 de especialidades mas estudiadas es:\n");
	for(int i = 0; i < 3; i++){
		if(auxiliar[i].contador > 1){
			printf("%s, con %d mecanicos\n", auxiliar[i].nombre, auxiliar[i].contador);
		}
		else{
			printf("%s, con %d mecanico\n", auxiliar[i].nombre, auxiliar[i].contador);
		}
	}
}



void MostrarCantidadClientesRecepcionistas(eServicio listaServicios[],int size, eRecepcionista listaRecepcionistas[], int sizeRecepcionistas,eAuxiliar auxiliar[]){
	int opcionElegida;
	int contador;
	char recepcionistaElegida[20];
	char turnoRecepcionistaElegida[20];
	contador = 0;
	printf("Ingrese el id de la recepcionista:\n1.Maria Pilar\n2.Vanina\n3.Pia\n");
	scanf("%d", &opcionElegida);


	for(int i = 0; i < sizeRecepcionistas; i++){
		for(int j = 0; j < size; j++){
			if(listaServicios[j].estado == ACTIVO && listaServicios[j].idRecepcionista == opcionElegida && listaRecepcionistas[i].idRecepcionista == opcionElegida){
				contador++;
				strcpy(recepcionistaElegida, listaRecepcionistas[i].nombreRecepcionista);
				switch(listaRecepcionistas[i].turno){
					case 1:
						strcpy(turnoRecepcionistaElegida, "mañana");
					break;

					case 2:
						strcpy(turnoRecepcionistaElegida, "tarde");
					break;
				}
			}
		}
	}

	printf("La recepcionista %s trabaja en el turno %s y tiene %d clientes\n", recepcionistaElegida, turnoRecepcionistaElegida,contador);

}

/* FUNCIONES PARA MODULARIZAR*/

void InicializarAuxiliar(eServicio listaServicios[],int size, eMecanico listaMecanicos[], int sizeMecanicos,eAuxiliar auxiliar[], int pregunta){
	for(int i = 0; i < sizeMecanicos; i++){
		auxiliar[i].id = listaMecanicos[i].idMecanico;
		auxiliar[i].contador = 0;
		auxiliar[i].suma = 0;

		switch(pregunta){
			case 0:
				auxiliar[i].contador = ContarServiciosMecanico(listaServicios, size, auxiliar, i);
			break;

			case 1:
				auxiliar[i].contador = ContarServiciosMecanico(listaServicios, size, auxiliar, i);
				auxiliar[i].suma = SumarPrecios(listaServicios, size, auxiliar, i);
			break;

			case 2:
				auxiliar[i].contador = ContarServiciosConDiagnosticoPorMecanico(listaServicios, size, auxiliar, i);
			break;
		}

		if(pregunta == 1){
			auxiliar[i].suma = SumarPrecios(listaServicios, size, auxiliar, i);
		}
	}
}

int ContarServiciosMecanico(eServicio listaServicios[],int size,eAuxiliar auxiliar[], int i){
	for(int j = 0; j < size; j++){
		if(listaServicios[j].estado == ACTIVO && auxiliar[i].id == listaServicios[j].idMecanico){
			auxiliar[i].contador++;
		}
	}
	return auxiliar[i].contador;
}

int DeterminarMaximo(eMecanico listaMecanicos[], int sizeMecanicos,eAuxiliar auxiliar[], int maximo){
	for(int i = 0; i < sizeMecanicos; i++){
		if(i == 0 || auxiliar[i].contador > maximo){
			maximo = auxiliar[i].contador;
		}
	}
	return maximo;
}

int SumarPrecios(eServicio listaServicios[],int size,eAuxiliar auxiliar[], int i){
	for(int j = 0; j < size; j++){
		if(listaServicios[j].estado == ACTIVO && auxiliar[i].id == listaServicios[j].idMecanico){
			auxiliar[i].suma += listaServicios[j].precio;
		}
	}
	return auxiliar[i].suma;
}

int ContarTotalMecanicosConServiciosDiagnosticados(eServicio listaServicios[],int size,eAuxiliar auxiliar[], int sizeMecanicos,int contadorTotal){
	for(int i = 0; i < sizeMecanicos; i++){
		for(int j = 0; j < size; j++){
			if(listaServicios[j].estado == ACTIVO && auxiliar[i].id == listaServicios[j].idMecanico && listaServicios[j].diagnostico != SINDIAGNOSTICO){
				contadorTotal++;
			}
		}
	}
	return contadorTotal;
}

int ContarServiciosConDiagnosticoPorMecanico(eServicio listaServicios[],int size,eAuxiliar auxiliar[],int i){

	for(int j = 0; j < size; j++){
		if(listaServicios[j].estado == ACTIVO && auxiliar[i].id == listaServicios[j].idMecanico && listaServicios[j].diagnostico != SINDIAGNOSTICO){
			auxiliar[i].contador++;
		}
	}

	return auxiliar[i].contador++;
}

void InicializarAuxiliarEspecialidades(eMecanico listaMecanicos[], int sizeMecanicos,sEspecialidad listaEspecialidades[], int sizeEspecialidades,eAuxiliar auxiliar[]){
	for(int i = 0; i < sizeEspecialidades; i++){
		auxiliar[i].id = listaEspecialidades[i].idEspecialidad;
		strcpy(auxiliar[i].nombre, listaEspecialidades[i].descripcionEspecialidad);
		auxiliar[i].contador = 0;

		auxiliar[i].contador = ContarEspecialidades(listaMecanicos, sizeMecanicos, auxiliar, i);


	}
}

void OrdenamientoEspecialidades(int sizeEspecialidades,eAuxiliar auxiliar[]){
	eAuxiliar otroAuxiliar;
	for(int i = 0; i < sizeEspecialidades - 1; i++){
		for(int j = i + 1; j < sizeEspecialidades; j++){
			if(auxiliar[i].contador < auxiliar[j].contador){
				otroAuxiliar = auxiliar[i];
				auxiliar[i] = auxiliar[j];
				auxiliar[j] = otroAuxiliar;
			}
		}
	}
}

int ContarEspecialidades(eMecanico listaMecanicos[], int sizeMecanicos, eAuxiliar auxiliar[], int i){
	for(int j = 0; j < sizeMecanicos; j++){
		if(auxiliar[i].id == listaMecanicos[j].idEspecialidad){
			auxiliar[i].contador++;
		}
	}
	return auxiliar[i].contador;
}
