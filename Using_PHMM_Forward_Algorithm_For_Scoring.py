import numpy
import math

MX = numpy.array (
[
[ 5.0/8.0, 1.0/8.0, 1.0/8.0 ],
[ 1.0/9.0, 1.0/9.0, 3.0/9.0 ],
[ 1.0/8.0, 1.0/8.0, 5.0/8.0]
]);

IX = numpy.array (
[
[ 1.0/4.0, 1.0/4.0, 1.0/4.0 ],
[ 3.0/9.0, 3.0/9.0, 2.0/9.0 ],
[ 1.0/4.0, 1.0/4.0, 1.0/4.0 ]
]);


aMM = numpy.array (
[5.0/8.0, 5.0/7.0, 2.0/8.0, 5.0/6.0]
);


aMI = numpy.array (
[1.0/8.0, 1.0/7.0, 4.0/8.0, 1.0/6.0]
);


aMD = numpy.array (
[2.0/8.0, 1.0/7.0, 2.0/8.0 ]
);

aIM = numpy.array (
[1.0/3.0, 1.0/3.0, 4.0/8.0, 1.0/2.0 ]
);


aII = numpy.array (
[ 1.0/3.0, 1.0/3.0, 3.0/8.0, 1.0/2.0 ]
);


aID = numpy.array (
[1.0/3.0, 1.0/3.0, 1.0/8.0 ]
);



aDM = numpy.array (
[ 0.0, 2.0/4.0, 1.0/3.0, 2.0/3.0 ]
);


aDI = numpy.array (
[ 0.0, 1.0/4.0, 1.0/3.0, 1.0/3.0 ]);


aDD = numpy.array (
[0.0,  1.0/4.0, 1.0/3.0 ]
);

qx = 1.0/3.0

F0M0 = 0.0
F1M1 = 0.0

def FM (j, i):
    
    if ( j > 0 and i > 0):
        print("Called with i value : " + str(i) + "       j value : " + str(j) + "        Under function FM - If\n")
        #print ( "\n" + str(math.log( (MX[j-1][i-1])/qx )) +"\t" + str(aMM[j-1]) +"\t" + str(math.exp(FM(j-1,i-1)) )+"\t" + str(aIM[j-1])+"\t" + str(math.exp(FI(j-1,i-1)))+"\t" + str(aDM[j-1])+"\t" + str(math.exp(FD(j-1,i-1))) + "\n" ) ;
        #temp = ( math.log( (MX[j-1][i-1])/qx ) +  math.log( aMM[j-1] * math.exp(FM(j-1,i-1)) + aIM[j-1] * math.exp(FI(j-1,i-1)) + aDM[j-1] * math.exp(FD(j-1,i-1)) ) );
        #print("F" + str(j) + "M" + str(i) + "=" + str(temp) );
        
        if (aMM[j-1] * math.exp(FM(j-1,i-1)) > 0 or aIM[j-1] * math.exp(FI(j-1,i-1)) > 0 or  aDM[j-1] * math.exp(FD(j-1,i-1)) > 0 ):
            if ((MX[j-1][i-1])/qx > 0):
                return (math.log( (MX[j-1][i-1])/qx ) +  math.log( aMM[j-1] * math.exp(FM(j-1,i-1)) + aIM[j-1] * math.exp(FI(j-1,i-1)) + aDM[j-1] * math.exp(FD(j-1,i-1)) ) );
                
            else:
                return (math.log( aMM[j-1] * math.exp(FM(j-1,i-1)) + aIM[j-1] * math.exp(FI(j-1,i-1)) + aDM[j-1] * math.exp(FD(j-1,i-1)) ) );
                
        elif ( (MX[j-1][i-1])/qx > 0 ):
            return ( math.log( (MX[j-1][i-1])/qx ) );
            
        else:
            return 0;

    elif ( j == 0 and i == 0):
        print("Called with i value : " + str(i) + "       j value : " + str(j) + "        Under function FM - ELIF 0 ")
        return 0    
            
    elif ( j < 1 or i < 1 ):
        print("Called with i value : " + str(i) + "       j value : " + str(j) + "        Under function FM - ELIF 1")
        return ( float("-inf") );
    

        
def FI (j, i):
    if ( j >= 0 and i > 0):
        print("Called with i value : " + str(i) + "       j value : " + str(j) + "        Under function FI")
        #print ( "\n" + str(math.log( (IX[j-1][i-1])/qx )) +"\t" + str(aMI[j-1]) +"\t" + str(math.exp(FM(j,i-1)) )+"\t" + str(aII[j-1])+"\t" + str(math.exp(FI(j,i-1)))+"\t" + str(aDI[j-1])+"\t" + str(math.exp(FD(j,i-1))) + "\n" ) ;
        #print ("\nans" + str(math.log( (IX[j-1][i-1])/qx ) +  math.log( aMI[j-1] * math.exp(FM(j,i-1)) + aII[j-1] * math.exp(FI(j,i-1)) + aDI[j-1] * math.exp(FD(j,i-1)) ) ))
        #temp = (math.log( (IX[j-1][i-1])/qx ) +  math.log( aMI[j-1] * math.exp(FM(j,i-1)) + aII[j-1] * math.exp(FI(j,i-1)) + aDI[j-1] * math.exp(FD(j,i-1)) ) );
        #print("F" + str(j) + "I" + str(i) + "=" + str(temp) );
        
        if ( aMI[j-1] * math.exp(FM(j,i-1)) > 0.0 or aII[j-1] * math.exp(FI(j,i-1)) > 0.0 or aDI[j-1] * math.exp(FD(j,i-1)) > 0.0 ):
            if ( (IX[j-1][i-1])/qx > 0 ):
                return ( math.log( (IX[j-1][i-1])/qx  )  +   math.log( aMI[j-1] * math.exp(FM(j,i-1)) + aII[j-1] * math.exp(FI(j,i-1)) + aDI[j-1] * math.exp(FD(j,i-1)) ) );
            else:
                return ( math.log( aMI[j-1] * math.exp(FM(j,i-1)) + aII[j-1] * math.exp(FI(j,i-1)) + aDI[j-1] * math.exp(FD(j,i-1)) )  );
                
        elif ((IX[j-1][i-1])/qx > 0):
            return ( math.log( (IX[j-1][i-1])/qx  ) )
        else:
            print("Inside else part")
            return 0
    
    elif ( j == 0 and i == 0):
        print("Called with i value : " + str(i) + "       j value : " + str(j) + "        Under function FI")
        return ( float("-inf") );

    elif ( j < 0 or i < 1 ):
        print("Called with i value : " + str(i) + "       j value : " + str(j) + "        Under function FI")
        return ( float("-inf") );
    
        
def FD (j, i):
    if ( j > 0 and i > 0):
        print("Called with i value : " + str(i) + "       j value : " + str(j) + "        Under function FD")
        #temp = ( math.log( aMD[j-1] * math.exp(FM(j-1,i)) + aID[j-1] * math.exp(FI(j-1,i)) + aDD[j-1] * math.exp(FD(j-1,i)) ) );
        #print("F" + str(j) + "D" + str(i) + "=" + str(temp) );
        
        if ( aMD[j-1] * math.exp(FM(j-1,i)) > 0 or aID[j-1] * math.exp(FI(j-1,i)) > 0 or aDD[j-1] * math.exp(FD(j-1,i)) > 0 ):
            return ( math.log( aMD[j-1] * math.exp(FM(j-1,i)) + aID[j-1] * math.exp(FI(j-1,i)) + aDD[j-1] * math.exp(FD(j-1,i)) ) );
        else:
            return ( float("-inf") );
            
    elif ( j == 0 and i == 0):
        print("Called with i value : " + str(i) + "       j value : " + str(j) + "        Under function FD")
        return ( float("-inf") );
            
    elif ( j < 1 or i < 1 ):
        print("Called with i value : " + str(i) + "       j value : " + str(j) + "        Under function FDel2")
        return ( float("-inf") );

#print (FM(1,1))
FMN = FM(3,3)
FIN = FI(3,3)
FDN = FD(3,3)

print("FM : " + str(FMN) + " FI : " + str(FIN) + " FD : " + str(FDN))

score = math.log( (aMM[3] * math.exp(FMN)) + (aIM[3] * math.exp(FIN)) + (aDM[3] * math.exp(FDN)) )

print("Final Score is : " + str(score));