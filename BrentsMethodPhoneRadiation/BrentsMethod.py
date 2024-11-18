import numpy as np
import matplotlib.pyplot as plt
import math


def Fs(n,delta, beta, d, theta):
    fi = delta+beta*d*math.cos(theta)
    retVal = 0
    for k in range(n):
        retVal+=math.e**(k*fi*(-1j))
    
    return retVal




def ModulFs(n,delta, beta, d, theta):
    FsVal = Fs(n, delta, beta, d, theta)
    return math.sqrt(FsVal.real**2 + FsVal.imag**2)


n=6
beta=20*math.pi
theta=math.pi/3
d=1/20
epsilon = 10**(-7)

deltas = np.linspace(0, math.pi*2, 200)

y = [ModulFs(n,delta,beta,d,theta) for delta in deltas]




f =plt.figure()
plt.plot( deltas, y, "b-", label="|F|")
plt.xlabel("$\delta$")
plt.ylabel("|Fs|")
plt.grid()
plt.show()



#Brentov metod
def Brent(func, neighbourhood, epsilon):
    
    x1=neighbourhood[0]
    x2=(neighbourhood[0]+neighbourhood[1])/2
    x3=neighbourhood[1]
    x=[x1,x2,x3]
    pastVal = func(n, x1 , beta, d, theta)
    
    
    while(1):
        print("x = {}".format(x))
        matrix_x = [[el**2, el, 1] for el in x]
        f = [func(n, delta, beta, d, theta) for delta in x]
        
        inverse_matrix = np.linalg.inv(matrix_x)
        [a, b, c] = inverse_matrix.dot(f)
        x_max = -b/(2*a)
        print("x_max = {}".format(x_max))
        
        #is precise enough
        currVal = func(n, x_max, beta, d, theta)
        print("f(x_max) = {} ".format(currVal))
        if(abs(currVal-pastVal)<epsilon):
            print("Kraj!")
            return
        else: 
            pastVal = currVal
        
        #new x
        x.append(x_max)
        f.append(func(n, x_max, beta, d, theta))
        fmin = min(f)
        i = f.index(fmin)
        x.pop(i)
        
        
        print("-----------------------------------------------------------------------")
        
        
        
        
Brent(ModulFs, [4,5], epsilon)
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    