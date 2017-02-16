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
	double reward; 

	void init();
	void pull();
};

void MAB::init(){
	mew = (LYRAND-0.5) * 50;
	sigma = LYRAND * 25;
	reward = 0.0;
}

void MAB::pull() {
		double U1 = LYRAND;
		double U2 = LYRAND;
		double z = sqrt(-2*log(U1))*cos(2*PI*U2);
		reward = reward + ((z*sigma) + mew);
}

int main() {
	srand(time(NULL));

	int num_arms = 0; //initalize num_arms 
	cout << "Welcome to Las Vegas! Lets play some slots!\n";
	cout << "How many arms does your bandit have?\n" << "Please enter an integer:" << endl;
	cin >> num_arms; //save user input to num arms

	vector<MAB> bandit_army; //create vector to store bandit information
	MAB bandito; //create bandit
	
	for (int i = 0; i < num_arms; i++) {
		bandito.init(); //initialize bandit
		bandit_army.push_back(bandito);//save bandit to vector element
	}

	//int rando = 
	bandit_army[rand()%num_arms].pull(); //randomly pull 1 arm

	return 0;
}