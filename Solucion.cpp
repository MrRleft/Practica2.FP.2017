//Practica 2 Por Rubén Izquierdo y Jorge Sánchez, sin ningún apartado opcional.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> //Esta funcion la necesitaremos a la hora de mostrar la fila


using namespace std;



//Constantes globales dentro del programa con el valor maximo del array entre otros.
const unsigned int CENTINELA = -1;
const int MAX_PROD = 25;
const int PROD_NULO = 0;


//Definicion del tipo array
typedef int tArray[MAX_PROD];

//Declaración funciones version 1
//-Declaración funciones dedicadas al manejo de filas
void mostrarFila(const tArray fila, int tam);
bool esPosValida(int tam, int pos);
bool estaVacia(const tArray fila, int pos);
bool filaOrdenada(tArray fila, int tam);

//-Declaración funciones dedicadas al manejo de archivos
void leerFilaFich(ifstream &fich, tArray fila, int &tam);
void escribirFilaFich(ofstream &fich, const tArray fila, int tam);

//-Declaración funciones dedicadas al manejo de la grua
//bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar);
bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar);
bool grua(tArray fila, tArray aux, int tam, int posIni, int posFin, int posSoltar);
bool esPosibleGrua1Entre(const tArray fila, tArray aux, int tam, int posIni, int posSoltar);
//bool grua1Elemento(tArray fila, tArray aux, int tam, int posIni, int posSoltar);

//-Declaración funciones dedicadas al manejo de la excavadora
int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion);
bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion);
bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion);

//-Declaración funciones relaccionadas con el menu
int menu();
void ejecutarOpc(int opc, tArray fila, int &tam, int &contador);
void ejecutarLeerFichero(tArray fila, int &tam, int &contador);
void ejecutarGuardarFichero(const tArray fila, int tam);
void ejecutarGrua(tArray fila, int tam, int &contador);
void ejecutarExcavadora(tArray fila, int tam, int &contador);

//-Funciones version 1
//-Funciones dedicadas al manejo de filas
void mostrarFila(const tArray fila, int tam) {
	int i;
	cout << "	A continuacion se encuentran los objetos y debajo su posicion.\n\n	|" ;
	for (i = 0; i < tam; i++) {
		if (fila[i] == 0) cout << setw(3) << "|";
		else cout << setw(2) << fila[i] << "|";
	}
	cout << "\n	";
	for (i = 0; i < tam; i++) {
		cout << "---";
		}
	cout << "-\n	|";
	for (i = 0; i < tam; i++) {
		cout << setw(2) << i << "|";
	}
	cout << endl;
}

bool esPosValida(int tam, int pos) {
	bool resultado;
	if (pos >= tam || pos < 0) { resultado = false; }
	else resultado = true;
	return resultado;
}

bool estaVacia(const tArray fila, int pos) { //Esta funcion al final tampoco le daremos mucho uso debido a su funcionamiento tan simple.
	bool resultado;
	if (fila[pos] == PROD_NULO) resultado = true;
	else resultado = false;
	return resultado;
}

bool filaOrdenada(tArray fila, int tam) { //Esta es la funcion exclusiva de la versión 3

	int aux = 0, i = 0;
	bool resultado = true;
	while ((i < tam) && (resultado != false)) {
		if ((fila[i] != PROD_NULO) && (fila[i] != (aux + 1))) resultado = false;
		else if (fila[i] == PROD_NULO) resultado = true;
		else if (fila[i] == (aux + 1)) {
			resultado = true;
			aux++;
		}
		i++;
	}

	return resultado;
}


//-Funciones dedicadas al manejo de archivos
void leerFilaFich(ifstream &fich, tArray fila, int &tam){//Aqui usamos z para sacarnos del bucle cuando encontramos el centinela

	unsigned int posible;
	int  z = 0;
	tam = 0;
	while (z != 1){
		fich >> posible;
		if (posible != CENTINELA) {// Haciéndolo de esta manera impedimos que el -1 quede incluido en nuestra fila
			fila[tam] = posible;
			tam++;
		}
		else z = 1;
	}
}

void escribirFilaFich(ofstream &fich,const tArray fila, int tam) {

	int i;

	for (i = 0; i < tam; i++) {
		fich << fila[i] << " ";
	}

	fich << -1;
}

//-Funciones dedicadas al manejo de la grua
bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar) {	//Aquí revisamos si en las condiciones principales de la grua hay algún error.

	bool resultado;
	if (!esPosValida(tam, posIni)) {
		cout << "	La posicion inicial introducida no esta dentro de lo permitido.\n";
		resultado = false;
	}

	else if (!esPosValida(tam, posFin)){
		cout << "	La posicion final no esta dentro de lo permitido.\n";
		resultado = false;
	}

	else if (posIni > posFin){
		cout << "	No es posible coger los objetos en ese intervalo.\n";
		resultado = false;
	}

	else if (!esPosValida(tam, posSoltar)) {
		cout << "	La posicion soltar introducida no está dentro de lo permitido.\n";
		resultado = false;
	}

	else resultado = true;
	return resultado;
}

bool esPosibleGrua(const tArray fila, tArray aux, int tam, int posIni, int posFin, int posSoltar) { //Aqui se comprueba si el movimiento es posible.

	bool resultado = true;

	while ((posIni <= posFin) && (resultado != false)) {
		if ((fila[posIni] != 0) && (aux[posSoltar] != PROD_NULO)) resultado = false;
		else resultado = true;
		posSoltar++;
		posIni++;
	}
	return resultado;
}

bool grua(tArray fila, tArray aux, int tam, int posIni, int posFin, int posSoltar) {
	bool resultado;
	int inicial = posIni, soltarB = posSoltar;

	while (inicial <= posFin) {
		if (fila[inicial] != PROD_NULO) {
			aux[soltarB] = fila[inicial];
			fila[inicial] = PROD_NULO;
		}
		inicial++;
		soltarB++;
	}

	while (posSoltar <= soltarB) {
		fila[posSoltar] = aux[posSoltar];
		posSoltar++;
	}

	return true;
}

/*
Aquí comantada se encuentra la funcion original de la grúa que aunque no la hayamos vuelto a utilizar, la dejo ahí como reliquia de lo que fue.
bool grua1Elemento(tArray fila, tArray aux, int tam, int posIni, int posSoltar) {
	int inicial;
	bool resultado;
	inicial = fila[posIni];
	if (fila[posIni] != PROD_NULO)  {
		fila[posSoltar] = fila[posIni];
		fila[posIni] = PROD_NULO;
		if ((fila[posIni] != 0) && (fila[posSoltar] != inicial)) resultado = false;
		else resultado = true;
	}
	else resultado = true;
	return resultado;

}
*/
//-Funciones dedicadas al manejo de la excavadora.
int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion) {
	int numEspacios = 0, proxPosicionLibre, posIniIni;
	posIniIni = posIni;
	posIni = posIni + direccion;
	while (esPosValida(tam, posIni) && (estaVacia(fila, posIni))) {
			numEspacios = numEspacios + direccion;
			posIni = posIni + direccion;
		}
	proxPosicionLibre = posIniIni + numEspacios + direccion;
	return proxPosicionLibre;

}

bool excavadora1Dir(tArray fila, int tam, int posIni, int direccion) {
	int proxPosOcupada, posSiguiente, contador = 0;
	bool resultado;
	posSiguiente = posIni + direccion;
	proxPosOcupada = posHuecoLibreDir(fila, tam, posIni, direccion);
	while ((proxPosOcupada == posSiguiente) && esPosValida(tam, posSiguiente))
		{
			posIni = posIni + direccion;
			proxPosOcupada = posHuecoLibreDir(fila, tam, posIni, direccion);
			posSiguiente = posIni + direccion;
			contador++;
		}
	if (esPosValida(tam, posSiguiente)) {
		while (contador >= 0) {
			fila[posSiguiente] = fila[posIni];
			fila[posIni] = PROD_NULO;
			contador--;
			posIni -= direccion;
			posSiguiente -= direccion;
		}
			resultado = true;
		}
	else resultado = false;
	return resultado;
}

bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion){
	bool resultado;

	if (!esPosValida(tam, posIni)) {
		cout << "	La posicion introducida no es correcta, no se produce ninguna accion\n";
		resultado = false;
	}

	else if ((direccion != -1) && (direccion != 1)) {
		cout << "	La direccion introducida no es correcta, no se produce ninguna accion.\n	";
		resultado = false;
	}

	else {
		while (numDespla >= 0){ //En este caso a diferencia de la grúa, puedo sacarle provecho a la excavadora básica para esta versión.
			excavadora1Dir(fila, tam, posIni, direccion);
			posIni += direccion;
			numDespla--;
		}
		cout << "	Se ha realizado la accion.\n";
		resultado = true;
	}

	return resultado;
}

//Funciones relacionadas con el menu
int menu(){//cambiar

	int opcion;

	cout << "\nElije la opcion que quieras utilizar de las siguientes\n ";
	cout << "\n		Opcion 1: Cargar fila. \n";
	cout << "\n		Opcion 2: Guardar fila en un fichero.\n";
	cout << "\n		Opcion 3: Ejecutar Grua.\n";
	cout << "\n		Opcion 4: Ejecutar Excavadora.\n";
	cout << "\n		Opcion 0: Salida.\n\n  ";

	cin >> opcion;
	while (opcion > 4) {
		cout << "	La opcion elegida no existe.\n	Elige una de las que existen. \n";
		cout << "\n		Opcion 1: Cargar fila. \n";
		cout << "\n		Opcion 2: Guardar fila en un fichero.\n";
		cout << "\n		Opcion 3: Ejecutar Grua.\n";
		cout << "\n		Opcion 4: Ejecutar Excavadora.\n";
		cout << "\n		Opcion 0: Salida.\n\n  ";
		cin >> opcion;
	}
	return opcion;
}

void ejecutarOpc(int opc, tArray fila, int &tam, int &contador){

		switch (opc)
		{
			case 1:
				ejecutarLeerFichero(fila, tam, contador);
				break;
			case 2:
				ejecutarGuardarFichero(fila, tam);
				break;
			case 3:
				ejecutarGrua(fila, tam, contador);
				break;
			case 4:
				ejecutarExcavadora(fila, tam, contador);
				break;
			default:
				cout << "	Esa opcion no existe. Elige otra opcion.\n";
				break;
		}
		mostrarFila(fila, tam);
		if (contador == 0) cout << "	No has realizado ningun movimiento de momento.\n";
		else cout << "	De momento has realizado " << contador << " movimiento(s).\n";
		if (filaOrdenada(fila, tam)) cout << "	ENHORABUENA! Ya has ordenado la fila.\n\n";
		else cout << "	La fila aun no esta ordenada.\n\n";

		system("pause");
}

void ejecutarLeerFichero(tArray fila, int &tam, int &contador){

	string nombrefich;
	ifstream fich;
	cout << "	Escribe el nombre del archivo a cargar\n	";
	cin >> nombrefich;
	fich.open(nombrefich);
	if (fich.is_open()){

		leerFilaFich(fich, fila, tam);
		fich.close();
		cout << "	La fila ha sido cargada y guardada\n";
		contador = 0;
	}

	else cout << "	  No se ha podido cargar la fila.\n";

}

void ejecutarGuardarFichero(const tArray fila, int tam){

	string nombrefich;
	ofstream fich;
	cout << "	 Escribe el nombre del fichero en el que quieres guardar la fila.\n	";
	cin >> nombrefich;
	fich.open(nombrefich);
	if (fich.is_open()){

		escribirFilaFich(fich, fila, tam);
		cout << "	El fichero ha sido creado como '"<< nombrefich <<"'.\n'";
		fich.close();
	}
	else cout << "	El archivo no se pudo crear. \n";
}

void ejecutarGrua(tArray fila, int tam, int &contador) {

	int posIni, posFinal, posSoltar;

	cout << "	De donde quieres partir para coger los objetos?\n	";
	cin >> posIni;
	cout << "	Donde terminas de cogerlos?\n	";
	cin >> posFinal;
	cout << "	Donde quieres soltarlo?\n	";
	cin >> posSoltar;

	if (sonPosicionesPosiblesGrua(tam, posIni, posFinal, posSoltar)) {
		int inicial;
		tArray aux; //Dado que no se me ocurria como hacer las comprobaciones de la grua sin utilizar un array aux, he aprovechador el que iba a crear
		inicial = posIni;//para el movimiento de manera que me valiese tanto para el comprobador como para la grua en si.
		for (int contador = 0; contador < tam; contador++) {
			if ((contador == posIni) && (posIni <= posFinal)) {
				aux[contador] = PROD_NULO;
				posIni++;
			}
			else aux[contador] = fila[contador];
		}
		posIni = inicial;

		if (esPosibleGrua(fila, aux, tam, posIni, posFinal, posSoltar)) {
			if (!grua(fila, aux, tam, posIni, posFinal, posSoltar)) cout << "	Ha habido un error en el proceso.\n";
			else {
				cout << "	Todo ha salido a pedir de boca.\n";
				contador++;
				}
			}
		else cout << "	No se ha podido realizar porque aplastarias algun objeto.\n";
	}
	else cout << "	No se ha podido realizar, debido a que tus condiciones no eran validas.\n";

}

void ejecutarExcavadora(tArray fila, int tam, int &contador) {

	int posIni, direccion, numDespla;
	cout << "	Donde quieres usar la excavadora?\n	";
	cin >> posIni;
	cout << "	Introduce la direccion (-1 izquierda, 1 derecha).\n	";
	cin >> direccion;
	cout << "	Indica el numero de veces que quieres usar la excavadora.\n	";
	cin >> numDespla;
	numDespla--;
	if (numDespla < 0) cout << "	El numero de desplazamientos es 0 asi que no se hace nada.\n";
	else {
		if (!excavadora(fila, tam, posIni, numDespla, direccion)) cout << "	Ha habido un error...\n";
		else {
			cout << "	Todo ha ido perfecto.\n";
			contador++;
		}
	}
}


int main(){

	//Tanto la inicialización de fila a 0 como tam a 20 está puesto para que en caso de que no se pueda inicializar un fichero muestre algo decente.
	tArray fila = { 0 };
	int opcion, tam = 20, contMov = 0;
	cout << "Bienvenido.\n\n";

	opcion = menu();
	while (opcion != 0){
		ejecutarOpc(opcion, fila, tam, contMov);
		opcion = menu();
	}

	cout << "Adios, hasta pronto. \n";
	system("pause");

}
