#include "pch.h"

// Standard normal distribution funcions block ======================================
double __stdcall cNormSDist(double& x)
{
	StandardNormalDistribution c;
	return (c.NormSDist(x));
}

double __stdcall cProbabilityDensityFunction(double& x)
{
	StandardNormalDistribution c;
	return (c.ProbabilityDensityFunction(x));
}

double __stdcall cDistributionFunction(double& z)
{
	StandardNormalDistribution c;
	return (c.DistributionFunction(z));
}

double __stdcall cNormSInv(double& probability)
{
	StandardNormalDistribution c;
	return (c.NormSInv(probability));
}

double __stdcall cInverseDistributionFunction(double& probability)
{
	StandardNormalDistribution c;
	return (c.InverseDistributionFunction(probability));
}


// Pricer functions block ====================================================================
double __stdcall cPricer(double& Fwd, double& K, double& T,	double& CPFlag,	double& R, double& vol)
{
	return (Pricer(Fwd, K, T, CPFlag, R, vol));
}

double __stdcall cgetDelta(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma, double& Borrow)
{
	return getDelta(Forward, Strike, Tau, Flag, Rate, Sigma, Borrow);
}

double __stdcall cgetVega(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getVega(Forward, Strike, Tau, Flag, Rate, Sigma);
}

double __stdcall cgetVegaRaph(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getVegaRaph(Forward, Strike, Tau, Flag, Rate, Sigma);
}

double __stdcall cgetDivOne(double& Tau, double& Rate, double& Fwd)
{
	return getDivOne(Tau, Rate, Fwd);
}

double __stdcall cgetDivOneBorrow(double& Tau, double& Borrow, double& Fwd)
{
	return getDivOneBorrow(Tau, Borrow, Fwd);
}

double __stdcall cgetRho(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getRho(Forward, Strike, Tau, Flag, Rate, Sigma);
}

double __stdcall cgetRhoBorrow(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma, double& Borrow)
{
	return getRhoBorrow(Forward, Strike, Tau, Flag, Rate, Sigma, Borrow);
}

double __stdcall cgetTheta(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getTheta(Forward, Strike, Tau, Flag, Rate, Sigma);
}

double __stdcall cgetGamma(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getGamma(Forward, Strike, Tau, Flag, Rate, Sigma);
}

double __stdcall cgetSpeed(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma, double& Borrow)
{
	return getSpeed(Forward, Strike, Tau, Flag, Rate, Sigma, Borrow);
}

double __stdcall cgetVanna(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma, double& Borrow)
{
	return getVanna(Forward, Strike, Tau, Flag, Rate, Sigma, Borrow);
}

double __stdcall cgetCharm(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma, double& Borrow)
{
	return getCharm(Forward, Strike, Tau, Flag, Rate, Sigma, Borrow);
}

double __stdcall cgetVolga(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getVolga(Forward, Strike, Tau, Flag, Rate, Sigma);
}

double __stdcall cgetCollor(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma, double& Borrow)
{
	return getCollor(Forward, Strike, Tau, Flag, Rate, Sigma, Borrow);
}

double __stdcall cgetVegaBleed(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getVegaBleed(Forward, Strike, Tau, Flag, Rate, Sigma);
}

double __stdcall cgetThetaBleed(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getThetaBleed(Forward, Strike, Tau, Flag, Rate, Sigma);
}

double __stdcall cgetZomma(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getZomma(Forward, Strike, Tau, Flag, Rate, Sigma);
}

double __stdcall cgetGammaBkeven(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma, double& Borrow)
{
	return getGammaBkeven(Forward, Strike, Tau, Flag, Rate, Sigma, Borrow);
}

double __stdcall cgetVolgaBkeven(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getVolgaBkeven(Forward, Strike, Tau, Flag, Rate, Sigma);
}

double __stdcall cgetVVol(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Sigma)
{
	return getVVol(Forward, Strike, Tau, Flag, Rate, Sigma);
}


// Calendar funcions block ====================================================
double __stdcall cDateDiff3(double& d1, double& m1, double& y1, double& d2, double& m2, double& y2)
{
	return DateDiff(static_cast<int>(d1), static_cast<int>(m1), static_cast<int>(y1), static_cast<int>(d2), static_cast<int>(m2), static_cast<int>(y2));
}

double __stdcall cjulianday_c(int& d1, int& m1, int& y1)
{
	return julianday_c(d1, m1, y1);
}


// implied_vol funcions block ====================================================
double __stdcall cImplied_vol(double& Forward, double& Strike, double& Tau, double& Flag, double& Rate, double& Target)
{
	return implied_vol(Forward, Strike, Tau, Flag, Rate, Target);
}
