#ifndef BEHAVIORS_H
#define BEHAVIORS_H

#include "behavior_map.h"

class Behaviors {
	private:
		//prevent instantiation of Behavior
		Behaviors(){}
		~Behaviors(){}
	public:
		static void dump();
		static void mine();
		static void move();
		
};

#endif