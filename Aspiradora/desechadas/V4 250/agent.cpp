#include "agent.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	ActionType accion;

if (dirty_&&!bump_){
    accion=actSUCK;
    mapa[x][y]=2;
    }
else{

if (camino){
    if (mapa[x][y]!=-1){
        accion=actFORWARD;
        camino=false;
        Agent::aumenta();
    }
    else{
        Agent::disminuye();
        camino=false;

    }
}


else if (bump_){
        mapa[x][y]=-1;
        Agent::disminuye();
        if (Agent::ValorDerecha()>=Agent::ValorIzquierda()){
                Agent::cambiaposiscionr();
                accion=actTURN_R;
                camino=true;
        }
        else if (Agent::ValorIzquierda()>=Agent::ValorDerecha()){
                Agent::cambiaposiscion();
                accion=actTURN_L;
                camino=true;
        }
    }
    else if (!bump_){
        mapa[x][y]=2;
        Agent::aumenta();

        if (mapa[x][y]>Agent::ValorDerecha()&&mapa[x][y]!=-1){
            if (mapa[x][y]>Agent::ValorIzquierda()){
                accion=actFORWARD;
            }
            else{
                Agent::disminuye();
                Agent::cambiaposiscion();
                accion=actTURN_L;
                camino=true;
            }
        }
        else if (Agent::ValorDerecha()>Agent::ValorIzquierda()){
                Agent::disminuye();
                Agent::cambiaposiscionr();
                accion=actTURN_R;
                camino=true;
        }
        else if (Agent::ValorIzquierda()>Agent::ValorDerecha()){
                Agent::disminuye();
                Agent::cambiaposiscion();
                accion=actTURN_L;
                camino=true;
        }
        else{
        accion=actFORWARD;
        }

    }

}

if (contador==3){
    Agent::MasValor();
    contador=0;
    }
    else
        contador++;

   // Agent::PintaMatriz();
    //cout << "PosicionX: " << x << "PosicionY: " << y << endl;
	return accion;

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	bump_ = env.isJustBump();
	dirty_ = env.isCurrentPosDirty();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actSUCK: return "SUCK";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
