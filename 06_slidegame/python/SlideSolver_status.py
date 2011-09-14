# coding: utf-8
import os.path
import time

#カウンタ
LC = 0
RC = 0
UC = 0
DC = 0


# 隣接リスト
adjacent = []

# 距離
distance = []

# 距離を求める
def get_distance(board):
	v = 0
	for x in xrange(len(board)):
		p = board[x]
		if p == "0": continue
		if p == "=": continue
		#v += distance[p][x]
		v += distance[int(p)][x]
	return v

# ゴールの局面
GOAL = []

# 盤面
board = []

# 動かした駒
move_piece = [None] * 200
move_history = [None] * 200

def convListToStr(array):
	arraybuf = []
	arraybuf = filter((lambda x: x!=None), array)
	return "".join(map(str,arraybuf))

def checkLRUDcount(strAns):
	global LC
	global RC
	global UC
	global DC
	
	global LX
	global RX
	global UX
	global DX
	
	if strAns == "timeout":
		return True
	
	#文字列からLRUDカウント
	LC += strAns.count("L")
	RC += strAns.count("R")
	UC += strAns.count("U")
	DC += strAns.count("D")
	
	if LC > LX:
		return False
	elif RC > RX:
		return False
	elif UC > UX:
		return False
	elif DC > DX:
		return False
	return True

# 下限値枝刈り法
def id_lower_search(limit, move, space, lower, w, h, s, tl):
	e = time.clock()
	if move == limit:
		if board == GOAL:
			global count
			count += 1
			global result
			result = convListToStr(move_history)
	elif e - s > tl:
		count += 1
		result = "timeout"
	else:
		for x in adjacent[space]:
			p = board[x]
			if p == "=": continue
			if move_piece[move] == p: continue
			# 駒を動かす
			board[space] = p
			board[x] = "0"
			move_piece[move + 1] = p
			move_distance = x - space	
			if move_distance == -w:			#上移動
				move_history[move] = "U"
			elif move_distance == -1:		#左移動
				move_history[move] = "L"
			elif move_distance == 1:		#右移動
				move_history[move] = "R"
			elif move_distance == w:		#下移動
				move_history[move] = "D"
				
			new_lower = lower - distance[int(p)][x] + distance[int(p)][space]
			# 下限値枝刈り法
			if new_lower + move <= limit:
				id_lower_search(limit, move + 1, x, new_lower, w, h, s, tl)
			# 元に戻す
			board[space] = "0"
			board[x] = p
			

def get_board(w,h,b):
	new_board = []
	for i in xrange(w*h):
		if b[i].isalpha():
			#英数字
			new_board.append(str(ord(b[i])-55))
		else:
			new_board.append(b[i])
	return new_board[:]

def get_GOAL(w,h,b):
	new_GOAL = []
	for i in xrange(w*h):
		if b[i] != "=":
			new_GOAL.append(str(i+1))
		else:
			new_GOAL.append("=")
	new_GOAL[len(new_GOAL)-1] = "0"
	return new_GOAL[:]

def setAdjacent(w,h):
	global adjacent
	adjacent = []
	for i in xrange(w*h):
		buf = []
		if i - w >= 0 and i - w < w*h:
			buf.append(i-w)
		if i - 1 >= 0 and i - 1 < w*h:
			if i % w != 0: 					#左端でなかったら
				buf.append(i-1)
		if i + 1 >= 0 and i + 1 < w*h:
			if i % w != w-1: 				#右端でなかったら
				buf.append(i+1)
		if i + w >= 0 and i + w < w*h:
			buf.append(i+w)
		adjacent.append(buf)

def setDistance(w,h):
	global distance
	distance = []
	for i in xrange(w*h):
		buf = []
		if i != 0: 
			for j in xrange(1,w*h+1):
				#距離計算
				dx = (j-1)%w - (i-1)%w if (j-1)%w - (i-1)%w > 0 else -((j-1)%w - (i-1)%w)	#横
				dy = (j-1)/w - (i-1)/w if (j-1)/w - (i-1)/w > 0 else -((j-1)/w - (i-1)/w)	#縦
				#if dx < 0:dx = -dx
				buf.append(dx + dy)
		distance.append(buf)

count = 0
result = ""
def solve_slide(w, h, b, tl):
	s = time.clock()
	global board
	global GOAL
	board = get_board(w,h,b)
	GOAL = get_GOAL(w,h,b)
	
	setAdjacent(w,h)
	setDistance(w,h)
	n = get_distance(board)
	strAns = ""
	global result
	for x in xrange(n, 200):
		#print 'move ', x
		#print board
		id_lower_search(x, 0, board.index("0"), n, w, h, s, tl)
		if count > 0: break
	return result


#メイン処理
LX = 0
RX = 0
UX = 0
DX = 0
N = 0

def main(start, end, min, max, tl, status):
	global LX
	global RX
	global UX
	global DX
	global N
	global count
	global move_piece
	global move_history

	#入力データ取得
	inputfile = "input_status.data"
	if os.path.exists(inputfile):
		fi = open(inputfile, 'r')
	else:
		exit()

	#出力ファイル作成
	outputfile = "output.data"
	fo =  open(outputfile, 'w')


	#使うことができる L, R, U, D それぞれの総数
	line = fi.readline().split(' ')
	LX = int(line[0])
	RX = int(line[1])
	UX = int(line[2])
	DX = int(line[3])

	N = int(fi.readline())

	for i in xrange(N):
		print i+1
		line = fi.readline().split(',')
		sta = line[0]
		w = int(line[1])
		h = int(line[2])
		b = line[3]
		if i + 1 < start:
			fo.write('\n')
		elif i + 1 > end:
			fo.write('\n')
		elif w * h < min:
			fo.write('\n')
		elif w * h > max:
			fo.write('\n')
		elif sta == status:
	#		if b.find("=") == -1:
			strAns = solve_slide(w,h,b,tl)
			if checkLRUDcount(strAns) == True:
				fo.write(strAns + '\n')
				print strAns
			else:
				fo.write('\n')
				continue
			#fo.write(str(w) + "," + str(h) + "," + b + '\n')
			#グローバル変数初期化
			count = 0
			move_piece = [None] * 200
			move_history = [None] * 200
	#		else:
	#			fo.write('\n')
		else:
			fo.write('\n')
	fi.close()
	fo.close()
	
if __name__ == "__main__":
	main(1,5000,0,99,300,"yet")	#1問目から
