#include <stdio.h>
#include <stdlib.h>
#define SIZE_POLYNOMIAL (sizeof(Polynomial))
#define SIZE_MONOMIAL (sizeof(Monomial))
#define SIZE_RESULT (sizeof(IteratorResult))
#define TRUE 1
#define FALSE 0
/**
 * 说明：
 * 可以调用本头文件中的getData(), setData()两个函数，以及iteratorResult()迭代器来完成多项式的运算。
 * 函数用法见注释。 
 * 函数前面带有private字样的最好不要调用。 
 * 退出前请调用freeAll()函数。  
 */ 
typedef struct Monomial
{
	double data; //储存数据
	int x_degree; //储存x次数 
	struct Monomial* next;
} Monomial;

typedef struct Polynomial
{
	int totalDegree; //储存x和y的总次数
	Monomial* header; //单项式链表的首地址 
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
  * 取出多项式中某一项的系数。 
  * 如果这一项对应的链表节点还没有创建，则自动创建，并且返回系数0。
  * @param x_degree 这一项的x次数 
  * @param y_degree 这一项的y次数
  * @return 这一项的系数 
  */
double getData(int x_degree, int y_degree)
{
	return findLocation(x_degree, y_degree) -> data;
}

/**
  * 设置多项式中某一项的数据。
  * 如果这一项对应的链表节点还没有创建，则自动创建。 
  * @param data 这一项的系数 
  * @param x_degree 这一项的x次数 
  * @param y_degree 这一项的y次数 
  */
void setData(double data, int x_degree, int y_degree)
{
	findLocation(x_degree, y_degree) -> data = data;
}

/**
  * 迭代器，用于遍历整个多项式。 
  * 第一次使用时，init参数设置为TRUE，迭代器将从第一项开始遍历。 
  * 之后使用时，init参数设置为FALSE，迭代器每调用一次将返回下一项的内容。 
  * @param init 如果是TRUE则从第一项开始遍历，否则从上次返回的那一项之后开始遍历。 
  * @return 遍历得到的项的内容，是个结构体指针，有三个成员。如果遍历完成则返回NULL。记得用完以后及时free哦！ 
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
  * 用递归的方式释放链表所占用的内存空间。结束程序前调用。 
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
