#include"SudokuClass.h"
int main(void)
{
	
	CSudoku sudok;//定义一个数独对象sudok
//	while(1)
//	{
		sudok.SetByFile();
		sudok.ShowSudoku("sudoku");
		sudok.FirstRemove();
		for(int k=0;k<81;k++)//循环使用成员函数对数独进行处理
		{
			sudok.RowTwoRem();
			sudok.ColTwoRem();
			sudok.JGTwoRem();
			sudok.SevGitsRow();
			sudok.SevGitsCol();
			sudok.RowColitsJG();
			sudok.RowTwoRecRem();
			sudok.ColTwoRecRem();
		}
		sudok.ShowSudoku("result");//输出运用成员函数赋值之后的数独,也就是输出数独解决后的结果
		sudok.Test();
		sudok.Initialization();//重新初始化!
//	}
	return 0;
}
