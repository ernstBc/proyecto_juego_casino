/*
Estructura de los arreglos
matriz_jugadores -> filas == jugadores|| columna 0 -> cara dado1, col_1 ->cara_dado2, col_2 -> dado3, col_3 ->apuesta realizada
dados_result --> filas == jugadores || col0 = n_caras_iguales, col_1 -> numero_mayor_dado
dinero_depositado
*/


#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;
void imprimir_dados(int[][4], int); // muestra el ascii de los dados
void lanzar_dados(int[][4], int); // selecciona 3 numeros aleatorios y los coloca en el arr2d de jugadores

int apuesta(int[], int); // devuelve la apuesta del jugador -- comprueba la cantidad de dinero del jugador
int calcular_iguales(int [][4], int); // calcula la cantidad de caras iguales de los dados tirados
int calcular_numero_mayor(int [][4], int); // numero mayor de los dados lanzados // ~~~~~cambiarla para que sirva para vectoes 1d~~~
int pool(int [][4], int); // suma todas las apuestas de los jugadores
int pos_ganador(int [][2], int);
int game_over(int [][2], int);
bool empate(int [][2], int);
void mostrar_result(int [][4], int[][2], string[], int, int, int);

main(){
    srand(time(NULL));
    int pools = 0;

    int num_jugadores;
    cout<<"Ingresa el numero de jugadores (2 a 4 jugadores): "; cin>>num_jugadores;cout<<endl;

    int matriz_jugadores[num_jugadores][4], dinero_depositado[num_jugadores];
    int dados_result[num_jugadores][2]; // 1 - n_caras iguales, 2 -> numero mayor
    string nombres[num_jugadores];

    for(int i = 0; i<num_jugadores; i++){
        cout<<"Ingresa el nombre del jugador "<<i + 1<<": ";cin>>nombres[i];
        cout<<nombres[i]<<", ingresa la cantidad de dinero que quieres depositar:  "; cin>>dinero_depositado[i]; cout<<endl;
    }

    while(0 == 0)
    {
        // fase de lanzar dado y apostar
        for(int i = 0; i<num_jugadores; i++){
            system("CLS");
            lanzar_dados(matriz_jugadores, i);
            imprimir_dados(matriz_jugadores, i);

            matriz_jugadores[i][3] = apuesta(dinero_depositado, i);

            // fase calcular resultados
            dados_result[i][0] = calcular_iguales(matriz_jugadores, i);
            dados_result[i][1] = calcular_numero_mayor(matriz_jugadores, i);
            system("CLS");
        }

        pools = pools + pool(matriz_jugadores, num_jugadores);
        bool emfate = empate(dados_result, num_jugadores);

        cout<<"\nPool: "<<pools;

        if(emfate == 1){
            mostrar_result(matriz_jugadores, dados_result, nombres, num_jugadores, -1, pools);
            int enter;
            cin>>enter;
            continue;
        }
        int posicion_ganador = pos_ganador(dados_result, num_jugadores);
        mostrar_result(matriz_jugadores, dados_result, nombres, num_jugadores, posicion_ganador, pools);
        break;







    }

/*
    for(int i = 0; i<num_jugadores; i++){
        cout<<"J"<<i<<":    ";
        for(int j = 0; j<3; j++){
            cout<<matriz_jugadores[i][j]<<" ";
        }
        cout<<"     "<<nombres[i]<<"gano "<<pools<<endl;
    }*/
}


void imprimir_dados(int dado[][4], int num_jugador){
    int idx;
    cout<<"Dados del jugador "<<num_jugador + 1<<endl;
    for(int i = 0; i<3; i++){
        idx = dado[num_jugador][i];

        if(idx == 1){
            cout<<"+-------+"<<endl<<
            "|       |"<<endl<<
            "|   O   |"<<endl<<
            "|       |"<<endl<<
            "+-------+"<<endl;
        }
        if(idx == 2){
            cout<<"+-------+"<<endl<<
            "| O     |"<<endl<<
            "|       |"<<endl<<
            "|     O |"<<endl<<
            "+-------+"<<endl;
        }
        if(idx == 3){
            cout<<"+-------+"<<endl<<
            "| O     |"<<endl<<
            "|   O   |"<<endl<<
            "|     O |"<<endl<<
            "+-------+"<<endl;
        }
        if(idx == 4){
            cout<<"+-------+"<<endl<<
            "| O   O |"<<endl<<
            "|       |"<<endl<<
            "| O   O |"<<endl<<
            "+-------+"<<endl;
        }
        if(idx == 5){
            cout<<"+-------+"<<endl<<
            "| O   O |"<<endl<<
            "|   O   |"<<endl<<
            "| O   O |"<<endl<<
            "+-------+"<<endl;
        }
        if(idx == 6){
            cout<<"+-------+"<<endl<<
            "| O   O |"<<endl<<
            "| O   O |"<<endl<<
            "| O   O |"<<endl<<
            "+-------+"<<endl;
        }
    }
}

void lanzar_dados(int matriz_jugadores[][4], int num_jugador){
    for(int i = 0; i<4; i++){
        matriz_jugadores[num_jugador][i] = (rand() % 5) + 1;
    }

}

int apuesta(int vector_dinero[], int n_jugador){

    int apuesta;
    while( 1 == 1){
        cout<<"Actualmente tienes $"<<vector_dinero[n_jugador]<<endl;
        cout<<"Cuanto dinero quieres apostar? "; cin>>apuesta;

        if(apuesta <= vector_dinero[n_jugador] && apuesta>0){
            break;
        }
        cout<<"Apuesta una cantidad de dinero dentro de tus posibilidades, mugre limosnero"<<endl<<endl;
    }
    return apuesta;
}

int calcular_iguales(int matrix[][4], int jugador){
    int n_dados_igual = 0;

    if(matrix[jugador][0] == matrix[jugador][1]){
        n_dados_igual++;
    }
    if(matrix[jugador][0] == matrix[jugador][2]){
        n_dados_igual++;
    }
    if(matrix[jugador][1] == matrix[jugador][2]){
        n_dados_igual++;
    }

    return n_dados_igual;
}

int calcular_numero_mayor(int matrix[][4], int jugador){
    int n_mayor;
    for(int i = 0; i<3; i++){
        if(i == 0){
            n_mayor = matrix[jugador][i];
        }
        if(matrix[jugador][i] > n_mayor){
            n_mayor = matrix[jugador][i];
        }
    }

    return n_mayor;
}

int pool(int matrix[][4], int n_jugadores){
    int sum_apuestas = 0;
    for(int i = 0; i<n_jugadores; i++){
        sum_apuestas += matrix[i][3];
    }
    return sum_apuestas;
}

bool empate(int dados[][2], int n_jugadores){
    bool empate = 0;
    int max, iguales = 0;
    for(int i = 0; i<n_jugadores-1; i++){
        if(i == 0){
            max = dados[i][0];
        }
        if(dados[i][0] > max){
            max = dados[i][0];
        }
    }
    
    for(int i = 0; i<n_jugadores-1; i++){
        if(max == dados[i][0]){
            iguales++;
        }
    }

    if(iguales>1){
        empate = 1;
    }

    return empate;
}
int pos_ganador(int dados[][2], int n_jugadores){
    int n_mayor, pos_win = 0;
    for(int i = 0; i<n_jugadores; i++){     
        if(i == 0){
            n_mayor = dados[i][0];
            pos_win = i;
        }

        if(dados[i][0] > n_mayor){
            n_mayor = dados[i][0];
            pos_win = i;
        }
    }

    return pos_win;
}

void mostrar_result(int matrix[][4], int dados[][2], string names[], int n_jugadores, int pos_ganador, int pool){

    cout<<endl;
    for(int i =0; i<n_jugadores; i++){
        cout<<"J"<<i+1<<":      ";
        for(int j = 0; j<3; j++){
            cout<<matrix[i][j]<<" ";
            if(j == 2){
                cout<<"     "<<names[i];

                if(pos_ganador>=0){
                    if(i == pos_ganador){
                        cout<<" gano "<<pool;
                    }
                    else{
                        cout<<" perdio "<<matrix[i][3];
                    }
                }
                else{
                    cout<<"Empate -- Se pasa +"<<matrix[i][3]<<" al pool de la proxima partida.";
                }

            }
        }
        cout<<endl;

    }
}