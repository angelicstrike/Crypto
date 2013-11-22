cipher = "GAWGST OTJPNA VBPLKM YPSYVU CZSXGU HTNINR PCLSOI WMGREH YPSYVU CZSXGU HIZIMP PCLSOI WMGREH YPSYVU CZSXGU IOQHFZ QNHDPB XPRCVD YAMYSL CQOXQQ JJHBJB QNHDPB XPRCVD YAMYSL DXYMTS KPVOVY RJXNJK XPRCVD ZSTKHE DXYMTS LHXQRK RJXNJK XPRCVD ZSTKHE DUOMAQ MVHFYB SGCADV XLICWW ZGGKDH DECMIV NTUZNJ SGCADV YEDYIC AYKTCN EVIUYW NTUZNJ TDJWZA YEDYIC BOOVFQ EVIUYW NDBZZO TDJWZA YEFYIC BOOVFQ FFEEXG OQMPQL TRAWLF YEDYIC BWFVBX FKLEUI OQMPQL UHAJRF YEDYIC BWFVBX FYPECM"

groupings = cipher.split(" ")

a = list()
b = list()
c = list()
d = list()
e = list()
f = list()

for x in groupings:
    a.append(x[0])
    b.append(x[1])
    c.append(x[2])
    d.append(x[3])
    e.append(x[4])
    f.append(x[5])

for x in range(len(groupings)):
    print(a[x] + "-->" + d[x] + ", " + b[x] + "-->" + e[x] + ", " + c[x] + "-->" + f[x])
