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
	double pull();
};

class learner {
public:
	double alpha;
	double epsilon;
	vector <double> Qtable;

	void init(int arms);
	int decide();
};

void bandit::init() {
	mew = (BMMRAND - 0.5) * 50; //set mean between -50 to 50
	sigma = BMMRAND * 25; //set sigma between 0 and 25;
}

double bandit::pull() {
	double r = 0;
	double z = 0;
	double U1 = BMMRAND;
	double U2 = BMMRAND;
	z = sqrt(-2 * log(U1))*cos(2*pi*U2);
	r = (z*sigma) + mew;
	return r;
}

void learner::init(int amrs) {
	alpha = 0.1; 
	epsilon = 0.1; //Take greedy action 10% of the time
}

int learner::decide() {

}

int main() {
	srand(time(NULL));

	///Generate number of bandits
	int num_arms = 5;
	vector<bandit> army;
	
	for (int i = 0; i < num_arms; i++) {
		bandit B;
		B.init();
		army.push_back(B);
		assert(B.mew < 50 && B.mew > -50);
	}
	assert(army.size() == num_arms); //make sure accurate number of arms created. 

	///Initialize Action Value Learner
	learner L;
	L.init();

	///Run for n statistical runs 
	int stat_runs = 1;
	int run = 1000;
	int select = -1;
	vector<vector<double>> reward;

	for (int i = 0; i < stat_runs; i++) {
		for (int j = 0; j < run; j++) {
			select = L.decide();
			reward[i][j].push_back(army[select].pull());
		}
	}

	return 0;
}