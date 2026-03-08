#ifndef IMPLIED_VOL_H
#define IMPLIED_VOL_H

double implied_vol(double Forward, double Strike, double Tau, double Flag, double Rate, double Target);
inline char isPositive(double x);

#endif //IMPLIED_VOL_H
