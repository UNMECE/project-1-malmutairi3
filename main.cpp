#include <iostream>
#include <iomanip>
#include "capacitor.h"

using namespace std;


const double delta_t = 1e-10;
const double final_t = 0.000005;

const int timesteps = 50000;
const double R = 1000;
const double C_val = 100e-12;
const double I_const = 1e-2;
const double V0 = 10.0;

void simulate_constant_current(Capacitor& cap) {
    cout << "=== Simulation of Constant Current Source  ===" << endl;

    cap.C =  C_val;
    cap.time[0 ] = 0 ;
    cap.voltage[0] = 0;
    cap.current[0] =  I_const;

    for (int t = 1; t <  timesteps; ++t ) {
        cap.time[t]  = cap.time[ t - 1] + delta_t;
        cap.current[t] = I_const;
        cap.voltage[t] =  cap.voltage[t - 1] + cap.current[t - 1]  * delta_t  * (1.0 / cap.C);

        if (t % 200 == 0) {
            cout << "t = " << setw(10) << cap.time[t];
            cout     << " s, V = " << setw(10) << cap.voltage[t] ;
            cout     << " V, I = " << cap.current[t] << " A" << endl;
        }
    }
}

void simulate_constant_voltage(Capacitor& cap) {
    cout << "\n=== Simulation of Constant Voltage Source  ===" << endl;

    cap.C = C_val;
    cap.time[0] = 0;
    cap.current[0] = V0 / R;
    cap.voltage[0] = 0;

    for (int t = 1; t < timesteps; ++t) {
        cap.time[t] = cap.time[t - 1] + delta_t;
        cap.current[t] = cap.current[t - 1] - (cap.current[t - 1] / (R * cap.C)) * delta_t;
        cap.voltage[t] = V0 - cap.current[t] * R;

        if (t % 200 == 0) 
        {
            cout << "t = "  << setw(10) << cap.time[t] ;
            cout     << " s, V = " <<  setw(10) << cap.voltage[t];
            cout     << " V, I = " <<   cap.current[t] << " A" << endl;
        }
    }
}

int main() 
{
    Capacitor cap;
    cap.time = new double[timesteps];
    cap.voltage = new double[timesteps];
    cap.current = new double[timesteps];

    simulate_constant_current(cap);
    simulate_constant_voltage(cap);

    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;

    return 0;
}
