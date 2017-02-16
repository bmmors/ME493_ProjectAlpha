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

#define LYRAND (double)rand()/RAND_MAX

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
	reward = 0;
}

int main() {
	srand(time(NULL));

	int num_arms = 0;
	cout << "Welcome to Las Vegas! Lets play some slots!\n";
	cout << "How many arms does your bandit have?\n" << "Please enter an integer:" << endl;
	cin >> num_arms;

	vector<MAB> bandit_army;
	MAB bandito;
	
	for (int i = 0; i < num_arms; i++) {
		bandito.init();
		bandit_army.push_back(bandito);
		
	}
	

	return 0;
}