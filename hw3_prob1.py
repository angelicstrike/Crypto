degree = 4
combinations = list()
#Creates a list of the 32 different possilbe combinations of 0's and 1's that form a string of
#length 5.
for w in range(2 ** degree):
    combinations.append(bin(w)[2:].zfill(degree))

#Does the actual linear feedback shifting to produce the recurrence strings
# that need to be analyzed to determine their period
for x in range(2**degree):
    for y in range(5,70):
        k = (int(combinations[x][y-5]) + int(combinations[x][y-4])) % 2
        combinations[x] += str(k)
        k = 0

#This just prints everything out
for z in range(2**degree):
    print(str(z+1) + ")."+ combinations[z])

