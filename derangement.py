import itertools

def derangement(x):
    perms = itertools.permutations(x)
    return ( i for i in perms if not any(i[k] == x[k] for k in range(len(x))))

if(__name__=="__main__"):
    n = [1,2,3,4,5,6]
    for x in range(6, 7):
        print(x)
        derange = list(derangement(n))
        for y in derange:
            print(y)
        n.append(x+1)
