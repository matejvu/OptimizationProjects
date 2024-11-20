# -*- coding: utf-8 -*-
"""
Created on Wed Dec 13 01:00:28 2023

@author: matej
"""



import matplotlib.pyplot as plt
import numpy as np

import pandas as pd
ime="data"

minimum = 2**26

#avgCM
fajl = open("data0.txt", "r")
data = (fajl.read()).split(",")
data = [int(x) for x in data[0:-1]]
data = np.array(data)
avgCM = np.zeros(data.shape[0])

print(data.shape)

p1 = plt.figure()
for i in range(20):
    imeFajla = ime+str(i)+".txt"

    fajl = open(imeFajla, "r")

    data = (fajl.read()).split(",")

    data = [int(x) for x in data[0:-1]]
    data = np.array(data)
    iterations = [i for i in range(data.shape[0])]

    plt.loglog( iterations, data, label="run"+str(i+1))
    
    avgCM +=data
    
    
  

plt.xlabel("iterations")
plt.ylabel("cummulative minimum")

#plt.xlim(0, 5*10**6)
#plt.ylim(0, 10**8)
plt.show()
#plt.legend()


 #%%
plt.figure()

avgCM = [x/20 for x in avgCM]
plt.loglog(iterations, avgCM, "r-")
plt.xlabel("iterations")
plt.ylabel("average cummulative minimum")

plt.xlim(0, 5*10**6)
plt.ylim(0, 10**8)
plt.show()
