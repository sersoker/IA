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

if (dirty_)
    accion=actSUCK;
else{
    if (primera){
        Agent::aumenta();
        accion=actFORWARD;
        primera=false;
    }
    else{
    if (contador1==0){
        if (bump_){
        mapa[x][y]=2;
        Agent::disminuye();
        }
        accion=actTURN_R;
        Agent::cambiaposiscionr();
        contador1=contador2;
        contador2++;
        }
        else if (bump_){
        mapa[x][y]=2;
        Agent::disminuye();
        accion=actTURN_R;
        Agent::cambiaposiscionr();
        }
        else {
        mapa[x][y]=1;
        Agent::aumenta();
        if (mapa[x][y]==2){
            accion=actTURN_R;
            Agent::disminuye();
            Agent::cambiaposiscionr();

        }
        else
        accion=actFORWARD;
        contador1--;
        }
    }
}
//Agent::PintaMatriz();

if (contador1>10){
contador1=1;
contador2=2;
}
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
