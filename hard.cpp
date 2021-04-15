#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

#define pi 3.141592
#define epsilon 1e-6
// can also use M_PI

using namespace std;

double proportional_probability_density_gaussian(double x, double mu, double sigma)
{
    //The Proportional Distribution used is the exponential part of the Univariate Truncated Gaussian
    double ans = (double)exp(-pow((x - mu) / sigma, 2) / 2);
    return ans;
}

void metropolis_hastings(double mu, double sigma, int x_min, int x_max, int y_min = 0, int y_max = 0.5)
{
    // Writing sampled values to external file
    ofstream outfile;
    outfile.open("data1.txt");

    // sample generator from the in-built normal distribution
    default_random_engine e(0);

    // Initialising a random state for x between x_min and x_max
    double rand_x = (double)x_min + (rand() % ((x_max - x_min + 1) * 100) / (double)100);

    // Total accepted transitions, ideally this value should correspond to 50% for the case of univariate gaussian
    int jumps = 0;

    // sampling for 10000 samples
    for (long long i = 0; i < 10000; ++i)
    {
        // transition distribution chosen is a univariate gaussian centred at previous sample
        normal_distribution<double> jumping_distribution(rand_x, 2);

        // sample a new value
        double rand_x_new = x_max + 1;
        while (rand_x_new < x_min || rand_x_new > x_max)
        {
            rand_x_new = jumping_distribution(e);
        }

        double alpha = proportional_probability_density_gaussian(rand_x_new, mu, sigma) / proportional_probability_density_gaussian(rand_x, mu, sigma);

        // sample from U(0, 1)
        double u = (rand() % 101) / (double)100;

        if (u <= alpha)
        {
            // acceptable transition
            rand_x = rand_x_new;
            jumps += 1;
        }

        outfile << rand_x << endl;
    }

    cout << (double)jumps * 100 / 10000;
    outfile.close();
    return;
}

int main()
{
    srand(time(0));
    metropolis_hastings(0, 1, -5, 5);
    return 0;
}