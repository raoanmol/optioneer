#include <iostream>
#include <cmath>

using namespace std;

// Function prototypes
double calculate_call_price(double, double, double, double, double, double);
double calculate_put_price(double, double, double, double, double, double);
double normal_cdf(double);

int main()
{
    // Input params
    double time_to_maturity = 0;        // year(s)
    double strike_price = 0;            // USD
    double stock_price = 0;             // USD
    double dividend_yield = 0;          // %
    double risk_free_rate = 0;          // %
    double volatility = 0;              // %

    // Output params
    double call_price = 0;
    double put_price = 0;

    // Reading
    cout << "Black-Scholes Option Price Calculator" << endl << endl;
    cout << "Enter the current stock price (USD): ";
    cin >> stock_price;
    cout << "Enter the strike price (USD): ";
    cin >> strike_price;
    cout << "Enter the time to maturity (years): ";
    cin >> time_to_maturity;
    cout << "Enter the dividend yield (%): ";
    cin >> dividend_yield;
    cout << "Enter the volatility (%): ";
    cin >> volatility;
    cout << "Enter the risk-free interest rate (%): ";
    cin >> risk_free_rate;

    // Pre-processing
    dividend_yield /= 100;
    volatility /= 100;
    risk_free_rate /= 100;

    // Calculating options price
    call_price = calculate_call_price(stock_price, strike_price, time_to_maturity, risk_free_rate, dividend_yield, volatility);
    put_price = calculate_put_price(call_price, stock_price, strike_price, time_to_maturity, risk_free_rate, dividend_yield);

    // Making sure values are non negative
    call_price = max(call_price, 0.0);
    put_price = max(put_price, 0.0);

    // Output:
    cout << "============================================" << endl;
    printf("Call option price: $%.2f\n", call_price);
    printf("Put option price: $%.2f\n", put_price);
}

// Normal cumulative distribution
double normal_cdf(double d1)
{
    return (0.5 * (1 + erf(d1 / sqrt(2))));
}

/* 
 * S: current stock price
 * K: strike price
 * T: time to maturity
 * r: risk-free rate yield
 * q: dividend yield
 * sigma: volatility
 */
double calculate_call_price(double S, double K, double T, double r, double q, double sigma)
{
    // Calculating d1 and d2
    double d1 = (log(S / K) + (r - q + 0.5 * pow(sigma, 2)) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    // Calculating call price
    return S * exp(-q * T) * normal_cdf(d1) - K * exp(-r * T) * normal_cdf(d2);
}

double calculate_put_price(double call_price, double S, double K, double T, double r, double q)
{
    return call_price - S * exp(-q * T) + K * exp(-r * T);
}
