#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator> // for ostream_iterator
#include <algorithm>
#include <stack>

using namespace std;

// You have a list of integers, and for each index you want to find the product 
// of every integer except the integer at that index.
// Write a function get_products_of_all_ints_except_at_index() that takes a list 
// of integers and returns a list of the products.


void printVector(const vector<int> & numbers)
{
    //for (int i : numbers)
    //    cout << i << " ";
    //std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::for_each(numbers.cbegin(), numbers.cend(), [] (const int c) {std::cout << c << " ";} );
    cout<<endl;
}

void get_products_of_all_ints_except_at_index(vector<int> & listIntegers )
{
    size_t size = listIntegers.size();
    vector<int> products(size);
    int res = 1;
    for (int i = 0; i < size; ++i)
    {
        // Calculate Product 
        products[i] = res;
        res *= listIntegers[i];
    }
    
    res = 1;
    for (int i = size - 1; i >= 0; --i)
    {
        products[i] = res*products[i];
        res *= listIntegers[i];
        
        // Place the result in the same vector
        listIntegers[i] = products[i];
    }
}

int main ()
{
    cout<< "Problem :  get_products_of_all_ints_except_at_index " <<endl<<endl;
    std::vector<int> listNumbers = {1, 2, 3, 4}; 
    
    cout<< "Original Vector: "; 
    printVector(listNumbers);

    get_products_of_all_ints_except_at_index(listNumbers);
    
    cout<< "Result Vector: ";
    // Expected Output  : [ 24, 12, 8, 6 ]
    printVector(listNumbers);
    
    
    listNumbers = {2, 3, 5, 4, 2, 10, 7,1,2,1,2}; 
    
    cout<< "Original Vector: "; 
    printVector(listNumbers);

    get_products_of_all_ints_except_at_index(listNumbers);
    
    cout<< "Result Vector: ";
    printVector(listNumbers);
}