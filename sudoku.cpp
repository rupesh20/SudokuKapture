#include <bits/stdc++.h>
using namespace std;

bool CheckRow(int SUDO[9][9],int row, int num)
{
	for(int col=0;col<9;col++)
	{
		if(SUDO[row][col]==num)
			return true;
	}
	return false;
}

bool CheckCol(int SUDO[9][9],int col,int num){
	for(int row=0;row<9;row++)
	{
		if(SUDO[row][col]==num)
			return true;
	}
	return false;
}

bool Checkbox(int SUDO[9][9],int r,int c,int num){

	for(int row=0;row<3;row++)
	{
		for(int col=0;col<3;col++)
		{
			if(SUDO[row+r][col+c]==num)
			{
				return true;
			}
		}
	}
	return false;
}
bool conflicts(int SUDO[9][9], int row,int col,int num)
{
	return !CheckRow(SUDO,row,num)&&
			!CheckCol(SUDO,col,num)&&
			!Checkbox(SUDO,row-row%3,col-col%3,num);
	
}

bool Unassign(int SUDO[9][9],int &row, int &col){
	for (row= 0;  row<9 ; row++)
	{
		for(col=0;col<9;col++){
			if(SUDO[row][col]==0)
				return true;
		}	
	}
	return false;	
}


bool SolveSudoku(int SUDO[9][9]){
	int row,col;

	if(!Unassign(SUDO,row,col))
		return true;

	for(int num=1;num<=9;num++)
	{

		if(conflicts(SUDO,row,col,num))
		{	
			SUDO[row][col]=num;

			if(SolveSudoku(SUDO))
			{	return true; }

			SUDO[row][col]=0;
		}	
	}
	return false;
}

int main()
{
	int SUDO[9][9]={ {3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    
    bool x=SolveSudoku(SUDO);
	if(x)
	{
		for (int i = 0; i <9 ; ++i)
		{
			for (int j = 0; j <9 ; ++j)
			{
				printf("%2d",SUDO[i][j]);
			}
			printf("\n");	
		}
	}
	return 0;
}