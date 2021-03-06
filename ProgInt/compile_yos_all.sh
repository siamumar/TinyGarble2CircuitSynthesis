#!/bin/bash
mkdir -p syn_all
echo "./compile_yos_all.sh. use -s to skip synthesis" 
if [ "$1" == "-s" ]
then 
	echo "skipping synthesis"
	for d in *
	do
		( cp ${d%/*}/syn/*.v syn_all)	
	done
else 
	for d in *
	do
		( cd "$d" && ./compile.sh  && cd ".." && cp ${d%/*}/syn/*.v syn_all)	
	done
fi
for verilogfile in syn_all/*.v
do
	empfile=${verilogfile%.*}.emp
	../Verilog2EMP/bin/V2EMP_Main -i $verilogfile -o $empfile --log2std
	../../tinygarble2/bin/readCircuitFile -i  $empfile &
done
wait

cp syn_all/*.bin ../../tinygarble2/tinygarble/netlists_pi/ 