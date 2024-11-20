import numpy as np
import matplotlib.pyplot as plt
import math as m
import random as rand

#PSO

def distance(x1,x2):
    return m.sqrt((x1[0]-x2[0])**2+(x1[1]-x2[1])**2+(x1[2]-x2[2])**2 )
def distance6d(x1,x2):
    xx1 = np.array(x1)
    xx2 = np.array(x2)
    return m.sqrt((xx1-xx2)**2)
    
def f(x):
    values = [10*v for v in x]
    S1=[0,0,0]
    S2=[0,0,0]
    S1[0], S1[1], S1[2] = values[0],values[1],values[2]
    S2[0], S2[1], S2[2] = values[3],values[4],values[5]
    
    rez = distance(A,S1) + distance(B,S1) + distance(C,S1) + distance(D,S2) + distance(E,S2) + distance(F,S2) +distance(S1,S2)  
    return rez


def updateSpeed():
    for i, a in enumerate(agents):
        vn_1 = np.array(speeds[i].copy())
        pi = (np.array(pminP[i].copy()))
        gi = np.array(gminP.copy())
        agent = np.array(a.copy())
        vn = w*vn_1+ c1*rand.random()*(pi - agent) + c2*rand.random()*(gi - agent)
        speeds[i] = vn.tolist()
def translate():
    for i, a in enumerate(agents):
      newa = [(a[ind] + speeds[i][ind]) for ind in range(6)]
      #print("newa",newa)
      agents[i] = [vr for vr in newa]
def checkStoping(epsilon):
    for agent in agents:
        if(distance(gminP, agent)>epsilon):return False
    return True

N=50
c1=c2=1.494
vmax=0.2
w=0.8
A=[1,4,0]
B=[3,2,0]
C=[2,7,1]
D=[6,3,3]
E=[7,6,5]
F=[5,7,4]
rand.seed(123)

agents = [[rand.uniform(-1, 1) for i in range(6)] for agent in range(N)]
speeds = [[0 for axis in range(6)] for i in range(N)]
'''pminP = np.array([[i for i in x] for x in agents])
pminV = [f(x) for x in pminP]
gminV = min(pminV)
gminP = pminP[pminV.index(gminV)]'''


#print(pminP)
#print(pminV)
#print(gminV)
#print(gminP)
brIter=0
while True:
    #print("1 ",agents[0])
    pminP = [[i for i in x] for x in agents]
    pminV = [f(x) for x in pminP]
    gminV = min(pminV)
    gminP = pminP[pminV.index(gminV)]
    #print("2", speeds[0])
    updateSpeed()
   # print("3", speeds[0])
    translate()
    #print("4 ",agents[0])
    print("Najmanji min za iteraciju[%d] je: %f"%(brIter, gminV))
   
    brIter+=1
    
    if(checkStoping(10**-3)):break
print(10*np.array(gminP))