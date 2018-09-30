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

if (bump_){
    mapa[x][y]=-1;
    Agent::disminuye();
    mapa[x][y]=2;
    if (dirty_){
        accion=actSUCK;
        mapa[x][y]=2;
    }
    else{
        if (Agent::ValorDerecha()>=Agent::ValorIzquierda()&&Agent::ValorDerecha()>=Agent::ValorDelante()){
                    Agent::cambiaposiscionr();
                    accion=actTURN_R;
                    mapa[x][y]=2;
                    camino=true;
        }
        else{
                    Agent::cambiaposiscion();
                    accion=actTURN_L;
                    mapa[x][y]=2;
                    camino=true;
        }
    }
}
else{
    if (dirty_){
        accion=actSUCK;
        mapa[x][y]=2;
    }
    else{
        mapa[x][y]=2;

        if (cambio){
                Agent::cambiaposiscionr();
                accion=actTURN_R;
                    mapa[x][y]=2;
                cambio=false;
                camino=true;
        }

        else if (camino&&Agent::ValorDelante()!=-1){
            Agent::aumenta();
            accion=actFORWARD;
            camino=false;
        }
        else if(Agent::ValorDerecha()==-1&&Agent::ValorIzquierda()==-1&&Agent::ValorDelante()==-1){
            Agent::cambiaposiscionr();
            accion=actTURN_R;
                mapa[x][y]=2;
            cambio=true;
        }
        else if (Agent::ValorDelante()>=Agent::ValorDerecha()&&Agent::ValorDelante()>=Agent::ValorIzquierda()){
            Agent::aumenta();
            accion=actFORWARD;
        }
        else if (Agent::ValorDerecha()>Agent::ValorIzquierda()){
                Agent::cambiaposiscionr();
                accion=actTURN_R;
                    mapa[x][y]=2;
                camino=true;
        }
        else {
                Agent::cambiaposiscion();
                accion=actTURN_L;
                    mapa[x][y]=2;
                camino=true;
        }
    }
}

 //Agent::PintaMatriz();
    Agent::MasValor();

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
