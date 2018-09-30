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

if (dirty_){
    accion=actSUCK;
    mapa[x][y]=2;
    }
else{
    if (bump_){
        mapa[x][y]=-1;
        disminuye();
        Agent::cambiaposiscion();
        if  (mapa[x][y]>=0){
            accion=actTURN_L;
        }
        else{
            accion=actTURN_R;
            Agent::cambiaposiscionr();
            Agent::cambiaposiscionr();
        }
    }
    else if (!bump_){
        mapa[x][y]=1;
        Agent:aumenta();

        if (mapa[x][y]>=0){
        accion=actFORWARD;
        }
        else {
            disminuye();
            if (Agent::SiguientePaso()==1){
                Agent::cambiaposiscion();
                accion=actTURN_L;
                camino=true;
            }
            else{
                Agent::cambiaposiscionr();
                accion=actTURN_R;
                camino=true;
            }
        }
    }

}

    Agent::MasValor();
    //Agent::PintaMatriz();
    cout << "PosicionX: " << x << "PosicionY: " << y << endl;
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
