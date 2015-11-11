def em_clustering(user_theta1, user_theta2, user_tow1, user_tow2):
    X = [8,5,9,4,7]

    N = 10

    theta1 = oldTheta1 = user_theta1
    theta2 = oldTheta1 = user_theta2

    tow1 = user_tow1
    tow2 = user_tow2
    
    i,j,k = 1,0,0

    #pi coressponds to p1,1 p1,2 p1,3 ... p1,n. Likewise pj coressponds to p2,1 p2,2 p2,3... p2,n
    pi =  [0,0,0,0,0]
    pj = [0,0,0,0,0]

    sumOfpi,sumOfpj = 0.0,0.0

    # Print to console the starting values for theta and tow
    print "User entered value of thetas - theta1 : " + str(round(theta1,4)) + "\ttheta2 : " + str(round(theta2,4))
    print "User entered value of tows - tow1 : " + str(round(tow1,4)) + "\ttow2 : " + str(round(tow2,4))

    while (j<5):
    
        pi[j] = ( tow1 * (pow(theta1,X[j]) * pow(1-theta1,10-X[j])) ) / ( ( tow1 * (pow(theta1,X[j]) * pow(1-theta1,10-X[j])) ) + ( tow2 * (pow(theta2,X[j]) * pow(1-theta2,10-X[j])) ) ) 
        pj[j] = 1 - pi[j]


        # Increment j to compute p12, p13, p14.... pnn
        j = j+1
    
        if j == 5:
            # Re-estimate tow
            tow1 = sum(pi)/5
            tow2 = 1 - tow1
        
            #Calculation to compute thetas
            sumOfpi = 0
            sumOfpj = 0
            k=0
            while(k<5):
                sumOfpi += pi[k]*X[k]
                sumOfpj += pj[k]*X[k]
                k = k+1
            
            # Re-estimate theta 
            oldTheta1 = theta1
            oldTheta2 = theta2           
            theta1 = (sumOfpi / (tow1*5))/10
            theta2 = (sumOfpj / (tow2*5))/10
    
            if ( (round(theta1,5) - round(oldTheta1,5) <= 0 ) and ( round(theta2,5) - round(oldTheta2,5) <= 0 )):
                break
            
            # Increment i to move to next iteration, reset j to 0 to calculate pi, pj
            i = i + 1
            j = 0
    
    print "\nTotal no of iterations model took to converge: " + str(i-1)        
    print "\nValue of thetas - theta1 : " + str(round(theta1,4)) + "\ttheta2 : " + str(round(theta2,4))
    #print "\nValue of tows - tow1 : " + str(round(tow1,4)) + "\ttow2 : " + str(round(tow2,4))
    print "\nValue of p after iteration : "

    k = 0
    while(k<5):
        print "p1," + str(k+1) + " = " + str(pi[k]) + "\tp2," + str(k+1) + " = " + str(pj[k])
        k += 1
    print "\n"    

#Call function with different initial values for theta and tow
em_clustering(0.5, 0.3, 0.8, 0.2)
em_clustering(0.5, 0.3, 0.9, 0.1)
em_clustering(0.1, 0.3, 0.4, 0.6)
em_clustering(0.2, 0.8, 0.5, 0.5)