#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct Polynode
{
	float coef;//ϵ��
	int exp;//ָ��
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
	while (rear && s->exp < rear->exp)//���Ҳ����λ��
	{
		pre = rear;
		rear = rear->next;
	}
	if (rear && s->exp == rear->exp)//ָ����ͬ�ĺϲ�
	{     
		rear->coef = rear->coef + s->coef;
		free(s);
		if (rear->coef == 0)//ϵ��Ϊ0�ͷŽ��
		{            
			pre->next = rear->next;
			free(rear);
		}
	}
	else//sָ������rearָ����������
	{                          
		s->next = rear;
		pre->next = s;
	}
}
Polylist PolyCreate()
{
	Polynode *head = malloc(sizeof(Polynode));//����ͷ���
	float c;//ϵ��
	int e;//����
	int xiangshu;//����
	head->coef = 0;//��ʼ��
	head->exp = 0;
	head->next = NULL;
	printf("��������:");
	scanf("%d", &xiangshu);
	while (xiangshu--)
	{
		printf("�������ʽ��ϵ����ָ��:>");
		scanf("%f %d", &c, &e);//�������ʽ��ϵ����ָ��
		Polynode *s = malloc(sizeof(Polynode));//�������
		s->coef = c;//��㸳ֵ
		s->exp = e;
		s->next = NULL;
		Insert(head, s);//������
	}
	return head;
}
Polylist PolyAdd(Polylist polya, Polylist polyb)//����������ʽ��ӣ�����ŵ�a�У��ͷ�b
{
	Polynode *a = polya->next;//a,b�ֱ�ָ�������������������Ԫ�ؽ��
	Polynode *b = polyb->next;
	Polynode *rear = polya;//ָ��Ͷ���ʽ��������һ�����
	Polynode *temp;
	while (a && b)
	{                       //����˳������
		if (a->exp < b->exp)//a��ָ��С��b��ָ��
		{
			rear->next = b;
			rear = b;
			b = b->next;
		}
		else if (a->exp == b->exp)//a��ָ������b��ָ��
		{
			float sum = a->coef + b->coef;
			if (sum == 0)//���ϵ��Ϊ0��ɾ���������
			{
				temp = a;
				a = a->next;
				free(temp);
				temp = b;
				b = b->next;
				free(temp);
			}
			else//��Ӻ�ϵ����Ϊ0��������ӵ�a���ͷ�b
			{
				a->coef = sum;//������ӵ�a
				rear->next = a;
				rear = a;
				a = a->next;
				temp = b;//�ͷ�b���
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
	if (a)//����ʽa����ʣ��
		rear->next = a;
	else
		rear->next = b;
	return polya;
}
Polylist PolySub(Polylist polya, Polylist polyb)
{
	Polylist pb = polyb->next;
	while (pb)//pb��ϵ������-1 ȡ��
	{           
		pb->coef *= -1;
		pb = pb->next;
	}
	return PolyAdd(polya, polyb);
}
void Print(Polylist pl)
{
	Polylist temp = pl->next;
	int flag = 1;//��¼����
	if (!temp)//����ǿն���ʽ�����0
	{
		printf("0\n");
		return;
	}
	while (temp)
	{
		if (temp->coef > 0 && flag != 1)//���ϵ������0�Ҳ��ǵ�һ������һ��+
			printf("+");
		if (temp->coef == 1)//���ϵ����1
		{
			if (temp->exp == 0)//���������0�����1
				putchar('1');
			else if (temp->exp == 1)//���������1�����x
				printf("x");
			else
				printf("x^%d", temp->exp);
		}
		else if (temp->coef == -1)//���ϵ����-1
		{
			if (temp->exp == 0)//���������0�����-1
				putchar('-1');
			else if (temp->exp == 1)//���������1�����-x
				printf("-x");
			else
				printf("-x^%d", temp->exp);
		}
		else
		{
			printf("%g", temp->coef);//�����ϵ���� ���������0��ֻ��Ҫϵ��
			if (temp->exp == 1)//���������1�������һ��x 
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
	printf("��һ������ʽ\n");
	Polylist pl1 = PolyCreate();
	printf("��һ������ʽ:");
	Print(pl1);
	printf("\n�ڶ�������ʽ\n");
	Polylist pl2 = PolyCreate();
	printf("�ڶ�������ʽ:");
	Print(pl2);

	printf("\n****1.�ӷ� 2.���� 0.�˳�****\n");
	int t = 1;
	while (t)
	{
		printf("��ѡ��:");
		scanf("%d", &t);
		switch (t)
		{
		case 1:
			padd = PolyAdd(pl1, pl2);
			printf("��������ʽ֮��Ϊ:");
			Print(padd);	
			Destory(padd);
			break;
		case 2:
			psub = PolySub(pl1, pl2);
			printf("��������ʽ֮��Ϊ:");
			Print(psub);
			Destory(psub);
			break;
		case 0:
			break;
		default:
			printf("�������");
			break;
		}
	}	
}
int main()
{
	Test();
	return 0;
}