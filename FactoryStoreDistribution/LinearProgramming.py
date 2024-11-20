import numpy as np
import scipy.optimize as opt

#proizvodnja
f = [500,300,700,250,750]

#potraznja
p = [1000,500,200,300]

#troskovi distribucije po 10 el
c = [[10,30,50,70,20],
     [20,30,35,45,65],
     [40,10,20,15,30],
     [60,15,30,20,60]]
#troskovi distribucije po 1 el
c = [[a/10 for a in x] for x in c]
#troskovi po formatu [x11,x12,...,x54]
formatedC = []
for i in range(5):
    for j in range(4):
        formatedC.append(c[j][i])

#optimizaciona promenljiva
#[x11,x12,...,x54]
x=np.zeros(20)

#optimizaciona funkcija
def optF(x, c):
    suma = 0;
    for i in range(5):
        for j in range(4):
            suma+=x[i*4+j] * c[j][i]
    return suma

#Uslovi:
#   x1j+x2j+x3j+x4j+x5j = p[j-1]    , j in {1,..,4}
#   xi1+xi2+xi3+xi4 <= f[i-1]       , i in {1,..,5}
#   xij >=0

#unequal
A_ub = []
for i in range(5):
    rowA=[]
    for j in range(20):
        if j in range(i*4, i*4+4): rowA.append(1)
        else: rowA.append(0) 
    A_ub.append(rowA)
b_ub = [i for i in f]

#equal
A_eq = [[],[],[],[]]
for i in range(20):
    for j in range(4):
        if(i%4==j): A_eq[j].append(1)
        else: A_eq[j].append(0)
b_eq = [i for i in p]

#bounds
b = (0, None)

#check
print('A_ub:')
for i in range(5):print(A_ub[i])
print('A_eq:')
for i in range(4):print(A_eq[i])
print('Format:')
print('x11,x12,x13,x14,x21,x22,x23,x24,x31,x32,x33,x34,x41,x42,x43,x44,x51,x52,x53,x54')
print('C:')
print(formatedC)


#optimization(phase 2)

res = opt.linprog(formatedC, A_ub, b_ub,
            A_eq, b_eq,b,'highs',
            options={'disp':True,})

print('Resenje: ')
for i in res.x: print(str(int(i))+',', end='')
print('')
print('Optimization function: ' + str(res.fun))
