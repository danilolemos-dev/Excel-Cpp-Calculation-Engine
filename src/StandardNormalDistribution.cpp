#include "pch.h"
//#include "StandardNormalDistribution.h"


/// <summary>
/// Alias para o método StandardCumulative desta classe, com o mesmo nome que a função equivalente do Excel em inglês
/// </summary>
/// <param name="z">Is the value for which you want the distribution</param>
/// <returns>
/// Returns the standard normal cumulative distribution function.
/// The distribution has a mean of 0 (zero) and a standard deviation of one.
/// Use this function in place of a table of standard normal curve areas.
/// </returns>
double StandardNormalDistribution::NormSDist(double z)
{
    return DistributionFunction(z);
}

/// <summary>
/// The Probabilities density function.
/// </summary>
/// <param name="x">The x.</param>
/// <returns></returns>
double StandardNormalDistribution::ProbabilityDensityFunction(double x)
{
    const double ONE_OVER_SQRT_2_PI = 0.398942280401433;
    return ONE_OVER_SQRT_2_PI * exp(-0.5 * x * x);
}

/// <summary>
/// Returns the probability that a sample taken from the distribution lies inside the specified interval.
/// </summary>
/// <param name="minValue">The min value.</param>
/// <param name="maxValue">The max value.</param>
/// <returns>The probability that a sample taken from the distribution lies between minValue and maxValue</returns>
double StandardNormalDistribution::Probability(double minValue, double maxValue)
{
    if (maxValue <= minValue) return 0.0;
    return DistributionFunction(maxValue) - DistributionFunction(minValue);
}

/// <summary>
/// Calcula a distribuicao normal acumulada
/// </summary>
/// <param name="z">o fator de confiança z</param>
/// <returns>a porcentagem acumulada até o valor de z [0; 1]</returns>        
/// /// <remarks>
/// Esta implementação segue HART 1968, conforme discutido em http://www4.ncsu.edu/unity/users/p/pfackler/www/ECG790C/accuratecumnorm.pdf
/// que é o mesmo algoritmo que o Excel 2003, mas não o algoritmo do Excel XP, 2000 e anteriores.
/// A precisão desta função é double, ao contrário da implementação anterior, que era single.
/// </remarks>
double StandardNormalDistribution::DistributionFunction(double z)
{
    if(z < -9999999) // TODO: aprimorar
    {
        return 0.0;
    }

    if (z > 9999999)
    {
        return 1.0;
    }

    if (z == 0.0)
    {
        return 0.5;
    }

    double Cumnorm;
    double XAbs = fabs(z);
    if (XAbs > 37.0)
    {
        Cumnorm = 0.0;
    }
    else
    {
        double Exponential = exp(-pow(XAbs, 2.0) / 2.0);
        if (XAbs < 7.07106781186547)
        {
            double build = 3.52624965998911E-02 * XAbs + 0.700383064443688;
            build = build * XAbs + 6.37396220353165;
            build = build * XAbs + 33.912866078383;
            build = build * XAbs + 112.079291497871;
            build = build * XAbs + 221.213596169931;
            build = build * XAbs + 220.206867912376;
            Cumnorm = Exponential * build;
            build = 8.83883476483184E-02 * XAbs + 1.75566716318264;
            build = build * XAbs + 16.064177579207;
            build = build * XAbs + 86.7807322029461;
            build = build * XAbs + 296.564248779674;
            build = build * XAbs + 637.333633378831;
            build = build * XAbs + 793.826512519948;
            build = build * XAbs + 440.413735824752;
            Cumnorm = Cumnorm / build;
        }
        else
        {
            double build = XAbs + 0.65;
            build = XAbs + 4.0 / build;
            build = XAbs + 3.0 / build;
            build = XAbs + 2.0 / build;
            build = XAbs + 1.0 / build;
            Cumnorm = Exponential / build / 2.506628274631;
        }
    }
    if (z > 0.0)
    {
        Cumnorm = 1.0 - Cumnorm;
    }

    return Cumnorm;
}

/// <summary>
/// Retorna a função de sobrevivencia
/// </summary>
/// <param name="z">The z.</param>
/// <returns></returns>
double StandardNormalDistribution::SurvivorDistributionFunction(double z)
{
    return 1.0 - DistributionFunction(z);
}

/// <summary>
/// Alias para a função StandardCumulativeInverse, com o mesmo nome que a função equivalente do Excel em inglês
/// </summary>
/// <param name="probability">probabilidade</param>
/// <returns>O inverso da cumulativa padrão</returns>
double StandardNormalDistribution::NormSInv(double probability)
{
    return InverseDistributionFunction(probability);
}

/// <summary>
/// Calcula a inversa da cumulativa normal
/// </summary>
/// <param name="probability">probabilidade</param>
/// <returns>O inverso da cumulativa padrão, 16 digitos de precisão</returns>
/// <remarks>
/// Retirado e adaptado do Fortran em 2010-10-26 a partir de http://lib.stat.cmu.edu/apstat/241
///
///    ALGORITHM AS241  APPL. STATIST. (1988) VOL. 37, NO. 3
///    Produces the normal deviate Z corresponding to a given lower
///    tail area of P; Z is accurate to about 1 part in 10**16.
/// </remarks>
double StandardNormalDistribution::InverseDistributionFunction(double probability)
{
    if ((probability < 0.0) || (probability > 1.0))
    {
        //throw new ArgumentOutOfRangeException("probability", probability, "Should be in [0; 1] interval.");
        //TODO
    }

    if (probability == 0.0)
    {
        return -9999999; // TODO: aprimorar
    }

    if (probability == 1.0)
    {
        return 9999999;
    }

    if (probability == 0.5)
    {
        return 0.0;
    }

    const double SPLIT1 = 0.4250,
        SPLIT2 = 5.0,
        CONST1 = 0.1806250,
        CONST2 = 1.60;

    //    Coefficients for P close to 0.5
    const double A0 = 3.38713287279636660800,
        A1 = 1.3314166789178437745E+2,
        A2 = 1.9715909503065514427E+3,
        A3 = 1.3731693765509461125E+4,
        A4 = 4.5921953931549871457E+4,
        A5 = 6.7265770927008700853E+4,
        A6 = 3.3430575583588128105E+4,
        A7 = 2.5090809287301226727E+3,
        B1 = 4.2313330701600911252E+1,
        B2 = 6.8718700749205790830E+2,
        B3 = 5.3941960214247511077E+3,
        B4 = 2.1213794301586595867E+4,
        B5 = 3.9307895800092710610E+4,
        B6 = 2.8729085735721942674E+4,
        B7 = 5.2264952788528545610E+3;

    //    Coefficients for P not close to 0, 0.5 or 1.
    const double C0 = 1.423437110749683577340,
        C1 = 4.630337846156545295900,
        C2 = 5.769497221460691405500,
        C3 = 3.647848324763204605040,
        C4 = 1.270458252452368382580,
        C5 = 2.41780725177450611770E-1,
        C6 = 2.27238449892691845833E-2,
        C7 = 7.74545014278341407640E-4,
        D1 = 2.053191626637758821870,
        D2 = 1.676384830183803849400,
        D3 = 6.89767334985100004550E-1,
        D4 = 1.48103976427480074590E-1,
        D5 = 1.51986665636164571966E-2,
        D6 = 5.47593808499534494600E-4,
        D7 = 1.05075007164441684324E-9;

    //    Coefficients for P near 0 or 1.
    const double E0 = 6.657904643501103777200,
        E1 = 5.463784911164114369900,
        E2 = 1.784826539917291335800,
        E3 = 2.96560571828504891230E-1,
        E4 = 2.65321895265761230930E-2,
        E5 = 1.24266094738807843860E-3,
        E6 = 2.71155556874348757815E-5,
        E7 = 2.01033439929228813265E-7,
        F1 = 5.99832206555887937690E-1,
        F2 = 1.36929880922735805310E-1,
        F3 = 1.48753612908506148525E-2,
        F4 = 7.86869131145613259100E-4,
        F5 = 1.84631831751005468180E-5,
        F6 = 1.42151175831644588870E-7,
        F7 = 2.04426310338993978564E-15;

    double r;
    double z;
    double q = probability - 0.5;

    if (fabs(q) <= SPLIT1)
    {
        r = CONST1 - q * q;
        z = q * (((((((A7 * r + A6) * r + A5) * r + A4) * r + A3)
            * r + A2) * r + A1) * r + A0) /
            (((((((B7 * r + B6) * r + B5) * r + B4) * r + B3)
                * r + B2) * r + B1) * r + 1.0);
        return z;
    }

    if (q < 0.0)
    {
        r = probability;
    }
    else
    {
        r = 1.0 - probability;
    }

    if (r <= 0.0)
    {
        // TODO: throw new ArgumentOutOfRangeException("probability", probability, "Should be in [0; 1] interval.");
    }

    r = sqrt(-log(r));
    if (r <= SPLIT2)
    {
        r = r - CONST2;
        z = (((((((C7 * r + C6) * r + C5) * r + C4) * r + C3)
            * r + C2) * r + C1) * r + C0) /
            (((((((D7 * r + D6) * r + D5) * r + D4) * r + D3)
                * r + D2) * r + D1) * r + 1.0);
    }
    else
    {
        r = r - SPLIT2;
        z = (((((((E7 * r + E6) * r + E5) * r + E4) * r + E3)
            * r + E2) * r + E1) * r + E0) /
            (((((((F7 * r + F6) * r + F5) * r + F4) * r + F3)
                * r + F2) * r + F1) * r + 1.0);
    }

    if (q < 0.0)
    {
        z = -z;
    }

    return z;
}
