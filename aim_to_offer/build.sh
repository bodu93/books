allfiles=$(ls)
for f in $allfiles
do
	if [ -e $f/Makefile ]
	then
		cd $f
		make
		cd ..
	fi
done
