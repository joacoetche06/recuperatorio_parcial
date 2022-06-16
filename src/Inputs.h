int ValidateString (char *B);

char* getString(char message[], int size);



/// @brief lee el stdin hasta que encuentra un '\n' o hsta que haya
/// copiado en cadena un maximo de 'longitud' -1 caracteres
/// @param pResultado puntero al espacio de memoria donde se copiara
/// donde se copiara la cadena obtenida
/// @param longitud define el tamaño de la cadea
/// @return retorna 0 (exito) si se obtiene una cadena si no -1 (error)
int myGets(char* cadena, int longitud);



/// @brief get an integer
/// @param pResultado int
/// @return return 0 SUCCESS or -1 ERROR
int getInt(int* pResultado);



/// @brief get an integer and validate it.
///
/// @param pResultado int
/// @param mensaje char
/// @param mensajeError char
/// @param minimo int
/// @param maximo int
/// @param reintentos int
/// @return return 0 SUCCESS or -1 ERROR
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);

int esNumerica(char* cadena);

/// @brief validate a float
///
/// @param fm char
/// @param var void
/// @return 0 SUCCESS or 1 ERROR
int validarFloat(const char* fm, void* var);



/// @brief validate an alphanumeric
///
/// @param variable char
/// @return 0 SUCCESS or -1 ERROR
int validarAlfanumerico(char variable[]);



/// @brief get an alphanumeric
///
/// @param nombre char
/// @param mensaje char
void PedirAlfanumerico(char nombre[], char mensaje[]);


int PedirDia(int mes, int dia);
