import os
import sys


files=os.listdir("../src")
for file in files:
    cmd="cd ../src && g++ -o ../target/"+file[:-3]+".exe "+file
    os.system(cmd)

print("finished!!")