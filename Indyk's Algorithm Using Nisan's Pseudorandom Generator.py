# -*- coding: utf-8 -*-
"""
Created on Thu Feb 11 09:40:34 2021

@author: Grant
"""

import random
import math
import numpy
import statistics

n = 15
m = 10
p = 1

def hash_function(input_value, k, buckets):
    p = 64371611191
    
    summation = 0
    for i in range(k):
        coefficient = random.randrange(p)
        
        summation = summation + coefficient * input_value**i
    
    result = summation % p
    result = result % buckets
    
    return result

initial_pi = []

class Node:
    def __init__(self, data):
        self.parent = None
        self.left = None
        self.right = None
        self.data = data
    
    def insert(self, data, level, n):
        if 2**(level - 1) > n:
            #print(data)
            if len(initial_pi) < n:
                initial_pi.append(data)
            return
        
        left = data
        right = hash_function(data, 2, 2)
        
        self.left = Node(left)
        self.right = Node(right)
        self.left.parent = self
        self.right.parent = self
        
        self.left.insert(left, level + 1, n)
        self.right.insert(right, level + 1, n)
            

def chunks(l, n):
    n = max(1, n)
    return (l[i:i+n] for i in range(0, len(l), n))

x = [1, 3, 5, 11, 15, 21, 18, 19, 5, 8, 23, 35, 9, 16, 38]

epsilon = 0.2

xp = 0

for e in range(n):
    xp = xp + x[e] ** p

xp = xp**(1/p)

pi = []
for i in range(m):
    initial_pi = []
    initial_value = hash_function(1, 2, 2)
    root = Node(initial_value)
    root.insert(initial_value, 1, n)
    
    pi.append(initial_pi[:])

c1 = 0
c2 = 0
for u in range(m):
    y_temp = 0
    for v in range(n):
        y_temp = y_temp + pi[u][v] * x[v]
    
    if y_temp <= (1 + epsilon)*xp:
        c1 += 1
    if y_temp >= (1 - epsilon)*xp:
        c2 += 1

if c1 > m/2 and c2 < m/2:
    print("The pi matrix is correct")
else:
    print("The pi matrix is incorrect")

x_matrix = numpy.array(x)
pi_matrix = numpy.array(pi)

y = numpy.dot(pi_matrix, x_matrix)

print(y)

for k in range(len(y)):
    y[k] = abs(y[k])

result = statistics.median(y)

print(result)

"""
print(root.data)
print(root.left.data)
print(root.left.left.data)
print(root.left.left.left.data)
print(root.left.left.left.left.data)

root.output()
"""        