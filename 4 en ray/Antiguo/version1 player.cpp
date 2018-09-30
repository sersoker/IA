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


// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){
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
         return ValoracionTest(tablero,jugador);
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
               cout << "Accion:" << act << " " << aux << endl;
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




double PodaAlfaBeta(const Environment&tablero, int jugador, int profundidad,int LimProfundidad,double &alpha, double &beta,bool jugadormaximizador,int &accion){
  cout << "Llamada" << endl;
   int ganador=tablero.RevisarTablero();
   if (profundidad==0||ganador!=0){
         return ValoracionTest(tablero,jugador);
            cout << "Nodo Final "<< endl;
   }
   else{
    cout << "Entra";
      int act=-1;
      Environment hijo=tablero.GenerateNextMove(act);
         while (act<7){
           if (jugadormaximizador){
                alpha=max(alpha,PodaAlfaBeta(hijo,jugador,profundidad-1,LimProfundidad,alpha,beta,false,accion));
                  if (beta<=alpha){
                  cout << "jugada es: "<< alpha << endl;
                  }
                  accion=act;
                  return alpha;

            }
            else{
                beta=min(beta,PodaAlfaBeta(hijo,jugador,profundidad-1,LimProfundidad,alpha,beta,true,accion));
                  if (beta<=alpha){
                   accion=act;
                  return beta;
                    cout << "jugada es: "<< beta << endl;
                  }

            }
         }
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
    double alpha= -999999999999.0;
    double beta= 999999999999.0; // Cotas de la poda AlfaBeta
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
            //double jugada = MinMax(actual_,jugador_,0,PROFUNDIDAD_MINIMAX,acc);
            double jugada = PodaAlfaBeta(actual_,jugador_,PROFUNDIDAD_ALFABETA,PROFUNDIDAD_ALFABETA,alpha,beta,jugadormax,act);

         cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (act)  ) << endl;
            accion = static_cast< Environment::ActionType > (act);




    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    // valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
    //cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

    return accion;
}

