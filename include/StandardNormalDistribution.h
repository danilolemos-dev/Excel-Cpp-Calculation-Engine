#pragma once

class StandardNormalDistribution
{
    /// <summary>
    /// Alias para o método StandardCumulative desta classe, com o mesmo nome que a função equivalente do Excel em inglês
    /// </summary>
    /// <param name="z">Is the value for which you want the distribution</param>
    /// <returns>
    /// Returns the standard normal cumulative distribution function.
    /// The distribution has a mean of 0 (zero) and a standard deviation of one.
    /// Use this function in place of a table of standard normal curve areas.
    /// </returns>
public:
    double NormSDist(double z);
    double ProbabilityDensityFunction(double x);
    double Probability(double minValue, double maxValue);
    double DistributionFunction(double z);
    double SurvivorDistributionFunction(double z);
    double NormSInv(double probability);
    double InverseDistributionFunction(double probability);
};

