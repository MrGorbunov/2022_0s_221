#!/bin/bash

#
# Program Tester
#
# This program automatically looks for all folders in the form pa####
# and if it finds an assignment_autograder.py in it, will check
# for proper output and then display whether all tests have been passed
#
# NOTES:
#	- Make sure you've activated the venv before calling this script
#		otherwise it will not have the python packages
#


startDir=$(pwd)
paDirs=$(ls -al | grep -o "pa[0-9]\+\$")

echo $(pip freeze)

# for d in $paDirs
for d in pa0
do
	echo ""

	# Go into a pa (performance assesment) directory
	cd $startDir
	cd $d
	echo $d

	gradingFile=$(ls -al | grep -o "assignment_autograder.py")
	if ! [[ $gradingFile =~ ^assignment_autograder.py$ ]]; then
		echo "It's not here"
		continue
	fi

	echo "It's here"
	testOutput=$(python assignment_autograder.py)
	finalScore=$(grep "\d out of" <<< "$testOutput")

	echo "\/ \/"
	echo
	echo $finalScore
	echo 
	echo $testOutput
done


