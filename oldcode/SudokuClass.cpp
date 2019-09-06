#include <iostream>
#include <fstream>
#include <string>
#include"SudokuClass.h"
using namespace std;

CSudoku::CSudoku()//数独类的构造函数的实现,初始化数独三维数组
{
	for(int m=0;m<10;m++)//每一层初始化值都相等,初始化,第m层的数均为m
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
	for(int m=0;m<10;m++)//每一层初始化值都相等,初始化,第m层的数均为m
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
		cin>>filename;//	ifstream infile("E:\\sudoku\\sudo1.dat",ios::in);//如果这样调用路径注意使用双反斜杠   
		infile.open(filename.c_str(),ios::in);
		infile?(cout<<"Open Success!"<<endl):cout<<"Open Error!Please try again!"<<endl;
		if(!infile)
			again=1;
	}
	for(int i=0;i<9;i++)//从文件读入数独题
		for(int j=0;j<9;j++)
			infile>>sudo[i][j][0];
	infile.close();//读完关闭文件
}
void CSudoku::ShowSudoku(const char * str)//按照一定的格式将三维数组最底层显示出来,即显示数独sudoku
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
	for(int row=0;row<9;row++)//调用格赋值函数,确定出每个空格可能的数,不可能的用零替换
		for(int col=0;col<9;col++)
			if(sudo[row][col][0]!=0)
				GridRemove(row+1,col+1);
}
void CSudoku::GridRemove(int rows,int cols)
{	/*确定格的数字后需要排除其他格有这个数字的可能性；
	调用这个函数的前提是这一竖的基数不为0;
	形参rows为这个格的行数,cols为这个格的列数*/
	int num,row,col;//row为九宫行指标，col为九宫列指标；
	num=sudo[rows-1][cols-1][0];//这一竖的基数为k，则第k层的行、列、竖、九宫都为0;
	for(int k=0;k<9;k++)
	{
		sudo[rows-1][k][num]=0;//这一行
		sudo[k][cols-1][num]=0;//这一列
		sudo[rows-1][cols-1][k+1]=0;//这一竖
	}
	switch(rows)//确定出在哪个九宫；
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
	for(int i=row;i<row+3;i++)//第k层九宫为0；
		for(int j=col;j<col+3;j++)
			sudo[i][j][num]=0;
}
void CSudoku::RowTwoRem()
{		/*(1)同一行中,两竖完全一样,且有且仅有两个不为0,
			则排除这两个不为0所在行中其他空格有这两个数的可能性
		(2)同一竖中,两行中只要是零的都完美对应,且每一行有且只有两个不为0,
			则排除这两个不为0所在竖中其他数的可能性*/
	int i,j,m,k,numb,number,q,n,b,c,s;
	for(i=0;i<9;i++)//每一行,对应(1)
		for(j=0;j<9;j++)//每一个
		{
			numb=0;//检测这一竖有几个不为0
			for(m=1;m<10;m++)
				if(sudo[i][j][m]!=0)
					numb++;
			switch(numb)
			{
			case 1://若只有一个,则唯一
				for(m=1;m<10;m++)
					if(sudo[i][j][m]!=0)
					{
						sudo[i][j][0]=m;//赋值
						GridRemove(i+1,j+1);//赋值后,排除行,列,竖,九宫中有这个数的可能
					}
					break;
			case 2://如果刚好两个不为零,则进入和后面同一行中每一竖的比较
				for(k=j+1;k<9;k++)
				{
					number=0;//检测这两竖有几个不一样
					for(m=1;m<10;m++)
						if(sudo[i][j][m]!=sudo[i][k][m])
							number++;
					if(number==0)//如果是0个不一样,则进入排除同一行中其他格有这两个数的可能性
						for(m=1;m<10;m++)//找出两个数所在位置
							if(sudo[i][j][m]!=0)
							{
								for(q=0;q<9;q++)//这一行其他数赋值为0
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
	for(i=0;i<9;i++)//每一行,对应(2)
		for(m=1;m<10;m++)//每一条
		{
			numb=0;//检测这一条有几个不为0
			for(j=0;j<9;j++)
				if(sudo[i][j][m]!=0)
					numb++;
			if(numb==1)//若只有一个,则唯一
				for(j=0;j<9;j++)
					if(sudo[i][j][m]!=0)
					{
						sudo[i][j][0]=m;
						GridRemove(i+1,j+1);//赋值后,排除行,列,竖,九宫中有这个数的可能
					}
			if(numb==2)
				for(k=m+1;k<10;k++)//进入和上面一条中每一个的比较
				{
					number=1;
					for(j=0;j<9;j++)//看看是否对应不为0
					{
						if(sudo[i][j][m]==m&&sudo[i][j][k]==0||sudo[i][j][m]==0&&sudo[i][j][k]==k)
						{
							number=0;break;
						}
					}
					if(number==1)//是对应的话进入排除
						for(j=0;j<9;j++)//找出这两个数
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
{	/*(1)同一列中,两竖完全一样,且有且仅有两个不为0,
		则排除这两个不为0的数所在列中其他空格有这两个数的可能性
		(2)同一竖中,两列中只要是零的都完美对应,且每一列有且只有两个不为0,
		则排除这两个不为0所在竖中其他数的可能性*/
	int i,j,m,k,numb,number,q,n,b,c,s;
	for(j=0;j<9;j++)//每一列,对应(1)
		for(i=0;i<9;i++)//每一个
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
	for(j=0;j<9;j++)//对应(2)
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
{	/*(1)同一九宫中,两竖完全一样,且有且仅有两个不为0,
		则排除这两个不为0所在九宫中其他空格有这两个数的可能性
		(2)同一竖中,两九宫中只要是零的都完美对应,且九宫中有且只有两个不为0,
		则排除这两个不为0所在竖中其他数的可能性*/
	int i,j,m,k,numb,number,row,col,h,s,x,a,b,c,d,n;
	for(row=0;row<9;row+=3)//对应(1)
		for(col=0;col<9;col+=3)
			for(i=row;i<row+3;i++)//每个九宫
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
	for(row=0;row<9;row+=3)//对应(2)
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
{	/*(1)在某一九宫格中，当所有可能出现某个数字的单元格都位于同一行时，
		就可以把这个数字从该行的其他单元格的候选数中删除；*/
	int i,j,m,k,num,number,arr[9],g,row,col;
	for(row=0;row<9;row+=3)//对应(1)
		for(col=0;col<9;col+=3)//每一个九宫
			for(m=1;m<10;m++)//每一层
			{
				for(k=0;k<9;k++)//这个数组在每一层的每一个九宫开始前都需要初始化
					arr[k]=0;
				for(i=row;i<row+3;i++)//判断这个九宫三行中有多少行在这一层的每个格都为0
				{
					num=0;
					for(j=col;j<col+3;j++)//每一行都进行列判断
						if(sudo[i][j][m]==m)
						{
							num++;
							break;
						}
					number=0;
					if(num==0)//都为0,则计数
						number++;//存放有几行都是0
					else
						arr[i]=1;//记录是哪一行有不为0
				}
				if(number==2)
					for(k=0;k<9;k++)//先找出哪一行是有不为0的
						if(arr[k]==1)
							for(g=0;g<9;g++)//这一层这一行中其他空格不可能有这个数的可能(每一层对应一个数)
								if(g!=col&&g!=col+1&&g!=col+2)
									sudo[k][g][m]=0;
			}

}
void CSudoku::SevGitsCol()//Several grid in the same columns
{/*(2)在某一九宫格中，当所有可能出现某个数字的单元格都位于同一列时，
			就可以把这个数字从该列的其他单元格的候选数中删除；*/
	int i,j,m,k,num,number,arr[9],g,row,col;
	for(row=0;row<9;row+=3)//对应(2)
		for(col=0;col<9;col+=3)//每个九宫
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
{/*(3)在某一行（列）中，当所有可能出现某个数字的单元格都位于同一九宫格中时，
			就可以把这个数字从该九宫格的其他单元格的候选数中删除。*/
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
						GridRemove(i+1,j+1);//赋值后,排除行,列,竖,九宫中有这个数的可能
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
	for(m=1;m<10;m++)//列
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
						GridRemove(i+1,j+1);//赋值后,排除行,列,竖,九宫中有这个数的可能
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
void CSudoku::RowTwoRecRem()//如果一个数字在某两行中能填入的位置正好在同样的两列中，则这两列的其他的单元格中将不可能再出现这个数字；
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
void CSudoku::ColTwoRecRem()//    如果一个数字在某两列中能填入的位置正好在同样的两行中，则这两行的其他的单元格中将不可能再出现这个数字。
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
