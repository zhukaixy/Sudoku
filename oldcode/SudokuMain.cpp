#include"SudokuClass.h"
int main(void)
{
	
	CSudoku sudok;//����һ����������sudok
//	while(1)
//	{
		sudok.SetByFile();
		sudok.ShowSudoku("sudoku");
		sudok.FirstRemove();
		for(int k=0;k<81;k++)//ѭ��ʹ�ó�Ա�������������д���
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
		sudok.ShowSudoku("result");//������ó�Ա������ֵ֮�������,Ҳ����������������Ľ��
		sudok.Test();
		sudok.Initialization();//���³�ʼ��!
//	}
	return 0;
}
