// ������� 
#include "Header.h"
#include "Polynomial.h"
#include "IO.h"
#include "Calculate.h"

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
		printf("==============================\n       ��Ԫ����ʽ������\n==============================\n\n");
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
				printf("�������");
				break;
		}
		wait();
		system("cls");
	} while (TRUE);
}

//��������������˵�*  
void printMenu()
{
	printf("    [1] ����ʽ����\n");
	printf("    [2] ����ʽ�ӷ�\n");
	printf("    [3] ����ʽ����\n");
	printf("    [4] ����ʽ�˷�\n");
	printf("    [5] ��������Ѵ���Ķ���ʽ\n");
	printf("    [0] �˳�\n");
}

//����[1] ����ʽ������  
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

//����[2] ����ʽ�ӷ� ����������ʽ��ӵ������Լ�ѡ��������������ʽ 
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

//����[3] ����ʽ���� ǰһ������һ��  
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

//����Ѵ���Ķ���ʽ   
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

//ÿһ�β�����������ʾ
void wait()
{
	printf("\n");
	system("pause");
} 

//����[4] ����ʽ�˷� ��ѡ������������ʽ���   
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
