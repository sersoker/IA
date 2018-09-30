#ifndef AGENT__
#define AGENT__
#include <iostream>
#include <string>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent():bump_(false), dirty_(false), posicion(0),x(10),y(10),camino(true){
	for (int i=0;i<20;i++){
        for (int j=0;j<20;j++)
            mapa[i][j]=0;

        }
    mapa[x][y]=2;
	}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
	    actSUCK,
	    actIDLE
	};

	void Perceive(const Environment &env);
	ActionType Think();

	void aumenta(){
	if (posicion==0)
        x++;
    else if (posicion==1)
        y--;
    else if (posicion==2)
        x--;
    else
        y++;
	}

    void disminuye(){
	if (posicion==0)
        x--;
    else if (posicion==1)
        y++;
    else if (posicion==2)
        x++;
    else
        y--;
	}

	void cambiaposiscion(){
        if (posicion==0)
            posicion=1;
        else if (posicion==1)
            posicion=2;
        else if (posicion==2)
            posicion=3;
        else if (posicion==3)
            posicion=0;
	}

    void cambiaposiscionr(){
        if (posicion==0)
            posicion=3;
        else if (posicion==1)
            posicion=0;
        else if (posicion==2)
            posicion=1;
        else if (posicion==3)
            posicion=2;
	}

	void PintaMatriz(){
		for (int i=0;i<20;i++){
            for (int j=0;j<20;j++)
            cout << mapa[i][j] << " ";
        cout << endl;
        }
            cout << endl;
        cout << endl;

	}

    void MasValor(){
        for (int i=0;i<20;i++){
        for (int j=0;j<20;j++)
            if (mapa[i][j]>=0)
                mapa[i][j]++;
        }
    }

    int ValorDerecha(){
        int resultado=2;
        if (posicion==0){
                resultado=mapa[x][y+1];
            }
        else if (posicion==1){
                resultado=mapa[x+1][y];
            }

        else if (posicion==2){
                resultado=mapa[x][y-1];
            }

        else if (posicion==3){
                resultado=mapa[x-1][y];
            }
    return resultado;
    }

    int ValorIzquierda(){
        int resultado=2;
        if (posicion==0){
                resultado=mapa[x][y-1];
            }
        else if (posicion==1){
                resultado=mapa[x-1][y];
            }

        else if (posicion==2){
                resultado=mapa[x][y+1];
            }

        else if (posicion==3){
                resultado=mapa[x+1][y];
            }
    return resultado;
    }

    int ValorDelante(){
        int resultado=2;
        if (posicion==0){
                resultado=mapa[x+1][y];
            }
        else if (posicion==1){
                resultado=mapa[x][y-1];
            }

        else if (posicion==2){
                resultado=mapa[x-1][y];
            }

        else if (posicion==3){
                resultado=mapa[x][y+1];
            }
    return resultado;
    }

private:
	bool bump_, dirty_;
	int posicion;
	int x,y,contador;
	int mapa[20][20];
	bool camino;

};

string ActionStr(Agent::ActionType);

#endif
