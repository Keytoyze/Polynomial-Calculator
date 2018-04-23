void processPolynomial(List* L, char* str)
{
	int i, j = 0;
	char monomial[1024] = "";
	char* p = str;
	List temp;
	for (i = 0; str[i]; i++)
	{
		monomial[j++] = str[i];
		if ((str[i] == '+' || str[i] == '-') && i != 0)
		{
			monomial[j-1] = '\0';
			temp = newPolynomial();
			processMonomial(&temp, monomial);
			*L = add(*L, temp);
			freeAll(temp);
			monomial[0] = str[i];
			j = 1;
		}
	}
	if (j >= 1) {
		monomial[j] = '\0';
		temp = newPolynomial();
		processMonomial(&temp, monomial);
		*L = add(*L, temp);
		freeAll(temp);
	}
	/*
	i = 0;
	List temp;
	while (*p)
	{
		temp = newPolynomial(); 
		p = processMonomial(&temp, p);
		*L = add(*L, temp);
		freeAll(temp);
	}*/
}

char* processMonomial(List* L, char* str)
{
	char* p = str;
	char tmp[60];
	char c;
	int n = -1, len;
	double data, x = 0, y = 0;
	
	if (str[0] == '-' && (str[1] == 'x' || str[1] == 'y')) //-x or -y
	{
		strcpy(tmp, "-1");
		strcat(tmp, str + 1);
		p = tmp;
	}
	
	if (str[0] == '+' && (str[1] == 'x' || str[1] == 'y')) // +x or +y
	{
		p++;
	}
	
	len = getNum(p, &data);
	if (len == 0) //没有输入系数 
	{
		 data = 1;
	}
	p += len;
	
	if (*p == '*')
	{
		p++;
	}
	
	if (*p == 'x') // 输入了 x
	{
		p++;
		if (*p == '^')
		{
			p++;
			p += getNum(p, &x);
		} else {
			x = 1;
		}
	}
	
	if (*p == '*')
	{
		p++;
	}
	
	if (*p == 'y') // 输入了 y
	{
		p++;
		if (*p == '^')
		{
			p++;
			p += getNum(p, &y);
		} else {
			y = 1;
		}
	}
	
	*L = setData(*L, data, (int)(x+0.5), (int)(y+0.5));
	return p;
}

int isNumber(char c)
{
	return c >= '0' && c <= '9';
}

int getNum(char* p, double* result)
{
	char c;
	int n = -1;
	double re = 0;
	int integer = TRUE;
	int bit = 0;
	int flag = 1;
	int i;
	while (++n, (c = *(p++)))
	{
		if (n == 0)
		{
			if (c == '-')
			{
				flag = -1;
				continue;
			} else if (c == '+')
			{
				continue;
			}
		}
		
		if (isNumber(c))
		{
			re = re * 10 + c - '0';
			if (!integer)
			{
				bit++;
			}
		} else if (c == '.')
		{
			integer = FALSE;
		} else {
			break;
		}
	}
	for (i = 0; i < bit; i++)
	{
		re = re / 10;
	}
	*result = flag * re;
	return n;
}

char* deleteEnd0(double num) //去掉num小数点后的0 
{
	static char re[60];
	re[0] = '\0';
	int i, integer = TRUE;
	if ((int)num == num)
	{
		sprintf(re, "%d", (int)num);
		return re;
	}
	sprintf(re, "%lf", num);
	for (i = 0; re[i]; i++)
	{
		if (re[i] == '.')
		{
			integer = FALSE;
		} else if (re[i] == '0' && !integer)
		{
			re[i] = '\0';
			break;
		}
	}
	return re;
}

char* printResult(List l)
{
	IteratorResult* p = createEmptyIteratorResult();
	iteratorResult(TRUE, l, p);
	int boolean = TRUE; 
	char m[60], n[60];
	static char re[1024];
	re[0] = '\0';
	int flag = 0;
	while(boolean)
	{
		m[0] = '\0';
		n[0] = '\0';
		if (p -> data != 1)
		{
			if (p -> data == -1)
			{
				strcat(m, "-");
			} else {
				strcat(m, deleteEnd0(p -> data));
			}
		}

		n[0] = '\0';
		if (p -> x_degree != 0)
		{
			if (p -> x_degree != 1)
			{
				sprintf(n, "x^%d", p -> x_degree);
			} else {
				strcpy(n, "x");
			}
			strcat(m, n);
		}
		
		n[0] = '\0';
		if (p -> y_degree != 0)
		{
			if (p -> x_degree != 0)
			{
				strcat(m, "*");
			} 
			if (p -> y_degree != 1)
			{
				sprintf(n, "y^%d", p -> y_degree);
			} else {
				strcpy(n, "y");
			}
			strcat(m, n);
		}
		
		if (p -> x_degree == 0 && p -> y_degree == 0 && (p -> data == 1 || p -> data == -1))
		{
			strcat(m, "1");
		}
		if (flag && m[0] != '-')
		{
			strcat(re, "+");
		}
		strcat(re, m);
		flag = 1;
		boolean = iteratorResult(FALSE, l, p);
	}
	return re;
}
