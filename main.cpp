//Completion requirement: Dimension of export subsidy
//Input: a=30, b=0.2, c=6, d=0.1 --- Test case: ceiling=8, floor=16, quota=60, tax=3, subsidy=3
//Input: world price=10 --- Test case: tariff=2, quota=30
//Input: world price=1

#include <iostream>
#include <cmath>

using namespace std;

double getEqPr(double a, double b, double c, double d);
double getEqQty(double a, double b, double c, double d);

double getInefficientPortion(double a, double b, double c, double d, double price);       //inefficient portion
double getInefficientPortion(double a, double b, double c, double d, int quota);

double getTotalSurplus(double a, double b, double c, double d, double price);
double getTotalSurplus(double a, double b, double c, double d, int qty);

double getTotalSurplus_t(double a, double b, double c, double d, double tax);
double getTotalSurplus_s(double a, double b, double c, double d, double subsidy);

double activityIncLoss(double a, double b, double c, double d, double price);
double activityIncLoss(double a, double b, double c, double d, int qty);

double deadweightLoss(double a, double b, double c, double d, double price);
double deadweightLoss(double a, double b, double c, double d, int qty);

double deadweightLoss_t(double b, double d, double tax);
double deadweightLoss_s(double b, double d, double subsidy);

double deadweightLoss(double b, double d, double tariff);
double deadweightLoss(double m, double tariff);

double dwl_prd(double a, double b, double c, double d, double price, int quota);
double dwl_imp(double a, double b, double c, double d, double price, int quota);
double dwl_tot(double a, double b, double c, double d, double price, int quota);

double getTotalSubsidy(double a, double b, double c, double d, double subsidy);

double getRevenue(double a, double b, double c, double d);
double getRevenue(double a, double b, double c, double d, double tax);
double getRevenue(double a, double b, double c, double d, double price, double tariff);
double getRevenue(double a, double b, double c, double d, double price, int quota);

double tradeGains(double a, double b, double c, double d, double price);
double tradeGains(double a, double b, double c, double d, double price, double tariff);
double tradeGains(double a, double b, double c, double d, double price, int quota);

double fastExp(double base, int exp, double acc);
double fastExp(double base, int exp);

int main()
{
    //Let's get started
    double a, b, c, d, regulator;

    cout << "Welcome to Testomics. " << endl << endl;

    cout << "Enter information for supply and demand curves. " << endl;
    cout << "Demand curve: p = a-bq\tSupply curve: p = c+dq" << endl << endl;

    cout << "Enter a: ";    cin >> a;
    cout << "Enter b: ";    cin >> b;
    cout << endl;
    cout << "Enter c: ";    cin >> c;
    cout << "Enter d: ";    cin >> d;

    cout << endl;

    cout << "Equilibrium price: " << getEqPr(a,b,c,d) << endl;
    cout << "Equilibrium quantity: " << getEqQty(a,b,c,d) << endl;
    cout << "Revenue at equilibrium: " << getRevenue(a,b,c,d) << endl;
    cout << "Total surplus at equilibrium: " << getTotalSurplus(a,b,c,d, getEqPr(a,b,c,d)) << endl;

    cout << endl;
    /*
    //Price regulated Overproduction
    cout << "Enter price floor: "; cin >> regulator;
    cout << "Excess of supply: " << getInefficientPortion(a,b,c,d, regulator) << endl;
    cout << "Loss from increased search activity: " << activityIncLoss(a,b,c,d, regulator) << endl;
    cout << "Deadweight loss: " << deadweightLoss(a,b,c,d,regulator) << endl;
    cout << "Total surplus with price regulation: " << getTotalSurplus(a,b,c,d,regulator) << endl;

    //Price regulated Underproduction
    cout << "Enter price ceiling: "; cin >> regulator;
    cout << "Shortage of supply: " << abs(getInefficientPortion(a,b,c,d, regulator)) << endl;
    cout << "Loss from increased search activity: " << activityIncLoss(a,b,c,d, regulator) << endl;
    cout << "Deadweight loss: " << deadweightLoss(a,b,c,d,regulator) << endl;
    cout << "Total surplus with price regulation: " << getTotalSurplus(a,b,c,d,regulator) << endl;

    //Qty regulated Underproduction
    cout << "Enter price quota: "; cin >> regulator;
    cout << "Shortage of supply: " << getInefficientPortion(a,b,c,d,(int)regulator) << endl;
    cout << "Deadweight loss: " << deadweightLoss(a,b,c,d, (int) regulator) << endl;
    cout << "Loss from increased activity: " << activityIncLoss(a,b,c,d, (int) regulator) << endl;
    cout << "Total surplus with quota: " << getTotalSurplus(a,b,c,d, (int) regulator) << endl;

    //Tax regulated Underproduction
    cout << "Enter tax amount: "; cin >> regulator;
    cout << "Deadweight loss: " << deadweightLoss(a,b,c,d, regulator) << endl;
    cout << "Tax revenue: " << getTaxRevenue(a,b,c,d, regulator) << endl;
    cout << "Total surplus after taxation: " << getTotalSurplus(a,b,c,d, regulator) << endl;


    double price;
    cout << "Enter world price: "; cin >> price;
    cout << endl << "Eligibility: ";
    if(price < getEqPr(a,b,c,d))
        cout << "imports";
    else
        cout << "exports";

    cout << endl << "Gains from trade: " << tradeGains(a,b,c,d,price) << endl << endl;

    if(price < getEqPr(a,b,c,d))
    {
        cout << "Enter tariff: "; cin >> regulator;
        cout << endl << "Tariff revenue:" << getRevenue(a,b,c,d,price, regulator) << endl;
        cout << "Gains from trade under tariff: " << tradeGains(a,b,c,d,price,regulator) << endl;
        cout << "Deadweight loss from higher costs of production: " << deadweightLoss(d,regulator) << endl;
        cout << "Deadweight loss from decreased number of imports: " << deadweightLoss(b,regulator) << endl;
        cout << "Total deadweight loss from tariff: " << deadweightLoss(b,d,regulator) << endl;
        //cout << "Enter quota: "; cin >> regulator;

        cout << "Enter import quota: "; cin >> regulator;
        cout << endl << "Importers revenue:" << getRevenue(a,b,c,d,price, (int)regulator) << endl;
        cout << "Gains from trade under quota: " << tradeGains(a,b,c,d,price,(int)regulator) << endl;
        cout << "Deadweight loss from higher costs of production: " << dwl_prd(a,b,c,d,price,(int)regulator) << endl;
        cout << "Deadweight loss from decreased number of imports: " << dwl_imp(a,b,c,d,price,(int)regulator) << endl;
        cout << "Total deadweight loss from tariff: " << dwl_tot(a,b,c,d,price,(int)regulator) << endl;

    }
    else
    {
    */
        cout << "Enter subsidy: "; cin >> regulator;
        cout << "Total expenditure on subsidies: " << getTotalSubsidy(a,b,c,d,regulator) << endl;
        cout << "Deadweight loss: " << deadweightLoss_s(b,d,regulator) << endl;
        cout << "Total surplus under subsidized production: " << getTotalSurplus_s(a,b,c,d,regulator) << endl;
    //}
    return 0;
}

//Equilibrium Price
double getEqPr(double a, double b, double c, double d)
{
    return (a*d+b*c)/(b+d);
}

//Equilibrium Qty
double getEqQty(double a, double b, double c, double d)
{
    return (a-c)/(b+d);
}

//excess <==> funct()
//Shortage <==> abs(funct())
double getInefficientPortion(double a, double b, double c, double d, double price)
{
    return (price-getEqPr(a,b,c,d))*(b+d)/(b*d);
}

double getInefficientPortion(double a, double b, double c, double d, int quota)
{
    return (getEqPr(a,b,c,d)-c+d*quota)*(b+d)/b/d;
}

//Surplus during underproduction
double getTotalSurplus(double a, double b, double c, double d, double price)
{
    return (b+d)/2.0*fastExp((price-c)/d,2);
    //return (b+d)/2.0*fastExp((getEqPr(a,b,c,d)-c)/d,2)
}

//Total Surplus during qty regulated underproduction
double getTotalSurplus(double a, double b, double c, double d, int qty)
{
    return (b+d)/2.0*fastExp(qty, 2);
}

//Total Surplus after tax
double getTotalSurplus_t(double a, double b, double c, double d, double tax)
{
    return fastExp(a-c-tax,2)/(b+d)/2.0;
}

double getTotalSurplus_s(double a, double b, double c, double d, double subsidy)
{
    return fastExp(a-c+subsidy,2)/(b+d)/2.0;
}

//Changes with comparison to price regulation: ceiling/floor
double activityIncLoss(double a, double b, double c, double d, double price)
{
    return (b+d)*(price-c)*(getEqPr(a,b,c,d)-price)/fastExp(d,2);
}

//Losses from increased search activity from qty regulation
double activityIncLoss(double a, double b, double c, double d, int qty)
{
    return qty*(getEqQty(a,b,c,d)-qty)*(b+d);
}

//Revenue @ Equilibrium
double getRevenue(double a, double b, double c, double d)
{
    return (a*c*(b-d)+fastExp(a,2)*d-b*fastExp(c,2) )/fastExp(b+d,2);
}

//Tax Revenue
double getRevenue(double a, double b, double c, double d, double tax)
{
    return ((a-c)*tax-fastExp(tax,2))/(b+d);
}

//Tariff Revenue
double getRevenue(double a, double b, double c, double d, double price, double tariff)
{
    return (b+d)*(getEqPr(a,b,c,d)-price-tariff)*tariff/b/d;
}

//Importers Revenue
double getRevenue(double a, double b, double c, double d, double price, int quota)
{
    return (getEqPr(a,b,c,d) - price - b*d*quota/(b+d) ) * quota;
}

//Total expenditure on subsidies
double getTotalSubsidy(double a, double b, double c, double d, double subsidy)
{
    return (a-c+subsidy)*subsidy/(b+d);
}

//Changes with comparison to price ceiling vs floor
double deadweightLoss(double a, double b, double c, double d, double price)
{
    return (b+d)/2.0*fastExp((getEqPr(a,b,c,d)-price)/d, 2);
}

//Deadweight loss from qty regulation
double deadweightLoss(double a, double b, double c, double d, int qty)
{
    return (b+d)/2.0*fastExp(getEqQty(a,b,c,d)-qty,2);
}

//Deadweight loss from taxation
double deadweightLoss_t(double b, double d, double tax)
{
    return fastExp(tax,2)/(b+d)/2.0;
}

//Deadweight loss from subsidies
double deadweightLoss_s(double b, double d, double subsidy)
{
    return fastExp(subsidy,2)/(b+d)/2.0;
}

//Deadweight loss from tariff imposition
double deadweightLoss(double b, double d, double tariff)
{
    return (b+d)*fastExp(tariff,2)/b/d/2.0;
}

//dwl_prd(b,...)
//dwl_imp(d,...)
double deadweightLoss(double m, double tariff)
{
    return fastExp(tariff,2)/m/2.0;
}

//dwl from higher costs of production under import quota
double dwl_prd(double a, double b, double c, double d, double price, int quota)
{
    return fastExp(getEqPr(a,b,c,d)-price-((b*d)/(b+d)*quota),2)/b/2.0;
}

//dwl from decreased number of imports under quota
double dwl_imp(double a, double b, double c, double d, double price, int quota)
{
    return fastExp(getEqPr(a,b,c,d)-price-((b*d)/(b+d)*quota),2)/d/2.0;
}

//dwl_total = dwl_prd + dwl_imp --> Total deadweight loss from import quota
//dwl_imp(d,b,...), dwl_prd(b,d,...)
double dwl_tot(double a, double b, double c, double d, double price, int quota)
{
    return fastExp(getEqPr(a,b,c,d)-price-((b*d)/(b+d)*quota),2)*(b+d)/(b*d)/2.0;
}
/*
    Switch b and d during function calls for dwl_prd and dwl_imp
    when equilibrium price can be calculated independently without
    function parameters
*/

//Trade gains from import/export
double tradeGains(double a, double b, double c, double d, double price)
{
    return fastExp(price-getEqPr(a,b,c,d),2)*(b+d)/b/d/2.0;
}

//Trade gains under tariff
double tradeGains(double a, double b, double c, double d, double price, double tariff)
{
    return (b+d)*fastExp(getEqPr(a,b,c,d)-price-tariff,2)/b/d/2.0;
}

//Trade gains under quota
double tradeGains(double a, double b, double c, double d, double price, int quota)
{
    return b*d*fastExp(quota,2)/(b+d)/2;
}

//Fast Exponential Loop Defined
double fastExp(double base, int exp)
{
    double acc = 1.0;

    while(exp != 0)
    {
        if(exp % 2 == 0) {
            base *= base;
            exp /= 2;
        }
        else
        {
            exp -= 1;
            acc *= base;
        }
    }
    return acc;
}

//Fast Exponential Recursive
double fastExp(double base, int exp, double acc)
{
    if(exp == 0)
        return acc;
    else if(exp % 2 == 0)
        return fastExp(base * base, exp/2, acc);
    else
        return fastExp(base, exp-1, base * acc);
}
