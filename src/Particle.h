#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE,
	PARTICLE_MODE_PAUSE
};

//contains all actions that can be performed
enum actionToPerform{
	DEFAULT_ACTION,
	TRIPLE_PARTICLE_SIZE,
	THIRD_PARTICLE_SIZE,
	QUADRUPLE_VELOCITY
	
};

class Particle{

	public:
		Particle();
		
		void setMode(particleMode newMode);	
		void setAction(actionToPerform newAction);
		void setAttractPoints( vector <glm::vec3> * attract );
		void attractToPoint(int, int);
		void repelFromPoint(int, int);
		void reset();
		void update();
		void draw();		
		
		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		float adjusted_scale;
		float adjusted_vel_x;
		float adjusted_vel_y;
		
		particleMode mode;
		actionToPerform action;
		
		vector <glm::vec3> * attractPoints; 
};
