#!/bin/sh
#{
#read a
#read b
#echo $(($a+$b))
#}



#i=0
#sum=0
#while [ $i -le 100 ]
#do
#sum=$(($i+$sum))
#i=$(($i+1))
#done
#echo $sum


#for i in `find ./ -name '*'`
#do
#if [ -d $i ]
#then :
#else
#mv $i "$i.bak"
#fi
#done

#for i in `find ./ -name '*'`
#do
#if [ -d $i ]
#then :
#else
#mv $i `echo $i | sed 's/.bak//g'`
#fi
#done


#for i in *.c
#do
#gcc $i -o `echo $i | sed 's/.c//g'`
#done


cat /etc/passwd |awk -F: '$7!="" {print $7}'|sort|uniq -c
