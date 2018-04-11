#include <stdio.h>
#include <stdlib.h>
#define SIZE_POLYNOMIAL (sizeof(Polynomial))
#define SIZE_MONOMIAL (sizeof(Monomial))
#define SIZE_RESULT (sizeof(IteratorResult))
#define TRUE 1
#define FALSE 0
/**
 * ˵����
 * ���Ե��ñ�ͷ�ļ��е�getData(), setData()�����������Լ�iteratorResult()����������ɶ���ʽ�����㡣
 * �����÷���ע�͡� 
 * ����ǰ�����private��������ò�Ҫ���á� 
 * �˳�ǰ�����freeAll()������  
 */ 
typedef struct Monomial
{
	double data; //��������
	int x_degree; //����x���� 
	struct Monomial* next;
} Monomial;

typedef struct Polynomial
{
	int totalDegree; //����x��y���ܴ���
	Monomial* header; //����ʽ������׵�ַ 
	struct Polynomial* next;
} Polynomial;

typedef struct IteratorResult
{
	int x_degree;
	int y_degree;
	double data;
} IteratorResult;

Monomial* findLocation(int x_degree, int y_degree);
double getData(int x_degree, int y_degree);
void setData(double data, int x_degree, int y_degree);
Monomial* findLocationInMonomial(int x_degree, Polynomial* father);
Polynomial* createPolynomial(int totalDegree);
Polynomial* insertPolynomial(Polynomial* last, Polynomial* next, int totalDegree);
Monomial* insertMonomial(Monomial* last, Monomial* next, int x_degree, double data);
Monomial* createMonomial(int x_degree, double data);
IteratorResult* iteratorResult(int init);
void freeAll();
void freeMonomial(Monomial *p);
void freePolynomial(Polynomial *p);

Polynomial* header = NULL;

/**
  * ȡ������ʽ��ĳһ���ϵ���� 
  * �����һ���Ӧ������ڵ㻹û�д��������Զ����������ҷ���ϵ��0��
  * @param x_degree ��һ���x���� 
  * @param y_degree ��һ���y����
  * @return ��һ���ϵ�� 
  */
double getData(int x_degree, int y_degree)
{
	return findLocation(x_degree, y_degree) -> data;
}

/**
  * ���ö���ʽ��ĳһ������ݡ�
  * �����һ���Ӧ������ڵ㻹û�д��������Զ������� 
  * @param data ��һ���ϵ�� 
  * @param x_degree ��һ���x���� 
  * @param y_degree ��һ���y���� 
  */
void setData(double data, int x_degree, int y_degree)
{
	findLocation(x_degree, y_degree) -> data = data;
}

/**
  * �����������ڱ�����������ʽ�� 
  * ��һ��ʹ��ʱ��init��������ΪTRUE�����������ӵ�һ�ʼ������ 
  * ֮��ʹ��ʱ��init��������ΪFALSE��������ÿ����һ�ν�������һ������ݡ� 
  * @param init �����TRUE��ӵ�һ�ʼ������������ϴη��ص���һ��֮��ʼ������ 
  * @return �����õ���������ݣ��Ǹ��ṹ��ָ�룬��������Ա�������������򷵻�NULL���ǵ������Ժ�ʱfreeŶ�� 
  */
IteratorResult* iteratorResult(int init)
{
	static Polynomial* p1;
	static Monomial* p2;
	
	if (init == TRUE)
	{
		p1 = header;
		p2 = header -> header;
	} else {
		p2 = p2 -> next;
	}
	
	if (p2 == NULL)
	{
		p1 = p1 -> next;
		if (p1 == NULL)
		{
			return NULL;
		}
		p2 = p1 -> header;
	}
	
	if (p2 -> data == 0)
	{
		return iteratorResult(FALSE);
	}

	IteratorResult* p = (IteratorResult*)malloc(SIZE_RESULT);
	p -> x_degree = p2 -> x_degree;
	p -> y_degree = p1 -> totalDegree - p2 -> x_degree;
	p -> data = p2 -> data;

	return p;
}

/**
  * �õݹ�ķ�ʽ�ͷ�������ռ�õ��ڴ�ռ䡣��������ǰ���á� 
  */
void freeAll()
{
	freePolynomial(header);
}

/*private*/ void freePolynomial(Polynomial *p)
{
	if (p == NULL)
	{
		return;
	}
	freeMonomial(p -> header);
	freePolynomial(p -> next);
	free(p);
}
 
/*private*/ void freeMonomial(Monomial *p)
{
	if (p == NULL)
	{
		return;
	}
	freeMonomial(p -> next);
	free(p);
}

/*private*/ Monomial* findLocation(int x_degree, int y_degree)
{
	if (header == NULL)
	{
		header = createPolynomial(x_degree + y_degree);
	}
	
	Polynomial* p = header;
	Polynomial* p2 = NULL;
	
	while (TRUE) {
		
		if (p -> totalDegree == x_degree + y_degree)
		{
			if (p -> header == NULL)
			{
				return p -> header = createMonomial(x_degree, 0);
			} 
			return findLocationInMonomial(x_degree, p);
		}
		
		if (p -> totalDegree > x_degree + y_degree) {
			if (p2 == NULL)
			{
				header = insertPolynomial(NULL, p, x_degree + y_degree);
				header -> header = createMonomial(x_degree, 0);
				return header -> header;
			}
			p = insertPolynomial(p2, p, x_degree + y_degree);
			p -> header = createMonomial(x_degree, 0);
			return p -> header; 
		}
		
		p2 = p;
		if (p -> next == NULL)
		{
			p = insertPolynomial(p, NULL, x_degree + y_degree);
			p -> header = createMonomial(x_degree, 0);
			return p -> header;
		}
		p = p -> next;
		
	}
}

/*private*/ Monomial* findLocationInMonomial(int x_degree, Polynomial* father)
{
	Monomial* header = father -> header;
	Monomial* p = header;
	Monomial* p2 = NULL;
	while (TRUE) {
		if (p -> x_degree == x_degree)
		{
			return p;
		}
		if (p -> x_degree > x_degree)
		{
			if (p2 == NULL)
			{
				return father -> header = insertMonomial(NULL, p, x_degree, 0);
			}
			return insertMonomial(p2, p, x_degree, 0);
		}
		p2 = p;
		if (p -> next == NULL)
		{
			return insertMonomial(p, NULL, x_degree, 0);
		}
		p = p -> next;
	}
}

/*private*/ Polynomial* createPolynomial(int totalDegree)
{
	Polynomial* p = (Polynomial*)malloc(SIZE_POLYNOMIAL);
	p -> totalDegree = totalDegree;
	p -> next = NULL;
	p -> header = NULL;
	return p;
}

/*private*/ Polynomial* insertPolynomial(Polynomial* last, Polynomial* next, int totalDegree)
{
	Polynomial* p = createPolynomial(totalDegree);
	if (next == NULL)
	{
		return last -> next = p;
	}
	if (last == NULL)
	{
		p -> next = next;
		return p;
	}
	p -> next = last -> next;
	last -> next = p;
	return p;
}

/*private*/ Monomial* insertMonomial(Monomial* last, Monomial* next, int x_degree, double data)
{
	Monomial* p = createMonomial(x_degree, data);
	if (next == NULL)
	{
		return last -> next = p;
	}
	if (last == NULL)
	{
		p -> next = next;
		return p;
	}
	p -> next = last -> next;
	last -> next = p;
	return p;
}

/*private*/ Monomial* createMonomial(int x_degree, double data)
{
	Monomial* p = (Monomial*)malloc(SIZE_MONOMIAL);
	p -> x_degree = x_degree;
	p -> data = data;
	p -> next = NULL; 
	return p;
}

/*
int main(void)
{
	setData(2.3, 2, 5);
	setData(-1, 0, 0);
	printf("%lf  %lf   %lf\n", getData(2,5), getData(4, 6), getData(0, 0));
	IteratorResult* p = iteratorResult(TRUE);
	while(p != NULL)
	{
		printf("%d %d %lf\n", p -> x_degree, p -> y_degree, p -> data);
		free(p);
		p = iteratorResult(FALSE);
	}
	freeAll();
}*/
