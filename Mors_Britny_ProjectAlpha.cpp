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
	 
	double alpha;

	vector<double> reward;
	vector<double> value;

	void init();
	void pull();
};

void MAB::init(){
	mew = (LYRAND-0.5) * 50;
	sigma = LYRAND * 25;
<<<<<<< HEAD
	alpha = 0.1;
	value.push_back(0);
}

void MAB::pull() {
		double U1 = LYRAND;
		double U2 = LYRAND;
		double z = sqrt(-2*log(U1))*cos(2*PI*U2);
		reward.push_back((z*sigma) + mew);
		int r_size = reward.size();
		int v_size = value.size();
		value.push_back((reward[r_size-1]*alpha) + (value[v_size - 1] * (1 - alpha)));
=======
	reward = 0;
>>>>>>> parent of 926f258... Version 4
}

int main() {
	srand(time(NULL));

	int num_arms = 0;
	cout << "Welcome to Las Vegas! Lets play some slots!\n";
<<<<<<< HEAD
	cout << "How many arms does your bandit have?\n" << "Please enter an integer between 1 and 5000:" << endl;
	cin >> num_arms; //save user input to num arms
=======
	cout << "How many arms does your bandit have?\n" << "Please enter an integer:" << endl;
	cin >> num_arms;
>>>>>>> parent of 926f258... Version 4

	vector<MAB> bandit_army;
	MAB bandito;
	
	for (int i = 0; i < num_arms; i++) {
<<<<<<< HEAD
		bandito.init(); //initialize bandit
		bandit_army.push_back(bandito);//save bandit to vector element
	}
	//int x = rand() % (num_arms-1);
	//bandit_army[x].pull();
=======
		bandito.init();
		bandit_army.push_back(bandito);
		
	}
>>>>>>> parent of 926f258... Version 4
	
	return 0;
}