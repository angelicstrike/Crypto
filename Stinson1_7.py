import math
import operator
import time

def IsPrime(number):
    a = int(math.sqrt(number))+1
    divisor = 3

    if((number % 2) == 0):
        return False

    while(divisor < a):
        if((number % divisor) == 0):
            return False
        divisor += 2
    return True

def SieveOfAtkins(limit):
    primes = [2, 3]
    isPrime = [False]*(limit+1)
    root = int(math.sqrt(limit+1))

    for x in range(1, root):
        for y in range(1, root):
            an = (4*x*x) + (y*y)
            if(an <= limit and ((an % 12 == 1) or (an % 12 == 5))):
                isPrime[an] = operator.xor(isPrime[an], True)

            bn = (3*x*x) + (y*y)
            if(bn <= limit and bn % 12 == 7):
                isPrime[bn] = operator.xor(isPrime[bn], True)

            cn = (3*x*x) - (y*y)
            if(x > y and cn <= limit and cn % 12 == 11):
                isPrime[cn] = operator.xor(isPrime[cn], True)
    for z in range(5, root):
        if(isPrime[z] == True):
            s = z*z
            for a in range(s, limit, s):
                isPrime[a] = False
    for b in range(5, limit, 2):
        if(isPrime[b] == True):
            primes.append(b)

    return primes

def factor(number):
    factors = list()
    numToFactor = number
    primes = SieveOfAtkins(number)

    primality = IsPrime(numToFactor)
    while(primality == False):
        for x in primes:
            if((numToFactor % x) == 0):
                factors.append(x)
                numToFactor = numToFactor/x
                primality = IsPrime(int(numToFactor))
                break
    if(numToFactor != 1):
        factors.append(int(numToFactor))
    return factors


def EulerTotient(number, factors):
    running_total = number
    for x in factors:
        running_total = running_total * (1 - (1/x)) 
    return running_total

def NumAffineKeys(m):
    factors = factor(m)
    mutual_primes = int(EulerTotient(m, set(factors)))
    answer = m * mutual_primes
    return answer

if(__name__ == '__main__'):
    print(NumAffineKeys(30100))
    print(NumAffineKeys(1225))
