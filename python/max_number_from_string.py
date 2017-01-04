def sortCriteria(num1, num2):
	return int( str(num2) + str(num1)) -  int(str(num1) + str(num2)) 

def getMaxNumber(numbers):
	numbers.sort(cmp = sortCriteria)
	# Join list into a string
	# join expects a string , therefore convert it to a string before
	return ''.join(str(n) for n in numbers)

# Example 1
# numbers [90, 9, 8]
# res = "9908"

# Example 2
# numbers [59, 5, 8]
# res = "8595"
if __name__ == "__main__":
	
	#numbers = [90, 9, 8]
	numbers = [59, 5, 8]
	res = getMaxNumber(numbers)
	print "Max number is" , res