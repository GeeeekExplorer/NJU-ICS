#!/bin/bash
cd ~
if [ ! -d "/.pa-nemu/" ]; then
	mkdir .pa-nemu/
fi
if [ ! -d "/.pa-nemu/emotion/" ]; then
	mkdir .pa-nemu/emotion/
fi

cd .pa-nemu/emotion/

T=$[$(date +%s%N)/1000000]
time=$(date "+%Y-%m-%d-%H:%M:%S")
 
dialog --nocancel --title "你当前状态和情绪如何?" --menu "\n鼠标或方向键选择，点击OK或回车确定, 请认真做答, 若不想做可以选择跳过, 谢谢参与！" 20 30 10 1 "跳过" 2 "能应对挑战 比较投入" 3 "遇到点问题 有些困惑" 4 "问题卡住了 感到沮丧" 5 "学不下去了 觉得无趣"  2>_m.txt

M=$(cat _m.txt)

#一小时内免打扰
if [ $M = "1" ]; then
	dialog --nocancel --menu "是否希望一小时内免打扰?" 15 20 10  1 "YES" 2 "NO" 2>_m.txt
	D=$(cat _m.txt)
	echo $D" "$T > Disturb.txt

else
	#dialog --nocancel --menu "程度如何?" 20 30 10  1 "1(一点点)" 2 "2" 3 "3" 4 "4" 5 "5(非常)" 2>_m.txt
	#N=$(cat _m.txt)

	case $M in
		"2")
			M="flow"
			;;
		"3")
			M="confused"
			;;
		"4")
			M="furstrated"
			;;
		"5")
			M="bored"
			;;
	esac

	dialog --nocancel --default-item "4" --menu "就过去15分钟所做的PA内容，感觉挑战难度有多高?\n鼠标或方向键选择, 点击OK或回车确定, 请认真做答, 谢谢参与!" 20 30 10 1 "1(很低)" 2 "2" 3 "3" 4 "4(中等)" 5 "5" 6 "6" 7 "7(很高)" 2>_m.txt
	CN=$(cat _m.txt)

	dialog --nocancel --default-item "4" --menu "就过去15分钟所做的PA内容，感觉自己应对挑战能力有多强?\n鼠标或方向键选择, 点击OK或回车确定, 请认真做答, 谢谢参与!" 20 30 10 1 "1(很低)" 2 "2" 3 "3" 4 "4(中等)" 5 "5" 6 "6" 7 "7(很高)" 2>_m.txt
	SN=$(cat _m.txt)

	#echo $T" "${M}" "${N}" "$time >> ${T}_emotion.txt
	echo $T" "${M}" "${CN}" "${SN}" "$time >> ${T}_emotion.txt
	echo $T > DoNotFreq.txt
fi

rm -f _m.txt
