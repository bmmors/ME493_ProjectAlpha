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

//---------------------------------Bandit Setup---------------------------------//
class bandit {
public:
	double mew; //mean
	double sigma; //standard deviation
	double actionvalue; 

	void init(double A);
	double pull();
	void update(double reward, double alpha);
};

double bandit::pull() {
	double r = 0;
	double z = 0;
	double U1 = BMMRAND;
	double U2 = BMMRAND;
	z = sqrt(-2 * log(U1))*cos(2 * pi*U2);
	r = (z*sigma) + mew;
	return r;
}

void bandit::update(double reward, double alpha) {
	double tempaction = actionvalue;
	actionvalue = reward*alpha + tempaction*(1 - alpha);
	//cout << "actionvalue:" << actionvalue << endl;
}

void bandit::init(double A) {
	mew = (BMMRAND - 0.5) * 25; //set mean between -25 to 25
	sigma = BMMRAND * 25; //set sigma between 0 and 25;
	actionvalue = 0;
	int R = pull(); //pull each arm at initialization to keep from having to manage ties
	actionvalue = R*A + actionvalue*(1 - A); //save first action value
}
//---------------------------------End Bandit Setup---------------------------------//






//---------------------------------Learner Setup---------------------------------//
class learner {
public:
	double alpha = 0.1;
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
	
	
	//cout << "Select:" << select << endl;
	return select;
}
//---------------------------------End Learner Setup---------------------------------//


int main() {
	srand(time(NULL));

	///Initialize Action Value Learner
	learner L;
	int selection = 0; //arm selection variable

	///Generate number of bandits
	int num_arms = 5;
	vector<bandit> army;

	for (int k = 0; k < num_arms; k++) {
		bandit B; //create an arm
		B.init(L.alpha); //initialize each arm
		assert(B.mew < 25 && B.mew > -25); //assert std deviation was created
		army.push_back(B); //save arm into army
		
	}
	assert(army.size() == num_arms); //make sure accurate number of arms created. 
	
	///Run for n statistical runs 
	int stat_runs = 30;
	int run = 1000;
	vector<double> reward;
	double tempreward = 0;

	for (int k = 0; k < run; k++) {
		reward.push_back(0); //set reward vector to zero
	}
	assert(reward.size() == run); //double check reward size

								  
//---------------------------------Begin Statistical Runs---------------------------------//

	for (int i = 0; i < stat_runs; i++) { 
		double total_reward = 0;
		tempreward = 0;
		//start learner loop
		for (int j = 0; j < run; j++) {
			selection = L.decide(army); //choose arm based on greedy/exploratory and actionvalue
			tempreward = army[selection].pull(); //pull the lever for the arm and get reward. Save into temp value.
			army[selection].update(tempreward, L.alpha); //update actionvalue for arm that was pulled based on reward
			total_reward += tempreward;
			//cout << "total reward:\t" << total_reward << endl;
			if (j == 0) {
				reward[j] += tempreward;
			}
			else {
				reward[j] = total_reward;
			}
			//cout << "stat run:\t" << i << "\tRun:\t" << j << "\tTempreward:\t" << tempreward << "\tReward:\t" << reward[j] << endl;
		}
		//end learner loop

		for (int k = 0; k < num_arms; k++) {
			army.at(k).init(L.alpha); //reset all action values back to zero for next stat run
		}
	}
	assert(reward.size() == run); //size of reward vector should be equal to the number of runs

	//---------------------------------End Statistical Runs---------------------------------//

	

	ofstream myfile;
	myfile.open("learningcurve.csv");
	for (int i = 0; i < run; i++) {
		myfile << reward[i] << endl;
	}
	myfile.close();
	
	return 0;
}