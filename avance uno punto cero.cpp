#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;
void imprimir_dados(int[][4], int);
void lanzar_dados(int[][4], int);
int apuesta(int[], int);

int calcular_iguales(int [][4], int);
int calcular_numero_mayor(int [][4], int);

main(){
    srand(time(NULL));
    int num_jugadores;
    cout<<"Ingresa el numero de jugadores (2 a 4 jugadores): "; cin>>num_jugadores;
    string nombres[num_jugadores];
    int matriz_jugadores[num_jugadores][4], dinero_depositado[num_jugadores];

    for(int i = 0; i<num_jugadores; i++){
        cout<<"Igresa el nombre del jugador "<<i + 1<<": ";cin>>nombres[i];
        cout<<nombres[i]<<", ingresa la cantidad de dinero que quieres depositar:  "; cin>>dinero_depositado[i]; cout<<endl;
    }

    // fase de lanzar dado y apostar
    for(int i = 0; i<num_jugadores; i++){
        system("CLS");
        lanzar_dados(matriz_jugadores, i);
        imprimir_dados(matriz_jugadores, i);
        matriz_jugadores[i][3] = apuesta(dinero_depositado, i);
    }

    // fase comparar resultados
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