/**
  * ����һ���յĶ���ʽ 
  * @return ����ʽ 
  */
List newPolynomial()
{
	List L1 = createPolynomial(0);
	return setData(L1, 0, 0, 0);
}
 
/**
  * ȡ������ʽ��ĳһ���ϵ���� 
  * �����һ���Ӧ������ڵ㻹û�д��������Զ����������ҷ���ϵ��0��
  * @param x_degree ��һ���x���� 
  * @param y_degree ��һ���y����
  * @return ��һ���ϵ�� 
  */
double getData(List header, int x_degree, int y_degree)
{
	return findLocation(&header, x_degree, y_degree) -> data;
}

/**
  * ���ö���ʽ��ĳһ������ݡ�
  * �����һ���Ӧ������ڵ㻹û�д��������Զ������� 
  * @param data ��һ���ϵ�� 
  * @param x_degree ��һ���x���� 
  * @param y_degree ��һ���y���� 
  * @return �õ����¶���ʽ 
  */
List setData(List header, double data, int x_degree, int y_degree)
{
	List header1 = header;
	findLocation(&header1, x_degree, y_degree) -> data = data;
	return header1;
}

/**
  * ����һ���յĵ������
  * @return �µĵ������ 
  */
IteratorResult* createEmptyIteratorResult()
{
	return (IteratorResult*) malloc(SIZE_RESULT);
}

/**
  * �����������ڱ�����������ʽ�� 
  * ��һ��ʹ��ʱ��init��������ΪTRUE�����������ӵ�һ�ʼ������ 
  * ֮��ʹ��ʱ��init��������ΪFALSE������������last���µ��� 
  * @param init �����TRUE��ӵ�һ�ʼ������������ϴη��ص���һ��֮��ʼ������ 
  * @param header ����ʽ
  * @param last ��һ�ε����Ľ�� 
  * @return �������׻��߲������󷵻ؼ٣����򷵻��� 
  */
int iteratorResult(int init, List header, IteratorResult* last)
{
	Polynomial* p1;
	Monomial* p2;
	
	if (init == TRUE)
	{
		p1 = header;
		p2 = header -> header;
	} else {
		if (last == NULL)
		{
			return FALSE;
		}
		p1 = last -> polynomial;
		p2 = last -> monomial;
		p2 = p2 -> next;
	}
	
	if (p2 == NULL)
	{
		p1 = p1 -> next;
		if (p1 == NULL)
		{
			free(last);
			return FALSE;
		}
		p2 = p1 -> header;
	}
	
	if (last == NULL)
	{
		return FALSE;
	} 
	
	last -> polynomial = p1;
	last -> monomial = p2;
	last -> x_degree = p2 -> x_degree;
	last -> y_degree = p1 -> totalDegree - p2 -> x_degree;
	last -> data = p2 -> data;
	
	if (p2 -> data == 0)
	{
		return iteratorResult(FALSE, header, last);
	}
	
	return TRUE;

}

/**
  * �õݹ�ķ�ʽ�ͷ�������ռ�õ��ڴ�ռ䡣��������ǰ���á� 
  */
void freeAll(List header)
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

/*private*/ Monomial* findLocation(List* headerAddress, int x_degree, int y_degree)
{
	List header = *headerAddress;
	if (header == NULL)
	{
		return NULL;
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
		
		if (p -> totalDegree < (x_degree + y_degree)) {
			if (p2 == NULL)
			{
				header = insertPolynomial(NULL, p, x_degree + y_degree);
				*headerAddress = header;
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
		if (p -> x_degree < x_degree)
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
