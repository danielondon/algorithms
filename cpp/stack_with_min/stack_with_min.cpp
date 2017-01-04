#include <iostream>
#include <stack>

using namespace std;

// How would you design a stack which, in addition to push and pop, also has a function
// min which returns the minimum element? Push, pop and min should all operate in
// O(1) time.


struct Element
{
    Element(int _value, int _min) : value(_value), min(_min) {}
    int value;
    int min;
};

struct StackMin
{
    StackMin()
    {}
    
    std::stack<Element> elements;
    
    void pop()
    {
        elements.pop();
    }
    
    void push(int value)
    {
        int min;
        if (empty())
        {
            min = value;
        }
        else if (value < elements.top().min)
        {
            min = value;
        }
        else
        {
            min = elements.top().min;
        }
        
        elements.push(Element(value, min));   
    }
    
    int top()
    {
        return elements.top().value;
    }
    
    bool empty()
    {
        return elements.empty();
    }
    
    int minValue()
    {
        return elements.top().min;
    }
};

void printStack(StackMin stack)
{
    cout<<"From Top to Bottom: ";
    while(!stack.empty())
    {
        cout<<stack.top()<< " ";
        stack.pop();
    }
    cout<<endl;
}

int main ()
{
    cout<<"Stack with min value"<<endl;
    StackMin stack;
    stack.push(10);
    stack.push(5);
    stack.push(1);
    stack.push(3);
    stack.push(2);
    
    cout<<"Stack is: ";
    printStack(stack);
    cout<<"Min value is "<<stack.minValue()<<endl;
    
    stack.pop();
    stack.pop();
    stack.pop();
    
    cout<<"Stack is: ";
    printStack(stack);
    cout<<"Min value is "<<stack.minValue()<<endl;
    
    stack.push(1);
    stack.push(-1);
    stack.push(0);
    stack.pop();
    stack.pop();
    
    cout<<"Stack is: ";
    printStack(stack);
    cout<<"Min value is "<<stack.minValue()<<endl;
    
    stack.push(-1);
    
    cout<<"Stack is: ";
    printStack(stack);
    cout<<"Min value is "<<stack.minValue()<<endl;
    
    return 0;
}