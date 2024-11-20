import random
import numpy as np
import math

S=[ -0.09940112332480822, -0.09570265063923192, -0.07782620994584906,
 -0.044595775065571636, -0.008470411838648773, -0.0013292572938769093,
 -0.01402876134848341, 0.0011785680597112547, -0.0016096599564817682,
 -0.03141072397571561, -0.05773121434057853, -0.07098734083487862,
 -0.07421256224434619, -0.09674779542915338, -0.13216942328836218,
 -0.18406033359301877, -0.24214426775005213, -0.25978279767024376,
 -0.2186443973931424, -0.3289283483195699, -0.4205252223787085,
 -0.32130499477499636, -0.205134242990832, -0.13760381018149595]

x = [i for i in range(-15,16,5)]
y = [i for i in range(-15,16,5)]

sensorCoordinates = [(xx, -15) for xx in x]
for i in y[1:]:
    sensorCoordinates.append((15,i))
for i in x[-2::-1]:
    sensorCoordinates.append((i, 15))
for i in y[-2:0:-1]:
    sensorCoordinates.append((-15, i))
    
print(len(sensorCoordinates))




#x = (xp1,yp1,xp2,yp2,A1,A2)

def selectRandom(population):
    choosen = (int) (random.random()*len(population))
    return population[choosen]

def f(x, sensorNum):
    suma=0
    xp1,yp1,xp2,yp2,A1,A2 = x[0],x[1],x[2],x[3],x[4],x[5]
    

    for i in range(sensorNum):
        xi,yi = sensorCoordinates[i][0], sensorCoordinates[i][1]
        si = S[i]
        suma+=(A1/math.sqrt((xi-xp1)**2 + (yi-yp1)**2) + 
               A2/math.sqrt((xi-xp2)**2 + (yi-yp2)**2) -
               si)**2
    return suma + penalty(x)

def penalty(x):
    xp1,yp1,xp2,yp2,A1,A2 = x[0],x[1],x[2],x[3],x[4],x[5]
    if(abs(xp1)>15 or abs(xp2)>15 or abs(yp1)>15 or abs(yp2)>15 
       or abs(A1)>15 or abs(A2)>15):return 3000000
    return 0
    

def generatePopulationZero(Npop, limitL, limitH):
    Arange=10
    Amin=-5
    population=[]
    for i in range(Npop):
        newX = [random.random()*(limitH-limitL) + limitL,random.random()*(limitH-limitL) + limitL,
                random.random()*(limitH-limitL) + limitL,random.random()*(limitH-limitL) + limitL,
                random.random()*Arange + Amin, random.random()*Arange + Amin ]
        population.append(newX)
    return population
    
    
    
population = generatePopulationZero(50, -15, 15)
generation = 40
epsilon = 10**(-16)
F = 0.8
CR = 0.9
D = 6


minX=[0 for x in range(6)]
minF = 2**20

while(minF>epsilon):
    
    for ind, x in enumerate(population):
        
        #generate xa,xb,xc
        xa = selectRandom(population)
        while(xa == x): xa = selectRandom(population)
        xb = selectRandom(population)
        while(xb == x or xb==xa): xb = selectRandom(population)
        xc = selectRandom(population)
        while(xc == x or xc==xa or xc==xb): xc = selectRandom(population)
        
        #calculate z
        z = np.array(xa) + F*(np.array(xb) - np.array(xc))
        
        #choose R
        R = math.floor(random.random()*6)
        
        #generate y
        y=[]
        for i in range(len(x)):
            ri = random.random()
            if(ri<CR or i==R):
                y.append(z[i])
            else:
                y.append(x[i])
        
        fx = f(x, 24)
        fy = f(y, 24)
        if(fx<minF):
            minF = fx
            minX = [xx for xx in x]
        if(fy<fx):
            population[ind] = y
        
    print(minF)
print(minF)
print(minX)      
        
print(f([-8.500000105349315, 5.000000137059198, 6.5000002314768315,
         -6.499999901876407, -2.9999999534993194, 0.9999999689759355],24))
   
    