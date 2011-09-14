# coding: utf-8
import os.path

#全て5の倍数、もしくは0であれば0を返す。そうでないなら-1
def isAllMultipleOf5(array):
	for x in array:
		if x % 5 != 0:
			return -1
	return 0

#与えられた数を半分にしていき、5の倍数がでるまでの回数を返す
def countDivToMultipleOf5(num):
	i = 0
	while num % 5 != 0:
		num = num /2
		i += 1
	return i

#与えられた数値を指定の回数だけ半分にする
def divideNum(num, count):
	for i in xrange(count):
		num = num /2
	return num

#5を含んでいれば0を返す。そうでないなら-1
def isContainMultipleOf5(array):
	for x in array:
		if x % 5 == 0:
			return 0
	return -1

#5 の倍数 (0 を含む) を全て取り除く
def clearMultipleOf5(array):
	i=0
	while i < len(array):
		if array[i] % 5 == 0:
			array.pop(i)
			i -= 1
		i += 1
	return array

#全ての数を半分にする（端数は切り捨て）
def divAllNum(array):
	return map((lambda x:x/2),array)
	
def solver(array):
	#文字列から数値に変換
	arrayint = map(int, array.split(' '))

	#メイン処理
	#とれる手段は以下の2つ
	# 1. 全ての数を半分にする（端数は切り捨て）
	# 2. 5 の倍数 (0 を含む) を全て取り除く
	cnt = 0
	q = [arrayint]
	while len(q) > 0:
		flg = False
		#dequeu
		arraypop = q.pop(0)
		arraylast = []		#探索中の最新手
		if isinstance(arraypop, list) == True:
			if isinstance(arraypop[0], list) == True:
				arraylast = arraypop[len(arraypop)-1]	#二次元配列状態[[10,22,30],[5,11,15],[]]
			else:
				flg = True
				arraylast = arraypop[:]					#数字の配列=一手目
		else:
			print "error"
		
		if isAllMultipleOf5(arraylast) == 0:
			#全ての数が5の倍数である場合
			if flg == True:
				#一手目
				cnt = 1
			else:
				cnt = len(arraypop)
			return str(cnt)
		else:
			if flg == True:	#数字の配列
				#queueから取得した状態に「全ての数を2で割った」手を追加する
				div_array = []	#全てを2で割った配列
				div_array.append(arraypop)
				div_array.append(divAllNum(arraylast))
				q.append(div_array)
				
				#queueから取得した状態に「5の倍数を削除した」手を追加する
				if isContainMultipleOf5(arraylast) == 0:
					#5の倍数を含む場合のみ
					del_array = []	#5の倍数を除去した配列
					del_array.append(arraypop)
					new_array = arraylast[:]
					del_array.append(clearMultipleOf5(new_array))
					q.append(del_array)
			else:			#配列の配列
				#queueから取得した状態に「全ての数を2で割った」手を追加する
				div_array = arraypop[:]
				div_array.append(divAllNum(arraylast))
				q.append(div_array)
				
				#queueから取得した状態に「5の倍数を削除した」手を追加する
				if isContainMultipleOf5(arraylast) == 0:
					#5の倍数を含む場合のみ
					del_array = arraypop[:]
					new_array = arraylast[:]
					del_array.append(clearMultipleOf5(new_array))
					q.append(del_array)

#メイン処理

#入力データ取得
inputfile = "input.data"
if os.path.exists(inputfile):
	fi = open(inputfile, 'r')
else:
	exit()

#出力ファイル作成
outputfile = "answer.data"
fo =  open(outputfile, 'w')


#テストケース数
T = fi.readline()
i = 0
while i < int(T):
	N = fi.readline()
	a = fi.readline()
	print str(i+1) + u"問目"
	fo.write(solver(a) + '\n')
	i += 1

fi.close()
fo.close()
