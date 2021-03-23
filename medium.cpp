#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

#define PI 3.1416

double randomizer(double upperLimit, double LowerLimit){
    return 0;
}

// ndf corresponds to normal density function with mean, variance, and x as usual parameters
double ndf(double x, double mean, double variance) {
    double y = (double)(1/(sqrt(2*PI)*variance)*exp(-pow((x-mean)/variance,2)/2));
    return y;
}

void accept_reject_sampler(double mean, double variance, double x_min, double x_max, double y_min, double y_max) {    

    double x, mean, variance;

    // Randomized values will be mentioned here alongwith the result of getting accepted or rejected in medium_output.txt
    fstream acc_rej_output;
    acc_rej_output.open("medium_output.txt");

    double p,q; // randomizing variables

    for(int i=0; i <= 10000 ; i++ ){

        p=randomizer(x_min,x_max);
        q=randomizer(y_min,y_max);

        if(q<ndf(p,x_min,x_max)){
            // ACCEPT
        }else{
            // REJECT
        }
    }

}

int main(){

    // Your values in the function should be looking like this for a standard normal density function
    // accept_reject_sampler(mean, variance, x_min, x_max, y_min, y_max) and enter x_min, max numbers > 0

    // accept_reject_sampler(mean, variance, x_min, x_max, y_min, y_max);
    return 0;
}