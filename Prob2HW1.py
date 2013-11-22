#James Gross
#MATH 4175, CRN 94509

import string
from fractions import gcd

cipher = "GYOMXNOGNGQUGNETNMXMPLMZOMXYMKTMMJOXAXENTKZZMQEBMFTZEQKJKZQEXYEXNMQLJKNOXANHMTJEEFETXMICXEIJMFAMIHOYHMKYHWMKZRZOXAGIONHON"
cipherTwo = "CDCBB XBGBC LZURC WBCWF JVRFQ BXNDU CRLZM ZJRVQ RFFRF"
cipherThree = "EDKCLHTADTNERERPFAHWHILOOAWOLNLOTLAAFEMMCTMLYEWREASAFDTOFLINDEOEETYEIIUWEWAUOCDOEDORSTANYTRFHOPCCEED"
alphabet = ','.join(string.ascii_uppercase).split(',')

# This is just a helper function that puts the alpabet into a key-value storage container
# that maps 'A' to 0, 'B' to 1, 'C' to 2, etc.
def BuildMappings():
    mappings = {}
    for x in range(0,26):
        mappings[alphabet[x]] = x
    return mappings

#Finds the modular inverse of a number modulo p. Returns -1 if the modular inverse is not
# found.
def modInverse(a, p):
    #try everything below p to see if it works
    #If we hit p, we're at the end of the ring, and to avoid an infinite loop,
    #we break if we reach p
    #print("Attempting to find a modular inverse for %d over mod %d" %(a, p))
    for inv in range(1,p):
        remainder = (inv*a) % p
        if(remainder==1):
            #print("Inverse found at %d" % inv)
            break
    else:
        #print("No inverse found...")
        inv = -1
    return inv

#Decrypts something that was encrypted using an Affine CIpher
def DecryptAffine(a, b, message):
    #We need the modular inverse for the decrypt function
    inverse = modInverse(a, 26)
    #If the modular inverse does not exist, go no further, this cannot be
    # a proper affine cipher
    if(inverse == -1):
        return ""
    #build the character mappings
    mappings = BuildMappings()
    plainText = ""
    #print("Decrypting %s now"%message)
    for x in message:
        if(x == ' '):
            #just ignores spaces. It actually removes spaces from the final output
            continue
        #attach the decrypted character to the end of the growing plaintext message
        plainText += alphabet[((mappings[x] - b-1) * inverse)%26]
    return plainText

print("Plaintext is: \n%s" %DecryptAffine(19,6,cipherThree))
for x in range(0,26):
    for y in range(0,26):
        answer = DecryptAffine(x,y,cipherThree)
        if(answer == ''):
            continue
        #print("%s" % answer)

#print(modInverse(55, 26))
