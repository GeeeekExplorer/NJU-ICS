#!/bin/bash

#User,StudentID,PA_path,Server_IP



time_ID=$(date "+%Y-%m-%d")
Log_path=/home/$User/.pa-nemu/tracking/$time_ID"_$Student_ID".log
Track_path=/home/$User/.pa-nemu/tracking/
CommitID=0

function gitmonitor(){
	if [ ! -d $Track_path ]; then
		mkdir $Track_path
	fi
	#echo "111" >>/home/$User/a.txt
	git add . -A
	check_results=`git commit -m "monitor test" --author="monitor<tracer@njuics.org>"`
	res=`echo $check_results | grep -E 'nothing to commit, working tree clean'`
	if [ ! -z "$res" ]
	then 
		time=$(date "+%Y-%m-%d %H:%M:%S")
	else
		current=`date "+%Y-%m-%d %H:%M:%S"`  
		timeStamp=`date -d "$current" +%s`   
		#将current转换为时间戳，精确到毫秒  
		currentTimeStamp=$((timeStamp*1000+`date "+%N"`/1000000)) 
		git commit -m "monitor test" --amend --author='monitor<tracer@njuics.org>' 
		CommitID=`git rev-parse --short HEAD`		
		echo "#----------------------------------------------------# " >> $Log_path
		echo $currentTimeStamp >> $Log_path
		git show $CommitID |tee $Log_path -a
		echo "#----------------------------------------------------# " >> $Log_path
	fi
	}
if [ -d $PA_PATH ]; then
	cd $PA_PATH
	gitmonitor
	/home/$User/.pa-nemu/scripts/upload_tracking $Student_ID $Server_IP
fi
