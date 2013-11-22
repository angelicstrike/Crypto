#Convert a given integer into a binary list of 0's and 1's of lenght num_bits
#if num_bits is less than the actual length of the bits needed for x, the
#bit string will be truncated. If it's longer, 0's will be padded on to the
#front of the bit string
def IntToBinary(x, num_bits):
    string = list()
    temp = x
    while(temp > 0 and len(string) < num_bits):
        string.insert(0,temp%2)
        temp = int(temp/2)

    while(len(string) < num_bits):
        string.insert(0, 0)
    
    return string

#Created an nxn Hadamard matrix for use in other functions
def HadamardGenerate(n):
    H = list()
    for i in range(n):
        H.append(list())
        i_str = IntToBinary(i, 5)
        for j in range(n):
            j_str = IntToBinary(j,5)
            temp = 0
            for x in range(5):
                temp += i_str[x]*j_str[x]
            H[i].append((-1)**temp)

    return H

#Multiplies two matrices together. Works in some cases, but not all.
#But for now, it does the homework, which is good enough for now
def MultiplyMatrices(row, multi):
    if(len(row) != len(multi)):
        print("Matrices cannot multiplied together")
    answer = list()
    width = 0
    height = 0
    if(len(row) < len(multi[0])):
        width = len(row)
    else:
        width = len(multi[0])

       
    for x in range(width):
        temp = 0
        for y in range(len(multi[0])):
            temp += row[y] * multi[y][x]
        answer.append( temp )
    return answer
            
s = [-1,1,-1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,-1]
t = [1,1,-1,1,-1,-1,-1,-1,-1,-1,1,1,1,-1,1,1]
u = [1,0,0,1,0,1,0,1,1,1,0,0,0,0,0]
test = [1,-1,-1, 1, 1, 1,-1, 1,-1, 1, 1, 1,-1,-1, 1,-1]
generator = HadamardGenerate(16)
print(generator)
#print(MultiplyMatrices(s, generator))
print(MultiplyMatrices(test, generator))
