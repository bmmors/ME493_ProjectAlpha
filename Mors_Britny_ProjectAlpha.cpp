//Britny Mors
//ME 493 - Autonomy
//Project Alpha
//February 16th, 2017
//Worked with Sierra Gonzales, Natan Brauner, and Bryant Clouse

//z=sqrt(-2*ln(U1))*sin(2*pi*U2)
//(z*sigma)+mew

#include <iostream>
#include <assert.h>
#include <vector>
#include <cmath>
#include <random>
#include <time.h>
#include <fstream>

#define LYRAND (double)rand()/RAND_MAX
#define PI (double)3.1415
using namespace std;


class MAB {
public:
	double mew; 
	double sigma;
	double alpha;
	double v1;
	double r1;

	vector<double> reward;
	vector<double> value;

	void init();
	void pull();
};

void MAB::init(){
	mew = (LYRAND-0.5) * 50; //set the mean between -50 to 50
	sigma = LYRAND * 25; //set sigma between 0 and 25
	alpha = 0.1; //set alpha to 0.1
}

void MAB::pull() {
		double U1 = LYRAND; //create a random number between 0-1
		double U2 = LYRAND; //create a rancom number between 0-1
		double z = sqrt(-2*log(U1))*cos(2*PI*U2); //box muller transform
		reward.push_back((z*sigma) + mew); //apply the appropriate std deviation and mean to the z value and save it as the reward
		int r_size = reward.size();
		int v_size = value.size();
		if (v_size == 0) {
			value.push_back(reward[0] * alpha);
			v1 = value[0];
			r1 = reward[0];
		}
		else {
			value.push_back((reward[r_size - 1] * alpha) + (value[v_size - 1] * (1 - alpha)));
			v1 = value[v_size - 1];
			r1 = reward[r_size - 1];
		}
		
}

int Decision_Time(vector<MAB> robit) {
	int robit_size = robit.size();
	int choice = 0; //choice variable tells you what element the best V(t) is located at
	vector<MAB> blegh; // temporary vector
	blegh.push_back(robit[0]); 
	for (int j = 0; j < robit_size; j++) {
		if (blegh[0].v1 < robit[j].v1) { //test each instance in the robit vector and find the higher V(t) value
			blegh[0] = robit[j]; //when a higher V(t) is found save it to the temporary vector and try to find another higher value
			choice = j; //save the element location of the highest V(t) and out put it
		}

	}
	return choice;
}

int Rando(vector<MAB> robit2) {
	int x = rand() % (robit2.size() - 1); //generate a random number between 0 and num_arms
		return x;
}


int main() {
	srand(time(NULL));

	int num_arms = 0; //initalize num_arms 
	cout << "How many arms does your bandit have?\n" << "Please enter an integer between 1 and 5:" << endl;
	cin >> num_arms; //save user input to num arms

	vector<MAB> bandit_army; //create vector to store bandit information
	MAB bandito; //create bandit
	
	bandit_army.clear(); //initialize bandit army
	
	for (int i = 0; i < num_arms; i++) {
		bandito.init();
		bandit_army.push_back(bandito); 
	}
	//bandit army built
	bandit_army[rand() % num_arms].pull(); //pull random arm first
	
	double e = 0.1; //take a random action 10% of the time
	int greedy_arm = 0;
	int rand_arm = 0;
	for (int k = 0; k < 10000; k++) {
		double y = LYRAND;
		if (e <= y) {
			rand_arm = Rando(bandit_army);
			bandit_army[rand_arm].pull(); //ten percent of the time explore by pulling random arm
		}
		else
			greedy_arm = Decision_Time(bandit_army);
			bandit_army[greedy_arm].pull(); //90 percent of the time be greedy
	}
	
	return 0;
}