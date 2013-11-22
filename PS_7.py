import math

occur = [1, 1, 1, 5, 1, 1, 2 ,1, 1, 2, 1, 1, 15, 1, 17, 1, 1, 1, 2, 1, 3, 2, 1, 2, 2,7, 1 ,1, 1, 1, 4, 1, 1 ,1, 1, 1, 3, 1, 8, 6, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 2 ,1 ,1, 1, 1, 1 ,1 ,2, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 11, 5, 1 ,1, 1, 1, 1 ,1, 1, 1, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
print(len(occur))
set_occur = set(occur)
mappings = dict()
print(set_occur)
entropy = 0.0
total = 0
for y in set_occur:
    for x in occur:
        if(x == y):
            total += 1
    print(str(y) + "==>" + str(total))
    mappings[y] = (total/101.0)
    total = 0
print(mappings)
for x in set_occur:
    entropy += mappings[x]*math.log(mappings[x],2)

print(entropy)
