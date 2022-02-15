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

for d in $paDirs
do
	echo ""

	# Go into a pa (performance assesment) directory
	cd $startDir
	cd $d

	gradingFile=$(ls -al | grep -o "assignment_autograder.py")
	if ! [[ $gradingFile =~ ^assignment_autograder.py$ ]]; then
		echo "It's not here"
		continue
	fi

	# Run autograder and extract scores & program names
	testOut=$(python assignment_autograder.py)
	outScores=$(grep -o "[0-9]\+ out of [0-9]\+" <<< $testOut)
	outPrograms=$(grep -o "Score on [^:]\+:" <<< $testOut)

	arrScores=($(grep -o "[0-9]\+" <<< $outScores))
	arrPrograms=($(grep -o "[^ ]\+:" <<< $outPrograms | grep -o "[^:]\+"))

	# Process scores
	#
	# If the assigment score is max, we don't need to do anything.
	# Otherwise we need to print out an itemized breakdown of which
	# tests failed

	maxInd=${#arrPrograms[@]}
	let maxInd--

	let maxScoreInd=maxInd*2
	scoreTotal=${arrScores[maxScoreInd]}
	let maxScoreInd++
	scoreMax=${arrScores[maxScoreInd]}


	if [[ $scoreTotal == $scoreMax ]]; then
		# Passed entire assigment
		echo "[x] $d"
	elif [[ $scoreTotal == 0 ]]; then
		echo "[ ] $d"
	else
		echo "[~] $d"
	fi

	# Now print out the itemized report
	for (( i=0; i<${#arrPrograms[@]}; i++))
	do
		programName=${arrPrograms[i]}

		let scoreInd=$i*2
		scoreGot=${arrScores[scoreInd]}
		let scoreInd++
		scoreMax=${arrScores[scoreInd]}

		if [[ $scoreGot == $scoreMax ]]; then
			echo "  - [x] $programName: $scoreGot/$scoreMax"
		elif [[ $scoreGot == 0 ]]; then
			echo "  - [ ] $programName: $scoreGot/$scoreMax"
		else
			echo "  - [~] $programName: $scoreGot/$scoreMax"
		fi
	done
done


