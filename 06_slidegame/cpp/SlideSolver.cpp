
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>


/* 定数の定義 */
#define TRUE       1
#define FALSE      0
#define SIZE      16
#define MAX_SIZE   36
#define MOJI_NUM  100
//#define SIZE      9
#define MAX_MOVE 200
/* 種別の定義 */
#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15
#define EQ 20	//equal

char result[MAX_MOVE];

/* 隣接リスト */
const char adjacent33[9][5] = {
	1,3,-1,-1,-1,
	0,2,4,-1,-1,
	1,5,-1,-1,-1,
	0,4,6,-1,-1,
	1,3,5,7,-1,
	2,4,8,-1,-1,
	3,7,-1,-1,-1,
	4,6,8,-1,-1,
	5,7,-1,-1,-1,
};
const char adjacent34[12][5] = {
	1,3,-1,-1,-1,
	0,2,4,-1,-1,
	1,5,-1,-1,-1,
	0,4,6,-1,-1,
	1,3,5,7,-1,
	2,4,8,-1,-1,
	3,7,9,-1,-1,
	4,6,8,10,-1,
	5,7,11,-1,-1,
	6,10,-1,-1,-1,
	7,9,11,-1,-1,
	8,10,-1,-1,-1,
};
const char adjacent35[15][5] = {
	1,3,-1,-1,-1,
	0,2,4,-1,-1,
	1,5,-1,-1,-1,
	0,4,6,-1,-1,
	1,3,5,7,-1,
	2,4,8,-1,-1,
	3,7,9,-1,-1,
	4,6,8,10,-1,
	5,7,11,-1,-1,
	6,10,12,-1,-1,
	7,9,11,13,-1,
	8,10,14,-1,-1,
	9,13,-1,-1,-1,
	10,12,14,-1,-1,
	11,13,-1,-1,-1,
};
const char adjacent36[18][5] = {
	1,3,-1,-1,-1,
	0,2,4,-1,-1,
	1,5,-1,-1,-1,
	0,4,6,-1,-1,
	1,3,5,7,-1,
	2,4,8,-1,-1,
	3,7,9,-1,-1,
	4,6,8,10,-1,
	5,7,11,-1,-1,
	6,10,12,-1,-1,
	7,9,11,13,-1,
	8,10,14,-1,-1,
	9,13,15,-1,-1,
	10,12,14,16,-1,
	11,13,17,-1,-1,
	12,16,-1,-1,-1,
	13,15,17,-1,-1,
	14,16,-1,-1,-1,
};
const char adjacent43[12][5] = {
	1,4,-1,-1,-1,
	0,2,5,-1,-1,
	1,3,6,-1,-1,
	2,7,-1,-1,-1,
	0,5,8,-1,-1,
	1,4,6,9,-1,
	2,5,7,10,-1,
	3,6,11,-1,-1,
	4,9,-1,-1,-1,
	5,8,10,-1,-1,
	6,9,11,-1,-1,
	7,10,-1,-1,-1,
};
const char adjacent44[16][5] = {
   1,  4, -1, -1, -1,  /* 0 */
   0,  2,  5, -1, -1,  /* 1 */
   1,  3,  6, -1, -1,  /* 2 */
   2,  7, -1, -1, -1,  /* 3 */
   0,  5,  8, -1, -1,  /* 4 */
   1,  4,  6,  9, -1,  /* 5 */
   2,  5,  7, 10, -1,  /* 6 */
   3,  6, 11, -1, -1,  /* 7 */
   4,  9, 12, -1, -1,  /* 8 */
   5,  8, 10, 13, -1,  /* 9 */
   6,  9, 11, 14, -1,  /* 10 */
   7, 10, 15, -1, -1,  /* 11 */
   8, 13, -1, -1, -1,  /* 12 */
   9, 12, 14, -1, -1,  /* 13 */
  10, 13, 15, -1, -1,  /* 14 */
  11, 14, -1, -1, -1,  /* 15 */
};
const char adjacent45[20][5] = {
	1,4,-1,-1,-1,
	0,2,5,-1,-1,
	1,3,6,-1,-1,
	2,7,-1,-1,-1,
	0,5,8,-1,-1,
	1,4,6,9,-1,
	2,5,7,10,-1,
	3,6,11,-1,-1,
	4,9,12,-1,-1,
	5,8,10,13,-1,
	6,9,11,14,-1,
	7,10,15,-1,-1,
	8,13,16,-1,-1,
	9,12,14,17,-1,
	10,13,15,18,-1,
	11,14,19,-1,-1,
	12,17,-1,-1,-1,
	13,16,18,-1,-1,
	14,17,19,-1,-1,
	15,18,-1,-1,-1,
};
const char adjacent46[24][5] = {
	1,4,-1,-1,-1,
	0,2,5,-1,-1,
	1,3,6,-1,-1,
	2,7,-1,-1,-1,
	0,5,8,-1,-1,
	1,4,6,9,-1,
	2,5,7,10,-1,
	3,6,11,-1,-1,
	4,9,12,-1,-1,
	5,8,10,13,-1,
	6,9,11,14,-1,
	7,10,15,-1,-1,
	8,13,16,-1,-1,
	9,12,14,17,-1,
	10,13,15,18,-1,
	11,14,19,-1,-1,
	12,17,20,-1,-1,
	13,16,18,21,-1,
	14,17,19,22,-1,
	15,18,23,-1,-1,
	16,21,-1,-1,-1,
	17,20,22,-1,-1,
	18,21,23,-1,-1,
	19,22,-1,-1,-1,
};
const char adjacent53[15][5] = {
	1,5,-1,-1,-1,
	0,2,6,-1,-1,
	1,3,7,-1,-1,
	2,4,8,-1,-1,
	3,9,-1,-1,-1,
	0,6,10,-1,-1,
	1,5,7,11,-1,
	2,6,8,12,-1,
	3,7,9,13,-1,
	4,8,14,-1,-1,
	5,11,-1,-1,-1,
	6,10,12,-1,-1,
	7,11,13,-1,-1,
	8,12,14,-1,-1,
	9,13,-1,-1,-1,
};
const char adjacent54[20][5] = {
	1,5,-1,-1,-1,
	0,2,6,-1,-1,
	1,3,7,-1,-1,
	2,4,8,-1,-1,
	3,9,-1,-1,-1,
	0,6,10,-1,-1,
	1,5,7,11,-1,
	2,6,8,12,-1,
	3,7,9,13,-1,
	4,8,14,-1,-1,
	5,11,15,-1,-1,
	6,10,12,16,-1,
	7,11,13,17,-1,
	8,12,14,18,-1,
	9,13,19,-1,-1,
	10,16,-1,-1,-1,
	11,15,17,-1,-1,
	12,16,18,-1,-1,
	13,17,19,-1,-1,
	14,18,-1,-1,-1,
};
const char adjacent55[25][5] = {
	1,5,-1,-1,-1,
	0,2,6,-1,-1,
	1,3,7,-1,-1,
	2,4,8,-1,-1,
	3,9,-1,-1,-1,
	0,6,10,-1,-1,
	1,5,7,11,-1,
	2,6,8,12,-1,
	3,7,9,13,-1,
	4,8,14,-1,-1,
	5,11,15,-1,-1,
	6,10,12,16,-1,
	7,11,13,17,-1,
	8,12,14,18,-1,
	9,13,19,-1,-1,
	10,16,20,-1,-1,
	11,15,17,21,-1,
	12,16,18,22,-1,
	13,17,19,23,-1,
	14,18,24,-1,-1,
	15,21,-1,-1,-1,
	16,20,22,-1,-1,
	17,21,23,-1,-1,
	18,22,24,-1,-1,
	19,23,-1,-1,-1,
};
const char adjacent56[30][5] = {
	1,5,-1,-1,-1,
	0,2,6,-1,-1,
	1,3,7,-1,-1,
	2,4,8,-1,-1,
	3,9,-1,-1,-1,
	0,6,10,-1,-1,
	1,5,7,11,-1,
	2,6,8,12,-1,
	3,7,9,13,-1,
	4,8,14,-1,-1,
	5,11,15,-1,-1,
	6,10,12,16,-1,
	7,11,13,17,-1,
	8,12,14,18,-1,
	9,13,19,-1,-1,
	10,16,20,-1,-1,
	11,15,17,21,-1,
	12,16,18,22,-1,
	13,17,19,23,-1,
	14,18,24,-1,-1,
	15,21,25,-1,-1,
	16,20,22,26,-1,
	17,21,23,27,-1,
	18,22,24,28,-1,
	19,23,29,-1,-1,
	20,26,-1,-1,-1,
	21,25,27,-1,-1,
	22,26,28,-1,-1,
	23,27,29,-1,-1,
	24,28,-1,-1,-1,
};
const char adjacent63[18][5] = {
	1,6,-1,-1,-1,
	0,2,7,-1,-1,
	1,3,8,-1,-1,
	2,4,9,-1,-1,
	3,5,10,-1,-1,
	4,11,-1,-1,-1,
	0,7,12,-1,-1,
	1,6,8,13,-1,
	2,7,9,14,-1,
	3,8,10,15,-1,
	4,9,11,16,-1,
	5,10,17,-1,-1,
	6,13,-1,-1,-1,
	7,12,14,-1,-1,
	8,13,15,-1,-1,
	9,14,16,-1,-1,
	10,15,17,-1,-1,
	11,16,-1,-1,-1,
};
const char adjacent64[24][5] = {
	1,6,-1,-1,-1,
	0,2,7,-1,-1,
	1,3,8,-1,-1,
	2,4,9,-1,-1,
	3,5,10,-1,-1,
	4,11,-1,-1,-1,
	0,7,12,-1,-1,
	1,6,8,13,-1,
	2,7,9,14,-1,
	3,8,10,15,-1,
	4,9,11,16,-1,
	5,10,17,-1,-1,
	6,13,18,-1,-1,
	7,12,14,19,-1,
	8,13,15,20,-1,
	9,14,16,21,-1,
	10,15,17,22,-1,
	11,16,23,-1,-1,
	12,19,-1,-1,-1,
	13,18,20,-1,-1,
	14,19,21,-1,-1,
	15,20,22,-1,-1,
	16,21,23,-1,-1,
	17,22,-1,-1,-1,
};
const char adjacent65[30][5] = {
	1,6,-1,-1,-1,
	0,2,7,-1,-1,
	1,3,8,-1,-1,
	2,4,9,-1,-1,
	3,5,10,-1,-1,
	4,11,-1,-1,-1,
	0,7,12,-1,-1,
	1,6,8,13,-1,
	2,7,9,14,-1,
	3,8,10,15,-1,
	4,9,11,16,-1,
	5,10,17,-1,-1,
	6,13,18,-1,-1,
	7,12,14,19,-1,
	8,13,15,20,-1,
	9,14,16,21,-1,
	10,15,17,22,-1,
	11,16,23,-1,-1,
	12,19,24,-1,-1,
	13,18,20,25,-1,
	14,19,21,26,-1,
	15,20,22,27,-1,
	16,21,23,28,-1,
	17,22,29,-1,-1,
	18,25,-1,-1,-1,
	19,24,26,-1,-1,
	20,25,27,-1,-1,
	21,26,28,-1,-1,
	22,27,29,-1,-1,
	23,28,-1,-1,-1,
};
const char adjacent66[36][5] = {
	1,6,-1,-1,-1,
	0,2,7,-1,-1,
	1,3,8,-1,-1,
	2,4,9,-1,-1,
	3,5,10,-1,-1,
	4,11,-1,-1,-1,
	0,7,12,-1,-1,
	1,6,8,13,-1,
	2,7,9,14,-1,
	3,8,10,15,-1,
	4,9,11,16,-1,
	5,10,17,-1,-1,
	6,13,18,-1,-1,
	7,12,14,19,-1,
	8,13,15,20,-1,
	9,14,16,21,-1,
	10,15,17,22,-1,
	11,16,23,-1,-1,
	12,19,24,-1,-1,
	13,18,20,25,-1,
	14,19,21,26,-1,
	15,20,22,27,-1,
	16,21,23,28,-1,
	17,22,29,-1,-1,
	18,25,30,-1,-1,
	19,24,26,31,-1,
	20,25,27,32,-1,
	21,26,28,33,-1,
	22,27,29,34,-1,
	23,28,35,-1,-1,
	24,31,-1,-1,-1,
	25,30,32,-1,-1,
	26,31,33,-1,-1,
	27,32,34,-1,-1,
	28,33,35,-1,-1,
	29,34,-1,-1,-1,
};
/* 初期状態 
char init_state[SIZE] = {
  A, B, A, S,
  C, D, C, D,
  A, B, A, B,
  C, D, C, D,
};
*/
//char init_state[SIZE] = {'4','1','14','12','8','6','0','7','9','11','10','5','3','2','15','13'};
//char init_state[SIZE] = {4,1,14,12,8,6,0,7,9,11,10,5,3,2,15,13};
//int board[SIZE] = {3,2,4,6,5,8,7,1,F,A,C,0,EQ,9,B,E};
//int board[SIZE] = {1,2,0,7,4,3,5,8,6};
int board[MAX_SIZE];

int count;         /* 発見した解の個数 */
//char GOAL[SIZE] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '0'};
//char GOAL[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
//int GOAL[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, EQ, E, F, 0};
//int GOAL[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
int GOAL[MAX_SIZE];

/* 動かした位置, 移動先の位置 */
char move_position[MAX_MOVE];
char move_history[MAX_MOVE];
char moveto_position[MAX_MOVE];

/*
 * 移動手数表
 *
 */
//int distance[16][16];
int distance[MAX_SIZE][MAX_SIZE];

void make_distance( int w, int h )
{
	memset(distance, -1, MAX_SIZE * MAX_SIZE);
	int i, j, dx, dy, buf;
	for(i=0; i<w*h; i++)
	{
		for(j=1; j<=w*h; j++)
		{
			if(i==0){
				distance[i][j-1] = -1;
			} else {
				buf = (j-1)%w - (i-1)%w;
				dx = (buf >= 0)?  buf : -buf;
				buf = (j-1)/w - (i-1)/w;
				dy = (buf >= 0)?  buf : -buf;
				distance[i][j-1] = dx + dy;
			}
		}
	}
}
void make_board( int w, int h, char *boardinfo )
{
	int i;
	char c;
	
	memset(board, -1, MAX_SIZE);
	
	for(i=0; i<w*h; i++)
	{
		c = boardinfo[i];
		if( c == '=' )
		{
			board[i] = EQ;
		}
		else if( c > '9' )
		{
			board[i] = (int)c - 55;
		}
		else
		{
			board[i] = (int)c - 48;
		}
	}
}
void make_GOAL( int w, int h, char *boardinfo )
{
	int i;
	char c;
	
	memset(GOAL, -1, MAX_SIZE);
	
	for(i=0; i<w*h; i++)
	{
		char c = boardinfo[i];
		if( c == '=' )
		{
			GOAL[i] = EQ;
		}
		else
		{
			GOAL[i] = i + 1;
		}
	}
	GOAL[w*h-1] = 0;
}

/* 下限値を求める */
int calc_lower_value( int w, int h, int *board )
{
	int i, j, d = 0;
	for( i = 0; i < w*h; i++ ){
		j = board[i];
		if( j > 0 && j < EQ ) d += distance[j][i];
	}
	return d;
}


/* 手順を表示 */
void print_answer( int m )
{
	int i;
	for( i = 1; i <= m; i++ ){
		printf("%d ", move_position[i] );
	}
	printf("\n");
}

void print_history( int m )
{
	int i;
	for( i = 1; i <= m; i++ ){
		printf("%c", move_history[i] );
	}
	printf("\n");
}

void print_board()
{
	int i;
	for( i = 0; i < MAX_SIZE; i++ ){
		printf("%d,", board[i] );
	}
	printf("\n");
}
void print_GOAL()
{
	int i;
	for( i = 0; i < MAX_SIZE; i++ ){
		printf("%d,", GOAL[i] );
	}
	printf("\n");
}
void print_adjacent(int w, int h, const char adjacent[][5])
{
	int i,j;
	for( i = 0; i < w*h; i++ ){
		for( j = 0; j < 5; j++ ){
			printf("%d,", adjacent[i][j] );
		}
	}
	printf("\n");
}

/* 初期化 */
int init( int w, int h, char *boardinfo )
{
	//memcpy( board, init_state, SIZE );
	move_position[0] = -1;
	moveto_position[0] = -1;
	move_history[0] = -1;
	count = 0;
	make_board(w, h, boardinfo);
	make_GOAL(w, h, boardinfo);
	make_distance(w,h);
	//print_board();
	//print_GOAL();
	return calc_lower_value( w, h, board );
}

bool isClear(int *arrayBoard, int *arrayGOAL, int intSize)
{
	int i;
	for( i = 0; i < intSize; i++ ){
		if(arrayBoard[i] != arrayGOAL[i]) {
			return false;
		}
	}
	return true;
}

void set_result( int m )
{
	int i;
	memset(result, '\0', MAX_MOVE);
	//memcpy(result, move_history, m);
	for( i = 0; i < m; i++ ){
		result[i] = move_history[i+1];
	}
}

/* 下限値枝刈り法 */
void solve_low( int limit, int move, int space, int low , int w, int h, int s, int tl, const char adjacent[][5])
{
	int e = clock();
	if( move == limit ){
		if( isClear( board, GOAL, w*h ) ){
			/* 見つけたよ */
			count++;
			//print_answer( move );
			//print_board();
			//print_history( move );
			set_result(move);
		}
	} else if((e-s)/1000 > tl) {
		count++;
		memset(result, '\0', MAX_MOVE);
		memcpy(result, "timeout", 7);
	} else {
		//print_history( move );
		//print_board();
		//print_adjacent(w,h,adjacent);
		//printf("space=%d\n", space);
		int i, j, new_low;
		for( i = 0; (j = adjacent[space][i]) != -1; i++ ){
			int p = board[j];
			int move_distance;
			if (p == EQ) continue;
			if( moveto_position[move] == j ) continue;
			//if( move_position[move] == p ) continue;
			/* 移動する */
			board[space] = p;
			board[j] = 0;
			move_position[move + 1] = j;
			moveto_position[move + 1] = space;

			move_distance = j - space;
			//printf("%d\n",move_distance);
			if (move_distance == -w) {
				move_history[move + 1] = 'U';
			} else if( move_distance == -1) {
				move_history[move + 1] = 'L';
			} else if( move_distance == 1) {
				move_history[move + 1] = 'R';
			} else if(move_distance == w) {
				move_history[move + 1] = 'D';
			}
			//print_history( move );
			new_low = low - distance[p][j] + distance[p][space];

			/* 下限値による枝刈り */
			if( new_low + move <= limit ){
				solve_low( limit, move + 1, j, new_low, w, h, s, tl, adjacent );
			}
			/* 元に戻す */
			board[space] = 0;
			board[j] = p;
		}
	}
}
int get_space()
{
	int i;
	for( i = 0; i < MAX_SIZE; i++ ){
		if(board[i] == 0) return i;
	}
	return -1;
}

char **split(char *str, char *sep)
{
	char *word = NULL;
	char *str_work = NULL;
	int last = 0;

	//うけとった文字列のコピーを作成
	str_work = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(str_work, str);

	//文字列のポインタを保持する配列
	char **results = (char **)malloc(sizeof(char *) * MOJI_NUM);

	//strtokで得たトークンのポインタを配列に代入
	last = 0;
	for(word = strtok(str_work,sep); word; word = strtok(NULL,sep),last++) {
		results[last] = word;
	}
	results[last] = NULL;

	return results;   
}

// splitで作成した配列のメモリを解放する
void split_free(char **words)
{   
	//words[0]をfreeすればすべてのトークンのメモリは解放される?
	free(words[0]);
	free(words);
}


/*
	arg1:開始位置 	デフォルト:1
	arg2:終了位置 	デフォルト:5000
	arg3:下限 		デフォルト:9
	arg4:上限 		デフォルト:36
	arg5:制限時間 	デフォルト:10000s

*/
int main(int argc, char *argv[])
{
	int low, limit, w, h, i;
	int start, end, min, max, tl;
	int LX, RX, UX, DX, N;
	int s;
	char **words = NULL;
	char *status;
	char *arg_status;
	char *boardinfo;
	
	//引数チェック
	if(argc < 2){
		//デフォルト値
		start 	= 1;
		end 	= 5000;
		min 	= 9;
		max 	= 36;
		tl 		= 10000;
		arg_status = "yet";
	} else {
		start 	= atoi(argv[1]);
		end 	= atoi(argv[2]);
		min 	= atoi(argv[3]);
		max 	= atoi(argv[4]);
		tl 		= atoi(argv[5]);
		arg_status = argv[6];
	}
	//printf("start=%d,end=%d,min=%d,max=%d,tl=%d,status=%s\n", start, end, min, max, tl, arg_status);
	//ファイル読み込み
	FILE *ifp;
	const char *ifile = "input_status.data";
	char input_line[MOJI_NUM];
	
	ifp = fopen( ifile, "r" );
	if( ifp == NULL ){
		return -1;
	}
	
	//書き込み用ファイル
	const char *ofile = "output.data";
	std::ofstream ofs(ofile);

	//使うことができる L, R, U, D それぞれの総数
	memset(input_line, '\0', MOJI_NUM);
	if(NULL != fgets(input_line, MOJI_NUM, ifp))
	{
		words = split(input_line, " ");
		
		LX = atoi(words[0]);
		RX = atoi(words[1]);
		UX = atoi(words[2]);
		DX = atoi(words[3]);
		
	}
	split_free(words);
	
	//テストケース数
	memset(input_line, '\0', MOJI_NUM);
	if(NULL != fgets(input_line, MOJI_NUM, ifp))
	{
		N = atoi(input_line);
	}
	i = 0;
	s = clock();
	while(NULL != fgets(input_line, MOJI_NUM, ifp))
	{
//	while(i<1)
//	{
		//fgets(input_line, MOJI_NUM, ifp);
		
		words = split(input_line, ",");
		status = words[0];
		w = atoi(words[1]);
		h = atoi(words[2]);
		boardinfo = words[3];
		//printf("status=%s, w=%d, h=%d, board=%s\n", status, w, h, boardinfo);
		
		if( i + 1 < start ) {
			//printf("start=%d, i+1=%d\n", start, i+1);
			ofs << std::endl;
			i ++;
			continue;
		}
		else if( i + 1 > end ) {
			//printf("end\n");
			ofs << std::endl;
			i ++;
			continue;
		}
		else if( w * h < min ) {
			//printf("min\n");
			ofs << std::endl;
			i ++;
			continue;
		}
		else if( w * h > max ) {
			//printf("max\n");
			ofs << std::endl;
			i ++;
			continue;
		}
		else if(strcmp(arg_status, status) != 0) {
			//printf("status\n");
			ofs << std::endl;
			i ++;
			continue;
		}
		printf("***** %d 番目の問題を探索中 *****\n", i + 1 );
			
		s = clock();
		low = init(w,h,boardinfo);
		//printf("low=%d\n", low);
		//print_board();
		//print_GOAL();
		switch(w)
		{
		case 3:
			switch(h)
			{
			case 3:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent33);
					if( count > 0 ) break;
				}
				break;
			case 4:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent34);
					if( count > 0 ) break;
				}
				break;
			case 5:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent34);
					if( count > 0 ) break;
				}
				break;
			case 6:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent34);
					if( count > 0 ) break;
				}
				break;
			default:
				printf("error\n");
				break;
			}
			break;
		case 4:
			switch(h)
			{
			case 3:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent43);
					if( count > 0 ) break;
				}
				break;
			case 4:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent44);
					if( count > 0 ) break;
				}
				break;
			case 5:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent45);
					if( count > 0 ) break;
				}
				break;
			case 6:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent46);
					if( count > 0 ) break;
				}
				break;
			default:
				printf("error\n");
				break;
			}
			break;
		case 5:
			switch(h)
			{
			case 3:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent53);
					if( count > 0 ) break;
				}
				break;
			case 4:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent54);
					if( count > 0 ) break;
				}
				break;
			case 5:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent55);
					if( count > 0 ) break;
				}
				break;
			case 6:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent56);
					if( count > 0 ) break;
				}
				break;
			default:
				printf("error\n");
				break;
			}
			break;
		case 6:
			switch(h)
			{
			case 3:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent63);
					if( count > 0 ) break;
				}
				break;
			case 4:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent64);
					if( count > 0 ) break;
				}
				break;
			case 5:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent65);
					if( count > 0 ) break;
				}
				break;
			case 6:
				for( limit = low; limit < MAX_MOVE; limit++ ){
					solve_low( limit, 0, get_space(), low, w, h, s, tl, adjacent66);
					if( count > 0 ) break;
				}
				break;
			default:
				printf("error\n");
				break;
			}
			break;
		}
		i++;
		split_free(words);
		printf("%s\n", result);
		ofs << result << std::endl;
	}
	//end = clock();
	
	//printf("個数 %d, 時間 %d \n", count, end - start );
	return 0;
}

