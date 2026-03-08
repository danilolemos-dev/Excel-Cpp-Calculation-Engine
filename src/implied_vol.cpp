#include "pch.h"
#define NMAX 25

inline char isPositive(double x)
{
	return (x >= 0);
}

double implied_vol(double Forward, double Strike, double Tau, double Flag, double Rate, double Target)
{
	double Vol = 0;
	double a = 0;
	double b = 5;

	double TOL = static_cast<double>(1) / 10000000;

	BOOL  condicao;	

	for (register unsigned int i = 0; i <= NMAX; i++)
	{
		Vol = (a + b) / static_cast<double>(2); // novo ponto médio
		condicao = (fabs((double)(a - b) / 2)) < TOL;

		if ( (fabs((double) (Pricer(Forward, Strike, Tau, Flag, Rate, Vol) - Target))  <= static_cast<double>(1) / 10000) || condicao ) // solução encontrada
		{
			return (Vol);
		}

		if ( isPositive(Pricer(Forward, Strike, Tau, Flag, Rate, Vol) - Target) == isPositive(Pricer(Forward, Strike, Tau, Flag, Rate, a) - Target))
			a = Vol;
		else
			b = Vol; // novo intervalo
	}

	return (-1);
}
