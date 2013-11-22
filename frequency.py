import string
from fractions import gcd

alphabet = ','.join(string.ascii_uppercase).split(',')
probabilities = {'A':0.08167,
'B':	0.01492,
'C':	0.02782,
'D':	0.04253,
'E':	0.12702,
'F':	0.02228,
'G':	0.02015,
'H':	0.06094,
'I':	0.06966,
'J':	0.00153,
'K':	0.00772,
'L':	0.04025,
'M':	0.02406,
'N':	0.06749,
'O':	0.07507,
'P':	0.01929,
'Q':	0.00095,
'R':	0.05987,
'S':	0.06327,
'T':	0.09056,
'U':	0.02758,
'V':	0.00978,
'W':	0.02360,
'X':	0.00150,
'Y':	0.01974,
'Z':0.00074
}

#Finds the modular inverse of a number modulo p. Returns -1 if the modular inverse is not
# found.
def modInverse(a, p):
    #try everything below p to see if it works
    #If we hit p, we're at the end of the ring, and to avoid an infinite loop,
    #we break if we reach p
    print("Attempting to find a modular inverse for %d over mod %d" %(a, p))
    for inv in range(1,p):
        remainder = (inv*a) % p
        if(remainder==1):
            print("Inverse found at %d" % inv)
            break
    else:
        print("No inverse found...")
        inv = -1
    return inv

# This is just a helper function that puts the alpabet into a key-value storage container
# that maps 'A' to 0, 'B' to 1, 'C' to 2, etc.
def BuildMappings():
    mappings = {}
    for x in range(0,26):
        mappings[alphabet[x]] = x
    return mappings

#This function breaks a given cipher text into len(ct)/length substrings. All of the substrings
# are of length "length" and are returned in the columns variable as a pythonic list of strings
def ColumnCreator(ct, length):
    columns = list()
    for z in range(0,length):
        columns.append("")
    for x in range(0, len(ct), length):
        for y in range(0,length):
            if(x + y >= len(ct)):
                columns[y] += "0"
            else:
                columns[y] += ct[x + y]
    return columns

#This function returns a list of integers that correspond to each of the starting points of
# the "repeated" parameter(which is a string) that should exist somewhere in the "ct" parameter
def FindPositions(ct, repeated):
    positions = list()
    for x in range(0, len(ct)-len(repeated)):
        if( ct[x:(x+len(repeated))] == repeated ):
            positions.append(x)
    return positions

#This function searches a string ct for reoccuring pattersof length n, and the results are
#returned as a pythonic dictionary.
def FindLengthN(ct, n):
    repeaters = dict()
    for x in range(0, len(ct) - n + 1):
        repeaters[ct[x:(x+n)]] = repeaters.get(ct[x:(x+n)], 0) + 1
    return repeaters

#for a give letter frequency count of a string, this function calculates the
#index of coincidence of a string of length sampleSize
def IndexCoincidence(frequencies, sampleSize):
    index = 0.0
    for letter in frequencies.keys():
        index += ((frequencies[letter] * (frequencies[letter] - 1)) / (sampleSize * (sampleSize - 1)))
    return index

#This function shifts the characters in a string ct by n places mod 26 (So if ct is C and
# n is 4, the function would return G
def ShiftN(ct, n):
    shifted = ""
    counter = 0
    for x in ct:
        if(x != '0'):
            shifted += alphabet[(alphabet.index(x)+n)%26]
    return shifted

#worker function that MgAnalysis depends on to actually work. Does the calculations, but
# right now it only works for the english language
def mg(col_len, freq, shift):
    accum = 0.0
    #print(freq['J'])
    for i in range(0,26):
        if(ShiftN(alphabet[i], shift) in freq.keys()):
            #print( str(probabilities[alphabet[i]]) + ' * ' + str(freq[ShiftN(alphabet[i], shift)]) + "/" + str(col_len))
            accum += probabilities[alphabet[i]] * freq[ShiftN(alphabet[i], shift)] / col_len
    
    return accum

#this is the top level function that performs the Mg function from page 35 of the Stinson
# Cryptography text book. You enter in the column to be operated on, the number of letters
# in the target alphabet, and it doesn it's thing
#One thing to note is that right now it only works for english. The subfunction that does
#the calculations is hardcoded to only use english language probabilities
def MgAnalysis(column, letters):
    mg_list = list()
    for g in range(0,letters):
        freq = LetterFrequencies(column)
        print(freq)
        mg_list.append(mg(len(column), freq, g))
    return mg_list

#Counts the occurences of a character in a string of text and returns it as a dictionary.
#Fairly straight forward
def LetterFrequencies(cipher):
    freqList = dict()
    for x in range(0, len(cipher)):
        freqList[cipher[x]] = freqList.get(cipher[x], 0) + 1
    return freqList

#Given a list of Mg values and a target index of coincidence, this function finds the closest
#value in teh list of Mg values to the target index of coincidence
def ClosestMg(MgValues, IC):
    closest = 0
    counter = 0
    #print(MgValues)
    for x in MgValues:
        if( abs(x - IC) < abs(MgValues[closest] - IC)):
            closest = counter
        counter += 1
    return closest

if(__name__=='__main__'):
    ct_one = "EDKCLHTADTNERERPFAHWHILOOAWOLNLOTLAAFEMMCTMLYEWREASAFDTOFLINDEOEETYEIIUWEWAUOCDOEDORSTANYTRFHOPCCEED"
    ct_two = "DVNVESHKPHWP"
    l = LetterFrequencies(ct_one)
    print(l)
    print(IndexCoincidence(l, len(ct_one)))
    lenN = FindLengthN(ct_one, 2)
    for x in lenN.keys():
        if(lenN[x] >= 2):
            print(x + " ==> " + str(lenN[x]))
