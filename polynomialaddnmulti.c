#include <stdio.h>
#include <malloc.h>

typedef struct polynode *polynomial;
struct polynode
{
	int coef;
	int expon;
	polynomial next;
};


polynomial ReadPoly();

polynomial Multi(polynomial P1, polynomial p2);

polynomial Add(polynomial P1, polynomial p2);

void PrintPoly(polynomial P);

void Cleanup(polynomial *P);

void Attach(int c, int e, polynomial* pRear);

int main()
{
	polynomial P1, P2, PP, PS;

	P1 = ReadPoly();
	P2 = ReadPoly();
	PP = Multi(P1, P2);
	PrintPoly(PP);
	PS = Add(P1, P2);
	PrintPoly(PS);
    Cleanup(&P1);
    Cleanup(&P2);
    Cleanup(&PP);
    Cleanup(&PS);

    system("pause");
    return 0;
}

polynomial Multi(polynomial P1, polynomial P2)
{
	polynomial t1, t2, Rear, P,t;
	int c, e;
	if (!P1 || !P2)
		return NULL;
	t1 = P1; t2 = P2;
	//第一个表的一个元素与第二个表每个元素相乘
	//创造节点
	P = (polynomial)malloc(sizeof(struct polynode));
	Rear = P;
	//第一个元素
	while (t2)
	{
		Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
		t2 = t2->next;
	}
	t1 = t1->next;
	//两个循环
	while (t1)
	{
		while (t2)
		{
			e = t1->expon + t2->expon;
			c = t1->coef * t2->coef;
			while (Rear->next && Rear->next->expon > e)
				Rear = Rear->next;
			if (Rear->next && Rear->next->expon == e)
			{
				if (Rear->next->coef+c)
				{
					Rear->next->coef += c;
				}
				else
				{
					t = Rear->next;
					Rear->next = Rear->next->next;
					free(t);
				}
			}
			else
			{
				t = (polynomial)malloc(sizeof(struct polynode));
				t->coef = c; t->expon = e;
				t->next = Rear->next;
				Rear->next = t;
				Rear = Rear->next;
			}

			t2 = t2->next;
		}
		t1 = t1->next;
	}
	t2 = P; P = P->next; free(t2);
	return P;
}

void Attach(int c, int e, polynomial* pRear)
{
	polynomial P;
	P = (polynomial)malloc(sizeof(struct polynode));
	P->coef = c;
	P->expon = e;
	P->next = NULL;
	(*pRear)->next = P;
	(*pRear) = P;
}

polynomial ReadPoly()
{
	int N,e,c;
	polynomial P,Rear,t;
	scanf("%d", &N);
	P = (polynomial)malloc(sizeof(struct polynode));
	P->next = NULL;
	Rear = P;
	while (N--)
	{
		scanf("%d%d", &c, &e);
		Attach(c, e, &Rear);
	}
	t = P, P = P->next, free(t);
	return P;
}

polynomial Add(polynomial P1, polynomial P2)
{
	polynomial t1, t2, P, Rear, t;
	t1 = P1; t2 = P2;
	P = (polynomial)malloc(sizeof(struct polynode));
	P->next = NULL;
	Rear = P;
	while (t1 && t2)
	{
		t = (polynomial)malloc(sizeof(struct polynode));
		if (t1->expon == t2->expon)
		{
			t->coef = t1->coef + t2->coef;
			t->expon = t1->expon;
			t1 = t1->next;
			t2 = t2->next;
		}
		else if (t1->expon > t2->expon)
		{
			t->coef = t1->coef;
			t->expon = t1->expon;
			t1 = t1->next;
		}
		else
		{
			t->coef = t2->coef;
			t->expon = t2->expon;
			t2 = t2->next;
		}
		Rear->next = t;
		Rear = t;
	}
	if (t1)
	{
		Rear->next = t1;
	}
	else if (t2)
	{
		Rear->next = t2;
	}

	t2 = P; P = P->next; free(t2);
	
	return P;

}

void Cleanup(polynomial *P)
{
	polynomial q;
	while (*P)
	{
		q = *P;
		*P = (*P)->next;
		free(q);
	}
}

void PrintPoly(polynomial P)
{
	polynomial tmp;
	tmp = P;
	int N = 1;
	while (tmp)
	{
		printf(" %d %d", tmp->coef, tmp->expon);
		if (N % 10 == 0)
			printf("\n");
	}
}
