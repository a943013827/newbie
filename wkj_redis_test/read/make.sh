#########################################################################
# File Name:make.sh
# Author: willie
# mail: willie99@163.com
# Created Time:Thu 12 May 2016 10:50:23 AM CST
#########################################################################
#!/bin/bash
g++ read.cpp -o read -Ihiredis -Lhiredis -lpthread -lhiredis
LD_LIBRARY_PATH=`pwd`/hiredis
export LD_LIBRARY_PATH
