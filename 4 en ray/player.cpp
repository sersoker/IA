#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar

int BuscaTres1(int jugador,const Environment&estado){//1110
   int suma=0;
     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){

         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==0)
               suma=suma+15;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==0)
               suma=suma+10;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==0)
               suma=suma+10;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==0)
               suma=suma+10;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==0)
               suma=suma+15;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+10;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+10;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+10;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+10;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==0)
               suma=suma+10;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+10;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+10;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+10;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+10;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==0)
            suma=suma+15;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==0)
               suma=suma+10;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+10;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+10;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+10;

            }
        }

      }
     }
return suma;
}

int BuscaTres2(int jugador,const Environment&estado){//1101
   int suma=0;
     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){

         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+15;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+10;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+10;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+10;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==jugador)
               suma=suma+15;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+10;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+10;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+10;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+10;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+10;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==jugador)
            suma=suma+15;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+10;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+10;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+10;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;

            }
        }

      }
     }
return suma;
}

int BuscaTres3(int jugador,const Environment&estado){//1011
   int suma=0;
     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){

         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+15;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+10;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+10;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+10;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==jugador)
               suma=suma+15;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+10;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+10;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+10;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+10;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+10;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==jugador)
            suma=suma+15;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+10;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+10;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+10;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;

            }
        }

      }
     }
return suma;
}

int BuscaTres4(int jugador,const Environment&estado){//0111
   int suma=0;
     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){

         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+15;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+10;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+10;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+10;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==jugador)
               suma=suma+15;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+10;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+10;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+10;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+10;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+10;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==jugador)
            suma=suma+15;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+10;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+10;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+10;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+10;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+10;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+10;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+10;

            }
        }

      }
     }
return suma;
}


int BuscaDos1(int jugador,const Environment&estado){//1100
   int suma=0;

     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){
         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==0)
               suma=suma+5;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==0)
               suma=suma+3;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==0)
               suma=suma+3;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==0)
               suma=suma+3;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==0)
               suma=suma+5;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+3;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==0)
               suma=suma+3;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+3;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==0)
            suma=suma+5;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==0)
               suma=suma+3;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+3;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+3;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;

            }
        }

      }
     }
return suma;
}

int BuscaDos2(int jugador,const Environment&estado){//1010
   int suma=0;

     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){
         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==0)
               suma=suma+5;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==0)
               suma=suma+3;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==0)
               suma=suma+3;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==0)
               suma=suma+3;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==0)
               suma=suma+5;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+3;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==0)
               suma=suma+3;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+3;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==0)
            suma=suma+5;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==0)
               suma=suma+3;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+3;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+3;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;

            }
        }

      }
     }
return suma;
}

int BuscaDos3(int jugador,const Environment&estado){//1001
   int suma=0;

     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){
         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+5;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+3;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+3;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+3;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==jugador)
               suma=suma+5;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+3;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+3;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+3;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==jugador)
            suma=suma+5;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+3;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+3;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+3;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;

            }
        }

      }
     }
return suma;
}

int BuscaDos4(int jugador,const Environment&estado){//0110
   int suma=0;

     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){
         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==0)
               suma=suma+5;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==0)
               suma=suma+3;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==0)
               suma=suma+3;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==0)
               suma=suma+3;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==0)
               suma=suma+5;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+3;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==0)
               suma=suma+3;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+3;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==0)
            suma=suma+5;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==0)
               suma=suma+3;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+3;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+3;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+3;

            }
        }

      }
     }
return suma;
}

int BuscaDos5(int jugador,const Environment&estado){//0101
   int suma=0;

     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){
         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+5;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+3;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+3;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+3;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==jugador)
               suma=suma+5;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+3;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+3;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+3;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==jugador)
            suma=suma+5;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+3;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+3;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+3;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;

            }
        }

      }
     }
return suma;
}

int BuscaDos6(int jugador,const Environment&estado){ //0011
   int suma=0;

     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){
         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+5;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+3;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+3;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+3;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==jugador)
               suma=suma+5;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+3;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+3;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+3;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+3;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==jugador)
            suma=suma+5;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+3;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+3;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+3;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+3;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+3;

            }
        }

      }
     }
return suma;
}


int BuscaUno1(int jugador,const Environment&estado){//1000
   int suma=0;

     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){
         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==0)
               suma=suma+1;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==0)
               suma=suma+1;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==0)
               suma=suma+1;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==0)
               suma=suma+1;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==0)
               suma=suma+1;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+1;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+1;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==0)
               suma=suma+1;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+1;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+1;
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==0)
            suma=suma+1;
            if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==0)
               suma=suma+1;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+1;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+1;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+1;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+1;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==jugador&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;

            }
        }

      }
     }
return suma;
}

int BuscaUno2(int jugador,const Environment&estado){//0100
   int suma=0;

     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){
         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==0)
               suma=suma+1;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==0)
               suma=suma+1;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==jugador&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==0)
               suma=suma+1;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==jugador&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==0)
               suma=suma+1;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==0)
               suma=suma+1;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+1;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+1;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==0)
               suma=suma+1;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+1;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+1;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==jugador&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==0)
            suma=suma+1;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==jugador&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==0)
               suma=suma+1;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+1;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==jugador&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==jugador&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+1;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==jugador&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==jugador&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;

            }
        }

      }
     }
return suma;
}

int BuscaUno3(int jugador,const Environment&estado){//0010
   int suma=0;

     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){
         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==0)
               suma=suma+1;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==0)
               suma=suma+1;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==jugador&&estado.See_Casilla(i,j-3)==0)
               suma=suma+1;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==jugador&&estado.See_Casilla(i,j+3)==0)
               suma=suma+1;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==0)
               suma=suma+1;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+1;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                     suma=suma+1;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==0)
               suma=suma+1;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+1;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                     suma=suma+1;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==jugador&&estado.See_Casilla(i+3,j)==0)
            suma=suma+1;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==jugador&&estado.See_Casilla(i-3,j)==0)
               suma=suma+1;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+1;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==jugador&&estado.See_Casilla(i-3,j+3)==0)
                    suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==jugador&&estado.See_Casilla(i+3,j+3)==0)
                    suma=suma+1;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==jugador&&estado.See_Casilla(i-3,j-3)==0)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==jugador&&estado.See_Casilla(i+3,j-3)==0)
                     suma=suma+1;

            }
        }

      }
     }
return suma;
}

int BuscaUno4(int jugador,const Environment&estado){//0001
   int suma=0;

     for (int i=0; i<7; i++){
      for (int j=0; j<7; j++){
         if (i>=0&&j<3){ //Suma Horizontales de columnas 0 1 y 2
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+1;
         }
         if (i>=0&&j>3){ //suma horizontales de columnas 4-6
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+1;
         }
         if(i>=0&&j==3){ //suma horizontales de columna 3
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j-1)==0&&estado.See_Casilla(i,j-2)==0&&estado.See_Casilla(i,j-3)==jugador)
               suma=suma+1;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i,j+1)==0&&estado.See_Casilla(i,j+2)==0&&estado.See_Casilla(i,j+3)==jugador)
               suma=suma+1;
         }
         if(i<=3){ // suma verticales
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==jugador)
               suma=suma+1;
            if(j>=0&&j<3) //suma diagonales hacia la derecha
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+1;
            if(j==3) //suma diagonales derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                     suma=suma+1;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+1;
            if(j>3) //suma diagonales hacia la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+1;
         }
         if(i>3){ //suma verticales hacia arriba
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+1;
            if(j>=0&&j<3) //suma diagonales hacia arriba
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+1;
            if(j==3) //suma diagonales hacia arriba, derecha e izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                     suma=suma+1;
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+1;
            if(j>3) //suma diagonales hacia arriba a la izquierda
                  if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+1;
         }

         if (i==3){ //Suma verticales ambos sentidos
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j)==0&&estado.See_Casilla(i+2,j)==0&&estado.See_Casilla(i+3,j)==jugador)
            suma=suma+1;
            if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j)==0&&estado.See_Casilla(i-2,j)==0&&estado.See_Casilla(i-3,j)==jugador)
               suma=suma+1;

            if (j<3){//Diagonale sarriba y abajo derecha
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+1;
            }
            if (j==3){//diagonales todas
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j+1)==0&&estado.See_Casilla(i-2,j+2)==0&&estado.See_Casilla(i-3,j+3)==jugador)
                    suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j+1)==0&&estado.See_Casilla(i+2,j+2)==0&&estado.See_Casilla(i+3,j+3)==jugador)
                    suma=suma+1;
            }
            if (j>3){//diagonales arriba y abajo izquierda
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i-1,j-1)==0&&estado.See_Casilla(i-2,j-2)==0&&estado.See_Casilla(i-3,j-3)==jugador)
                     suma=suma+1;
                if (estado.See_Casilla(i,j)==0&&estado.See_Casilla(i+1,j-1)==0&&estado.See_Casilla(i+2,j-2)==0&&estado.See_Casilla(i+3,j-3)==jugador)
                     suma=suma+1;

            }
        }

      }
     }
return suma;
}

double PunValor2(int jugador,const Environment&estado){
  int suma=0;

  suma=BuscaTres1(jugador,estado);
  suma=BuscaTres2(jugador,estado);
  suma=BuscaTres3(jugador,estado);
  suma=BuscaTres4(jugador,estado);

  suma=suma+BuscaDos1(jugador,estado);
  suma=suma+BuscaDos2(jugador,estado);
  suma=suma+BuscaDos3(jugador,estado);
  suma=suma+BuscaDos4(jugador,estado);
  suma=suma+BuscaDos5(jugador,estado);
  suma=suma+BuscaDos6(jugador,estado);

  suma=suma+BuscaUno1(jugador,estado);
  suma=suma+BuscaUno2(jugador,estado);
  suma=suma+BuscaUno3(jugador,estado);
  suma=suma+BuscaUno4(jugador,estado);
  return suma;
}


double Valoracion(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();
    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return PunValor2(jugador,estado);

}

// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<7; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}



double MinMax(const Environment&tablero, int jugador, int profundidad,int LimProfundidad,int &accion){
   int ganador=tablero.RevisarTablero();
   if (profundidad==LimProfundidad||ganador!=0){
         return Valoracion(tablero,jugador);
   }
   else{
      int act=-1;
      double mejor;
      if (profundidad%2==0){
         mejor=-999999999999.0;
      }
      else{
         mejor = 999999999999.0;
      }

      Environment hijo=tablero.GenerateNextMove(act);
         while (act<7){
            double aux=MinMax(hijo,jugador,profundidad+1,LimProfundidad,accion);
            if (profundidad==0){
           //    cout << "Accion:" << act << " " << aux << endl;
            }
           if (profundidad%2==0){
               if (aux>mejor){
                  mejor=aux;
                  if (profundidad==0)
                  accion=act;
               }
               hijo= tablero.GenerateNextMove(act);
            }
            else{
               if (aux<mejor){
                  mejor=aux;
               }
               hijo= tablero.GenerateNextMove(act);
            }
         }
         return mejor;
   }

}


double PodaAlfaBeta(const Environment&tablero, int jugador, int profundidad,int LimProfundidad,double alpha, double beta,int &accion){
   bool vector[7];
   int casillasLibres=tablero.Get_Casillas_Libres();
   int ganador=tablero.RevisarTablero();

   if (profundidad==LimProfundidad||ganador!=0){
       return Valoracion(tablero,jugador);
   }
   else{
      int act=-1;
      double aux;
      Environment hijo=tablero.GenerateNextMove(act);
      if(tablero.possible_actions(vector)==0)
         return Valoracion(tablero,jugador);
      while (!(hijo==tablero)){
        if (profundidad==0){
           cout << "Accion:"<< act<<endl;
        }
        aux=PodaAlfaBeta(hijo,jugador,profundidad+1,LimProfundidad,alpha,beta,accion);
        if (profundidad==0){
        cout << "Accion:"<< act<< " = " << aux <<endl;}
           if (profundidad%2==0){//nodo max
                  if (aux>alpha){
                    alpha=aux;
                    if (profundidad==0)
                        accion=act;
                  }
                  if (alpha>=beta)
                    return beta;
            }
            else{
                  if (aux<beta){
                    beta=aux;
                  }
                if (beta<=alpha)
                    return alpha;
            }
          hijo=tablero.GenerateNextMove(act);
         }
         if (profundidad%2==0)
            return alpha;
         else
            return beta;
   }
}


// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acción que se va a devolver
    bool aplicables[7]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha= -99999999.0;
    double beta= 99999999.0; // Cotas de la poda AlfaBeta
    bool jugadormax=true;

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<7; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;



int act;
            //double jugada = MinMax(actual_,jugador_,0,PROFUNDIDAD_MINIMAX,act);
            double jugada = PodaAlfaBeta(actual_,jugador_,0,PROFUNDIDAD_ALFABETA,menosinf,masinf,act);
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (act)  ) << endl;
            accion = static_cast< Environment::ActionType > (act);

    return accion;
}

