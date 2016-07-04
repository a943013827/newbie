#########################################################################
# File Name:set.sh
# Author: willie
# mail: willie99@163.com
# Created Time:Wed 11 May 2016 10:33:24 AM CST
#########################################################################
#!/bin/bash
python del.py>redis_commands_del.txt
python parse.py <redis_commands_del.txt >redis_data_del.txt

