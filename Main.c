#include "Header.h"
#include "Polynomial.h"
#include "IO.h"
#include "Calculate.h"

/*
要求：1）实现一个可以交互控制台风格的界面；
	  2）程序界面显示一个菜单，选择操作序号1-多项式输入；2-多项式加（+）；3-多项式减（-）；3-多项式乘（*）；4-多项式输出；0-退出；以调用相应函数完成具体相应操作；
3）输出格式按照次幂的大小从高到低输出多项式；
4）模块化设计，程序结构清晰，注释清楚；
5）编写详细的设计与实现文档。
*/
void printMenu();
void Input();
void Add();
void Sub();
void Mul();
void Output();
void printInputHint();
void wait();

int N = 0;
List lists[1024];

int main(void)
{

	char str[60];
	int op, i;
	do
	{
		printf("==============================\n\       二元多项式计算器\n==============================\n\n");
		printf(" * 当前已储存的多项式数量：%d\n\n", N); 
		printMenu();
		printf("\n请输入所要进行操作的序号：\n");
		printInputHint();
		scanf("%s", str);
		op = str[0] - '0';
		switch (op)
		{
			case 1:
				Input(); break;
			case 2:
				Add(); break;
			case 3:
				Sub(); break;
			case 4:
				Mul();break;
			case 5:
				Output(); break;
			case 0:
				for (i = 0; i < N; i++)
				{
					freeAll(lists[i]);
				}
				exit(0);
			default:
				printf("输入错误。\n");
				break;
		}
		wait();
		system("cls");
	} while (TRUE);
}

void printMenu()
{
	printf("    [1] 多项式输入\n");
	printf("    [2] 多项式加法\n");
	printf("    [3] 多项式减法\n");
	printf("    [4] 多项式乘法\n");
	printf("    [5] 输出所有已储存的多项式\n");
	printf("    [0] 退出\n");
}

void Input()
{
	printf("请输入一个多项式，每一项格式为(+/-)a*x^p*y^q。其中a, ^p, ^q, *, x, y均可省略。\n");
	printInputHint();
	char m[60];
	scanf("%s", m);
	List l = newPolynomial();
	processPolynomial(&l, m);
	lists[N] = l;
	printf("已成功输入多项式！该多项式编号为%d。\n", N);
	printf(" * P[%d] = %s\n", N, printResult(lists[N]));
	N++;
}

void Add()
{
	int a, b;
	printf("请输入要相加的两个多项式编号。两个编号之间用空格隔开。\n");
	printInputHint();
	List l = newPolynomial();
	scanf("%d%d", &a, &b);
	if (a >= N || a < 0 || b >= N || b < 0)
	{
		printf("无效输入。\n");
		return;
	}
	l = add(l, lists[a]);
	l = add(l, lists[b]);
	lists[N] = l;
	printf("操作成功！相加得到的多项式编号为%d。\n", N);
	printf(" * P[%d] = %s\n", N, printResult(lists[N]));
	N++;
	
}

void Sub()
{
	int a, b;
	printf("请输入要相减的两个多项式编号。两个编号之间用空格隔开。\n");
	printInputHint();
	List l = newPolynomial();
	scanf("%d%d", &a, &b);
	if (a >= N || a < 0 || b >= N || b < 0)
	{
		printf("无效输入。\n");
		return;
	}
	l = add(l, lists[a]);
	l = sub(l, lists[b]);
	lists[N] = l;
	printf("操作成功！相减得到的多项式编号为%d。\n", N);
	printf(" * P[%d] = %s\n", N, printResult(lists[N]));
	N++;
}

void Output()
{
	int a, i;
	if (N == 0)
	{
		printf("暂未输入。\n");
		return;
	}
	for (i = 0; i < N; i++)
	{
		printf(" * P[%d] = %s\n", i, printResult(lists[i]));
	}
}

void printInputHint()
{
	printf(">>>> ");
}

void wait()
{
	printf("\n");
	system("pause");
} 

void Mul()
{
	int a, b;
	printf("请输入要相乘的两个多项式编号。两个编号之间用空格隔开。\n");
	printInputHint();
	List l = newPolynomial();
	scanf("%d%d", &a, &b);
	if (a >= N || a < 0 || b >= N || b < 0)
	{
		printf("无效输入。\n");
		return;
	}
	l = add(l, lists[a]);
	l = multiply(l, lists[b]);
	lists[N] = l;
	printf("操作成功！相乘得到的多项式编号为%d。\n", N);
	printf(" * P[%d] = %s\n", N, printResult(lists[N]));
	N++;
} 
