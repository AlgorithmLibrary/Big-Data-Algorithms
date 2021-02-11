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
m = 10

x = [1, 3, 5, 11, 15, 21, 18, 19, 5, 8, 23, 35, 9, 16, 38]

p = 1
theta_array = [0] * (n * m)
r_array = [0] * (n * m)
pi_array = [0] * (n * m)

for count in range(m*n):
    theta = random.uniform(-math.pi/2, math.pi/2)
    r = random.uniform(0, 1)
        
    temp = (math.sin(p * theta) / (math.cos(theta))**(1/p)) * (math.cos(theta * (1 - p)) / math.log(1 / r))**((1 - p) / p)
        
    pi_array[count] = temp

pi = list(chunks(pi_array, n))

x_matrix = numpy.array(x)
pi_matrix = numpy.array(pi)

y = numpy.dot(pi_matrix, x_matrix)

for k in range(len(y)):
    y[k] = abs(y[k])

result = statistics.median(y)

print(result)
        