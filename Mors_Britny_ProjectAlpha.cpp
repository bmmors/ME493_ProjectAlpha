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

	vector<double> reward;
	vector<double> value;

	void init();
	void pull();
};

void MAB::init(){
	mew = (LYRAND-0.5) * 50;
	sigma = LYRAND * 25;
	alpha = 0.1;
}

void MAB::pull() {
		double U1 = LYRAND;
		double U2 = LYRAND;
		double z = sqrt(-2*log(U1))*cos(2*PI*U2);
		reward.push_back((z*sigma) + mew);
		int r_size = reward.size();
		int v_size = value.size();
		if (v_size == 0) {
			value.push_back(reward[r_size - 1] * alpha);
		}
		else {
			value.push_back((reward[r_size - 1] * alpha) + (value[v_size - 1] * (1 - alpha)));
		}
}

int Greedy(vector<MAB> robit) {
	int robit_size = robit.size();
	int output = 0;
	for (int j = 0; j < robit_size; j++) {
		if (robit[output])
	}
}
int main() {
	srand(time(NULL));

	int num_arms = 0; //initalize num_arms 
	cout << "Welcome to Las Vegas! Lets play some slots!\n";
	cout << "How many arms does your bandit have?\n" << "Please enter an integer between 1 and 5000:" << endl;
	cin >> num_arms; //save user input to num arms

	vector<MAB> bandit_army; //create vector to store bandit information
	MAB bandito; //create bandit
	
	bandit_army.clear();
	
	for (int i = 0; i < num_arms; i++) {
		bandito.init();
		bandit_army.push_back(bandito);
	}

	
	return 0;
}