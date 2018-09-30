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
	Agent():bump_(false), dirty_(false), posicion(0),x(7),y(7),camino(true),contador(0){
	for (int i=0;i<15;i++){
        for (int j=0;j<15;j++)
            mapa[i][j]=0;

        }
    mapa[x][y]=1;
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
    //cout << "PosicionX:" << x << "PosicionY:" << y<<endl;
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
   // cout << "PosicionX:" << x << "PosicionY:" << y<<endl;
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
		for (int i=0;i<15;i++){
            for (int j=0;j<15;j++)
            cout << mapa[i][j] << " ";
        cout << endl;
        }
            cout << endl;
        cout << endl;

	}

    void MasValor(){
        for (int i=0;i<15;i++){
        for (int j=0;j<15;j++)
            if (mapa[i][j]>=0)
                mapa[i][j]++;
        }
    }

    int SiguientePaso(){
        int resultado=1;
        if (posicion==0){
            if (mapa[x][y-1]>=mapa[x][y+1]){
                resultado=1;
                mapa[x][y-1]=2;
            }
            else{
                resultado=0;
                mapa[x][y+1]=2;
            }
            }
        else if (posicion==1){
            if (mapa[x-1][y]>=mapa[x+1][y]){
                resultado=1;
                mapa[x-1][y]=2;
            }
            else{
                resultado=0;
                mapa[x+1][y]=2;
            }
        }
        else if (posicion==2){
            if (mapa[x][y-1]>=mapa[x][y+1]){
                resultado=0;
                mapa[x][y-1]=2;
            }
            else{
                resultado=1;
                mapa[x][y+1]=2;
            }
        }
        else if (posicion==3){
            if (mapa[x-1][y]>=mapa[x+1][y]){
                resultado=0;
                mapa[x-1][y]=2;
            }
            else{
                resultado=1;
                mapa[x+1][y]=2;
            }
            }
    return resultado;
    }

private:
	bool bump_, dirty_;
	int posicion;
	int x,y,contador;
	int mapa[15][15];
	bool camino;

};

string ActionStr(Agent::ActionType);

#endif
