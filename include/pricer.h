#ifndef PRICER_H
#define PRICER_H

constexpr auto daycount = 252;

double Pricer(double, double, double, double, double, double);
double getDelta(double, double, double, double, double, double, double);
double getVega(double, double, double, double, double, double);
double getVegaRaph(double, double, double, double, double, double);
double getDivOne(double, double, double);
double getDivOneBorrow(double, double, double);
double getRho(double, double, double, double, double, double);
double getRhoBorrow(double, double, double, double, double, double, double);
double getTheta(double, double, double, double, double, double);
double getGamma(double, double, double, double, double, double);
double getSpeed(double, double, double, double, double, double, double);
double getVanna(double, double, double, double, double, double, double);
double getCharm(double, double, double, double, double, double, double);
double getVolga(double, double, double, double, double, double);
double getCollor(double, double, double, double, double, double,double);
double getVegaBleed(double, double, double, double, double, double);
double getThetaBleed(double, double, double, double, double, double);
double getZomma(double, double, double, double, double, double);
double getGammaBkeven(double, double, double, double, double, double, double);
double getVolgaBkeven(double, double, double, double, double, double);
double getVVol(double, double, double, double, double, double);

#endif //PRICER_H
