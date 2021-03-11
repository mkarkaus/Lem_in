#!/bin/bash
trap "exit" INT
MINARGS=1
if [ $# -lt $MINARGS ]; then
	echo "Usage: sh eval_lemin.sh 'flow-one' | 'flow-ten' | 'flow-thousand' | 'big' | 'big-superposition' | 'valid' | 'error'"
	exit $E_NOARGS
fi
ARG=$1
REQ_RESULTS=0
OWN_RESULTS=0
slow=0
over_max=0
dif_limit=10
longest_time=0.0
biggest_dif=0
i=0
if [ $ARG == "valid" ]; then
	./maps/lemin_valid.sh
	echo "Simple valid maps tested"
	exit 0
fi
if [ $ARG == "error" ]; then
	./maps/lemin_error.sh
	echo "Errors tested"
	exit 0
fi
while [ $i -lt 100 ]
do
	./generator --$ARG > argFILE
	(time -p ./lem-in < argFILE > outFILE) &> "timeFILE"
	TIME=$(grep real "timeFILE" | awk '{print $2}')
	OUTNUM=$(wc -l "outFILE" | awk '{print $1}')
	ARGNUM=$(wc -l "argFILE" | awk '{print $1}')
	REQ=$(head -5 'argFILE' |  grep 'require' | awk '{print $8}')
	REQ_RESULTS=$(( $REQ_RESULTS + $REQ ))
	LINES_NUM=$(( $OUTNUM - $ARGNUM - 1 ))
	OWN_RESULTS=$(( $OWN_RESULTS + $LINES_NUM ))
	printf "$i:\tRequired: $REQ			"
	printf "Our own: $LINES_NUM			"
	DIF=$(($LINES_NUM - $REQ))
	if (( $DIF > $dif_limit )); then
		over_max=$(( $over_max + 1 ))
	fi
	printf "Difference: $DIF		"
	echo "||	Execution time $TIME"
	if (( $(echo "$TIME > 3.00" |bc -l) )); then
		slow=$(( $slow + 1 ))
	fi
	if (( $LINES_NUM < $REQ - 5 ))
	then
		cp -rf outFILE outProblem
		cp -rf argFILE inProblem
	fi
	# if (( $DIF > 3 ))
	# then
	# 	cp -rf argFILE ./problem_maps/argOVER$DIF.map
	# fi
	if (( $(echo "$TIME > $longest_time" |bc -l) )); then
		longest_time=$(echo "$TIME" |bc -l)
	fi
	if (( $DIF > $biggest_dif )); then
		biggest_dif=$(( $DIF ))
	fi
	rm -rf timeFILE
	rm -rf outFILE
	rm -rf argFILE
	i=$(( $i + 1 ))
	sleep 0.7s
done
REQ_AVERAGE=$(( $REQ_RESULTS / $i))
OWN_AVERAGE=$(( $OWN_RESULTS / $i))
AV_DIF=$(( $OWN_AVERAGE - $REQ_AVERAGE ))
printf "\nOur average difference per $i tests: $AV_DIF \n"
echo "$slow times over 3.00s, biggest dif: $biggest_dif"
echo "$over_max times over $dif_limit lines, Longest time: $longest_time"
exit 0
