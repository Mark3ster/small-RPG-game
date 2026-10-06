#include <iostream>
#include <string>
#include <conio.h> // para usar getch()
#include <ctime>
using namespace std;

const int TAMANNO_TIENDA = 6;   //si hacese la tienda más grande (añades mas cosas), cambia ese numero

void crearFichaJugador();
void mostrarInvent(string objetosTienda[TAMANNO_TIENDA], int inventario[TAMANNO_TIENDA]);   //tiene q tener acceso a los objetosdeljuego y al inventario
void iniciartienda(string objetosTienda[TAMANNO_TIENDA], int inventario[TAMANNO_TIENDA], int monedas);    //tienda,   inventario, monedas
void combate(int vidaTuya, int vidaMonstruo, int vidasJugador, int monedas, int inventario[], int danoJugador);
void mostrarCombate(int vidaTuya, int vidaMonstruo, int numero);
void combateBoss(int vidaTuya, int vidaBoss, int inventario[], int danoJugador, bool finJuego);
void mostrarboss(int vidaTuya, int vidaBoss);



int main()
{
    char ch = 0; // para el wasd
    int coord_x = 2; // posición inicial del jugador (X)
    int coord_y = 1; // posición inicial del jugador (Y)
    int monedas = 0;
    string objetosTienda[] = { "pocion(curacion)", "pocion(danno)", "espada", "tenedor", "madera", "piedra" };  // array de los objetos de la tienda
    int inventario[TAMANNO_TIENDA] = {}; //empezamos vacio (representa q tienes de cada cosa objetostienda
    int elecctienda = 0;
    bool salir = false;
    int eleccion = 0;
    char confirmarelecc;  //para dar opcion de elegir (s/n)
    bool finJuego = false;
    int vidaMonstruo = 100;
    int vidaTuya = 100;
    int vidaBoss = 150;
    int vidasJugador = 3; // Vidas generales del jugador (como en mario bros)
    int danoJugador = 40;


    char mapa[30][40] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', 'P', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', '#', ' ', 'O', ' ', '#', '#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', 'T', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', '#', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', 'O', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', ' ', '#', '#', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', 'F', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', '#', ' ', ' ', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', 'O', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', 'O', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', '#', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };

    crearFichaJugador();    //empiezas a crear a tu personaje

    while (!finJuego)   //mientras fin de juego sea true
    {

        if (vidasJugador <= 0) //   si las vidas generales llegna a 0, se terminaría el juego (falta añadir q se termine el juego)
        {
            cout << "\nHas perdido todas tus vidas! Fin del juego" << endl;
            break;  // Termina el juego si no tienes vidas
            finJuego = true;
        }

        // Redibujar el mapa
        system("cls"); // Limpiar la pantalla

        if (inventario[1] > 0) { // si compras una pocion(curacion)se te suma uno a la vida general
            vidasJugador += 1;
        }

        cout << "Monedas: " << monedas << " | Vidas restantes: " << vidasJugador << endl;

        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 30; j++)
            {
                cout << mapa[i][j];
            }
            cout << endl;
        }

        ch = _getch(); // Lee la entrada del usuario

        // Calcular nuevas coordenadas en el mapa para P en funcion de (wasd)
        int nueva_x = coord_x;
        int nueva_y = coord_y;

        switch (ch)
        {
        case 'W':
        case 'w':
            nueva_y = coord_y - 1;
            break;
        case 'A':
        case 'a':
            nueva_x = coord_x - 1;
            break;
        case 'S':
        case 's':
            nueva_y = coord_y + 1;
            break;
        case 'D':
        case 'd':
            nueva_x = coord_x + 1;
            break;
        case 'I':   //si pulsas esta tecla se abre el inventario
        case 'i':
            mostrarInvent(objetosTienda, inventario);
            break;
        }

        // Si la nueva posicion de P es un esapcio libre (' '), P puede moverse a esa nueva posicion
        if (mapa[nueva_y][nueva_x] == ' ')
        {
            // Mover jugador
            mapa[coord_y][coord_x] = ' '; // Limpia la posición anterior a P (la deja libre otra vez)
            coord_x = nueva_x;
            coord_y = nueva_y;
            mapa[coord_y][coord_x] = 'P'; // Dibuja el jugador en la nueva posición 
            combate(vidaTuya, vidaMonstruo, vidasJugador, monedas, inventario, danoJugador);
        }

        if (mapa[nueva_y][nueva_x] == 'T')
        {
            mapa[coord_y][coord_x] = ' ';
            coord_x = nueva_x;
            coord_y = nueva_y;
            mapa[coord_y][coord_x] = 'P';
            iniciartienda(objetosTienda, inventario, monedas);
        }

        if (mapa[nueva_y][nueva_x] == 'O') // recoges monedas y desaparecen del mapa(al ponerse P, O se borra)
        {
            mapa[coord_y][coord_x] = ' '; // Limpia la posición anterior a P(la deja libre otra vez)
            coord_x = nueva_x;
            coord_y = nueva_y;
            mapa[coord_y][coord_x] = 'P'; // Dibuja el jugador en la Posicion de O 
            monedas += 20;
        }

        if (mapa[nueva_y][nueva_x] == 'F') // al ponerse mover P a F, se termina el juego
        {
            mapa[coord_y][coord_x] = ' '; // Limpia la posición anterior (la deja libre otra vez)
            coord_x = nueva_x;
            coord_y = nueva_y;
            mapa[coord_y][coord_x] = 'P';
            combateBoss(vidaTuya, vidaBoss, inventario, danoJugador, finJuego);


        }
    }
    cout << "\nSe ha terminado el Juego, enhorabuena" << endl;
}
void crearFichaJugador() {
    // Variables
    string nombre = "", origen_str = "", profesion_str = "";
    int origen = 0, profesion = 0;
    int estadisticas[3] = { 0, 0, 0 }; // Array para fuerza, destreza, magia
    int estadisticasTotales[3] = { 0, 0, 0 };
    bool salir = false;

    // Arrays de opciones de origen, profesión y estadísticas
    string nombresOrigenes[6] = { "Elfo", "Enano", "Orco", "Humano", "Ciclope", "Gnomo" };
    string nombresProfesiones[8] = { "Guerre.", "Mago", "Arquero", "Esclavo", "Espia", "Marine.", "Ladron", "Sacerd." };
    string nombresEstadisticas[3] = { "Fuerza", "Destreza", "Magia   " };

    // Array dos dimensiones modificadores profesión 8 profesiones, 3 estadísticas (fuerza, destreza, magia (en este orden))
    float modProfesiones[8][3] = {
        {0.3, 0.05, -0.2},  // Guerrero
        {-0.3, 0.1, 0.2},   // Mago
        {0.1, 0.3, -0.1},   // Arquero
        {0.05, 0.05, 0.05}, // Esclavo
        {0.05, 0.5, -0.1},  // Espia
        {0.1, 0.2, -0.1},   // Marinero
        {-0.2, 0.6, -0.1},  // Ladron
        {-0.15, 0.1, -0.1}  // Sacerdote
    };
    // Array dos dimensiones modificadores origen 6 origenes y 3 estadísticas (fuerza, destreza, magia (en este orden))
    float modOrigenes[6][3] = {
        {-0.1, 0.2, 0.3},   // Elfo
        {0.3, 0.1, -0.2},   // Enano
        {0.4, 0.1, -0.3},   // Orco
        {0.1, 0.1, 0.1},    // Humano
        {0.5, -0.2, -0.4},  // Ciclope
        {-0.2, 0.3, 0.2}    // Gnomo
    };

    srand(time(0)); // Inicializa la semilla del generador de números aleatorios

    // Bucle del menú principal
    while (!salir)
    {
        system("cls"); // Limpia la consola

        cout << "\n\tFICHA FINAL DE JUGADOR" << endl;
        cout << "\n\tNombre: " << nombre;
        cout << "\n\tOrigen: " << origen_str;
        cout << "\n\tProfesion: " << profesion_str;

        // Calcula las estadísticas totales con modificadores de profesión
        for (int i = 0; i < 3; i++)
        {
            estadisticasTotales[i] = estadisticas[i] + (int)(estadisticas[i] * modProfesiones[profesion][i]);
        }

        cout << "\n\tEstadisticas (\tTirada Base + \tMod Origen + \tMod Profesion --> \tTotal): \n";
        for (int i = 0; i < 3; i++)
        {
            cout << "\n\t" << nombresEstadisticas[i] << ": \t" << estadisticas[i]
                << "  \t\t" << modOrigenes[origen][i] * estadisticas[i]
                << "  \t\t" << modProfesiones[profesion][i] * estadisticas[i]
                << "  \t\t\t" << estadisticasTotales[i];
        }

        // Menú de opciones
        cout << "\n\n\t\tMENU";
        cout << "\n1.- Cambiar nombre";
        cout << "\n2.- Cambiar origen";
        cout << "\n3.- Cambiar profesion";
        cout << "\n4.- Hacer tiradas aleatorias de las estadisticas";
        cout << "\n5.- Ver tabla de modificadores de profesion";
        cout << "\n6.- Ver tabla de modificadores de origen";
        cout << "\n7.- Salir de la creación de la ficha\n";
        cout << "\nElige una opcion: ";

        int eleccion;
        cin >> eleccion;
        cin.ignore(); // Para evitar problemas con el salto de línea

        switch (eleccion)
        {
        case 1:
            cout << "Cual es tu nombre?" << endl;
            getline(cin, nombre);
            break;

        case 2:
            cout << "\nCual es tu origen?" << "\n\n";
            for (int i = 0; i < 6; i++)
            {
                cout << i + 1 << "._ " << nombresOrigenes[i] << endl;
            }
            cin >> origen;
            origen--;

            if (origen < 0 || origen >= 6)
            {
                cout << "\nSeleccion no valida, repite tu eleccion" << endl;
            }
            else
            {
                origen_str = nombresOrigenes[origen];
            }
            break;

        case 3:
            cout << "\n¿Que profesion quieres?" << endl;
            for (int i = 0; i < 8; i++)
            {
                cout << i + 1 << "._ " << nombresProfesiones[i] << endl;
            }
            cin >> profesion;
            profesion--;

            if (profesion < 0 || profesion >= 8)
            {
                cout << "\nSeleccion no valida" << endl;
            }
            else
            {
                profesion_str = nombresProfesiones[profesion];
            }
            break;

        case 4:
            // Genera números aleatorios para las estadísticas
            for (int i = 0; i < 3; i++)
            {
                estadisticas[i] = (rand() % 51) + 50;
            }
            cout << "\nTiradas de estadisticas generadas" << endl;
            break;
        case 5:

            cout << "MODIFICADORES DE PROFESION" << endl;
            cout << "\t";

            for (int estadisticas = 0; estadisticas < 3; estadisticas++)
            {
                cout << "\t\t" << nombresEstadisticas[estadisticas];


            }
            cout << "\n";   //  para que no se junten los nombres de estadisticas con los modificadores de profesion ( para ordenar la tabla) super importante


            for (int prof = 0; prof < 8; prof++)
            {
                cout << nombresProfesiones[prof];
                for (int estadisticas = 0; estadisticas < 3; estadisticas++)
                {
                    cout << "\t\t\t" << modProfesiones[prof][estadisticas];
                }
                cout << endl;
            }

            break;
        case 6:
            cout << "MODIFICADORES DE ORIGEN" << endl;
            cout << "\t";

            for (int origenes = 0; origenes < 3; origenes++)
            {
                cout << "\t\t" << nombresEstadisticas[origenes];


            }
            cout << "\n";   //  para que no se junten los nombres de estadisticas con los modificadores de profesion ( para ordenar la tabla) super importante


            for (int orig = 0; orig < 6; orig++)
            {
                cout << nombresOrigenes[orig];
                for (int origenes = 0; origenes < 3; origenes++)
                {
                    cout << "\t\t\t" << modOrigenes[orig][origenes];
                }
                cout << endl;
            }

            break;
        case 7:
            salir = true;
            break;

        default:
            cout << "\nSeleccion no valida. Repite la eleccion" << endl;
        }

        if (!salir)
        {
            cout << "\nPresiona ENTER para continuar";
            cin.ignore();
        }
    }



}
void iniciartienda(string objetosTienda[TAMANNO_TIENDA], int inventario[TAMANNO_TIENDA], int monedas)
{
    bool salir = false;
    int elecctienda = 0;
    int eleccion = 0;
    char confirmarelecc;
    int precios[] = { 50, 75, 200, 10, 5, 20 }; // Precios de los objetos (esta en orden)

    while (!salir)
    {
        system("cls");
        // Mostrar la tienda
        cout << "\t\t\t\tTIENDA" << endl;
        cout << "-----------------------------------------------------------------------------------------------------" << endl;
        cout << "-----------------------------------------------------------------------------------------------------" << endl;

        // Opciones del menú de la tienda
        cout << "\n" << endl;
        cout << "\t" << "-----------------" << endl;
        cout << "\t" << "|" << "1. - Comprar" << "    |" << endl;
        cout << "\t" << "|" << "2. - Salir" << "      |" << endl;
        cout << "\t" << "-----------------" << endl;

        cout << "\n\nEleccion: ";
        cin >> eleccion;
        cin.ignore();
        cout << "Monedas disponibles: " << monedas << endl;

        switch (eleccion)
        {
        case 1: // Ver objetos a la venta en la tienda
            cout << "\nObjetos disponibles en la tienda:" << endl;
            for (int i = 0; i < 6; i++)
            {
                cout << i + 1 << ". " << objetosTienda[i] << " - " << precios[i] << " monedas" << endl; //te enseña todos los objetos de la tienda (i+1 pq asi no empieza desde 0)
            }
            cout << "0. Salir" << endl;
            cout << "Que quieres hacer? " << endl;
            cin >> elecctienda;
            if (elecctienda > 0 && elecctienda <= 6) // Validar selección dentro del rango de objetos
            {
                elecctienda = elecctienda - 1; // Restar 1 porque el array comienza en 0
                cout << "Has seleccionado: " << objetosTienda[elecctienda] << " que cuesta " << precios[elecctienda] << " monedas." << endl;
                cout << "Tienes " << monedas << " monedas. Quieres comprarlo? (s/n): ";

                cin >> confirmarelecc;   //viene del char confirmar;

                if (confirmarelecc == 's' || confirmarelecc == 'S')
                {
                    if (monedas >= precios[elecctienda])
                    {
                        monedas -= precios[elecctienda];
                        inventario[elecctienda]++;
                        cout << "Ahora tienes " << inventario[elecctienda] << " " << objetosTienda[elecctienda] << " en tu inventario." << endl;
                    }
                    else
                    {
                        cout << "No tienes suficientes monedas para comprar este objeto" << endl;
                    }
                }
                else //opcion N o n o cualquier otra cosa
                {
                    cout << "Has cancelado la compra." << endl;
                }
                break;
        case 2: // Opción para salir
            salir = true;
            break;
        default:
            cout << "\nSeleccion no valida. Repite la eleccion." << endl;
            }
            if (!salir)
            {
                cout << "\nPresiona ENTER para continuar";
                cin.ignore();
            }
        }
    }// Fin del while
}
void mostrarInvent(string objetosTienda[TAMANNO_TIENDA], int inventario[TAMANNO_TIENDA])
{
    system("cls");
    int eleccion = 0;
    bool salir = false;

    while (!salir)
    {

        //  TE APARECE EL INVENTARIO
        cout << "\t\t\t\tINVENTARIO DEL JUGADOR" << endl;
        cout << "-----------------------------------------------------------------------------------------------------" << endl;
        cout << "-----------------------------------------------------------------------------------------------------" << endl;

        //  OPCIONES DETRO DEL INVENTARIO
        cout << "\n" << endl;
        cout << "\t" << "-----------------" << endl;
        cout << "\t" << "|" << "1. - Ver" << "       |" << endl;
        cout << "\t" << "|" << "2. - Salir" << "      |" << endl;
        cout << "\t" << "-----------------" << endl;

        cout << "Decision: ";
        cin >> eleccion;
        cin.ignore();

        switch (eleccion)
        {
        case 1: // ver todo el inventario
            for (int i = 0; i < TAMANNO_TIENDA; i++)
            {
                cout << objetosTienda[i] << ": " << inventario[i] << endl; // Se ve cada objeto y la cantidad que tienes de cada
            }
            break;
        case 2: // salir del inventario
            salir = true;
            break;
        default:
            cout << "\nSeleccion no valida. Repite la eleccion" << endl;
        }
        if (!salir)
        {
            cout << "\nPresiona ENTER para continuar";
            cin.ignore();
        }
    }   //fin del while
}// fin void
void mostrarCombate(int vidaTuya, int vidaMonstruo, int numero) //muestra al monstruo y barras de vida
{

    system("cls");
    cout << "\t\t\t\tCOMBATE" << endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    if (numero < 3) {   // este numero es una variable en la funcion combate para la que "trabaja" esta funcion mostrarcombate, así no hay problemas con los personajes
        // RANA
        cout << "      (')-=-(')" << endl;
        cout << "    __(   \"   )__" << endl;
        cout << "   / _/'-----'\\_ \\" << endl;
        cout << "___\\ \\     // //___" << endl;
        cout << ">____)/_\\---/_\\(____<" << endl;
    }
    else if (numero < 5) {
        cout << R"(
      (\-"""-/)
       |     |
       \ ^ ^ /  .-.
        \_o_/  / /
       /`   `\/  |
      /       \  |
      \ (   ) /  |
     / \_) (_/ \ /
    |   (\-/)   |
    \  --^o^--  / 
     \ '.___.' /
    .'  \-=-/  '.
   /   /`   `\   \
  (//./       \.\\)
   `"`         `"`
    )" << endl;
    }
    else if (numero < 8) {
        cout << R"(
 ___    ___
( _<    >_ )
//        \\
\\___..___//
 `-(    )-'
   _|__|_
  /_|__|_\
  /_|__|_\
  /_\__/_\
   \ || /  _)
     ||   ( )
     \\___//
      `---'
    )" << endl;
    }
    else
    {
        cout << R"(
                                              ____
  ___                                      .-~. /_"-._
`-._~-.                                  / /_ "~o\  :Y
      \  \                                / : \~x.  ` ')
      ]  Y                              /  |  Y< ~-.__j
     /   !                        _.--~T : l  l<  /.-~
    /   /                 ____.--~ .   ` l /~\ \<|Y
   /   /             .-~~"        /| .    ',-~\ \L|
  /   /             /     .^   \ Y~Y \.^>/l_   "--'
 /   Y           .-"(  .  l__  j_j l_/ /~_.-~    .
Y    l          /    \  )    ~~~." / `/"~ / \.__/l_
|     \     _.-"      ~-{__     l  :  l._Z~-.___.--~
|      ~---~           /   ~~"---\_  ' __[>
l  .                _.^   ___     _>-y~
 \  \     .      .-~   .-~   ~>--"  /
  \  ~---"            /     ./  _.-'
   "-.,_____.,_  _.--~\     _.-~
               ~~     (   _}       
                      `. ~(
                        )  \
                  /,`--'~\--'~\
 
    )" << endl;
    }
    //  BARRAS DE VIDA
    cout << "\nVida monstruo: ";
    cout << "[" << vidaMonstruo << "/100]" << endl;
    cout << "Tu vida: ";
    cout << "[" << vidaTuya << "/100]" << endl;

    cout << "-----------------------------------------------------------------------------------------------------\n";
}
void combate(int vidaTuya, int vidaMonstruo, int vidasJugador, int monedas, int inventario[], int danoJugador)
{
    // varibales
    srand(time(0));
    int probabMonstr = rand(); // Genera un número random
    int eleccion = 0;
    bool salir = false;
    bool fincombat = false;

    int numero = 0;   //numero para generar posteriormente un random para elegir un monstruo con el cual luchar

    // Probabilidad aleatoria de que aparezca un monstruo
    probabMonstr = probabMonstr % 21;  // Número random entre 0 y 20 para calcularprobabilidad de mosntruo cada vez que se mueve el personaje

    // Si esa probabilidad ocurre, aparece el monstruo
    if (probabMonstr > 17)
    {
        numero = rand() % 11;   // para calcular un numero para la funcion mostrarCombate (eleccion de monstruo)
        while (!salir)
        {
            mostrarCombate(vidaTuya, vidaMonstruo, numero); //hay que incluirlo dentro del bucle para que se vea la vida de cada uno

            // Opciones de combate
            cout << "\n";
            cout << "\t -----------------" << endl;
            cout << "\t | 1. - Luchar   |" << endl;
            cout << "\t | 2. - Escapar  |" << endl;
            cout << "\t -----------------" << endl;

            if (inventario[2] > 0) { //espada es la posición 2 en la tienda (en el invenatrio esta la espada (si la tienes))
                danoJugador += 50; // La espada aumenta tu daño
                cout << "La espada aumenta tu dano en +20!" << endl;
            }
            if (inventario[1] > 0) { //pocion(dano) es la posición 1 en la tienda (en el invenatrio esta la espada (si la tienes))
                danoJugador += 15; // La pocion aumenta tu daño
                cout << "La pocion8dano) aumenta tu dano en +15!" << endl;
            }
            if (inventario[3] > 0) { //tenedor
                danoJugador += 7;
                cout << "El tenedor aumenta tu dano en +7!" << endl;
            }
            if (inventario[4] > 0) { //madera
                danoJugador += 2;
                cout << "la madera aumenta tu dano en +2!" << endl;
            }
            if (inventario[5] > 0) { //piedra
                danoJugador += 5;
                cout << "La piedra aumenta tu dano en +5!" << endl;
            }


            cin >> eleccion;
            //  en ufncion de la eleccion, Luchar O Escapar
            switch (eleccion)
            {
                // Luchar
            case 1:
                while (!fincombat)
                {
                    // Tu turno
                    cout << "Es tu turno!" << endl;
                    cout << "Le haces " << danoJugador << " de dano al monstruo!" << endl;
                    vidaMonstruo -= danoJugador;

                    //  Si la vida monstruo llega a 0 se termina
                    if (vidaMonstruo <= 0)
                    {
                        vidaMonstruo = 0;
                        cout << "Has derrotado al monstruo!" << endl;
                        fincombat = true;
                        salir = true;
                        monedas += 20;
                        break;
                    }

                    cout << "ENTER para pasar al turno del monstruo";
                    cin.ignore();
                    cin.get();

                    // Turno del monstruo
                    cout << "Es el turno del monstruo..." << endl;
                    cout << "El monstruo te hace " << 20 << " de danno!" << endl;
                    vidaTuya -= 20;


                    //  Si tu vida llega a 0 se termina
                    if (vidaTuya <= 0)
                    {
                        cout << "Has sido derrotado!" << endl;
                        fincombat = true;
                        salir = true;
                        // Restar una vida al jugador (la vida general (3))
                        vidasJugador -= 1;
                        break;
                    }
                    mostrarCombate(vidaTuya, vidaMonstruo, numero);
                    cout << "ENTER para pasar a tu turno";
                    cin.ignore();
                    cin.get();
                }
                break;

                // Escapar
            case 2:
                cout << "Has elegido escapar..." << endl;
                int escapar = rand() % 2;  // 0 o 1
                if (escapar == 0)
                {
                    cout << "Has conseguido escapar!" << endl;
                    salir = true;  // Salir del combate
                }
                else
                {
                    cout << "No has podido escapar!" << endl;
                    cout << "El monstruo te ataca mientras intentas huir" << endl;

                    // Turno del monstruo mientras intentas escapar
                    cout << "El monstruo te hace " << 30 << " de danno!" << endl;
                    vidaTuya -= 30;
                    if (vidaTuya <= 0)
                    {
                        mostrarCombate(vidaTuya, vidaMonstruo, numero);
                        cout << "Has sido derrotado!" << endl;
                        salir = true;
                        // Restar una vida al jugador
                        vidasJugador -= 1; // Restar una vida al jugador (la vida general (3))

                    }
                }
                break;
            }

            if (!salir) {
                cout << "\nENTER para continuar";
                cin.ignore();
                cin.get();
            }
        }
    }
}
void combateBoss(int vidaTuya, int vidaBoss, int inventario[], int danoJugador, bool finJuego)
{
    bool salir = false;
    bool fincombat = false;

    while (!salir)
    {
        mostrarboss(vidaTuya, vidaBoss);

        // Luchar

        while (!fincombat)
        {

            if (inventario[2] > 0) { //espada es la posición 2 en la tienda (en el invenatrio esta la espada (si la tienes))
                danoJugador += 50; // La espada aumenta tu daño
            }
            if (inventario[1] > 0) { //pocion(dano) es la posición 1 en la tienda (en el invenatrio esta la espada (si la tienes))
                danoJugador += 15; // La pocion aumenta tu daño

            }
            if (inventario[3] > 0) { //tenedor
                danoJugador += 7;

            }
            if (inventario[4] > 0) { //madera
                danoJugador += 2;

            }
            if (inventario[5] > 0) { //piedra
                danoJugador += 5;

            }
            // Tu turno
            cout << "Es tu turno!" << endl;
            cout << "Le haces " << danoJugador << " de daño al monstruo!" << endl;
            vidaBoss -= danoJugador;

            //  Si la vida monstruo llega a 0 se termina
            if (vidaBoss <= 0)
            {
                vidaBoss = 0;
                cout << "Has derrotado al monstruo!" << endl;
                // finjuego completamente 

                salir = true;
                break;
            }

            cout << "ENTER para pasar al turno del monstruo";
            cin.ignore();
            cin.get();

            // Turno del monstruo
            cout << "Es el turno del monstruo..." << endl;
            cout << "El monstruo te hace " << 30 << " de danno!" << endl;
            vidaTuya -= 30;

            //  Si tu vida llega a 0 se termina
            if (vidaTuya <= 0)
            {
                cout << "Has sido derrotado!" << endl;
                // finjuego completamente 
                fincombat = true;

                break;
            }
            mostrarboss(vidaTuya, vidaBoss);
            cout << "ENTER para pasar a tu turno";
            cin.ignore();
            cin.get();
        }
        cout << "\n\n";
        cout << "  GGGGG   AAAAA  M   M  EEEEE      OOO   V   V  EEEEE  RRRR   \n";
        cout << " G        A   A  MM MM  E         O   O  V   V  E      R   R  \n";
        cout << " G  GG    AAAAA  M M M  EEEE      O   O  V   V  EEEE   RRRR   \n";
        cout << " G   G    A   A  M   M  E         O   O  V   V  E      R  R   \n";
        cout << "  GGGG    A   A  M   M  EEEEE      OOO    VVV   EEEEE  R   R  \n";
        cout << "\n\n";
    }

    if (!salir) {
        cout << "\n\n";
        cout << " GGGGG   GGGGG   SSSSS \n";
        cout << " G       G       S      \n";
        cout << " G  GG   G  GG   SSSSS  \n";
        cout << " G   G   G   G       S  \n";
        cout << " GGGG    GGGG    SSSSS  \n";
        cout << "\n\n";
    }
}
void mostrarboss(int vidaTuya, int vidaBoss)
{

    system("cls");

    cout << "\t\t\t\tCOMBATE" << endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;


    cout << R"(
        _____                 
    ,-~"     "~-.           
  ,^ ___     ___ ^.      
 / .^   ^. .^   ^. \     
Y  l    O! l    O!  Y   
l_ `.___.' `.___.' _[   
l^~"-------------"~^I  
!\,               ,/!  
 \ ~-.,_______,.-~ /    
  ^.             .^         
    "-.._____.,-"
    )" << endl;


    //  BARRAS DE VIDA
    cout << "\nVida monstruo: ";
    cout << "[" << vidaBoss << "/150]" << endl;
    cout << "Tu vida: ";
    cout << "[" << vidaTuya << "/100]" << endl;

    cout << "-----------------------------------------------------------------------------------------------------\n";
}