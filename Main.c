#include "Header.h"
#include "Polynomial.h"
#include "IO.h"
#include "Calculate.h"

/*
Ҫ��1��ʵ��һ�����Խ�������̨���Ľ��棻
	  2�����������ʾһ���˵���ѡ��������1-����ʽ���룻2-����ʽ�ӣ�+����3-����ʽ����-����3-����ʽ�ˣ�*����4-����ʽ�����0-�˳����Ե�����Ӧ������ɾ�����Ӧ������
3�������ʽ���մ��ݵĴ�С�Ӹߵ����������ʽ��
4��ģ�黯��ƣ�����ṹ������ע�������
5����д��ϸ�������ʵ���ĵ���
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
		printf("==============================\n\       ��Ԫ����ʽ������\n==============================\n\n");
		printf(" * ��ǰ�Ѵ���Ķ���ʽ������%d\n\n", N); 
		printMenu();
		printf("\n��������Ҫ���в�������ţ�\n");
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
				printf("�������\n");
				break;
		}
		wait();
		system("cls");
	} while (TRUE);
}

void printMenu()
{
	printf("    [1] ����ʽ����\n");
	printf("    [2] ����ʽ�ӷ�\n");
	printf("    [3] ����ʽ����\n");
	printf("    [4] ����ʽ�˷�\n");
	printf("    [5] ��������Ѵ���Ķ���ʽ\n");
	printf("    [0] �˳�\n");
}

void Input()
{
	printf("������һ������ʽ��ÿһ���ʽΪ(+/-)a*x^p*y^q������a, ^p, ^q, *, x, y����ʡ�ԡ�\n");
	printInputHint();
	char m[60];
	scanf("%s", m);
	List l = newPolynomial();
	processPolynomial(&l, m);
	lists[N] = l;
	printf("�ѳɹ��������ʽ���ö���ʽ���Ϊ%d��\n", N);
	printf(" * P[%d] = %s\n", N, printResult(lists[N]));
	N++;
}

void Add()
{
	int a, b;
	printf("������Ҫ��ӵ���������ʽ��š��������֮���ÿո������\n");
	printInputHint();
	List l = newPolynomial();
	scanf("%d%d", &a, &b);
	if (a >= N || a < 0 || b >= N || b < 0)
	{
		printf("��Ч���롣\n");
		return;
	}
	l = add(l, lists[a]);
	l = add(l, lists[b]);
	lists[N] = l;
	printf("�����ɹ�����ӵõ��Ķ���ʽ���Ϊ%d��\n", N);
	printf(" * P[%d] = %s\n", N, printResult(lists[N]));
	N++;
	
}

void Sub()
{
	int a, b;
	printf("������Ҫ�������������ʽ��š��������֮���ÿո������\n");
	printInputHint();
	List l = newPolynomial();
	scanf("%d%d", &a, &b);
	if (a >= N || a < 0 || b >= N || b < 0)
	{
		printf("��Ч���롣\n");
		return;
	}
	l = add(l, lists[a]);
	l = sub(l, lists[b]);
	lists[N] = l;
	printf("�����ɹ�������õ��Ķ���ʽ���Ϊ%d��\n", N);
	printf(" * P[%d] = %s\n", N, printResult(lists[N]));
	N++;
}

void Output()
{
	int a, i;
	if (N == 0)
	{
		printf("��δ���롣\n");
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
	printf("������Ҫ��˵���������ʽ��š��������֮���ÿո������\n");
	printInputHint();
	List l = newPolynomial();
	scanf("%d%d", &a, &b);
	if (a >= N || a < 0 || b >= N || b < 0)
	{
		printf("��Ч���롣\n");
		return;
	}
	l = add(l, lists[a]);
	l = multiply(l, lists[b]);
	lists[N] = l;
	printf("�����ɹ�����˵õ��Ķ���ʽ���Ϊ%d��\n", N);
	printf(" * P[%d] = %s\n", N, printResult(lists[N]));
	N++;
} 
