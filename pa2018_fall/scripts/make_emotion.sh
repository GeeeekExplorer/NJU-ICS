#!/bin/bash

#判断间隔时间

flag_dis='true'   
flag_DNF='true'    #exist

if [ ! -f ~/.pa-nemu/emotion/Disturb.txt ]; then
	flag_dis='false'
fi
if [ ! -f ~/.pa-nemu/emotion/DoNotFreq.txt ]; then
	flag_DNF='false'
fi
	
if [ $flag_dis = 'true' ]; then
while read line
do
    #echo $line 
    var1=`echo $line|awk -F ' ' '{print $1}'`
    var2=`echo $line|awk -F ' ' '{print $2}'`
done < ~/.pa-nemu/emotion/Disturb.txt
fi

if [ $flag_DNF = 'true' ]; then
while read line
do
    #echo $line 
    var3=`echo $line`
done < ~/.pa-nemu/emotion/DoNotFreq.txt
fi

D_time=3600000   #a hour
D2_time=900000   #a quarter

flag_skip='false'

T=$[$(date +%s%N)/1000000]   #current time
   
if [ $flag_DNF = 'true' ]; then
	T2=$[$T-$var3]
	if [ $T2 -lt $D2_time ]; then   #less than a quarter
		flag_skip='true'
	fi
fi

if [ $flag_skip = 'false' ]; then
	if [ $flag_dis = 'true' ]; then
		if [ $var1 = "1" ]; then    #do not disturb
    		T1=$[$T-$var2]
    		#echo $T
    		if [ $T1 -lt $D_time ]; then
        		flag_skip='true'
    		else
      	  		flag_skip='false'
    		fi
		fi
	fi
fi

#echo $flag_skip

if [ $flag_skip = 'false' ]; then
        sessionName=$(tmux display-message -p "#S")
        echo "session_name_"$sessionName
        if [ "session_name_"$sessionName != "session_name_PA-NEMU" ];then
            tmux new-session -s "PA-NEMU" -d
        fi

        tmux split-window -h
        tmux select-pane -t 0
        tmux send-keys "make all |& tee make.log; while  [ ! -f  ".lock_tmux" ]; do sleep 0.1; done; rm .lock_tmux; exit" C-m
        tmux select-pane -t 1
        tmux send-keys "scripts/emotion_dialog.sh; touch .lock_tmux; exit" C-m
        tmux attach -t "PA-NEMU" 
else
        make all |& tee make.log 
fi
