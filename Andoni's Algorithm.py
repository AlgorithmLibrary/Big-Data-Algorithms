# -*- coding: utf-8 -*-
"""
Created on Thu Feb 11 09:40:34 2021

@author: Grant
"""

import random
import math
import numpy
import statistics

def chunks(l, n):
    n = max(1, n)
    return (l[i:i+n] for i in range(0, len(l), n))

n = 15
m = 11
seed = 5

x = [1, 3, 5, 11, 15, 21, 18, 19, 5, 8, 23, 35, 9, 16, 38]

p = 3

P = [[0 for i in range(n)] for j in range(m)]

for a in range(n):
    random_row = random.randrange(m)
    random_sign = random.randrange(2)
    
    if random_sign == 1:
        P[random_row][a] = 1
    else:
        P[random_row][a] = -1

D = []

for i in range(n):
    temp = []
    for j in range(n):
        if i == j:
            ui = numpy.random.exponential(1)
            
            temp.append(ui**(-1/p))
        else:
            temp.append(0)
    D.append(temp)

P_matrix = numpy.array(P)
D_matrix = numpy.array(D)

x_matrix = numpy.array(x)
pi_matrix = numpy.dot(P_matrix, D_matrix)

y = numpy.dot(pi_matrix, x_matrix)

for k in range(len(y)):
    y[k] = abs(y[k])

result = max(y)

print(result) 