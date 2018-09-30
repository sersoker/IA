#ifndef AGENT__
#define AGENT__

#include <string>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent():bump_(false), dirty_(false), n_avances_(0),n_chupadas(2){}

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
private:
	bool bump_, dirty_;
	int n_avances_,n_chupadas;
};

string ActionStr(Agent::ActionType);

#endif
