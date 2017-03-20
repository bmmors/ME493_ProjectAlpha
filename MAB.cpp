//Britny Mors
//ME 493 - Autonomy
//Second attemp at Multi Armed Bandit

#include <iostream>
#include <assert.h>
#include <vector>
#include <random>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <fstream>

using namespace std;

#define BMMRAND (double)rand()/RAND_MAX //generates random number from 0 to 1
#define pi (double)3.1415

class bandit {
public:
	double mew; //mean
	double sigma; //standard deviation

	void init();
};

class learner {
public:
	double alpha;
	double epsilon;

	void init();
};

void bandit::init() {
	mew = (BMMRAND - 0.5) * 50; //set mean between -50 to 50
	sigma = BMMRAND * 25; //set sigma between 0 and 25;
}

void learner::init() {
	alpha = 0.1; 
	epsilon = 0.1; //Take greedy action 10% of the time
}

int main() {
	srand(time(NULL));
	//Generate number of bandits
	int num_arms = 5;
	vector<bandit> army;
	
	for (int i = 0; i < num_arms; i++) {
		bandit B;
		B.init();
		army.push_back(B);
		assert(B.mew < 50 && B.mew > -50);
	}
	assert(army.size() == num_arms); //make sure accurate number of arms created. 


	return 0;
}