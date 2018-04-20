#include "Polynomial.h" 
List add(List L1, List L2);
List sub(List L1, List L2);
List multiply(List L1, List L2);
List copy(List L);

List add(List L1, List L2)
{
	IteratorResult* p2 = createEmptyIteratorResult();
	iteratorResult(TRUE, L2, p2);

	List result = L1;
	do 
		result = setData(result, getData(result, p2 -> x_degree, p2 -> y_degree) + p2 -> data, p2 -> x_degree, p2 -> y_degree);	
	while (iteratorResult(FALSE, L2, p2));
	return result;
}

List sub(List L1, List L2)
{
	IteratorResult* p2 = createEmptyIteratorResult();
	iteratorResult(TRUE, L2, p2);
	List result = L1;
	do
		result = setData(result, getData(result, p2 -> x_degree, p2 -> y_degree) - p2 -> data, p2 -> x_degree, p2 -> y_degree);
	while (iteratorResult(FALSE, L2, p2));
	return result;
}

List multiply(List L1, List L2)
{
	IteratorResult* p1 = createEmptyIteratorResult();
	iteratorResult(TRUE, L1, p1);
	
	List result = newPolynomial();
	do {
		
		IteratorResult* p2 = createEmptyIteratorResult();
		iteratorResult(TRUE, L2, p2);

		do {
			int x = p1 -> x_degree + p2 -> x_degree;
			int y = p1 -> y_degree + p2 -> y_degree;
			double data = p1 -> data * p2 -> data; 
			result = setData(result, getData(result, x, y) + data, x, y);
		}
		while (iteratorResult(FALSE, L2, p2));
		
	}
	while (iteratorResult(FALSE, L1, p1));
	
	return result;
}

List copy(List L)
{
	return add(newPolynomial(), L);
}

/*
int Main(void)
{
	List l1 = newPolynomial();
	List l2 = newPolynomial();
	
	l1 = setData(l1, -2.3, 2, 5);
	l1 = setData(l1, -1, 0, 0);
	l1 = setData(l1, -3, 0, 0);
	l1 = setData(l1, -1.1, 7, 0);
	printResult(l1);
	
	l2 = setData(l2, 3, 2, 5);
	l2 = setData(l2, 7, 2, 8);
	l2 = setData(l2, -1.1, 7, 0);
	l2 = setData(l2, 1, 0, 0);
	printResult(l2);
	
	List re;
	
	printf("\nadd:\n");
	re = add(copy(l1), l2);
	printResult(re);
	freeAll(re);
	
	printf("\nsub:\n");
	re = sub(copy(l1), l2);
	printResult(re);
	freeAll(re);
	
	printf("\nmultiply:\n");
	re = multiply(copy(l1), l2);
	printResult(re);
	
	freeAll(re);
	freeAll(l1);
	freeAll(l2);
	
}*/







