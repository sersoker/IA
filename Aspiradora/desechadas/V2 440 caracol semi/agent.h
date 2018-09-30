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
	Agent():bump_(false), dirty_(false), n_avances_(0),n_chupadas(2),posicion(0),x(8),y(8),contador1(1),contador2(2),primera(true){
	for (int i=0;i<16;i++)
        {
        for (int j=0;j<16;j++)
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
		for (int i=0;i<16;i++){
            for (int j=0;j<16;j++)
            cout << mapa[i][j] << " ";
        cout << endl;
        }
            cout << endl;
        cout << endl;

	}
private:
	bool bump_, dirty_;
	int n_avances_,n_chupadas;
	int posicion;
	int x,y;
	int mapa[16][16];
	int contador1, contador2;
	bool primera;

};

string ActionStr(Agent::ActionType);

#endif
