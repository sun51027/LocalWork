# define a module yourself
def fib(n):
	a,b=0,1
	while a<n:
		print(a)
		a,b=b,a+b
print('Print a Fibonacci series up to 1000:')
print fib(1000)

