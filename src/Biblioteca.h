#define SINDIAGNOSTICO 0
#define ACEITE 1
#define MOTOR 2
#define SUSPENSION 3
#define ACTIVO 1
#define VACIO 0
#define M 6
#define E 5
#define R 3
#define MANANA 1
#define TARDE 2


typedef struct{

	int idMecanico;
	char nombreMecanico[50];
	int idEspecialidad;
	int idRecepcionista;
}eMecanico;

typedef struct{
	int idEspecialidad;
	char descripcionEspecialidad[20];
}sEspecialidad;

typedef struct{

	int idServicio;
	char nombreCliente[50];
	int dia;
	int mes;
	int anio;
	int diagnostico;
	float precio;
	int idMecanico;
	int estado;
	int idEspecialidad;
	int idRecepcionista;
}eServicio;

typedef struct{

	int idRecepcionista;
	char nombreRecepcionista[20];
	int turno;

}eRecepcionista;

typedef struct{
	int id;
	int contador;
	float suma;
	float promedio;
	float porcentaje;
	char nombre[20];
}eAuxiliar;

/// @brief pide al usuario un numero de menu
///
/// @return opcion de menu elegida por el usuario
int PedirNumeroMenu();

/// @brief pide al usuario los datos de un usuario
///
/// @param i numero que le indica a la funcion que id ingresar
/// @return un servicio(estructura)
eServicio PedirServicio(int i);

/// @brief cambia el estado de los servicios a vacio asi al principio estan todos los servicios sin diagnostico
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @return 1 si esta todo bien
int InicializarServicios(eServicio listaServicios[], int size);

/// @brief busca un espacio sin ocupar en el array
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @return un numero que indica a otra funcion si logro encontrar el espacio libre
int BuscarEspacioLibre(eServicio listaServicios[], int size);

/// @brief permite cargar los servicios ingresados al array
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
void CargarListaServicios(eServicio listaServicios[], int size);

/// @brief permite al usuario modificar el servicio elegido
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @return un numero que indica si logro modificar el servicio
int ModificarServicio(eServicio listaServicios[], int size, eMecanico listaMecanicos[]);

/// @brief permite elegir un diagnostico al servicio elegido
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
/// @return un numero que indica si logro diagnosticar el servicio
int DiagnosticarServicio(eServicio listaServicios[], int size, eMecanico listaMecanicos[], int sizeMecanicos, sEspecialidad listaespecialidades[]);

/// @brief permite eliminar un servicio
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @return un numero que indica si logro eliminar el servicio
int EliminarServicio(eServicio listaServicios[], int size);

/// @brief muestra la lista de informes que el usuario puede elegir
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
/// @param auxiliar estructura que se usa para almacenar datos de determinado mecanico/servicio
/// @param listaEspecialidades array de especialidades
void Listar(eServicio listaServicios[], int size, eMecanico listaMecanicos[], eAuxiliar auxiliar[], sEspecialidad listaEspecialidades[],eRecepcionista listaRecepcionistas[]);

/// @brief muestra la lista de mecanicos
///
/// @param listaMecanicos array de mecanicos
/// @param sizeMecanicos tamaño del array de mecanicos
/// @param listaEspecialidades array de especialidades
/// @param sizeEspecialidad tamaño del array de especialidades
void MostrarTodosLosMecanicos(eMecanico listaMecanicos[], int sizeMecanicos, sEspecialidad listaEspecialidades[], int sizeEspecialidad);


/// @brief muestra la lista de servicios
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
/// @param listaEspecialidades array de especialidades
/// @param sizeEspecialidad tamaño del array de especialidades
void MostrarServicios(eServicio listaServicios[], int size, eMecanico listaMecanicos[],int sizeMecanicos, sEspecialidad listaEspecialidades[], int sizeEspecialidades, eRecepcionista listaRecepcionistas[], int sizeRecepcionista);

/// @brief muestra a los mecanicos que no se les asignó un servicio
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
/// @param sizeMecanicos tamaño del array de mecanicos
/// @param listaEspecialidades array de especialidades
/// @param sizeEspecialidad tamaño del array de especialidades
/// @param auxiliar estructura que se usa para almacenar datos de determinado mecanico
void MostrarMecanicosSinServicio(eServicio listaServicios[], int size, eMecanico listaMecanicos[],  int sizeMecanicos, sEspecialidad listaEspecialidades[], int sizeEspecialidad,eAuxiliar auxiliar[]);
/// @brief muestra los servicios realizados en una fecha ingresada por el usuario
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
/// @param sizeEspecialidad tamaño del array de especialidades
void MostrarServiciosPorFecha(eServicio listaServicios[], int size, eMecanico listaMecanicos[], sEspecialidad listaEspecialidades[],eRecepcionista listaRecepcionistas[]);
/// @brief muestra la cotizacion que se percibió por el cambio de aceite en determinada fecha
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
void MostrarCotizacionPorDeterminadaFecha(eServicio listaServicios[], int size);

/// @brief calcula y muestra la cotizacion promedio de cada mecanico
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
/// @param sizeMecanicos tamaño del array de mecanicos
/// @param listaEspecialidades array de especialidades
/// @param sizeEspecialidad tamaño del array de especialidades
/// @param auxiliar estructura que se usa para almacenar datos de determinado mecanico
void MostrarCotizacionPromedio(eServicio listaServicios[], int size, eMecanico listaMecanicos[],  int sizeMecanicos, sEspecialidad listaEspecialidades[], int sizeEspecialidad, eAuxiliar auxiliar[]);

/// @brief calcula cual de los mecanicos realizo mas servicios
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
/// @param auxiliar estructura que se usa para almacenar datos de determinado mecanico
void MostrarMecanicoConMasServicios(eServicio listaServicios[],int size, eMecanico listaMecanicos[], int sizeMecanicos,eAuxiliar auxiliar[]);

/// @brief muestra a los servicios por especialidad y por orden alfabetico
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
/// @param listaEspecialidades array de especialidades
void MostrarServiciosPorEspecialidadMecanico(eServicio listaServicios[],int size, eMecanico listaMecanicos[],sEspecialidad listaEspecialidades[], eRecepcionista listaRecepcionistas[]);
/// @brief muestra los servicios de determinada especialidad realizados entre marzo y mayo del 2022
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
void MostrarServiciosMarzoMayo(eServicio listaServicios[],int  size, eMecanico listaMecanicos[]);

/// @brief calcula y muestra el porcentaje de servicios que realizo cada mecanico
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
/// @param auxiliar estructura que se usa para almacenar datos de determinado mecanico
void MostrarPorcentajeMecanicosDiagnosticados(eServicio listaServicios[],int size, eMecanico listaMecanicos[], int sizeMecanicos,eAuxiliar auxiliar[]);

/// @brief
///
/// @param listaServicios array de servicios
/// @param size tamaño del array
/// @param listaMecanicos array de mecanicos
/// @param auxiliar estructura que se usa para almacenar datos de determinada especialidad
/// @param listaEspecialidades array de especialidades
void MostrarTopEspecialidades(eMecanico listaMecanicos[], int sizeMecanicos,sEspecialidad listaEspecialidades[], int sizeEspecialidades,eAuxiliar auxiliar[]);

/// @brief muestra la cantidad de clientes de la recepcionista elegida por el usuario
///
/// @param listaServicios array de servicios
/// @param size tamaño del array listaServicios
/// @param listaRecepcionistas array de recepcionistas
/// @param sizeRecepcionistas tamaño del array listaRecepcionistas
/// @param auxiliar estructura que se usa para almacenar datos de determinada recepcionista
void MostrarCantidadClientesRecepcionistas(eServicio listaServicios[],int size, eRecepcionista listaRecepcionistas[], int sizeRecepcionistas,eAuxiliar auxiliar[]);

/// @brief inicializa los campos de la estructura auxiliar
///
/// @param listaServicios
/// @param size
/// @param listaMecanicos
/// @param sizeMecanicos
/// @param auxiliar
/// @param pregunta
void InicializarAuxiliar(eServicio listaServicios[],int size, eMecanico listaMecanicos[], int sizeMecanicos,eAuxiliar auxiliar[], int pregunta);

/// @brief cuenta la cantidad de servicios por mecanico
///
/// @param listaServicios
/// @param size
/// @param auxiliar
/// @param i
/// @return la cantidad de servicios por mecanico
int ContarServiciosMecanico(eServicio listaServicios[],int size,eAuxiliar auxiliar[], int i);

/// @brief cuenta la cantidad de servicios con diagnostico por mecanico
///
/// @param listaServicios
/// @param size
/// @param auxiliar
/// @param i
/// @return la cantidad de servicios con diagnostico por mecanico
int ContarServiciosConDiagnosticoPorMecanico(eServicio listaServicios[],int size,eAuxiliar auxiliar[],int i);

/// @brief determina cual es el mecanico con mas servicios
///
/// @param listaMecanicos
/// @param sizeMecanicos
/// @param auxiliar
/// @param maximo
/// @return la cantidad mas alta de servicios
int DeterminarMaximo(eMecanico listaMecanicos[], int sizeMecanicos,eAuxiliar auxiliar[], int maximo);

/// @brief suma los precios de los servicios de cada mecanico
///
/// @param listaServicios
/// @param size
/// @param auxiliar
/// @param i
/// @return suma total de los servicios de cada mecanico
int SumarPrecios(eServicio listaServicios[],int size,eAuxiliar auxiliar[], int i);

/// @brief cuenta la cantidad total de servicios diagnosticados
///
/// @param listaServicios
/// @param size
/// @param auxiliar
/// @param sizeMecanicos
/// @param contadorTotal
/// @return cantidad total de servicios
int ContarTotalMecanicosConServiciosDiagnosticados(eServicio listaServicios[],int size,eAuxiliar auxiliar[], int sizeMecanicos,int contadorTotal);

/// @brief inicializa los campos del auxiliar de especialidades
///
/// @param listaMecanicos
/// @param sizeMecanicos
/// @param listaEspecialidades
/// @param sizeEspecialidades
/// @param auxiliar
void InicializarAuxiliarEspecialidades(eMecanico listaMecanicos[], int sizeMecanicos,sEspecialidad listaEspecialidades[], int sizeEspecialidades,eAuxiliar auxiliar[]);

/// @brief cuenta la cantidad de especialidades estudiadas por los mecanicos
///
/// @param listaMecanicos
/// @param sizeMecanicos
/// @param auxiliar
/// @param i
/// @return cantidad de especialidades
int ContarEspecialidades(eMecanico listaMecanicos[], int sizeMecanicos, eAuxiliar auxiliar[], int i);

/// @brief ordena las especialidades desde la que se estudia mas
///
/// @param sizeEspecialidades
/// @param auxiliar
void OrdenamientoEspecialidades(int sizeEspecialidades,eAuxiliar auxiliar[]);
