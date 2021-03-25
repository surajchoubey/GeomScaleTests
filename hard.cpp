#include<iostream>
#include<fstream>
#include<cmath>
#include<random>
using namespace std;

#define PI 3.1416

double randomizer(double lowerLimit, double upperLimit){
    double rdno = (double)(rand()) / (RAND_MAX) ;
    return rdno*(upperLimit-lowerLimit);
}

// ndf corresponds to normal density function with mean, variance, and x as usual parameters
double ndf(double x, double mean, double variance) {
    double y = (double)(1/(sqrt(2*PI)*variance)*exp(-pow((x-mean)/variance,2)/2));
    return y;
}

void metropolis_hastings(double mean, double variance, double x_min, double x_max, double y_min, double y_max) {    

    // Randomized values will be mentioned here alongwith the result of getting accepted or rejected in medium_output.txt
    fstream metro_hast_output;
    metro_hast_output.open("hard_output.csv");

    double p,q,r; // randomizing variables

    double accept_count=0;
    double reject_count=0;
    double previous=0;

    for(int i=0; i <= 10000 ; i++ ){

        p=randomizer(x_min,x_max);
        q=randomizer(y_min,y_max);
        r=randomizer(0,1);

        if(q<ndf(p,mean,variance)){
            if(q >= previous){
                // ACCEPT
                previous=q;
                metro_hast_output << p << "," << q << endl ;//<< "," << 1 << endl;
            }else if(r < previous/q){
                // ACCEPT
                previous=q;
                metro_hast_output << p << "," << q << endl ;//<< "," << 1 << endl;
            }else{
                continue;
            }
        }
        else{
            // REJECT
            // metro_hast_output << p << "," << q << "," << 0 << endl;
        }
    }

    metro_hast_output.close();

}

int main(){

    // Your values in the function should be looking like this for a standard normal density function
    // accept_reject_sampler(mean, variance, x_min, x_max, y_min, y_max) and enter x_min, max numbers > 0
    srand( (unsigned)time( NULL ) );
    metropolis_hastings(0.5, 0.5, 0, 1, 0, 1);
    return 0;
}