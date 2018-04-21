#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/* For Polynomial.h */

#define SIZE_POLYNOMIAL (sizeof(Polynomial))
#define SIZE_MONOMIAL (sizeof(Monomial))
#define SIZE_RESULT (sizeof(IteratorResult))

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
	/*private*/ Monomial* monomial;
	/*private*/ Polynomial* polynomial;
	int x_degree;
	int y_degree;
	double data;
} IteratorResult;

typedef Polynomial* List; 

Monomial* findLocation(List* header, int x_degree, int y_degree);
double getData(List header, int x_degree, int y_degree);
List setData(List header, double data, int x_degree, int y_degree);
Monomial* findLocationInMonomial(int x_degree, Polynomial* father);
Polynomial* createPolynomial(int totalDegree);
Polynomial* insertPolynomial(Polynomial* last, Polynomial* next, int totalDegree);
Monomial* insertMonomial(Monomial* last, Monomial* next, int x_degree, double data);
Monomial* createMonomial(int x_degree, double data);
IteratorResult* createEmptyIteratorResult();
int iteratorResult(int init, List header, IteratorResult* last);
void freeAll(List header);
void freeMonomial(Monomial *p);
void freePolynomial(Polynomial *p);
List newPolynomial();

/* For Calculate.h */

List add(List L1, List L2);
List sub(List L1, List L2);
List multiply(List L1, List L2);
List copy(List L);

/* For IO.h */

char* processMonomial(List* L, char* str);
int isNumber(char c);
int getNum(char* p, double* result);
char* deleteEnd0(double num);
char* printResult(List header);
void processPolynomial(List*L, char* str);
