#ifndef __SUDOKU_CLASS_H
#define __SUDOKU_CLASS_H

//#include<fstream>
//#include<iostream>
//#include<string>
//using namespace std;

class CSudoku
{
private:
	int sudo[9][9][10];//最底层用来存放数独题目,之上的九层用来存放各个格可能的数,这个空格不可能的数字用零代替
	bool result;
public:
	CSudoku();
	~CSudoku(){};
	bool Test();
	void Initialization();//Initialization
	void SetByFile();//从dat文件输入数独
	void ShowSudoku(const char *pstr);//按照一定的格式将三维数组最底层显示出来,即显示数独
	void FirstRemove();
	void GridRemove(int rows,int cols);//确定格的数字后需要排除其他格有这个数字的可能性,前提为格中数字不为0
	void RowTwoRem();//Row two remove排除
	void ColTwoRem();//Columns two remove排除
	void JGTwoRem();//九宫排除
	void SevGitsRow();//Several Grid in the same row
	void SevGitsCol();//Several Grid in the same columns
	void RowColitsJG();//Row and Columns in the same jiugong
	void RowTwoRecRem();//Rectangle
	void ColTwoRecRem(); //Columns two rectangle remove
};

#endif//__SUDOKU_CLASS_H
