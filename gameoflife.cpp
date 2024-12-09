#include <iostream>
#include <string>
#include <cstdlib>     //sirve para limpiar la pantalla
#include<ctime>      //random
#include<unistd.h>      //para lograr el parpadeo  (intervalo de tiempo)
using namespace std;
//variables
const int x= 20;//tamaño
const int generaciones_maximas=100;
const char celula_viva='O';
const char celula_muerta=' ';
int key ;

//prototipos de Funciones juego de la vida
void tablerodejuego(int tablero[x][x]);
void zona_objetivo(int objetivo[x][x]);
void mostrar_tablero(int tablero[x][x],int objetivo[x][x]);
void nueva_generacion(int alctual[x][x], int nuevageneracion[x][x]);
int contador_vecinos(int tablero[x][x], int fila, int columna);
bool objetivo_cumplido(int tablero[x][x], int objetivo[x][x]);
//prototipo de funciones aventura de texto
void introduccion();
void bosque_encantado();
void cueva_misteriosa();
void searchexit();
void montañas();
void resolver_acertijo(int &vidas, bool &exito);

int main() {
    // Tableros de trabajo y objetivo
    int tablero[x][x]={0};
    int nuevageneracion[x][x]={0};
    int objetivo[x][x]={0};
    int generacion=0;

    // Inicializacion
    srand(time(0));
   tablerodejuego(tablero);
   zona_objetivo(objetivo);


    while (generacion<generaciones_maximas) {
        cout<<"Generacion: "<<generacion+1<<endl;


        mostrar_tablero(tablero,objetivo);

        if (objetivo_cumplido(tablero,objetivo)) {
            cout<<"!Objetivo alcanzado en "<< generacion+1 <<" generaciones!"<<endl;

              srand(time(NULL)); // Inicializa la semilla aleatoria

    cout << " " << endl;
    cout << "=========================================" << endl;
    cout << " !Bienvenido a un Mundo Paralelo de Aventuras! " << endl;
    cout << "=========================================" << endl;

    introduccion();
    return 0;








        }
         usleep(100000);
    system("cls");

        nueva_generacion(tablero,nuevageneracion);

        // Copiar la nueva generacion al tablero actual
        for (int i=0;i<x;++i)
            for (int j= 0;j<x;++j)
               tablero[i][j]=nuevageneracion[i][j];
           // 0.4 segundos
        generacion++;
    }

    if (generacion==generaciones_maximas) {
        cout<<"No se logro poblar la zona objetivo en el limite de generaciones."<<endl;
    }
    return 0;






}
//funciones Juego de la vida
// Inicializa el tablero
void tablerodejuego(int tablero[x][x]) {
    for (int i=0;i<x;i++) {
        for (int j=0;j<x;j++) {
            tablero[i][j]= rand()%2; // 50% vivas, 50% muertas
        }
    }
}

   //para marcar con "+" el objetivo
void zona_objetivo(int objetivo[x][x]) {
    for (int i=0;i<x;++i) {
        for (int j=0;j<x;++j) {
            objetivo[i][j]=0; // Inicialmente todas las celdas del objetivo estan vacias
        }
    }
// region aleatoria
    int fila= rand()%x;
    int columna= rand()%x;
    int ancho= 2;
    int alto= 2;

    for (int i=fila;i<fila+alto && i<x;i++) {
        for (int j =columna; j <columna+ancho &&j<x;j++) {
            objetivo[i][j] = 1; // Marcar esta celda como parte del objetivo
        }
    }
}
//mostrar los o y los + y los " "
void mostrar_tablero(int tablero[x][x],int objetivo[x][x]) {
    for (int i=0;i<x;i++) {
        for (int j=0;j<x;j++) {
            if (objetivo[i][j]==1 && tablero[i][j]==1) {
                cout<<"*"; // Celula viva en la zona objetivo
            } else if(objetivo[i][j]==1){
                cout<<'+'; // Zona objetivo no poblada
            } else {
               cout<<(tablero[i][j] ? celula_viva:celula_muerta);
            }
        }
        cout<<endl;
    }
    cout<<string(50,'-') <<endl; // Separador
}

// las reglas del Juego de la Vida
void nueva_generacion(int actual[x][x], int siguientegen[x][x]) {
    for (int i=0;i<x;++i) {
        for (int j=0;j<x;j++) {
            int vecinos=contador_vecinos(actual,i,j);
            // Reglas del Juego de la Vida
            if (actual[i][j]==1){ // 1 representa a la celula viva
                siguientegen[i][j] = (vecinos==2 || vecinos==3) ? 1 : 0;
            } else { // Celda muerta
               siguientegen[i][j] = (vecinos==3) ? 1 : 0;
            }
        }
    }
}
// Cuenta los vecinos vivos de una celda
int contador_vecinos (int tablero[x][x],int fila,int columna) {
    int contar = 0;
    for (int i=-1;i<=1;++i) {
        for (int j=-1;j<=1;++j){
            if (i == 0 && j==0) continue; // Ignorar celda
            int r=fila + i, c = columna + j;
            if (r>=0 && r<x && c>=0 && c<x) {
                contar += tablero[r][c];
            }
        }
    }
    return contar;
}

// Comprueba si la zona objetivo esta completamente poblada
bool objetivo_cumplido(int tablero[x][x], int objetivo[x][x]) {
    for (int i=0;i<x;i++) {
        for (int j=0;j<x;j++) {
            if (objetivo[i][j]==1 && tablero[i][j]==0) {
                return false; // Zona objetivo no completamente poblada
            }
        }
    }
    return true;
}


//funciones Aventura de texto
void introduccion() {
    cout<<"Despiertas en un mundo Paralelo"<<endl;
    cout<<"Debes alcanzar el castillo del Sabio para regresar a tu realidad."<<endl;
    cout<<"¿ Por donde quieres comenzar tu aventura?"<<endl;
    cout<<"1.Ingresar al bosque encantado."<<endl;
    cout<<"2.Explorar la cueva misteriosa."<<endl;
    cout<<"3.Explorar las cordilleras de gran extensión" << endl;
    cout<<"4.Intentas buscar una salida" << endl;

    int eleccion;
    cin >> eleccion;
    switch (eleccion) {
        case 1:
            bosque_encantado();
        break;
        case 2:
            cueva_misteriosa();
        break;
        case 3:
            montañas();
            break;
        case 4:
            searchexit();
            break;

        default:
        cout <<"Decisión inválida. El juego termina aquí."<< endl;
    }
}

void elegir () {
    cout << " "<<endl;
    cout << "Aparece una persona , Eliges salvarla?" << endl;
    cout << "1.Salvar"<<endl;
    cout << "2.Denegar"<<endl;
    cin >> key;
    if(key == 1 || key == 2) {


        cout << "Recordaras esta opcion mas adelantee..."<< endl;

    }
    cout << "Esta opcion no esta establecida , vuelve a intentar!"<< endl;
    return ;
}

void bosque_encantado() {
    int vidas=3;
    bool exito=false;

    cout<<"Has entrado en el bosque encantado. "<<endl;
    elegir();
    cout<<"Te encuentras con un nomo que bloquea tu camino." << endl;

    cout << "El nomo llama a sus hermanos y todos juntos te amenazan y te obligan a contestar un acertijo" << endl;
    resolver_acertijo(vidas, exito);


    if (exito) {
        cout <<"El nomo te felicita a regañadientes , finalmente no te deja pasar y te activa una trampa que se encontraba en el suelo "<<endl;
        cout << "Caes varios metros en el hueco....."<<endl;
        cout << "Te das cuenta que no eres la primera persona en pasar por ese lugar...." << endl;
        cout << "Te acercas a la persona que se encuentra encerrada , el te comenta que hay una forma de escapar pero debido a su vejez nunca quiso intentarlo."<<endl;
        cout << "A cambio debes ayudarlo a completar una serie de preguntas que ya se te hacen familiares." << endl;
        resolver_acertijo(vidas, exito);
        if(exito) {
            cout << "Wow el viejo se sorprende y accede a ayudarte."<<endl;
            cout << "El viejo te comenta que con varios palos que venian cayendo a lo largo de los años pudo construir una herramienta" << endl;
            cout << "La usas para trepar el hueco y logras escapar despidiendote del viejo "<<endl;
            cout << "Te das cuenta que los nomos defendian la entrada principal al cañon en el fondo ves una cadena montañosa." << endl;
            cout << "Piensas que hubiera sido mas sencillo ir por ahi , ries y logras escapar del mundo paralelo " << endl;
            cout << key << endl;
            if(key == 1 ) {
                cout << "Si escogiste salvar a esa persona , logras escapar con ella y conviven una vida pacifica en el campo" << endl;
            }else if (key == 2 ) {
                cout << "Si no llegaste a salvar a esa persona , en tus sueños estara presente recordandote lo egoista que fuiste "<< endl;
            }

        }else {
            cout << "El viejo se siente insatisfecho y se niega a ayudarte , mueres de hambre, Perdiste!" << endl;
        }
    }else {
        cout <<"Has perdido todas tus vidas.Te quedas atrapado en el bosque para siempre."<<endl;
    }
}




void cueva_misteriosa() {
    int vidas =3;
    bool exito=false;

    cout << "Te adentras en la cueva oscura y húmeda. Escuchas ruidos extraños." << endl;
    cout << "De repente, un espiritu aparece y te lanza un desafio." << endl;

    resolver_acertijo(vidas, exito);

    if (exito) {
        cout<<"El espiritu desaparece, dejando un camino libre hacia el castillo del Sabio."<<endl;
        cout<<"Una vez en el castillo del sabio , el te comenta que conoce una salida pero antes" << endl;
        cout << "Debes resolver un acertijo .....";
        resolver_acertijo(vidas, exito);
        if(exito) {
            cout << "El sabio te felicita por tu extenso conocimiento"<<endl;
            cout << "Te guia a la entrada del largo del camino" << endl;
            cout << "Despues de todo el camino fue muy tranquilo ,al final del camino te das cuenta que no hay mas por donde continuar."<<endl;
            cout << "Es un gran agujero! - exclamas , lograste escapar del mundo paralelo" << endl;
        }else {
            cout << "El sabio detesta la ignorancia , te encierra en su calabozo.Perdiste!" << endl;
        }
    } else {
        cout<<"Has perdido todas tus vidas. La cueva colapsa, atrap�ndote para siempre."<<endl;
    }
}
void montañas() {
    int vidas = 3;
    bool exito=false;
    cout << "Empiezas a subir la montaña ,te empiezas a cansar ,el frio aumenta..." << endl;
    cout << "De pronto ves a un yeti acercarse y te desafia a un duelo." << endl;
    resolver_acertijo(vidas, exito);
    if (exito) {
        cout<<"El yeti te deja avanzar... te adentras mas alto "<<endl;
        cout<<"Debido a la altura necesitas oxigeno , para tu fortuna " << endl;
        cout<<"Encuentras una casilla con oxigeno , pero para acceder debes resolver un acertijo"<< endl;
        resolver_acertijo(vidas, exito);
        if(exito) {
            cout << "Con el oxigeno consigues seguir avanzando..."<<endl;
            cout << "Llegaste a la cima , logras observar el hermoso paisaje de este mundo tan raro." << endl;
            cout << "A lo lejos logras observar un gran cañon , posiblemente sea la salida que buscas..."<<endl;

        }else {
            cout << "Moriste debido al frio excesivo , vuelve a intentarlo campeon!" << endl;
        }
    } else {
        cout<<"Has perdido todas tus vidas. La montaña colapsa, atrap�ndote para siempre."<<endl;
    }

}
void searchexit() {
    cout << "Intentas buscar una salida        .........."<< endl;
    cout << "............................................" << endl;
    cout << "No encuentras nada ...."<< endl;
    cout << "Sigues buscando - te acercas a un agujero ..."<< endl;
    cout << "Fuiste empujado por un desconocido,pierdes todas tus vidas."<< endl;
}


void resolver_acertijo(int &vidas, bool &exito) {
    string respuesta;
    int intentos=3;

    // Acertijos aleatorios
    string acertijos[]={
        "Soy alto cuando soy joven y bajo cuando soy viejo. ¿Qué soy? (responde: vela)",
        "Tengo ciudades, pero no casas.Tengo montañas,pero no árboles.Tengo agua,pero no peces.¿Qué soy?(responde: mapa)",
        "Cuanto más me quitas, más grande me vuelvo. ¿Qué soy? (responde: agujero)",
        "Soy ligero como una pluma, pero ni el hombre más fuerte puede sostenerme por mucho tiempo. ¿Qué soy? ",
        "Tiene agujas pero no pincha, tiene números pero no cuenta. ¿Qué es?"
    };
    string respuestas[]={"vela","mapa","agujero","aliento","reloj"};

    // Selecci�n de un acertijo aleatorio
    int indice = rand() % 3;

    while (intentos > 0) {
        cout<<"Acertijo: "<<acertijos[indice]<<endl;
        cout<<"Tienes "<<intentos<<" intento(s) restante(s). Escribe tu respuesta: ";
        cin>>respuesta;

        if(respuesta==respuestas[indice]){
            cout<<"Correcto.Has superado el acertijo."<<endl;
            exito=true;
            return;
        }else{
            intentos--;
            vidas--;
            cout <<"Incorrecto. Pierdes una vida. Te quedan "<<vidas<<" vidas."<<endl;
        }
    }

    exito=false;
}