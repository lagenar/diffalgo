import sys
import pdb
from pprint import pprint

objflag = False
uso = """uso: python patch.py file diff
flags: -o ---> objetivo a origen"""
if len(sys.argv) < 3:
    print uso
    sys.exit()
elif len(sys.argv) == 3:
    nf1 = sys.argv[1]
    ndiff = sys.argv[2]
elif sys.argv[1] == '-o':
    objflag = True
    nf1 = sys.argv[2]
    ndiff = sys.argv[3]
else:
    print uso
    
f1 = open(nf1).read().split("\n")
diff = open(ndiff).read().split("\n")
if not f1:
    f1 = f1[:-1]
if not diff[-1]:
    diff = diff[:-1]
f1 = [[x, False, []] for x in f1]
f1 = [[None, False, []]] + f1
x = 0

while x < len(diff):
    if diff[x].find('a')!=-1 and objflag:
        lineaor = diff[x].split('a')[0]
        lineadp, lineadf = diff[x].split('a')[1].split(',')
        diff[x] = "%s,%sd%s" % (lineadp, lineadf, lineaor)
    elif diff[x].find('d')!=-1 and objflag:
        lineaorp, lineaorf = diff[x].split('d')[0].split(',')
        linead = diff[x].split('d')[1]
        diff[x] = "%sa%s,%s" % (linead, lineaorp, lineaorf)
    if diff[x].find('a') != -1:
        lineaor = int(diff[x].split('a')[0])
        lineadp, lineadf = diff[x].split('a')[1].split(',')
        lineadp, lineadf = int(lineadp), int(lineadf)
        r = [y[2:] for y in diff[x+1 : x+lineadf-lineadp+2]]
        x += lineadf - lineadp + 2
        f1[lineaor][2] = r
    else:
        lineaorp, lineaorf = diff[x].split('d')[0].split(',')
        lineaorp, lineaorf = int(lineaorp), int (lineaorf)
        linead = int(diff[x].split('d')[1])
        for k in range(lineaorp, lineaorf+1):
            f1[k][1] = True
        x += lineaorf - lineaorp + 2

for l in f1[0][2]:
    print l
for r in f1[1:]:
    if not r[1]:
        print r[0]
    for l in r[2]:
        print l
