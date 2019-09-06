#ifndef __SUDOKU_CLASS_H
#define __SUDOKU_CLASS_H

//#include<fstream>
//#include<iostream>
//#include<string>
//using namespace std;

class CSudoku
{
private:
	int sudo[9][9][10];//��ײ��������������Ŀ,֮�ϵľŲ�������Ÿ�������ܵ���,����ո񲻿��ܵ������������
	bool result;
public:
	CSudoku();
	~CSudoku(){};
	bool Test();
	void Initialization();//Initialization
	void SetByFile();//��dat�ļ���������
	void ShowSudoku(const char *pstr);//����һ���ĸ�ʽ����ά������ײ���ʾ����,����ʾ����
	void FirstRemove();
	void GridRemove(int rows,int cols);//ȷ��������ֺ���Ҫ�ų���������������ֵĿ�����,ǰ��Ϊ�������ֲ�Ϊ0
	void RowTwoRem();//Row two remove�ų�
	void ColTwoRem();//Columns two remove�ų�
	void JGTwoRem();//�Ź��ų�
	void SevGitsRow();//Several Grid in the same row
	void SevGitsCol();//Several Grid in the same columns
	void RowColitsJG();//Row and Columns in the same jiugong
	void RowTwoRecRem();//Rectangle
	void ColTwoRecRem(); //Columns two rectangle remove
};

#endif//__SUDOKU_CLASS_H
