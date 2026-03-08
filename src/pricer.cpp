#include "pch.h"

double Pricer(
	double Fwd,
	double K,
	double T,
	double CPFlag,
	double R,
	double vol)
{
	StandardNormalDistribution c;
	double	PV,
		newRate,
		d1, d2,
		Nd1, Nd2;

	newRate = log(1 + R);
	PV = exp(-newRate * T);
	d1 = (log(Fwd / K) + 0.5 * T * pow(vol, 2)) / (vol * sqrt(T));
	d2 = d1 - vol * sqrt(T);
	Nd1 = c.NormSDist(CPFlag * d1);
	Nd2 = c.NormSDist(CPFlag * d2);
	
    return (CPFlag * PV * (Fwd * Nd1 - K * Nd2));
}

double getDelta(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma, double Borrow)
{
	double bump, df,
		upFwd, downFwd;

    bump = 0.01;
	upFwd = Forward * (1 + bump);
	downFwd = Forward * (1 - bump);
    df = ( pow(((1 + Rate) / (1 + Borrow)), Tau) );
	
	return ( (df * (Pricer(upFwd, Strike, Tau, Flag, Rate, Sigma) - Pricer(downFwd, Strike, Tau, Flag, Rate, Sigma))) / (2 * Forward * bump) );
}

double getVegaRaph(double Vol, double Forward, double Strike, double Tau, double Flag, double Rate)
{
	double bump,
		upVol, downVol;

	bump = 0.0005; // 5 bps increments
	upVol = Vol + bump;
	downVol = Vol - bump;

	return ((Pricer(Forward, Strike, Tau, Flag, Rate, upVol) - Pricer(Forward, Strike, Tau, Flag, Rate, downVol)) / (2 * bump) * 0.01);
}

double getVega(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma)
{
	double bump,
		upVol, downVol;

	bump = 0.01;
	upVol = Sigma + bump;
	downVol = Sigma - bump;
	return((Pricer(Forward, Strike, Tau, Flag, Rate, upVol) - Pricer(Forward, Strike, Tau, Flag, Rate, downVol)) / (2 * bump) * 0.01);
}

double getDivOne(double	Tau, double Rate, double Fwd)
{
	return ( Tau / (1 + Rate) * Fwd );
}

double getDivOneBorrow(double Tau, double Borrow, double Fwd)
{
	return ( ((-1) * Tau) / (1 + Borrow) * Fwd);
}

double getRho(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma)
{
	double bump,
		upRate, downRate,
		upFwd, downFwd;

	bump = 0.0005; //5 bps increments
	upRate = (Rate + bump);
	downRate = (Rate - bump);
	upFwd = Forward + getDivOne(Tau, Rate, Forward) * bump;
	downFwd = Forward - getDivOne(Tau, Rate, Forward) * bump;

	return( (Pricer(upFwd, Strike, Tau, Flag, upRate, Sigma) - Pricer(downFwd, Strike, Tau, Flag, downRate, Sigma)) / (2 * bump) * 0.0001 );
}

double getRhoBorrow(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma, double Borrow)
{
    double bump,
        upRate, downRate,
        upFwd, downFwd;

    bump = 0.0005; // 5 bps increments
    upRate = (Borrow + bump); 
    downRate = (Borrow - bump);
    upFwd = (Forward + getDivOneBorrow(Tau, Borrow, Forward) * bump);
    downFwd = (Forward - getDivOneBorrow(Tau, Borrow, Forward) * bump);
        
    return( ((Pricer(upFwd, Strike, Tau, Flag, Rate, Sigma) - Pricer(downFwd, Strike, Tau, Flag, Rate, Sigma)) / (2 * bump)) * 0.0001);
}

double getTheta(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma)
{
    double downTau;

    if (Tau < (static_cast<double>(1) / daycount))
    {
        return (Pricer(Forward, Strike, Tau, Flag, Rate, Sigma));
    }
    else
    {
        downTau = (Tau - static_cast<double>(1) / daycount);

        return (Pricer(Forward, Strike, downTau, Flag, Rate, Sigma) - Pricer(Forward, Strike, Tau, Flag, Rate, Sigma));
    }     
}
 
double getGamma(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma)
{
    double bump,
        upFwd, downFwd,
        pxUp, px, pxDown;

    bump = 0.01;
    upFwd = (Forward * (1 + bump));
    downFwd = (Forward * (1 - bump));
    pxUp = Pricer(upFwd, Strike, Tau, Flag, Rate, Sigma);
    px = Pricer(Forward, Strike, Tau, Flag, Rate, Sigma);
    pxDown = Pricer(downFwd, Strike, Tau, Flag, Rate, Sigma);
        
    return((pxUp - 2 * px + pxDown) / (pow((Forward * bump), 2)) * (0.01 * pow(Forward, 2)));
}

double getSpeed(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma,double Borrow)
{
    double bump,
        upupFwd, upFwd, downFwd,
        pxUpUp, pxUp, px, pxDown, df;

    bump = 0.01;
    df = pow(((1 + Rate) / (1 + Borrow)), Tau);
    bump = 0.01;
    upupFwd = (Forward * (1 + 2 * bump));
    upFwd = (Forward * (1 + bump));
    downFwd = Forward * (1 - bump);
    pxUpUp = Pricer(upupFwd, Strike, Tau, Flag, Rate, Sigma);
    pxUp = Pricer(upFwd, Strike, Tau, Flag, Rate, Sigma);
    px = Pricer(Forward, Strike, Tau, Flag, Rate, Sigma);
    pxDown = Pricer(downFwd, Strike, Tau, Flag, Rate, Sigma);
        
    return((pxUpUp - 3 * pxUp + 3 * px - pxDown) / (pow((Forward * bump), 3)) * pow(df, 3) * (0.01 * (Forward / df)));
}

double getVanna(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma, double Borrow)
{
    double bump,
        upFwd, downFwd,
        upVol, downVol,
        pxUpSUpV, pxUpSDownV, pxDownSUpV, pxDownSDownV,df;

    bump = 0.01;
    df = pow(((1 + Rate) / (1 + Borrow)), Tau);
    bump = 0.01;
    upFwd = (Forward * (1 + bump));
    downFwd = (Forward * (1 - bump));
    upVol = Sigma + bump;
    downVol = Sigma - bump;
    pxUpSUpV = Pricer(upFwd, Strike, Tau, Flag, Rate, upVol);
    pxUpSDownV = Pricer(upFwd, Strike, Tau, Flag, Rate, downVol);
    pxDownSUpV = Pricer(downFwd, Strike, Tau, Flag, Rate, upVol);
    pxDownSDownV = Pricer(downFwd, Strike, Tau, Flag, Rate, downVol);
    
    return( (pxUpSUpV - pxUpSDownV - pxDownSUpV + pxDownSDownV) / (4 * bump * Forward * bump) * df );
}

double getCharm(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma, double Borrow)
{
    double downTau, df,
        currentDelta, tomDelta,
        bump, upFwd, downFwd;

    currentDelta = getDelta(Forward, Strike, Tau, Flag, Rate, Sigma, Borrow);
    if (Tau < static_cast<double>(1) / daycount)
    {
        return (- 1 * currentDelta);
    }
    else
    {
        downTau = (Tau - static_cast<double>(1) / daycount);
        bump = 0.01;
        upFwd = (Forward * (1 + bump));
        downFwd = (Forward * (1 - bump));
        df = (pow(((1 + Rate) / (1 + Borrow)), Tau));
        tomDelta = (df * (Pricer(upFwd, Strike, downTau, Flag, Rate, Sigma) - Pricer(downFwd, Strike, downTau, Flag, Rate, Sigma)) / (2 * Forward * bump));

        return (tomDelta - currentDelta);
    }
}

double getVolga(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma)
{
    // financial volga: every 1% move in sigma, how much VegaP changes
    double bump,
        upVol, downVol,
        pxUp, px, pxDown;

    bump = 0.01;
    upVol = (Sigma + bump);
    downVol = (Sigma - bump);
    pxUp = Pricer(Forward, Strike, Tau, Flag, Rate, upVol);
    px = Pricer(Forward, Strike, Tau, Flag, Rate, Sigma);
    pxDown = Pricer(Forward, Strike, Tau, Flag, Rate, downVol);
        
    return((pxUp - 2 * px + pxDown) / (pow(bump, 2)) * (pow(0.01, 2)));
}

double getCollor(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma, double Borrow)
{
    double downTau,
        currentGamma, tomGamma,
        bump, upFwd, downFwd;

    currentGamma = getGamma(Forward, Strike, Tau, Flag, Rate, Sigma);
    if (Tau < static_cast<double>(1) / daycount)
    {
        return (- 1 * currentGamma);
    }
    else
    {
        double pxUp, px, pxDown;

        downTau = (Tau - static_cast<double>(1) / daycount);
        bump = 0.01;
        upFwd = (Forward * (1 + bump));
        downFwd = (Forward * (1 - bump));
        pxUp = Pricer(upFwd, Strike, downTau, Flag, Rate, Sigma);
        px = Pricer(Forward, Strike, downTau, Flag, Rate, Sigma);
        pxDown = Pricer(downFwd, Strike, downTau, Flag, Rate, Sigma);
        tomGamma = ((pxUp - 2 * px + pxDown) / (pow((Forward * bump), 2)) * (0.01 * pow(Forward, 2)));

        return (tomGamma - currentGamma);
    }
}

double getVegaBleed(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma)
{
    double downTau,
        currentVega, tomVega,
        bump, upSigma, downSigma;

    currentVega = getVega(Forward, Strike, Tau, Flag, Rate, Sigma);
    if (Tau < static_cast<double>(1) / daycount)
    {
        return (-1 * currentVega);
    }
    else
    {
        double pxUp, pxDown;
        downTau = (Tau - static_cast<double>(1) / daycount);
        bump = 0.01;
        upSigma = (Sigma + bump);
        downSigma = (Sigma - bump);
        pxUp = Pricer(Forward, Strike, downTau, Flag, Rate, upSigma);
        pxDown = Pricer(Forward, Strike, downTau, Flag, Rate, downSigma);
        tomVega = ((pxUp - pxDown) / (2 * bump) * 0.01);
        
        return (tomVega - currentVega);
    }
}

double getThetaBleed(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma)
{
    double downTau, downdownTau,
        currentTheta, tomTheta;

    currentTheta = getTheta(Forward, Strike, Tau, Flag, Rate, Sigma);
    if (Tau < (static_cast<double>(2) / daycount))
    {
        return (-1 * currentTheta);
    }
    else
    {
        downTau = (Tau - static_cast<double>(1) / daycount);
        downdownTau = (Tau - static_cast<double>(2) / daycount);
        tomTheta = Pricer(Forward, Strike, downdownTau, Flag, Rate, Sigma) - Pricer(Forward, Strike, downTau, Flag, Rate, Sigma);
        
        return (tomTheta - currentTheta);
    }
}

double getZomma(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma)
{
    double pxUpSUpV, pxUpSDownV, pxDownSUpV, pxDownSDownV, pxUpV, pxDownV;
        
    double bump = 0.01;
    pxUpSUpV = Pricer(Forward * (1 + bump), Strike, Tau, Flag, Rate, Sigma + bump);
    pxUpSDownV = Pricer(Forward * (1 + bump), Strike, Tau, Flag, Rate, Sigma - bump);
    pxDownSUpV = Pricer(Forward * (1 - bump), Strike, Tau, Flag, Rate, Sigma + bump);
    pxDownSDownV = Pricer(Forward * (1 - bump), Strike, Tau, Flag, Rate, Sigma - bump);
    pxUpV = Pricer(Forward, Strike, Tau, Flag, Rate, Sigma + bump);
    pxDownV = Pricer(Forward, Strike, Tau, Flag, Rate, Sigma - bump);
    
    return ((1 / (2 * bump * pow((Forward * bump),2))) * (pxUpSUpV - 2 * pxUpV + pxDownSUpV - pxUpSDownV + 2 * pxDownV - pxDownSDownV) * 0.01 * (0.01 * pow(Forward, 2)));
}

double getGammaBkeven(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma, double Borrow)
{
    return (sqrt(-1 * getTheta(Forward, Strike, Tau, Flag, Rate, Sigma) / (50 * getGamma(Forward, Strike, Tau, Flag, Rate, Sigma))));
}

double getVolgaBkeven(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma)
{
     return (0.01 * sqrt(-2 * getTheta(Forward, Strike, Tau, Flag, Rate, Sigma) / getVolga( Forward,  Strike,  Tau,  Flag,  Rate,  Sigma)));
}

double getVVol(double Forward, double Strike, double Tau, double Flag, double Rate, double Sigma)
{
    double deltaVol = getVolgaBkeven(Forward, Strike, Tau, Flag, Rate, Sigma);

    return (log((Sigma + deltaVol) / Sigma) * sqrt(daycount)); 
}

