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

////Bandit Setup////
class bandit {
public:
	double mew; //mean
	double sigma; //standard deviation
	double actionvalue; 

	void init(int A);
	double pull();
	void update(double reward, double alpha);
};

void bandit::init(int A) {
	mew = (BMMRAND - 0.5) * 50; //set mean between -50 to 50
	sigma = BMMRAND * 25; //set sigma between 0 and 25;
	actionvalue = 0;
	int R = pull();
	cout << "R:" << R << endl;
	update(R, A);
	cout << "actionvalue" << actionvalue << endl;
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

void bandit::update(double reward, double alpha) {
	actionvalue = reward*alpha + actionvalue*(1 - alpha);
	cout << "actionvalue:" << actionvalue << endl;
}
////End Bandit Setup////



////Learner Setup////
class learner {
public:
	double alpha;
	double epsilon;

	void init();
	int decide(vector<bandit> B);
};

void learner::init() {
	alpha = 0.1; 
}

int learner::decide(vector<bandit> B) {
	epsilon = BMMRAND;
	int select = 0;

	if (epsilon <= 0.1) {
		select = rand() % B.size();
	}
	else {
		double temp = B[0].actionvalue;

		for (int i = 1; i < B.size(); i++) {
			if (temp < B[i].actionvalue) {
				select = i;
				temp = B[i].actionvalue;
			}
		}
	}
	
	
	cout << "Select:" << select << endl;
	return select;
}

////End Learner Setup////


int main() {
	srand(time(NULL));

	///Initialize Action Value Learner
	learner L;
	L.init();
	int selection = 0;

	///Generate number of bandits
	int num_arms = 5;
	vector<bandit> army;

	for (int k = 0; k < num_arms; k++) {
		bandit B; //create an arm
		B.init(L.alpha); //initialize each arm
		army.push_back(B); //save arm into army
		assert(B.mew < 50 && B.mew > -50); //assert std deviation was created
	}
	assert(army.size() == num_arms); //make sure accurate number of arms created. 
	/*
	///Run for n statistical runs 
	int stat_runs = 10;
	int run = 1000;
	vector<double> reward;
	double tempreward = 0;

	for (int k = 0; k < run; k++) {
		reward.push_back(0);
	}
	assert(reward.size() == run);


	for (int i = 0; i < stat_runs; i++) { //statistical runs

										  //pull random arm first
		selection = rand() % num_arms;
		cout << "first select:" << selection << endl;
		tempreward = army[selection].pull();
		army[selection].update(tempreward, L.alpha);
		reward[0] += tempreward;

		//start learner loop
		for (int j = 1; j < run-1; j++) {
			selection = L.decide(army); //choose arm based on greedy/exploratory and actionvalue
			tempreward = army[selection].pull(); //pull the lever for the arm and get reward. Save into temp value.
			//cout << "Tempreward:" << tempreward << endl;
			army[selection].update(tempreward, L.alpha); //update actionvalue for arm that was pulled based on reward
			//cout << "Rewardbefore:" << reward[j] << endl;

			reward[j] += tempreward;
			//cout << "Rewardafter:" << reward[j] << endl;
		}
		//end learner loop

		for (int k = 0; k < num_arms; k++) {
			army[k].actionvalue = 0; //reset all action values back to zero for next stat run
		}
	}
	//end stat runs
	assert(reward.size() == run); //size of reward vector should be equal to the number of runs

	ofstream myfile;
	myfile.open("learningcurve.csv");
	for (int i = 0; i < run; i++) {
		myfile << reward[i] << endl;
	}
	myfile.close();
	*/
	return 0;
}