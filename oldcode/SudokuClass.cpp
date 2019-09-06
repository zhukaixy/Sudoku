#include <iostream>
#include <fstream>
#include <string>
#include"SudokuClass.h"
using namespace std;

CSudoku::CSudoku()//������Ĺ��캯����ʵ��,��ʼ��������ά����
{
	for(int m=0;m<10;m++)//ÿһ���ʼ��ֵ�����,��ʼ��,��m�������Ϊm
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				sudo[i][j][m]=m;
	result=true;
}
bool CSudoku::Test()
{
	result=true;	//bool result;
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
			if(sudo[i][j][0]==0)
			{
				result=false;
				break;
			}
		if(result==false)
			break;
	}
	for(int a=0;a<9;a++)
		for(int b=0;b<9;b++)
		{
			for(int k=b+1;k<9;k++)
				if(sudo[a][b][0]==sudo[a][k][0])
					result=false;
			for(int k=a+1;k<9;k++)
				if(sudo[a][b][0]==sudo[k][b][0])
					result=false;
		}
	for(int row=0;row<9;row+=3)
		for(int col=0;col<9;col+=3)
			for(int i=row;i<row+3;i++)
				for(int j=col;j<col+3;j++)
				{
					for(int g=row;g<row+3;g++)
						for(int h=col;h<col+3;h++)
							if((sudo[i][j][0]==sudo[g][h][0])&&(g!=i||h!=j))
							{
								result=false;
								break;
							}
				}
	if(result==true)
		cout<<"The answer is right!"<<endl;
	else
		cout<<"The answer is wrong!Please try again!"<<endl;
	return result;
}
void CSudoku::Initialization()
{
	for(int m=0;m<10;m++)//ÿһ���ʼ��ֵ�����,��ʼ��,��m�������Ϊm
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				sudo[i][j][m]=m;
}
void CSudoku::SetByFile()
{
	ifstream infile;
	string filename;
	int again=1;
	while(again)
	{
		again=0;
		cout<<"Please enter the address of the sudoku,such as: /home/user/sudo.dat"<<endl;
		cout<<"Enter the address:";
		cin>>filename;//	ifstream infile("E:\\sudoku\\sudo1.dat",ios::in);//�����������·��ע��ʹ��˫��б��   
		infile.open(filename.c_str(),ios::in);
		infile?(cout<<"Open Success!"<<endl):cout<<"Open Error!Please try again!"<<endl;
		if(!infile)
			again=1;
	}
	for(int i=0;i<9;i++)//���ļ�����������
		for(int j=0;j<9;j++)
			infile>>sudo[i][j][0];
	infile.close();//����ر��ļ�
}
void CSudoku::ShowSudoku(const char * str)//����һ���ĸ�ʽ����ά������ײ���ʾ����,����ʾ����sudoku
{
	cout<<"The "<<str<<" is:"<<endl;
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			cout<<sudo[i][j][0]<<" ";
			if(j==2||j==5)
				cout<<" ";
		}
		cout<<endl;
		if(i==2||i==5)
			cout<<endl;
	}
}
void CSudoku::FirstRemove()
{
	for(int row=0;row<9;row++)//���ø�ֵ����,ȷ����ÿ���ո���ܵ���,�����ܵ������滻
		for(int col=0;col<9;col++)
			if(sudo[row][col][0]!=0)
				GridRemove(row+1,col+1);
}
void CSudoku::GridRemove(int rows,int cols)
{	/*ȷ��������ֺ���Ҫ�ų���������������ֵĿ����ԣ�
	�������������ǰ������һ���Ļ�����Ϊ0;
	�β�rowsΪ����������,colsΪ����������*/
	int num,row,col;//rowΪ�Ź���ָ�꣬colΪ�Ź���ָ�ꣻ
	num=sudo[rows-1][cols-1][0];//��һ���Ļ���Ϊk�����k����С��С������Ź���Ϊ0;
	for(int k=0;k<9;k++)
	{
		sudo[rows-1][k][num]=0;//��һ��
		sudo[k][cols-1][num]=0;//��һ��
		sudo[rows-1][cols-1][k+1]=0;//��һ��
	}
	switch(rows)//ȷ�������ĸ��Ź���
	{
	case 1:
	case 2:
	case 3:row=0;break;
	case 4:
	case 5:
	case 6:row=3;break;
	case 7:
	case 8:
	case 9:row=6;break;
	default :break;
	}
	switch(cols)
	{
	case 1:
	case 2:
	case 3:col=0;break;
	case 4:
	case 5:
	case 6:col=3;break;
	case 7:
	case 8:
	case 9:col=6;break;
	default :break;
	}
	for(int i=row;i<row+3;i++)//��k��Ź�Ϊ0��
		for(int j=col;j<col+3;j++)
			sudo[i][j][num]=0;
}
void CSudoku::RowTwoRem()
{		/*(1)ͬһ����,������ȫһ��,�����ҽ���������Ϊ0,
			���ų���������Ϊ0�������������ո������������Ŀ�����
		(2)ͬһ����,������ֻҪ����Ķ�������Ӧ,��ÿһ������ֻ��������Ϊ0,
			���ų���������Ϊ0���������������Ŀ�����*/
	int i,j,m,k,numb,number,q,n,b,c,s;
	for(i=0;i<9;i++)//ÿһ��,��Ӧ(1)
		for(j=0;j<9;j++)//ÿһ��
		{
			numb=0;//�����һ���м�����Ϊ0
			for(m=1;m<10;m++)
				if(sudo[i][j][m]!=0)
					numb++;
			switch(numb)
			{
			case 1://��ֻ��һ��,��Ψһ
				for(m=1;m<10;m++)
					if(sudo[i][j][m]!=0)
					{
						sudo[i][j][0]=m;//��ֵ
						GridRemove(i+1,j+1);//��ֵ��,�ų���,��,��,�Ź�����������Ŀ���
					}
					break;
			case 2://����պ�������Ϊ��,�����ͺ���ͬһ����ÿһ���ıȽ�
				for(k=j+1;k<9;k++)
				{
					number=0;//����������м�����һ��
					for(m=1;m<10;m++)
						if(sudo[i][j][m]!=sudo[i][k][m])
							number++;
					if(number==0)//�����0����һ��,������ų�ͬһ���������������������Ŀ�����
						for(m=1;m<10;m++)//�ҳ�����������λ��
							if(sudo[i][j][m]!=0)
							{
								for(q=0;q<9;q++)//��һ����������ֵΪ0
									sudo[i][q][m]=0;
								sudo[i][j][m]=m;
								sudo[i][k][m]=m;
							}
				}
			case 3:
				for(k=j+1;k<9;k++)
				{
					n=0;
					for(m=1;m<10;m++)
						if(sudo[i][k][m]!=0)
							n++;
					if(n==3 || n==2)
					{
						b=0;
						for(m=1;m<10;m++)
							if(0==sudo[i][j][m]&&0==sudo[i][k][m])
								b++;
						if(6==b)
						{
							for(int r=k+1;r<9;r++)
							{
								s=0;
								for(m=1;m<10;m++)
									if(sudo[i][r][m]!=0)
										s++;
								if(s==3||s==2)
								{
									c=0;
									for(m=1;m<10;m++)
										if(0==sudo[i][j][m]&&0==sudo[i][k][m]&&0==sudo[i][r][m])
											c++;
									if(6==c)
										for(m=1;m<10;m++)
										if(0!=sudo[i][j][m] || 0!=sudo[i][k][m] || 0!=sudo[i][r][m])
											for(q=0;q<9;q++)
												if(q!=j && q!=k && q!=r)
													sudo[i][q][m]=0;
								}
							}
						}
					}
				}
				break;
			default :break;

			}

		}
	for(i=0;i<9;i++)//ÿһ��,��Ӧ(2)
		for(m=1;m<10;m++)//ÿһ��
		{
			numb=0;//�����һ���м�����Ϊ0
			for(j=0;j<9;j++)
				if(sudo[i][j][m]!=0)
					numb++;
			if(numb==1)//��ֻ��һ��,��Ψһ
				for(j=0;j<9;j++)
					if(sudo[i][j][m]!=0)
					{
						sudo[i][j][0]=m;
						GridRemove(i+1,j+1);//��ֵ��,�ų���,��,��,�Ź�����������Ŀ���
					}
			if(numb==2)
				for(k=m+1;k<10;k++)//���������һ����ÿһ���ıȽ�
				{
					number=1;
					for(j=0;j<9;j++)//�����Ƿ��Ӧ��Ϊ0
					{
						if(sudo[i][j][m]==m&&sudo[i][j][k]==0||sudo[i][j][m]==0&&sudo[i][j][k]==k)
						{
							number=0;break;
						}
					}
					if(number==1)//�Ƕ�Ӧ�Ļ������ų�
						for(j=0;j<9;j++)//�ҳ���������
							if(sudo[i][j][m]!=0)
							{
								for(q=1;q<10;q++)
									sudo[i][j][q]=0;
								sudo[i][j][m]=m;
								sudo[i][j][k]=k;
							}
				}
		}
}
void CSudoku::ColTwoRem()
{	/*(1)ͬһ����,������ȫһ��,�����ҽ���������Ϊ0,
		���ų���������Ϊ0�����������������ո������������Ŀ�����
		(2)ͬһ����,������ֻҪ����Ķ�������Ӧ,��ÿһ������ֻ��������Ϊ0,
		���ų���������Ϊ0���������������Ŀ�����*/
	int i,j,m,k,numb,number,q,n,b,c,s;
	for(j=0;j<9;j++)//ÿһ��,��Ӧ(1)
		for(i=0;i<9;i++)//ÿһ��
		{
			numb=0;
			for(m=1;m<10;m++)
				if(sudo[i][j][m]!=0)
					numb++;
			switch(numb)
			{
			case 2:
				for(k=i+1;k<9;k++)
				{
					number=0;
					for(m=1;m<10;m++)
						if(sudo[i][j][m]!=sudo[k][j][m])
							number++;
					if(number==0)
						for(m=1;m<10;m++)
							if(sudo[i][j][m]!=0)
							{
								for(q=0;q<9;q++)
									sudo[q][j][m]=0;
								sudo[i][j][m]=m;
								sudo[k][j][m]=m;
							}
				}
			case 3:
			for(k=i+1;k<9;k++)
				{
					n=0;
					for(m=1;m<10;m++)
						if(sudo[k][j][m]!=0)
							n++;
					if(n==3||2==n)
					{
						b=0;
						for(m=1;m<10;m++)
							if(0==sudo[i][j][m]&&0==sudo[k][j][m])
								b++;
						if(6==b)
						{
							for(int r=k+1;r<9;r++)
							{
								s=0;
								for(m=1;m<10;m++)
									if(sudo[r][j][m]!=0)
										s++;
								if(s==3||2==s)
								{
									c=0;
									for(m=1;m<10;m++)
										if(0==sudo[i][j][m]&&0==sudo[k][j][m]&&0==sudo[r][j][m])
											c++;
									if(6==c)
										for(m=1;m<10;m++)
										if(0!=sudo[i][j][m] || 0!=sudo[k][j][m] || 0!=sudo[r][j][m])
											for(q=0;q<9;q++)
												if(q!=i && q!=k && q!=r)
													sudo[q][j][m]=0;
								}
							}
						}
					}
				}
				break;
			default :break;
			}

		}
	for(j=0;j<9;j++)//��Ӧ(2)
		for(m=1;m<10;m++)
		{
			numb=0;
			for(i=0;i<9;i++)
				if(sudo[i][j][m]!=0)
					numb++;
			if(numb==1)
				for(i=0;i<9;i++)
					if(sudo[i][j][m]!=0)
					{
						sudo[i][j][0]=sudo[i][j][m];
						GridRemove(i+1,j+1);
					}
			if(numb==2)
				for(k=m+1;k<10;k++)
				{
					number=1;
					for(i=0;i<9;i++)
					{
						if(sudo[i][j][m]==m&&sudo[i][j][k]==0||sudo[i][j][m]==0&&sudo[i][j][k]==k)
							{
								number=0;break;
							}
					}
					if(number==1)
						for(i=0;i<9;i++)
							if(sudo[i][j][m]!=0)
							{
								for(q=1;q<10;q++)
									sudo[i][j][q]=0;
								sudo[i][j][m]=m;
								sudo[i][j][k]=k;
							}
				}
		}
}
void CSudoku::JGTwoRem()
{	/*(1)ͬһ�Ź���,������ȫһ��,�����ҽ���������Ϊ0,
		���ų���������Ϊ0���ھŹ��������ո������������Ŀ�����
		(2)ͬһ����,���Ź���ֻҪ����Ķ�������Ӧ,�ҾŹ�������ֻ��������Ϊ0,
		���ų���������Ϊ0���������������Ŀ�����*/
	int i,j,m,k,numb,number,row,col,h,s,x,a,b,c,d,n;
	for(row=0;row<9;row+=3)//��Ӧ(1)
		for(col=0;col<9;col+=3)
			for(i=row;i<row+3;i++)//ÿ���Ź�
				for(j=col;j<col+3;j++)
				{
					numb=0;
					for(m=1;m<10;m++)
						if(sudo[i][j][m]!=0)
							numb++;
					switch(numb)
					{
					case 2:
						for(k=row;k<row+3;k++)
							for(h=col;h<col+3;h++)
							{
								if(k>=i)
									if((i==k)&&(h<=j));
									else
									{
										number=0;
										for(m=1;m<10;m++)
											if(sudo[i][j][m]!=sudo[k][h][m])
												number++;
										if(number==0)
											for(m=1;m<10;m++)
												if(sudo[i][j][m]!=0)
												{
													for(s=row;s<row+3;s++)
														for(x=col;x<col+3;x++)
															sudo[s][x][m]=0;
													sudo[i][j][m]=m;
													sudo[k][h][m]=m;
												}
									}
							}
					case 3:
						for(k=row;k<row+3;k++)
							for(h=col;h<col+3;h++)
								if(k>i||(k==i&&h>j))
								{
									n=0;
									for(m=1;m<10;m++)
										if(sudo[k][h][m]!=0)
											n++;
									if(n==3 || n==2)
									{
										b=0;
										for(m=1;m<10;m++)
											if(0==sudo[i][j][m]&&0==sudo[k][h][m])
												b++;
										if(6==b)
										{
											for(a=row;a<row+3;a++)
												for(b=col;b<col+3;b++)
													if(a>k||(a==k&&b>h))
													{
														s=0;
														for(m=1;m<10;m++)
															if(sudo[a][b][m]!=0)
																s++;
														if(s==3||s==2)
														{
															c=0;
															for(m=1;m<10;m++)
																if(0==sudo[i][j][m]&&0==sudo[k][h][m]&&0==sudo[a][b][m])
																	c++;
															if(6==c)
																for(m=1;m<10;m++)
																	if(0!=sudo[i][j][m] || 0!=sudo[k][h][m] || 0!=sudo[a][b][m])
																		for(c=row;c<row+3;c++)
																			for(d=col;d<col+3;d++)
																				if((c!=i||d!=j)&&(c!=k||d!=h)&&(c!=a||d!=b))
																					sudo[c][d][m]=0;
														}
													}
										}
									}
								}
						break;
					default :break;
					}
				}
	for(row=0;row<9;row+=3)//��Ӧ(2)
		for(col=0;col<9;col+=3)
			for(m=1;m<10;m++)
				{
					numb=0;
					for(i=row;i<row+3;i++)
						for(j=col;j<col+3;j++)
							if(sudo[i][j][m]!=0)
								numb++;
					if(numb==1)
					for(i=row;i<row+3;i++)
						for(j=col;j<col+3;j++)
							if(sudo[i][j][m]!=0)
							{
								sudo[i][j][0]=m;
								GridRemove(i+1,j+1);
							}
					if(numb==2)
						for(k=m+1;k<10;k++)
						{
							number=1;
							for(i=row;i<row+3;i++)
							{
								for(j=col;j<col+3;j++)
								{
									if(((sudo[i][j][m]==0)&&(sudo[i][j][k]==k))||((sudo[i][j][m]==m)&&(sudo[i][j][k]==0)))
									{
										number=0;
										break;
									}
								}
								if(number==0)
									break;
							}
							if(number==1)
							{
								for(i=row;i<row+3;i++)
									for(j=col;j<col+3;j++)
										if(sudo[i][j][m]==m)
										{
											for(h=1;h<10;h++)
												sudo[i][j][h]=0;
											sudo[i][j][m]=m;
											sudo[i][j][k]=k;
										}
							}
						}
			}
}
void CSudoku::SevGitsRow()//Several grid in the same row
{	/*(1)��ĳһ�Ź����У������п��ܳ���ĳ�����ֵĵ�Ԫ��λ��ͬһ��ʱ��
		�Ϳ��԰�������ִӸ��е�������Ԫ��ĺ�ѡ����ɾ����*/
	int i,j,m,k,num,number,arr[9],g,row,col;
	for(row=0;row<9;row+=3)//��Ӧ(1)
		for(col=0;col<9;col+=3)//ÿһ���Ź�
			for(m=1;m<10;m++)//ÿһ��
			{
				for(k=0;k<9;k++)//���������ÿһ���ÿһ���Ź���ʼǰ����Ҫ��ʼ��
					arr[k]=0;
				for(i=row;i<row+3;i++)//�ж�����Ź��������ж���������һ���ÿ����Ϊ0
				{
					num=0;
					for(j=col;j<col+3;j++)//ÿһ�ж��������ж�
						if(sudo[i][j][m]==m)
						{
							num++;
							break;
						}
					number=0;
					if(num==0)//��Ϊ0,�����
						number++;//����м��ж���0
					else
						arr[i]=1;//��¼����һ���в�Ϊ0
				}
				if(number==2)
					for(k=0;k<9;k++)//���ҳ���һ�����в�Ϊ0��
						if(arr[k]==1)
							for(g=0;g<9;g++)//��һ����һ���������ո񲻿�����������Ŀ���(ÿһ���Ӧһ����)
								if(g!=col&&g!=col+1&&g!=col+2)
									sudo[k][g][m]=0;
			}

}
void CSudoku::SevGitsCol()//Several grid in the same columns
{/*(2)��ĳһ�Ź����У������п��ܳ���ĳ�����ֵĵ�Ԫ��λ��ͬһ��ʱ��
			�Ϳ��԰�������ִӸ��е�������Ԫ��ĺ�ѡ����ɾ����*/
	int i,j,m,k,num,number,arr[9],g,row,col;
	for(row=0;row<9;row+=3)//��Ӧ(2)
		for(col=0;col<9;col+=3)//ÿ���Ź�
			for(m=1;m<10;m++)
			{
				for(j=col;j<col+3;j++)
				{
					for(k=0;k<9;k++)
						arr[k]=0;
					num=0;
					for(i=row;i<row+3;i++)
						if(sudo[i][j][m]==m)
						{
							num++;
							break;
						}
					number=0;
					if(num==0)
						number++;
					else
						arr[i]=1;
				}
				if(number==2)
					for(k=0;k<9;k++)
						if(arr[k]!=0)
							for(g=0;g<9;g++)
								if(g!=col&&g!=col+1&&g!=col+2)
									sudo[g][k][m]=0;
			}
}
void CSudoku::RowColitsJG()//row or columns in the same jiugong
{/*(3)��ĳһ�У��У��У������п��ܳ���ĳ�����ֵĵ�Ԫ��λ��ͬһ�Ź�����ʱ��
			�Ϳ��԰�������ִӸþŹ����������Ԫ��ĺ�ѡ����ɾ����*/
	int i,j,m,k,num,arr[3],row,col,g,h;
	for(m=1;m<10;m++)
		for(i=0;i<9;i++)
		{
			switch(i)
			{
			case 0:
			case 1:
			case 2:row=0;break;
			case 3:
			case 4:
			case 5:row=3;break;
			case 6:
			case 7:
			case 8:row=6;break;
			default:break;
			}
			num=0;
			for(j=0;j<9;j++)
				if(sudo[i][j][m]==m)
					num++;
			if(num!=0&&num<=3)
			switch(num)
			{
			case 1:for(j=0;j<9;j++)
					if(sudo[i][j][m]!=0)
					{
						sudo[i][j][0]=m;
						GridRemove(i+1,j+1);//��ֵ��,�ų���,��,��,�Ź�����������Ŀ���
					}
					break;
			case 2:
				/*for(k=0;k<3;k++)
					   arr[k]=0;
					for(k=0;k<9;k++)
						if(sudo[i][k][m]==m)
							switch(k)
							{
							case 1:
							case 2:
							case 3:arr[0]++;break;
							case 4:
							case 5:
							case 6:arr[1]++;break;
							case 7:
							case 8:
							case 9:arr[2]++;break;
							}
						for(k=0;k<3;k++)
							if(2==arr[k])
								for(g=row;g<row+3;g++)
									if(g!=i)
										for(h=3*k;h<3*k+3;h++)
											sudo[g][h][m]=0;
					break;*/
			case 3:for(k=0;k<3;k++)
					   arr[k]=0;
					for(k=0;k<9;k++)
						if(sudo[i][k][m]==m)
							switch(k)
							{
							case 0:
							case 1:
							case 2:arr[0]++;break;
							case 3:
							case 4:
							case 5:arr[1]++;break;
							case 6:
							case 7:
							case 8:arr[2]++;break;
								default:break;
							}
						for(k=0;k<3;k++)
							if(arr[k]==3||((2==num)&&(2==arr[k])))
								for(g=row;g<row+3;g++)
									if(g!=i)
										for(h=3*k;h<3*k+3;h++)
											sudo[g][h][m]=0;
					break;
			default :break;
			}
		}
	for(m=1;m<10;m++)//��
		for(j=0;j<9;j++)
		{
			switch(j)
			{
			case 0:
			case 1:
			case 2:col=0;break;
			case 3:
			case 4:
			case 5:col=3;break;
			case 6:
			case 7:
			case 8:col=6;break;
				default:break;
			}
			num=0;
			for(i=0;i<9;i++)
				if(sudo[i][j][m]==m)
					num++;
			if(num!=0&&num<=3)
			switch(num)
			{
			case 1:for(i=0;i<9;i++)
					if(sudo[i][j][m]!=0)
					{
						sudo[i][j][0]=m;
						GridRemove(i+1,j+1);//��ֵ��,�ų���,��,��,�Ź�����������Ŀ���
					}
					break;
			case 2:
				/*for(k=0;k<3;k++)
					   arr[k]=0;
					for(k=0;k<9;k++)
						if(sudo[i][k][m]==m)
							switch(k)
							{
							case 1:
							case 2:
							case 3:arr[0]++;break;
							case 4:
							case 5:
							case 6:arr[1]++;break;
							case 7:
							case 8:
							case 9:arr[2]++;break;
							}
						for(k=0;k<3;k++)
							if(arr[k]==2)
								for(g=col;g<col+3;g++)
									if(g!=j)
										for(h=3*k;h<3*k+3;h++)
											sudo[h][g][m]=0;
					break;*/
			case 3:for(k=0;k<3;k++)
					   arr[k]=0;
					for(k=0;k<9;k++)
						if(sudo[k][j][m]==m)
							switch(k)
							{
							case 0:
							case 1:
							case 2:arr[0]++;break;
							case 3:
							case 4:
							case 5:arr[1]++;break;
							case 6:
							case 7:
							case 8:arr[2]++;break;
								default:break;
							}
						for(k=0;k<3;k++)
							if(arr[k]==3||2==num&&2==arr[k])
								for(g=col;g<col+3;g++)
									if(g!=j)
										for(h=3*k;h<3*k+3;h++)
											sudo[h][g][m]=0;
					break;
			default :break;
			}
		}
}
void CSudoku::RowTwoRecRem()//���һ��������ĳ�������������λ��������ͬ���������У��������е������ĵ�Ԫ���н��������ٳ���������֣�
{
	int i,j,m,k,num,number,q,n;
	for(m=1;m<10;m++)
		for(i=0;i<9;i++)
		{
			num=0;
			for(j=0;j<9;j++)
				if(sudo[i][j][m]!=0)
					num++;
			switch(num)
			{
			case 2:
				for(k=i+1;k<9;k++)
				{
					number=0;
					for(j=0;j<9;j++)
						if(sudo[i][j][m]!=sudo[k][j][m])
							number++;
					if(number==0)
					{
						for(j=0;j<9;j++)
						{
							if(sudo[i][j][m]!=0)
							{
								for(q=0;q<9;q++)
									sudo[q][j][m]=0;
							sudo[i][j][m]=m;
							sudo[k][j][m]=m;
							}
						}
					}
				}
				break;
			case 3:
				for(k=i+1;k<9;k++)
				{
					number=0;
					for(j=0;j<9;j++)
						if(sudo[i][j][m]!=sudo[k][j][m])
							number++;
					if(number==0)
					{
						for(int r=k+1;r<9;r++)
						{
							n=0;
							for(j=0;j<9;j++)
								if(sudo[i][j][m]!=sudo[r][j][m])
									n++;
							if(n==0)
								for(j=0;j<9;j++)
								{
									if(sudo[i][j][m]!=0)
									{
										for(q=0;q<9;q++)
											sudo[q][j][m]=0;
									sudo[i][j][m]=m;
									sudo[k][j][m]=m;
									sudo[r][j][m]=m;
									}
								}
						}
						
					}
				}
				break;
			default :break;
			}
		}
}
void CSudoku::ColTwoRecRem()//    ���һ��������ĳ�������������λ��������ͬ���������У��������е������ĵ�Ԫ���н��������ٳ���������֡�
{
	int i,j,m,k,num,number,q,n;
	for(m=1;m<10;m++)
		for(j=0;j<9;j++)
		{
			num=0;
			for(i=0;i<9;i++)
				if(sudo[i][j][m]!=0)
					num++;
			if(num==2)
				for(k=j+1;k<9;k++)
				{
					number=0;
					for(i=0;i<9;i++)
						if(sudo[i][j][m]!=sudo[i][k][m])
							number++;
					if(number==0)
					{
						for(i=0;i<9;i++)
						{
							if(sudo[i][j][m]!=0)
							{
								for(q=0;q<9;q++)
									sudo[i][q][m]=0;
							sudo[i][j][m]=m;
							sudo[i][k][m]=m;
							}
						}
					}
				}
			if(3==num)
			{
				for(k=j+1;k<9;k++)
					{
						number=0;
						for(i=0;i<9;i++)
							if(sudo[i][j][m]!=sudo[i][k][m])
								number++;
						if(number==0)
						{
							for(int r=k+1;r<9;r++)
							{
								n=0;
								for(i=0;i<9;i++)
									if(sudo[i][j][m]!=sudo[i][r][m])
										n++;
								if(n==0)
								{
									for(i=0;i<9;i++)
									{
										if(sudo[i][j][m]!=0)
										{
											for(q=0;q<9;q++)
												sudo[i][q][m]=0;
											sudo[i][j][m]=m;
											sudo[i][k][m]=m;
											sudo[i][r][m]=m;
										}
									}
								}
							}
						}
					}

			}
		}
}
