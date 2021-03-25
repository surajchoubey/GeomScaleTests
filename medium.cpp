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

void accept_reject_sampler(double mean, double variance, double x_min, double x_max, double y_min, double y_max) {    

    // Randomized values will be mentioned here alongwith the result of getting accepted or rejected in medium_output.txt
    fstream acc_rej_output;
    acc_rej_output.open("medium_output.csv");

    double p,q; // randomizing variables

    double accept_count=0;
    double reject_count=0;

    for(int i=0; i <= 10000 ; i++ ){

        p=randomizer(x_min,x_max);
        q=randomizer(y_min,y_max);

        if(q<ndf(p,mean,variance)){
            // ACCEPT
            acc_rej_output << p << "," << q << "," << 1 << endl;
            ++accept_count;
        }else{
            // REJECT
            acc_rej_output << p << "," << q << "," << 0 << endl;
            ++reject_count;
        }
    }

    cout<<"Accepted area = "<<(x_max-x_min)*(y_max-y_min)*(accept_count/( accept_count + reject_count ))<< endl;
    acc_rej_output.close();

}

int main(){

    // Your values in the function should be looking like this for a standard normal density function
    // accept_reject_sampler(mean, variance, x_min, x_max, y_min, y_max) and enter x_min, max numbers > 0
    srand( (unsigned)time( NULL ) );
    accept_reject_sampler(0.5, 0.5, 0, 1, 0, 1);
    return 0;
}