import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import scipy.optimize as opt
import math


#w1,..w16
#uslovi:
#   -30<=w1,..w16<=30
def a(x):
    return 1. / ( 1 + math.e**(-x))

def y_out(x_in, w):    
    suma=w[15]
    for k in range(5):
        suma += w[k+10] * a(w[k]*x_in + w[k+5])
    
    return suma
    
def f(w, xt, yt):
    suma=0
    
    for k in range(51):
        suma+=(y_out(xt[k], w) - yt[k])**2
        
    return suma/51.


data = pd.read_table("data.txt", delimiter=" ", header=None)
data=data.values
x_trening = data[:, 0]
y_trening = data[:, 1]


#%%

def wrapper(x, *args):
    #x - optimizational variables
    #args[0] - x from training
    #args[1] - y from training
    #args[2] - limit
    return f(x, args[0], args[1]) + penalty(x, args[2])

def penalty(w, limit):
    suma = 0
    for k in range(16):
        if abs(w[k]) >limit:
            suma += (limit - abs(w[k]))**2
    if suma>0:
        suma+=10
    return suma




limit = 30
epsilon = 10**-2
w = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
#w = [-40*ww for ww in w]
#print(w)
#%%

br=1
#print(solver_options)
while(True):
    res = opt.minimize(wrapper, w, args=(x_trening, y_trening, limit), 
                       method="Nelder-Mead", options={'disp':True,'return_all':True,}) 
    w = res.x
#naci kako da prikaze min vrednost opt fije
    print("Iteration"+str(br)+": " + res.message)
    br+=1
    if res.fun<epsilon: break

print("[", end='')
for i, resW in enumerate( res.x):
    
    if i==15:print("{:.15f}]".format(resW))
    else: print("{:.15f},".format(resW), end='')

#%%


plt.figure()
plt.plot(x_trening, y_trening, 'r.', label='trening')

x_map=np.linspace(0, 0.25, 100)
ypred = [y_out(x, res.x) for x in x_map]
print("f(W): "+ str(res.fun))#f(res.x, x_trening, y_trening)))

plt.plot(x_map, ypred,  'b-', label='predikcija')

plt.xlabel("x")
plt.ylabel("y")
plt.grid()
plt.legend()


