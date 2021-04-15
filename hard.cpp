#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

#define pi 3.141592

using namespace std;

// Normal function
double density_function(double, double, double);
// Metropolis Hastings function
void metro_hastings(double, double, int, int ,int, int);

int main()
{
    srand(time(0));
    metro_hastings(0, 1, -3, 3);
    return 0;
}

double density_function(double x, double mu, double sigma)
{
    double y = (double)exp(-pow((x - mu) / sigma, 2) / 2);
    return y;
}

void metro_hastings(double mu, double sigma, int x_min, int x_max, int y_min = 0, int y_max = 0.5)
{
    ofstream myfile;
    myfile.open("hard_output.csv");

    // sample generator from the in-built normal distribution
    default_random_engine e(0);
    double rand_x = (double)x_min + (rand() % ((x_max - x_min + 1) * 100) / (double)100);

    // Total accepted transitions
    int jumps = 0;

    // sampling for 10000 samples
    for (long i = 0; i < 10000; ++i)
    {
        // transition distribution chosen is a univariate gaussian centred at previous sample
        normal_distribution<double> jumping_distribution(rand_x, 2);

        double rand_x_new = x_max + 1;
        while (rand_x_new < x_min || rand_x_new > x_max)
        {
            rand_x_new = jumping_distribution(e);
        }

        double alpha = density_function(rand_x_new, mu, sigma) / density_function(rand_x, mu, sigma);

        // sample from U(0, 1)
        double u = (rand() % 101) / (double)100;

        if (u <= alpha)
        {
            // acceptable transition
            rand_x = rand_x_new;
            jumps += 1;
        }

        myfile << rand_x << endl;
    }

    cout << (double)jumps * 100 / 10000;
    myfile.close();
    return;
}