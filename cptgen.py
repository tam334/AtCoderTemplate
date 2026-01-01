import sys;
from enum import Enum;
import os;
import shutil;
import subprocess

target = sys.argv[1]

ftestcase = open("testcase_" + target + ".txt")
line = ftestcase.readline()
class State(Enum):
    NONE = 1
    IN = 2
    OUT = 3
state = State.NONE
count = 0
while line != "":
    if state == State.NONE:
        #inを探す
        if line.startswith("\\i"):
            state = State.IN
    elif state == State.IN:
        #outを探す
        if line.startswith("\\o"):
            count += 1
            state = State.OUT
    elif state == State.OUT:
        #inを探す
        if line.startswith("\\i"):
            state = State.IN
    line = ftestcase.readline()

includes = "#include \"" + target + ".h\""

parameters = "INSTANTIATE_TEST_SUITE_P(ABC, MyTest, testing::Values("
subparams = []
for i in range(count):
    subparams.append("ABCParams(" + str(i) + ")\n")
parameters += ",".join(subparams)
parameters += "));"

ftestscript = open("cpttemplate.cpp")
line = ftestscript.readline()
convertedscript = ""
while line != "":
    line = line.replace("{@insert parameters}", parameters)
    line = line.replace("{@insert target_module}", target)
    convertedscript += line
    line = ftestscript.readline()

subdir = "test_" + target
if not os.path.isdir(subdir):
    os.mkdir(subdir)
os.chmod(subdir,0o777)

shutil.copy("testcase_" + target + ".txt", subdir)
shutil.copy(target + ".cpp", subdir)
shutil.copy(target + ".h", subdir)
fconvertedscript = open(subdir + "/test_" + target + ".cpp", "w")
fconvertedscript.write(convertedscript)
fconvertedscript.close()

cmd = "cd " + subdir + " && g++ --std=c++20 test_" + target + ".cpp " + target + ".cpp -DCPTEST -lgtest_main -lgtest && ./a.out"
#print(cmd)
subprocess.run(cmd, shell=True)
