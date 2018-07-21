#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct Polynode
{
	float coef;//系数
	int exp;//指数
	struct Polynode *next;
}Polynode, *Polylist;
void Insert(Polylist head, Polynode* s)
{
	Polynode *pre = head;
	Polynode *rear = head->next;
	if (s->coef == 0)
	{
		free(s);
		return;
	}
	while (rear && s->exp < rear->exp)//查找插入的位置
	{
		pre = rear;
		rear = rear->next;
	}
	if (rear && s->exp == rear->exp)//指数相同的合并
	{     
		rear->coef = rear->coef + s->coef;
		free(s);
		if (rear->coef == 0)//系数为0释放结点
		{            
			pre->next = rear->next;
			free(rear);
		}
	}
	else//s指数大于rear指数，插入结点
	{                          
		s->next = rear;
		pre->next = s;
	}
}
Polylist PolyCreate()
{
	Polynode *head = malloc(sizeof(Polynode));//建立头结点
	float c;//系数
	int e;//次数
	int xiangshu;//项数
	head->coef = 0;//初始化
	head->exp = 0;
	head->next = NULL;
	printf("输入项数:");
	scanf("%d", &xiangshu);
	while (xiangshu--)
	{
		printf("输入多项式的系数和指数:>");
		scanf("%f %d", &c, &e);//输入多项式的系数和指数
		Polynode *s = malloc(sizeof(Polynode));//建立结点
		s->coef = c;//结点赋值
		s->exp = e;
		s->next = NULL;
		Insert(head, s);//插入结点
	}
	return head;
}
Polylist PolyAdd(Polylist polya, Polylist polyb)//将两个多项式相加，结果放到a中，释放b
{
	Polynode *a = polya->next;//a,b分别指向两个多项是链表的首元素结点
	Polynode *b = polyb->next;
	Polynode *rear = polya;//指向和多项式链表的最后一个结点
	Polynode *temp;
	while (a && b)
	{                       //降幂顺序排列
		if (a->exp < b->exp)//a的指数小于b的指数
		{
			rear->next = b;
			rear = b;
			b = b->next;
		}
		else if (a->exp == b->exp)//a的指数等于b的指数
		{
			float sum = a->coef + b->coef;
			if (sum == 0)//相加系数为0，删除两个结点
			{
				temp = a;
				a = a->next;
				free(temp);
				temp = b;
				b = b->next;
				free(temp);
			}
			else//相加后系数不为0，将结果加到a，释放b
			{
				a->coef = sum;//将结果加到a
				rear->next = a;
				rear = a;
				a = a->next;
				temp = b;//释放b结点
				b = b->next;
				free(temp);
			}
		}
		else
		{
			rear->next = a;
			rear = a;
			a = a->next;
		}
	}
	if (a)//多项式a中有剩余
		rear->next = a;
	else
		rear->next = b;
	return polya;
}
Polylist PolySub(Polylist polya, Polylist polyb)
{
	Polylist pb = polyb->next;
	while (pb)//pb的系数乘以-1 取反
	{           
		pb->coef *= -1;
		pb = pb->next;
	}
	return PolyAdd(polya, polyb);
}
void Print(Polylist pl)
{
	Polylist temp = pl->next;
	int flag = 1;//记录项数
	if (!temp)//如果是空多项式，输出0
	{
		printf("0\n");
		return;
	}
	while (temp)
	{
		if (temp->coef > 0 && flag != 1)//如果系数大于0且不是第一项，先输出一个+
			printf("+");
		if (temp->coef == 1)//如果系数是1
		{
			if (temp->exp == 0)//如果次数是0，输出1
				putchar('1');
			else if (temp->exp == 1)//如果次数是1，输出x
				printf("x");
			else
				printf("x^%d", temp->exp);
		}
		else if (temp->coef == -1)//如果系数是-1
		{
			if (temp->exp == 0)//如果次数是0，输出-1
				putchar('-1');
			else if (temp->exp == 1)//如果次数是1，输出-x
				printf("-x");
			else
				printf("-x^%d", temp->exp);
		}
		else
		{
			printf("%g", temp->coef);//先输出系数； 如果次数是0，只需要系数
			if (temp->exp == 1)//如果次数是1，再输出一个x 
				printf("x");
			else if (temp->exp)
				printf("x^%d", temp->exp);
		}
		temp = temp->next;
		flag++;
	}
	printf("\n");
}
void Destory(Polylist pl)
{
	Polylist pre = pl->next;
	Polylist p = pre->next;
	while (p)
	{
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}
void Test()
{
	Polylist padd = NULL;
	Polylist psub = NULL;
	printf("第一个多项式\n");
	Polylist pl1 = PolyCreate();
	printf("第一个多项式:");
	Print(pl1);
	printf("\n第二个多项式\n");
	Polylist pl2 = PolyCreate();
	printf("第二个多项式:");
	Print(pl2);

	printf("\n****1.加法 2.减法 0.退出****\n");
	int t = 1;
	while (t)
	{
		printf("请选择:");
		scanf("%d", &t);
		switch (t)
		{
		case 1:
			padd = PolyAdd(pl1, pl2);
			printf("两个多项式之和为:");
			Print(padd);	
			Destory(padd);
			break;
		case 2:
			psub = PolySub(pl1, pl2);
			printf("两个多项式之差为:");
			Print(psub);
			Destory(psub);
			break;
		case 0:
			break;
		default:
			printf("输入错误");
			break;
		}
	}	
}
int main()
{
	Test();
	return 0;
}