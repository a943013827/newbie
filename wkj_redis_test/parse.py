#-*- coding:utf-8 -*-

import sys

while True:
      line=sys.stdin.readline()
      if not line:
          break
      str=line.split()
      sys.stdout.write("*{0}\r\n".format(len(str)))
      for x in str:
          sys.stdout.write("${}\r\n{}\r\n".format(len(x),x))

