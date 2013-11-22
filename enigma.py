import sys

enigma = "GAWGST OTJPNA VBPLKM YPSYVU CZSXGU HTNINR PCLSOI WMGREH YPSYVU CZSXGU HIZIMP PCLSOI WMGREH YPSYVU CZSXGU IOQHFZ QNHDPB XPRCVD YAMYSL CQOXQQ JJHBJB QNHDPB XPRCVD YAMYSL DXYMTS KPVOVY RJXNJK XPRCVD ZSTKHE DXYMTS LHXQRK RJXNJK XPRCVD ZSTKHE DUOMAQ MVHFYB SGCADV XLICWW ZGGKDH DECMIV NTUZNJ SGCADV YEDYIC AYKTCN EVIUYW NTUZNJ TDJWZA YEDYIC BOOVFQ EVIUYW NDBZZO TDJWZA YEFYIC BOOVFQ FFEEXG OQMPQL TRAWLF YEDYIC BWFVBX FKLEUI OQMPQL UHAJRF YEDYIC BWFVBX FYPECM"

def compose(composition):
    cycle = list()
    counter = 0
    letters_used = list()
    for x in composition.keys():
        mapping = composition[x]
        if( x in letters_used ):
            continue
        
        cycle.append(list())
        cycle[counter].append(x)
        if(x == composition[x]):
            counter += 1
            continue
            
        cycle[counter].append(composition[x])

        letters_used.append(x)
        letters_used.append(composition[x])
        while(composition[mapping] != cycle[counter][0]):
            cycle[counter].append(composition[mapping])
            letters_used.append(composition[mapping])
            mapping = composition[mapping]
            
        counter += 1
    return cycle

def enigma_cycles(cipher):
    cycles = cipher.split(" ")
    DcompA = dict()
    EcompB = dict()
    FcompC = dict()
    count = 0
    print("Decompositions")
    for x in cycles:
        if(x[0] in DcompA.keys()):
            if(DcompA[x[0]] != x[3]):
                print("DcompA already has " + x[0] + " mapped to " + DcompA[x[0]])
        DcompA[x[0]] = x[3]
        
        if(x[1] in EcompB.keys()):
            if(EcompB[x[1]] != x[4]):
                print("EcompB already has " + x[1] + " mapped to " + EcompB[x[1]])
        EcompB[x[1]] = x[4]
        
        if(x[2] in FcompC.keys()):
            if(FcompC[x[2]] != x[5]):
                print("FcompC already has " + x[2] + " mapped to " + FcompC[x[2]])
        FcompC[x[2]] = x[5]
        count += 1
        print(x[0] + "-->" +x[3] + ", " + x[1] + "-->" + x[4] + ", " + x[2] + "-->" + x[5] + "\\\\")
    print(count)
    
    cycles = list()
    cycles.append(compose(DcompA))
    cycles.append(compose(EcompB))
    cycles.append(compose(FcompC))
    wat = 0
    for x in cycles:
        for y in x:
            print(y)
            wat+= len(y)
        print(" ")
    print(wat)
    
    
if(__name__=='__main__'):
    enigma_cycles(enigma)
