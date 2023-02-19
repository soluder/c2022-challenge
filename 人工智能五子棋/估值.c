//// 获取一个叶节点的价值
////从行 列 对角线 斜对角线 四个方向评价该节点
////构建一个含有所有棋型的字符串数组
////黑子为一，白子为负一，空白为零
//#include<string.h>
//
//int evaluate(int pawn[320][320], int xPos, int yPos)
//{
//	int value=0;
//	int left = 20;
//	int right = 300;
//	int bottom = 300;
//	int top = 20;
//	int width = 20;
//	int count = 0;
//	//棋型库
//	char chess[4][9] = {
//		"666666666",
//		"666666666",
//		"666666666",
//		"666666666",
//};
//     char* chesstype[24] = {
//	"11111",//1,长联
//	"011110",//2，活四
//	"011112",//3，冲四
//	"0101110",//4
//	"0110110",//5
//	"01110",//6，活三
//	"010110",//7
//	"001112",//8，眠三
//	"010112",//9
//	"011012",//10
//	"10011",//11
//	"10101",//12
//	"2011102",//13
//	"00110",//14，活二
//	"01010",//15
//	"010010",//16
//	"000112",//17眠二
//	"001012",//18
//	"010012",//19
//	"10001",//20
//	"2010102",//21
//	"2011002",//22
//	//"211112",//23，死四
//	//"21112",//24，死三
//	//"2112",//25，死二
//	"010",//23,活一
//	"0120",//24，眠一
//	//"212",//28，死一
//	
//	};
//	int ChessTypeValue[24] = {
//		1000000,//1
//		50000,//2
//		400,//3
//		400,//4
//		400,//5
//		400,//6
//		400,//7
//		20,//8
//		20,//9
//		20,//10
//		20,//11
//		20,//12
//		20,//13
//		20,//14
//		20,//15
//		20,//16
//		2,//17
//		2,//18
//		2,//19
//		2,//20
//		2,//21
//		2,//22
//		//-5,//23
//		//-5,//24
//		//-5,//25
//		 2,//23
//		 1,//24
//		 //1,//27
//		 //-5,//28
//
//	}; 
//	int ChessTypeValue2[24] = {
//		10000000,//1
//		100000,//2
//		100000,//3
//		100000,//4
//		100000,//5
//		8000,//6
//		8000,//7
//		50,//8
//		50,//9
//		50,//10
//		50,//11
//		50,//12
//		50,//13
//		50,//14
//		50,//15
//		50,//16
//		3,//17
//		3,//18
//		3,//19
//		3,//20
//		3,//21
//		3,//22
//		//-5,//23
//		//-5,//24
//		//-5,//25
//		 3,//23
//		 2,//24
//		 //1,//27
//		 //-5,//28
//
//	};
//	
//	
//	//将节点相应位置信息转为字符串，通过查找字符串评价节点
//	for (int i = xPos - 80,count=0; i <= xPos + 80; i += width)
//	{
//		if (i<left || i>right)
//		{
//			chess[0][count] = '6';
//			count++;
//		}
//		else {
// 			if (*(pawn[i] + yPos) == 1)
//			{
//				chess[0][count] = '1';
// 			}
//			else if (*(pawn[i] + yPos) == 0)
//			{
//				chess[0][count] = '0';
//			}
//			else if (*(pawn[i] + yPos) == -1)
//			{
//				chess[0][count] = '2';
//			}
//			count++;
//		}
//	}
//	for (int i = yPos - 80, count = 0; i <= yPos + 80; i += width)
//	{
//		if (i<top || i>bottom)
//		{
//			chess[1][count] = '6';
//			count++;
//		}
//		else {
//			if (*(pawn[xPos] + i) == 1)
//			{
//				chess[1][count] = '1';
//			}
//			else if (*(pawn[xPos] + i) == 0)
//			{
//				chess[1][count] = '0';
//			}
//			else if (*(pawn[xPos] + i) == -1)
//			{
//				chess[1][count] = '2';
//			}
//			count++;
//		}
//	}
//	for (int i = xPos - 80, j = yPos - 80,count=0; i <= xPos + 80; i += width, j += width)
//	{
//		if (i<left || i>right || j<top || j>bottom)
//		{
//			chess[2][count] = '6';
//			count++;
//		}
//		else {
//			if (*(pawn[i] + j) == 1)
//			{
//				chess[2][count] = '1';
//			}
//			else if (*(pawn[i] + j) == 0)
//			{
//				chess[2][count] = '0';
//			}
//			else if (*(pawn[i] + j) == -1)
//			{
//				chess[2][count] = '2';
//			}
//			count++;
//		}
//	}
//	for (int i = xPos - 80, j = yPos + 80, count = 0; i <= xPos + 80; i += width, j -= width)
//	{
//		if (i<left || i>right || j<top || j>bottom)
//		{
//			chess[3][count] = '6';
//			count++;
//		}
//		else {
//			if (*(pawn[i] + j) == 1)
//			{
//				chess[3][count] = '1';
//			}
//			else if (*(pawn[i] +j) == 0)
//			{
//				chess[3][count] = '0';
//			}
//			else if (*(pawn[i] + j) == -1)
//			{
//				chess[3][count] = '2';
//			}
//			count++;
//		}
//	}
//	//检查行
//	//for (int i = left; i <= right; i += width)
//	//{
//	//	for (int j = top,cnt=0; j <= bottom; j += width)
//	//	{
//	//		 
//	//		            if (*(pawn[i] + j) == 1)
//	//					{
//	//						chess[count][cnt++] = '1';
//	//		 			}
//	//					else if (*(pawn[i] + j) == 0)
//	//					{
//	//						chess[count][cnt++] = '0';
//	//					}
//	//					else if (*(pawn[i] + j) == -1)
//	//					{
//	//						chess[count][cnt++] = '2';
//	//					}
//	//	}
//	//	count++;
//	//}
//	////检查行
//	//for (int j = left; j <= right; j += width)
//	//{
//	//	for (int i = top, cnt = 0; i <= bottom; i += width)
//	//	{
//
//	//		if (*(pawn[i] + j) == 1)
//	//		{
//	//			chess[count][cnt++] = '1';
//	//		}
//	//		else if (*(pawn[i] + j) == 0)
//	//		{
//	//			chess[count][cnt++] = '0';
//	//		}
//	//		else if (*(pawn[i] + j) == -1)
//	//		{
//	//			chess[count][cnt++] = '2';
//	//		}
//	//	}
//	//	count++;
//	//}
//	////检查对角线上半部分 
//	//for (int m = left; m < right - 80; m += width)
//	//{
//	//	for (int i = m, j = 20,cnt=0; i <= right; i += width, j += width)
//	//	{
//	//		if (*(pawn[i] + j) == 1)
//	//		{
//	//			chess[count][cnt++] = '1';
//	//		}
//	//		else if (*(pawn[i] + j) == 0)
//	//		{
//	//			chess[count][cnt++] = '0';
//	//		}
//	//		else if (*(pawn[i] + j) == -1)
//	//		{
//	//			chess[count][cnt++] = '2';
//	//		}
//
//
//	//	}
//	//	count++;
//	//}
//	////检查对角线下半部分
//	//for (int m = top + width; m < bottom - 80; m += width)
//	//{
//	//	for (int i = 20, j = m,cnt=0; i <= bottom; i += width, j += width)
//	//	{
//	//		if (*(pawn[i] + j) == 1)
//	//		{
//	//			chess[count][cnt++] = '1';
//	//		}
//	//		else if (*(pawn[i] + j) == 0)
//	//		{
//	//			chess[count][cnt++] = '0';
//	//		}
//	//		else if (*(pawn[i] + j) == -1)
//	//		{
//	//			chess[count][cnt++] = '2';
//	//		}
//
//
//	//	}
//	//	count++;
//	//}
//	////检查斜对角线上半部分
//	//for (int m = right; m > left + 80; m -= width)
//	//{
//	//	for (int i = m, j = 20,cnt=0; i >= left; i -= width, j += width)
//	//	{
//	//		if (*(pawn[i] + j) == 1)
//	//		{
//	//			chess[count][cnt++] = '1';
//	//		}
//	//		else if (*(pawn[i] + j) == 0)
//	//		{
//	//			chess[count][cnt++] = '0';
//	//		}
//	//		else if (*(pawn[i] + j) == -1)
//	//		{
//	//			chess[count][cnt++] = '2';
//	//		}
//
//
//	//	}
//	//	count++;
//	//}
//	////检查斜对角线下半部分
//	//for (int m = top + width; m < bottom - 80; m += width)
//	//{
//	//	for (int i = 320, j = m,cnt=0; j <= bottom; i -= width, j += width)
//	//	{
//	//		if (*(pawn[i] + j) == 1)
//	//		{
//	//			chess[count][cnt++] = '1';
//	//		}
//	//		else if (*(pawn[i] + j) == 0)
//	//		{
//	//			chess[count][cnt++] = '0';
//	//		}
//	//		else if (*(pawn[i] + j) == -1)
//	//		{
//	//			chess[count][cnt++] = '2';
//	//		}
//	//	}
//	//	count++;
//	//}
//	//strstr评价
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 24; j++)
//		{
//			if (strstr( chess[i], chesstype[j])!=NULL || strstr(_strrev(chess[i]), chesstype[j]) != NULL)
//			{
//			    
//				value += ChessTypeValue[j];
//			}
//		}
//	}
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 9; j++)
//		{
//			if (chess[i][j] == '1')
//			{
//				chess[i][j] = '2';
//			}else if (chess[i][j] == '2')
//			{
//				chess[i][j] = '1';
//			}
//		}
//	}
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 24; j++)
//		{
//			if (strstr(chess[i], chesstype[j]) != NULL || strstr(_strrev(chess[i]), chesstype[j]) != NULL)
//			{
//
//				value -= ChessTypeValue2[j]; 
//			}
//		}
//	}
//	
//
//                                                                                                                                                     
//
//	
//
//	return value;
//}