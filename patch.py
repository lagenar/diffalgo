import sys
import pdb
from pprint import pprint

f1 = open(sys.argv[1]).read().split("\n")
diff = open(sys.argv[2]).read().split("\n")
if not f1:
    f1 = f1[:-1]
if not diff[-1]:
    diff = diff[:-1]
f1 = [[x, False, []] for x in f1]
f1 = [[None, False, []]] + f1
x = 0

while x < len(diff):
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
