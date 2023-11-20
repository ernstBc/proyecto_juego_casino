/*
Ernesto Bravo Contreras
Avance #2      13/11/23

Estructura de los arreglos
*/
#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;
void imprimir_dados(int[][10], int); // muestra el ascii de los dados
void lanzar_dados(int[][10], int); // selecciona 3 numeros aleatorios y los coloca en el arr2d de jugadores

int apuesta(int[][10], int, int); // devuelve la apuesta del jugador -- comprueba la cantidad de dinero del jugador
int calcular_iguales(int [][10], int); // calcula la cantidad de caras iguales de los dados tirados
int calcular_numero_mayor(int [][10], int); // numero mayor de los dados lanzados // ~~~~~cambiarla para que sirva para vectoes 1d~~~
int calcular_num_caras_ig(int [][10], int); // num_pares_caras iguales
int pool(int [][10], int, int); // suma todas las apuestas de los jugadores
int empate(int [][10], int, int, int, int);
void mostrar_result(int [][10], string[], int, int, int);

int ganador(int [][10], int, int, int, int);
int num_mayor_col(int [][10], int, int);
int pos_mayor_col(int [][10], int, int);
int verif_valor_repe_col(int[][10], int, int, int);
void redistribuir(int[][10], int, int, int, int, int);
int pos_cero_dinero(int [][10], int, int);
int verif_arr_repetidos(int [][10], int, int, int);
int sum_dados(int[][10], int);

void iniciar_matriz(int [][10], int);

main(){
    srand(time(NULL));

    // estructura del arreglo (columnas)
    int IDX_DINERO = 3;
    int IDX_APUESTA = 4;
    int IDX_N_IGUALES = 5;
    int IDX_NUM_MAYOR = 6;
    int IDX_PAR_MAYOR = 7;
    int IDX_SUM_DADOS = 8;
    int IDX_JUGADOR_ACTIVO = 9;
    int pools = 0;
    int num_jugadores;
    int posicion_ganador;
    char wait;
    cout<<"Ingresa el numero de jugadores (2 a 4 jugadores): "; cin>>num_jugadores;cout<<endl;

    int num_jugadores_activos = num_jugadores;
    int matriz_juego[num_jugadores][10];
    string nombres[num_jugadores];
    iniciar_matriz(matriz_juego, num_jugadores);

    int dinero;
    for(int i = 0; i<num_jugadores; i++){
        cout<<"Ingresa el nombre del jugador "<<i + 1<<": ";cin>>nombres[i];
        cout<<nombres[i]<<", ingresa la cantidad de dinero que quieres depositar:  ";cin>>dinero; cout<<endl;
        matriz_juego[i][IDX_DINERO] = dinero;
        matriz_juego[i][IDX_JUGADOR_ACTIVO] = 1;
    }

    while(num_jugadores_activos>1)
    {
        // fase de lanzar dado y apostar
        for(int i = 0; i<num_jugadores; i++){
            if(matriz_juego[i][IDX_JUGADOR_ACTIVO] == 1){
                system("CLS");
                lanzar_dados(matriz_juego, i);
                imprimir_dados(matriz_juego, i);

                matriz_juego[i][IDX_APUESTA] = apuesta(matriz_juego, i, IDX_DINERO);
                                    // fase calcular resultados
                matriz_juego[i][IDX_N_IGUALES] = calcular_iguales(matriz_juego, i);
                matriz_juego[i][IDX_NUM_MAYOR] = calcular_numero_mayor(matriz_juego, i);
                matriz_juego[i][IDX_PAR_MAYOR] = calcular_num_caras_ig(matriz_juego, i);
                matriz_juego[i][IDX_SUM_DADOS] = sum_dados(matriz_juego, i);
                system("CLS");
            }
        }

        pools = pools + pool(matriz_juego, num_jugadores, IDX_APUESTA);
        int emfate = empate(matriz_juego, num_jugadores, IDX_NUM_MAYOR, IDX_NUM_MAYOR, IDX_PAR_MAYOR);

        cout<<"\nPool: "<<pools;
        if(emfate == 1){
            mostrar_result(matriz_juego, nombres, num_jugadores, -1, pools);
            cout<<"Ingresa cualquier tecla + Enter para pasar a la siguiente ronda   ";cin>>wait;
            continue;
        }

        posicion_ganador = ganador(matriz_juego, num_jugadores, IDX_N_IGUALES, IDX_NUM_MAYOR, IDX_PAR_MAYOR);
        cout<<endl<<endl<<nombres[posicion_ganador]<<" ha ganado!";

        mostrar_result(matriz_juego, nombres, num_jugadores, posicion_ganador, pools);
        redistribuir(matriz_juego, num_jugadores, posicion_ganador, pools, IDX_DINERO, IDX_APUESTA);
        pools = 0; // reinicia el monto de las apuestas al finalizar la partida.

/**     nomas para comprobar como va el arreglo en cada turno. 
        for(int j = 0; j<num_jugadores; j++){
            for(int i =0; i<8; i++){
                cout<<matriz_juego[j][i]<<"  ";
            }
        cout<<"------------------\n";
        }
 */


        int jugadores_sin_money = 0;
        while(jugadores_sin_money != -1){
            int pos_ceros = pos_cero_dinero(matriz_juego, num_jugadores, IDX_DINERO);
            if(pos_ceros != -1){
                matriz_juego[pos_ceros][IDX_JUGADOR_ACTIVO] = 0;
                //"borra" al jugador sin dinero de la partida
                for(int j = 0; j<10; j++){
                    matriz_juego[pos_ceros][j] = 0;
                    if(j == IDX_DINERO){
                        matriz_juego[pos_ceros][IDX_DINERO] = -1;
                    }
                }
                cout<<"Jugador "<<pos_ceros + 1<<": "<<nombres[pos_ceros]<<" no tiene dinero suficiente para continuar. Queda eliminado del juego.\n";
                num_jugadores_activos--;
            }
            else{
                jugadores_sin_money = -1;
            }
        }
        cout<<"Presiona cualquier tecla para empezar una nueva ronda: ";cin>>wait;
    }

    cout<<"\nFin del juego.";
}


void imprimir_dados(int matriz[][10], int num_jugador){
    int idx;
    cout<<"Dados del jugador "<<num_jugador + 1<<endl;
    for(int i = 0; i<3; i++){
        idx = matriz[num_jugador][i];

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

void lanzar_dados(int matriz_jugadores[][10], int num_jugador){
    for(int dado = 0; dado<3; dado++){
        matriz_jugadores[num_jugador][dado] = (rand() % 5) + 1;
    }

}

int apuesta(int matriz_juego[][10], int n_jugador, int idx_dinero){

    int apuesta;
    while( 1 == 1){
        cout<<"Actualmente tienes $"<<matriz_juego[n_jugador][idx_dinero]<<endl;
        cout<<"Cuanto dinero quieres apostar? "; cin>>apuesta;

        if(apuesta <= matriz_juego[n_jugador][idx_dinero] && apuesta>0){
            break;
        }
        cout<<"Apuesta una cantidad de dinero dentro de tus posibilidades, mugre limosnero"<<endl<<endl;
    }
    return apuesta;
}

int calcular_iguales(int matrix[][10], int jugador){
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

int calcular_numero_mayor(int matrix[][10], int jugador){
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

int num_mayor_col(int matrix[][10], int num_jugadores, int col_idx){
    int num_mayor;
    for(int i = 0; i<num_jugadores; i++){
        if(i == 0){
            num_mayor = matrix[i][col_idx];
        }

        if(matrix[i][col_idx] > num_mayor){
            num_mayor = matrix[i][col_idx];
        }
    }
    return num_mayor;
}

int pool(int matrix[][10], int n_jugadores, int idx_apuesta){
    int sum_apuestas = 0;
    for(int i = 0; i<n_jugadores; i++){
        sum_apuestas += matrix[i][idx_apuesta];
    }
    return sum_apuestas;
}

int empate(int matriz[][10], int n_jugadores, int idx_pares, int idx_n_mayor, int idx_num_iguales){
    int empate = 0, pos_win, ver_empate;
    int max;
    max = num_mayor_col(matriz, n_jugadores, idx_pares);


    if(max == 0){
        pos_win = pos_mayor_col(matriz, n_jugadores, idx_n_mayor);
        ver_empate = verif_valor_repe_col(matriz, n_jugadores, idx_n_mayor, pos_win);

        if(ver_empate == 0){
            cout<<"empate tipo 1";
            return empate;
        }
        else{
            empate = 1;
            cout<<"empate tipo 2";
            return empate;
        }
    }
    
    else{
        pos_win = pos_mayor_col(matriz, n_jugadores, idx_pares);
        ver_empate = verif_valor_repe_col(matriz, n_jugadores, idx_pares, pos_win);

        if(ver_empate == 0){
            cout<<"empate tipo 3";
            return empate;
        }
        else{
            pos_win = pos_mayor_col(matriz, n_jugadores, idx_num_iguales);
            int ver_empate_2 = verif_valor_repe_col(matriz, n_jugadores, idx_num_iguales, pos_win);

            if(ver_empate_2 == 0){
                cout<<"empate tipo4";
                return empate;
            }
            else{
                empate = 1;
                cout<<"empate tipo 5";
                return empate;
            }
        }

    }
}

void mostrar_result(int matrix[][10], string names[], int n_jugadores, int pos_ganador, int pool){

    cout<<endl;
    for(int i =0; i<n_jugadores; i++){
        if(matrix[i][9] == 1){
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
                            cout<<" perdio "<<matrix[i][4];
                        }
                    }
                    else{
                        cout<<"     Empate -- Se pasa +"<<matrix[i][4]<<" al pool de la proxima partida.";
                    }

                }
            }
            cout<<endl;

        }
        
    }
}

int calcular_num_caras_ig(int matrix[][10], int num_jugadores){
    int num_de_par = 0;
    int res = calcular_iguales(matrix, num_jugadores);
    if(res > 0){
        if(matrix[num_jugadores][0] == matrix[num_jugadores][1]){
            num_de_par = matrix[num_jugadores][0];
        }
        if(matrix[num_jugadores][0] == matrix[num_jugadores][2]){
            num_de_par = matrix[num_jugadores][0];
        }
        if(matrix[num_jugadores][1] == matrix[num_jugadores][2]){
            num_de_par = matrix[num_jugadores][1];
        }
    }
    return num_de_par;
}


void iniciar_matriz(int matrix[][10], int n_jugadores){
    for(int fila = 0; fila<n_jugadores; fila++){
        for(int col = 0; col <8; col++){
            matrix[fila][col] = rand()%10;
        }
    }
}


int pos_mayor_col(int matrix[][10], int num_jugadores, int col_idx){
    int pos_mayor = -1;
    int num_mayor = num_mayor_col(matrix, num_jugadores, col_idx);

    for(int i = 0; i<num_jugadores; i++){
        if(matrix[i][col_idx] == num_mayor){
            pos_mayor = i;
        }
    }

    return pos_mayor;

}
int verif_valor_repe_col(int matrix[][10], int num_jugadores, int idx_col, int pos_ganador){
    int iguales = 0;

    for(int i = 0; i<num_jugadores; i++){
        if(i != pos_ganador){
            if(matrix[i][idx_col] == matrix[pos_ganador][idx_col]){
                iguales++;
            }  
        }
    }

    return iguales;
}


int ganador(int matriz[][10], int n_jugadores, int idx_pares, int idx_num_mayor, int idx_caras_mayor){
    int pos_win;
    int max;
    max = num_mayor_col(matriz, n_jugadores, idx_pares);

    if(max == 0){
        pos_win = pos_mayor_col(matriz, n_jugadores, idx_num_mayor);
        return pos_win;
    }

    else{
        pos_win = pos_mayor_col(matriz, n_jugadores, idx_pares);
        int verif_empate = verif_valor_repe_col(matriz, n_jugadores, idx_pares, pos_win);

        if(verif_empate == 0){
            return pos_win;
        }
        else{
            pos_win = pos_mayor_col(matriz, n_jugadores, idx_caras_mayor);
            return pos_win;
        }
    }

}

void redistribuir(int matriz[][10], int n_jugadores, int pos_ganadors,int pools,  int idx_dinero, int idx_apuestas){
    for(int i = 0; i<n_jugadores; i++){
        if(i != pos_ganadors){
            matriz[i][idx_dinero]  -= matriz[i][idx_apuestas];
            matriz[i][idx_apuestas] = 0;
        }
        else{
            matriz[i][idx_dinero] += pools;
            matriz[i][idx_apuestas] = 0;           
        }
    }
}

int pos_cero_dinero(int matriz[][10], int n_jugadores, int idx_col){
    int pos = -1;
    for(int i = 0; i<n_jugadores; i++){
        if(matriz[i][idx_col] == 0){
            pos = i;
        }
    }
    return pos;
}

int verif_arr_repetidos(int matriz[][10], int n_jugadores, int idx_jugador1){
    int rep [3], identicos = 0;
    rep[0] = 0, rep[1] = 0, rep[2] = 0;

    for(int i = 0; i<3; i++){
        int arr_jugador = matriz[idx_jugador1][i];
        for(int j = 0; j<n_jugadores; j++){
            if(j != idx_jugador1){
                if(matriz[j][i] == arr_jugador){
                    rep[i] = 1;
                }
            }
        }
    }

    int sum_ident = 0;
    for(int i =0; i<3; i++){
        if(rep[i] == 1){
            sum_ident++;
        }
    }

    if(sum_ident == 3){
        identicos = 1;
    }
    return identicos;
}

int sum_dados(int matriz[][10], int idx_jugador){
    int sum = 0;
    for(int i = 0; i<3; i++){
        sum += matriz[idx_jugador][i];
    }

    return sum;
}