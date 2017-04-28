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

	void init();
	double pull();
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

void bandit::init() {
	mew = (BMMRAND - 0.5) * 50; //set mean between -25 to 25
	sigma = BMMRAND * 25; //set sigma between 0 and 25;
	int R = pull(); //pull each arm at initialization to keep from having to manage ties
}
//---------------------------------End Bandit Setup---------------------------------//






//---------------------------------Learner Setup---------------------------------//
class learner {
public:
	double alpha = 0.1;
	double epsilon;
	int select;
	vector<double> v;

	void init(int num_arms);
	void decide(int num_arms);
	void update(double R);
};

void learner::init(int num_arms) { 
	for (int i = 0; i < num_arms; i++) {
		v.push_back(100);
	}
}

void learner::decide(int num_arms) {
	epsilon = rand()%10;
	int select = 0; //start at first arm
	double test = 0; //clear test variable
	test = v.at(select); //set test variable to the action value of the first arm
	for (int i = 1; i < num_arms; i++) {
		if (epsilon == 1) { //exploratory 
			select = rand() % num_arms;
		}
		else if (test < v.at(i)) { //greedy
			select = i; //save arm with highest action value
			test = v.at(i); //save new highest value
		}
	}
}

void learner::update(double R) {
	v.at(select) = v.at(select) + alpha*(R - v.at(select));
}
//---------------------------------End Learner Setup---------------------------------//


int main() {
	srand(time(NULL));

	///Generate number of bandits
	int num_arms = 5;
	vector<bandit> army; 

	for (int k = 0; k < num_arms; k++) {
		bandit B; //create an arm
		B.init(); //initialize each arm
		assert(B.mew < 50 && B.mew > -50); //assert std deviation was created
		army.push_back(B); //save arm into army

	}
	assert(army.size() == num_arms); //make sure accurate number of arms created.

	///Initialize Action Value Learner
	learner L;
	L.init(num_arms);
	
	///Run for n statistical runs 
	int stat_runs = 10;
	int run = 100;
	vector<double> reward;
	double r = 0;
	
	for (int i = 0; i < run; i++) {
		reward.push_back(0);
	}
	assert(reward.size() == run);
							  
//---------------------------------Begin Statistical Runs---------------------------------//

	for (int i = 0; i < stat_runs; i++) { 

		L.select = rand() % num_arms; //pull random arm first
		r = army.at(L.select).pull();
		reward.at(0) += r; //save reward
		L.update(r); //update action value for that arm

		cout << "Arm:\t" << L.select << "\tReward:\t" << r << "\tQ:\t" << L.v.at(L.select) << endl;
		///start learner loop
		for (int j = 1; j < run-1; j++) {
			L.decide(num_arms); //decide which arm to pull 
			r = army.at(L.select).pull();
			reward.at(j) += r; //save reward
			L.update(r); //update action value for that arm
			cout << "Arm:\t" << L.select << "\tReward:\t" << r << "\tQ:\t" << L.v.at(L.select) << endl;
		}
		///end learner loop
		L.init(num_arms);
	}
		

//---------------------------------End Statistical Runs---------------------------------//

	
	ofstream myfile;
	myfile.open("learningcurve.csv");
	for (int i = 0; i < run; i++) {
		myfile << reward[i] << endl;
	}
	myfile.close();

	return 0;
}