#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

#define pi 3.141592

using namespace std;

double density_function(double x, double mu, double sigma)
{
    double y = (double)exp(-pow((x - mu) / sigma, 2) / 2) / (sqrt(2 * pi));
    return y;
}

void rejection_sampling(double mu, double sigma, int x_min, int x_max, int y_min = 0, int y_max = 1)
{
    // Storing samples in medium_output.csv
    ofstream myfile;
    myfile.open("medium_output.csv");

    // erf is the error function, used to calculate the normalising factor for truncated gaussian
    double erf_x_max = erf((x_max - mu) / sigma);
    double erf_x_min = erf((x_min - mu) / sigma);

    for (long i = 0; i < 10; ++i)
    {
        double rand_x = (double)x_min + (rand() % ((x_max - x_min + 1) * 100) / (double)100);

        double rand_y = (double)y_min + (rand() % ((y_max - y_min + 1) * 100) / (double)100);

        double cdf_x = density_function(rand_x, mu, sigma) / (sigma * (erf_x_max - erf_x_min));

        if (rand_y <= cdf_x)
        {
            myfile << rand_x << "," << rand_y << endl;
        }
    }

    myfile.close();
    return;
}

int main()
{
    srand(time(0));
    rejection_sampling(-0.5, 0.5, -3, 1);
    return 0;
}