#!/bin/sh

is_dtr()
{
	if [ ! -d $1 ]
	then return 1
	else return 0
	fi
}

for DIR in $@
do
if is_dir $DIR
then :
else
echo "$DIR doesnt exist"
mkdir $DIR 
fi
done
