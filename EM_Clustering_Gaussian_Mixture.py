import numpy as numpy
from numpy import array
from numpy.linalg import inv
import math

def em_clustering(user_m1, user_m2, user_s1, user_s2, user_tow1, user_tow2):

    X00 =  [ 3.6,1.8,2.283,3.333,2.883,4.533,1.95,1.833,4.7,3.6,1.6,4.35,3.917,4.2,1.75,1.8,4.7,2.167,4.8,1.75 ]
    X11 =  [ 79,54,62,74,55,85,51,54,88,85,52,85,84,78,62,51,83,52,84,47 ]
    i = 0
    while (i<20):
        X0 = array([ [X00[i]],
                     [X11[i]] ])
                  
        detS = numpy.linalg.det(user_s1)
        detS2 = numpy.linalg.det(user_s2)

        Sinv = inv(user_s1)
        Sinv2 = inv(user_s2)

        tow1 = user_tow1
        tow2 = user_tow2
    
        m1 = (numpy.subtract(X0,user_m1)).transpose()
        m2 = Sinv

        v1 = -(m2[0][0]*m1[0][0]*m1[0][0] + m2[0][1]*m1[0][0]*m1[0][1] + m2[1][0]*m1[0][0]*m1[0][1] + m2[1][1]*m1[0][1]*m1[0][1])/2
        v2 = (1/(2* 3.14 * math.sqrt(detS))) * math.exp(v1) 
    
        m1 = (numpy.subtract(X0,user_m2)).transpose()
        m2 = Sinv2
        v21 = -(m2[0][0]*m1[0][0]*m1[0][0] + m2[0][1]*m1[0][0]*m1[0][1] + m2[1][0]*m1[0][0]*m1[0][1] + m2[1][1]*m1[0][1]*m1[0][1])/2
        v22 = (1/(2* 3.14 * math.sqrt(detS2))) * math.exp(v21)

    
        pi[i] = (tow1 * v2  ) / ( ( tow1 * v2  ) + ( tow2 * v22) )
        pj[i] = 1 - pi[i]
        print pi[i], pj[i]
        
        i = i+1
        
i,j,k = 0,0,0

    #pi coressponds to p1,1 p1,2 p1,3 ... p1,n. Likewise pj coressponds to p2,1 p2,2 p2,3... p2,n
pi =  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
pj = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

sumOfpi,sumOfpj = 0.0,0.0




#Call function to compute Bayes formula for Gaussian mixture
m1 = array([ [2.5],
            [65.0] ])

m2 = array([ [3.5],
            [70.0] ])

            
s1 = array([ [1,5],
            [5,100] ])

s2 = array([ [2,10],
            [10,200] ])
                        
N = 20

em_clustering(m1, m2, s1, s2, 0.6, 0.4)
print pi
print pj

tow1 = sum(pi)/N
tow2 = sum(pj)/N

print tow1, tow2
#a,b,c,d=1,2,3,4
#s2 = array([ [a,b],
#             [c,d] ])
#print s2