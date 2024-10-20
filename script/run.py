import os
import sys


files=os.listdir("../src")
for file in files:
    exe_name=None
    if sys.platform=="win32":
        exe_name=file[:-3]+"exe"
    else:
        exe_name=file[:-3]

    cmd="cd ../src && g++ -o ../target/"+exe_name+" "+file
    os.system(cmd)

print("finished!!")