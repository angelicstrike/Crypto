import numpy
import scipy

#Recurrence to solve for
recurrence = [1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0]
def LFSR_SOLVER(degree):
    #Creates an MxM matrix that will contain the matrix that we need to be invertible
    #for the recurrence to have a unique solution at the length degree
    #For now, we initialize it to zero, and we'll fill it later
    deterMatrix = scipy.zeros((degree, degree), 'int')
    answers = scipy.zeros((degree,1), 'int')
    counter = 0
    #fill the determinant matrix with values from the recurrence, just like the examples
    # in class
    for x in range(0,degree):
        for y in range(0, degree):
            deterMatrix[x][y] = recurrence[counter + y]
        counter += 1
    for z in range(0, degree):
        answers[z] = recurrence[degree + z]
    #Since the library we're using (scipy/numpy) deals a lot with doubles, while we need
    #integer values, we call round on the numpy.linalg.det() function (which finds the
    #determinant of a matrix for us), to produce an integer answer mod 2
    det = round(numpy.linalg.det(deterMatrix)) % 2
    #print("Determinant H(%d) = %d" % (degree, det))
    #if we have a singular matrix, just die now
    if(det == 0):
        return None
    # some basic printing out
    print("determinant matrix")
    print(deterMatrix)
    print("z matrix")
    print(answers)

    #Solve for our LFSR coefficients, and put them into a matrix we can use
    coeff_temp = numpy.linalg.solve(deterMatrix, answers);
    coeff = list()
    for a in range(len(coeff_temp)):
        k = int(coeff_temp[a])%2
        coeff.append(k)
    #more printing out
    print("Coefficients")
    print(coeff)
    #start putting out final output together, starting with out initial parameters
    output = list()
    for b in range(degree):
        output.append(int(round((recurrence[b]))))

    #generate a recurrence using the coefficients found above. This is will be our final
    #output
    for c in range(degree, 50):
        cur_el = 0
        for d in range(degree):
            cur_el += coeff[degree - d -1] * output[c-d-1]
        cur_el = cur_el % 2
        output.append(cur_el)
    #some output functions that I didn't need at the moment, but can use when needed
    #print("final output")
    #print(output)
    #print("original recurrence")
    #print(recurrence[0:51])
    #print("")
    return output

if(__name__=='__main__'):
    #try every possible value between 3 and the length of the original recurrence divided by 2
    #There has to be some patter in there, otherwise this isn't an LFSR
    for x in range(3,50):
        answer = LFSR_SOLVER(x)
        found = 1
        if(answer == None):
            continue
        else:
            for y in range(len(answer)):
                if(answer[y] != recurrence[y]):
                    found = 0
            if(found):
                print("Answer found at %d\n" % (x))
            else:
                #print("No answer found, trying %d" %(x+1))
                found = 1
