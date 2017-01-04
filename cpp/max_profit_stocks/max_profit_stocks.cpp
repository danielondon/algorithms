#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Suppose we could access yesterday's stock prices as a list, where:
// The indices are the time in minutes past trade opening time, which was 9:30am local time.
// The values are the price in dollars of Apple stock at that time.
// So if the stock cost $500 at 10:30am, stock_prices_yesterday[60] = 500.

// Write an efficient function that takes stock_prices_yesterday and returns the best 
// profit I could have made from 1 purchase and 1 sale of 1 Apple stock yesterday.

// For example:

// stock_prices_yesterday = [10, 7, 5, 8, 11, 9]
// get_max_profit(stock_prices_yesterday)
// returns 6 (buying for $5 and selling for $11)

// No "shorting"—you must buy before you sell. You may not buy and sell in the 
// same time step (at least 1 minute must pass).

void printVector(const vector<int> & stockPrices)
{
    for (int i : stockPrices)
        cout << i << " ";
    cout<<endl;
}

int get_max_profit(const vector<int> & stockPrices)
{
    // validate that vector is greater than two values
    if (stockPrices.size() <= 1)
        return 0;
    
    int maxProfit = stockPrices[1] - stockPrices[0];
    int minValue = stockPrices[0];
    for (int i  = 1; i < stockPrices.size() - 1; ++i)
    {
        if (stockPrices[i] < minValue)
            minValue = stockPrices[i];
        
        if (stockPrices[i+1] - minValue > maxProfit)
            maxProfit = stockPrices[i+1] - minValue;
    }
    
    return maxProfit;    
}

int main ()
{
    cout<<"Stocks, max profit"<<endl;
    std::vector<int> stockPrices = {10, 7, 5, 8, 11, 9};
    
    cout<<"Prices are: ";
    printVector(stockPrices);
    cout<<"Max Profit is: "<<get_max_profit(stockPrices)<<endl;

    stockPrices = {10, 7, 5, 3, 1, 0};
    cout<<"Prices are: ";
    printVector(stockPrices);
    cout<<"Max Profit is: "<<get_max_profit(stockPrices)<<endl;
    
    
    stockPrices = {1, 7, 55, 38, 99, 100};
    cout<<"Prices are: ";
    printVector(stockPrices);
    cout<<"Max Profit is: "<<get_max_profit(stockPrices)<<endl;
    
    return 0;
}