#########################################################################
# File Name:set.sh
# Author: willie
# mail: willie99@163.com
# Created Time:Wed 11 May 2016 10:33:24 AM CST
#########################################################################
#!/bin/bash
python set.py>redis_commands.txt
python parse.py <redis_commands.txt >redis_data.txt

