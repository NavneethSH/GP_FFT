import os
import random
#li=list(range(1,1001))
fin=[]
sec=[]
for i in range(100000):
	fin.append(str(random.randint(1,10)))
	sec.append(str(random.randint(1,10)))
f=open("input.txt","w")
f.write("100000 100000\n")
f.write(" ".join(fin))
f.write("\n")
f.write(" ".join(sec))
f.close()