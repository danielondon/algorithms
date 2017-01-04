from copy import deepcopy

# How would you design a stack which, in addition to push and pop, also has a function
# min which returns the minimum element? Push, pop and min should all operate in
# O(1) time.


class Element:
    def __init__(self, _value, _min):
        self.value = _value
        self.min = _min
        
class StackMin:

    def __init__(self):
        self.elements = []
        
    def pop(self):
        self.elements.pop()
    
    def push(self, value):
        if self.empty():
            min = value
        elif value < self.elements[len(self.elements)-1].min:
            min = value
        else:
            min = self.elements[len(self.elements)-1].min

        self.elements.append(Element(value, min))
    
    def top(self):
        return self.elements[len(self.elements)-1].value
    
    def empty(self):
        return len(self.elements) == 0
    
    def minValue(self):
        return self.elements[len(self.elements)-1].min
        
    
# We assume we pass a copy to the print function
# Therefore we can pop the elements, in case
# a reference is passed, then use the iterator of
# arrays to print the stack.
def printStack(stack):
    text = ""
    while not stack.empty() :
        text += str(stack.top()) + " "
        stack.pop()
        
    print "From Top to Bottom:", text

if __name__ == "__main__":
    print "Stack with min value"
    stack = StackMin()
    stack.push(10)
    stack.push(5)
    stack.push(1)
    stack.push(3)
    stack.push(2)
    
    print "Stack is: "
    printStack(deepcopy(stack))
    print "Min value is ", stack.minValue()
    
    stack.pop()
    stack.pop()
    stack.pop()
    
    print "Stack is: "
    printStack(deepcopy(stack))
    print "Min value is ", stack.minValue()
    
    stack.push(1)
    stack.push(-1)
    stack.push(0)
    stack.pop()
    stack.pop()
    
    print "Stack is: "
    printStack(deepcopy(stack))
    print "Min value is ", stack.minValue()
    
    stack.push(-1)
    
    print "Stack is: "
    printStack(deepcopy(stack))
    print "Min value is ", stack.minValue()