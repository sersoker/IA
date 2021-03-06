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
   if(dirty_&&n_chupadas<3){
      accion = actSUCK;
      n_chupadas++;
   }
   else {
     n_chupadas=0;

     if (bump_ or n_avances_>3) {
         accion = actTURN_R;
         n_avances_=0;
      }
      else{
      switch(rand()%3){
        case 0: accion = actFORWARD;
                n_avances_++;
        break;
        case 1: accion = actTURN_L;
        break;
        case 2: accion = actFORWARD;
                n_avances_++;
        break;
	       }
      }

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
