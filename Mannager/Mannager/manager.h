#include "rbtree.h"
#define MAX_AVALIABLE_NUM 10
#define START printf("------------------------------------start----------------------------------\n");
#define END printf("--------------------------------------end----------------------------------\n\n");
#pragma warning(disable:4996)
#define DEBUG 0
int all_book = 0, all_people = 0, all_borrowing = 0;

typedef struct date {
	int Year;
	int Month;
	int Day;
}Date;

typedef struct store_information {
	char Index[MAX_NAME];          //���
	char Book_Name[MAX_NAME];      //����
	char Author_Name[MAX_NAME];    //������
	char Press[MAX_NAME];          //������
	char Category[MAX_NAME];       //���
	Date Press_Date;
	int Price;
	int Borrownum;
	int All_Have;
	int Current_Have;
	int AllBorrow;
}Store;

typedef struct book_information {
	char OnlyBorrowCode[MAX_NAME * 2 + 2];
	char Index[MAX_NAME];          //���
	char Book_Name[MAX_NAME];      //����
	char LCardNumber[MAX_NAME];    //����֤��
	Date Borrow_Date;
	Date Return_Date;
	int Price;
}Book;

typedef struct people_information {
	char LCardNumber[MAX_NAME];    //����֤��
	char Name[MAX_NAME];
	char ID[MAX_NAME];
	char BorrowID[MAX_AVALIABLE_NUM][MAX_NAME];
	char BorrowName[MAX_AVALIABLE_NUM][MAX_NAME];
	int Category;                  //1 stuent 0 teacher
	int AllAvaliableBorrowNum;
	int key;                       //1 avaliable 0 anti
	int BorrowNum;
	int clas;
}People;

int avaliable(int start, int end, int input)
{
	while (input > end || input < start)
	{
		printf("������%d��%d֮���ֵ.\n", start, end);
		scanf("%d", &input);
	}
	return input;
}

void init_date(Date *A)
{
	A->Day = 0;
	A->Month = 0;
	A->Year = 0;
}

void write_date(Date *A, char B[])
{
	printf("%s���� 1998 1 1\n", B);
	scanf("%d %d %d", &(A->Year), &(A->Month), &(A->Day));
}

void read_date(Date A)
{
	printf("%d %d %d\t", A.Year, A.Month, A.Day);
}

int compare(void* key_a, void* key_b)
{
	return strcmp((char*)key_a, (char*)key_b);

}

void add_book_store(rbtree *tree)
{
	START
		Store*data = (Store*)malloc(sizeof(Store));
	printf("�������鼮���.\n");
	scanf("%s", data->Index);
	if (rbtree_lookup(tree, data->Index))
		printf("�����鼮�Ѵ��ڣ�\n"), free(data);
	else
	{
		printf("����������.\n");
		scanf("%s", data->Book_Name);
		printf("����������.\n");
		scanf("%s", data->Author_Name);
		printf("�����������.\n");
		scanf("%s", data->Press);
		printf("���������.\n");
		scanf("%s", data->Category);
		write_date(&(data->Press_Date), "�������������.");
		printf("������۸�.\n");
		scanf("%d", &(data->Price));
		printf("��������.\n");
		scanf("%d", &(data->All_Have));
		printf("�����������.\n");
		scanf("%d", &(data->Borrownum));
		data->Current_Have = data->All_Have - data->Borrownum;
		printf("�������ܽ����.\n");
		scanf("%d", &(data->AllBorrow));
		rbtree_insert(tree, data->Index, data);
		all_book++;
		printf("�����\n\n");
	}
	END
}

void find_book_store(rbtree *tree)
{
	START
		char temp[MAX_NAME];
	printf("��������ҪѰ�ҵ��鼮���.\n");
	scanf("%s", temp);
	Store*data = (Store*)rbtree_lookup(tree, temp);
	if (data)
	{
		printf("����:                   %s\n", data->Book_Name);
		printf("����:                   %s\n", data->Author_Name);
		printf("������:                 %s\n", data->Press);
		printf("���:                   %s\n", data->Category);
		printf("��������:               "); read_date(data->Press_Date);
		printf("�۸�:                   %d\n", data->Price);
		printf("���:                   %d\n", data->All_Have);
		printf("���:                   %d\n", data->Borrownum);
		printf("�ڿ�:                   %d\n", data->All_Have - data->Borrownum);
		printf("�ܽ��:                 %d\n", data->AllBorrow);
		END
			return;
	}
	printf("%s ������!\n", temp);
	END
}

void edit_book_store(rbtree*tree)
{
	START
		char Index[MAX_NAME];
	printf("��������༭�鼮���.\n");
	scanf("%s", Index);
	Store*data = (Store*)rbtree_lookup(tree, Index);
	printf("����������.\n");
	scanf("%s", data->Book_Name);
	printf("������������.\n");
	scanf("%s", data->Author_Name);
	printf("�����������.\n");
	scanf("%s", data->Press);
	printf("���������.\n");
	scanf("%s", data->Category);
	write_date(&(data->Press_Date), "�������������.");
	printf("������۸�.\n");
	scanf("%d", &(data->Price));
	printf("��������.\n");
	scanf("%d", &(data->All_Have));
	printf("�����������.\n");
	scanf("%d", &(data->Borrownum));
	data->Current_Have = data->All_Have - data->Borrownum;
	printf("�������ܽ����.\n");
	scanf("%d", &(data->AllBorrow));
	printf("���޸�\n");
	END
}

void delete_book_store(rbtree*tree)
{
	START
		char Index[MAX_NAME];
	printf("��������Ҫɾ�����鼮���.\n");
	scanf("%s", Index);
	Store*data = (Store*)rbtree_lookup(tree, Index);
	if (data)
	{
		rbtree_remove(tree, Index);
		all_book--;
		printf("%s��ɾ��!\n", Index);
	}
	else
		printf("����!%s������!\n", Index);
	END
}

void printf_store(struct rbtree_node* node)
{
	printf("����\t\t\t����\t\t������\t\t���\t��������\t�۸�\t���\t���\t�ڿ�\t�ܽ��\t\n\n");
	if (!node) return;
	Store*head = (Store*)node->data;
	printf("%s\t", head->Book_Name);
	printf("%s\t", head->Author_Name);
	printf("%s\t", head->Press);
	printf("%s\t", head->Category);
	printf(""); read_date(head->Press_Date);
	printf("%d\t", head->Price);
	printf("%d\t", head->All_Have);
	printf("%d\t", head->Borrownum);
	printf("%d\t", head->All_Have - head->Borrownum);
	printf("%d\t\n\n", head->AllBorrow);
	if (node->left)
		printf_store(node->left);
	if (node->right)
		printf_store(node->right);
}

void list_book_store(rbtree*tree)
{
	START
		printf_store(tree->root);
	END
}

void add_people(rbtree *tree)
{
	START
		People*data = (People*)malloc(sizeof(People));
	printf("��������Ҫ��ӵ�ID.\n");
	scanf("%s", data->ID);
	if (rbtree_lookup(tree, data->ID))
		printf("����!�û��Ѵ���!\n"), free(data);
	else
	{
		printf("�������û����.   1.ѧ��   0.��ʦ\n");
		data->Category = avaliable(0, 1, 3);
		printf("����������.\n");
		scanf("%s", data->Name);
		printf("����������.\n");
		scanf("%s", data->LCardNumber);
		if (data->Category)
		{
			printf("������༶\n");
			scanf("%d", &(data->clas));
			data->AllAvaliableBorrowNum = MAX_AVALIABLE_NUM / 2;
		}
		else
			data->AllAvaliableBorrowNum = MAX_AVALIABLE_NUM;
		data->BorrowNum = 0;
		data->key = 1;
		rbtree_insert(tree, data->ID, data);
		all_people++;
		printf("�����\n\n\n");
	}
	END
}

void find_people(rbtree *tree)
{
	START
		char ID[MAX_NAME];
	printf("���������ID.\n");
	scanf("%s", ID);
	People*data = (People*)rbtree_lookup(tree, ID);
	if (data)
	{
		printf("ID:               %s\n", data->ID);
		printf("�����:           %s\n", data->LCardNumber);
		printf("����:             %s\n", data->Name);
		printf("�ɽ����:         %d\n", data->AllAvaliableBorrowNum - data->BorrowNum);
		if (data->Category)
			printf("�༶:             %d\n", data->clas);
		printf("\n");
		for (int i = 0; i < data->BorrowNum; i++)
			printf("                  %s\n", data->BorrowName[i]);
		printf("\n");
	}
	else
		printf("%s������.\n", ID);
	END
}

void delete_people(rbtree *tree)
{
	START
		char ID[MAX_NAME];
	printf("��������Ҫɾ����ID.\n");
	scanf("%s", ID);
	People*data = (People*)rbtree_lookup(tree, ID);
	if (data)
	{
		rbtree_remove(tree, ID);
		all_people--;
		printf("��ɾ��\n");
	}
	else
		printf("%s������.\n", ID);
	END;
}

void lose(rbtree *tree)
{
	START
		char ID[MAX_NAME];
	printf("��������Ҫ��ʧ��ID.\n");
	scanf("%s", ID);
	People*data = (People*)rbtree_lookup(tree, ID);
	if (data)
	{
		data->key = 0;
		printf("�ѹ�ʧ\n");
	}
	else
		printf("����,%s������.\n", ID);
	END
}

void remain(rbtree *tree)
{
	START
		char ID[MAX_NAME];
	printf("��������Ҫ�ⶳ��ID.\n");
	scanf("%s", ID);
	People*data = (People*)rbtree_lookup(tree, ID);
	if (data)
	{
		data->key = 1;
		printf("�ѽⶳ\n");
	}
	else
		printf("����,%s������.\n", ID);
	END
}

void printf_people(struct rbtree_node* node)
{
	if (!node) return;
	People*data = (People*)node->data;
	printf("ID:               %s\n", data->ID);
	printf("�����:           %s\n", data->LCardNumber);
	printf("����:             %s\n", data->Name);
	printf("�ɽ����:         %d\n", data->AllAvaliableBorrowNum - data->BorrowNum);
	printf("�ɽ�״̬:             %s\n", data->key ? "��" : "��");
	if (data->Category)
		printf("�༶:             %d\n", data->clas);
	printf("\n");
	for (int i = 0; i < data->BorrowNum; i++)
		printf("                  %s\n", data->BorrowName[i]);
	printf("\n");
	if (node->left)
		printf_people(node->left);
	if (node->right)
		printf_people(node->right);
}

void list_people(rbtree *tree)
{
	START
		printf_people(tree->root);
	END
}

void creat_only(Store* sdata, People *pdata, Book *bdata)
{
	strcpy(bdata->OnlyBorrowCode, pdata->ID);
	strcat(bdata->OnlyBorrowCode, sdata->Index);
	char temp[3];
	itoa(pdata->BorrowNum, temp, 10);
	strcat(bdata->OnlyBorrowCode, temp);
}

void borrow_book(rbtree *stree, rbtree *ptree, rbtree *btree)
{
	START
		char ID[MAX_NAME], Borrow_ID[MAX_NAME];
	printf("���������ID.\n");
	scanf("%s", ID);
	People*pdata = (People*)rbtree_lookup(ptree, ID);
	if (pdata)
	{
		if (pdata->key)
		{
			printf("�������鼮���.\n", Borrow_ID);
			scanf("%s", Borrow_ID);
			Store*sdata = (Store*)rbtree_lookup(stree, Borrow_ID);
			if (!sdata)
			{
				printf("%s������.\n", Borrow_ID);
				END
					return;
			}
			if (pdata->BorrowNum >= pdata->AllAvaliableBorrowNum)
			{
				printf("�Բ�������������Ŀ�Ѵ�����.\n");
				END
					return;
			}

			if ((sdata->All_Have - sdata->Borrownum) > 0)
			{
				Book*bdata = (Book*)malloc(sizeof(Book));
				write_date(&(bdata->Borrow_Date), "�������������.");
				strcpy(bdata->Book_Name, sdata->Book_Name);
				strcpy(bdata->Index, sdata->Index);
				strcpy(bdata->LCardNumber, pdata->LCardNumber);
				bdata->Price = sdata->Price;
				creat_only(sdata, pdata, bdata);
				rbtree_insert(btree, bdata->OnlyBorrowCode, bdata);
				(sdata->AllBorrow)++;
				(sdata->Current_Have)--;
				(sdata->Borrownum)++;
				strcpy(pdata->BorrowID[pdata->BorrowNum], sdata->Index);
				strcpy(pdata->BorrowName[pdata->BorrowNum], sdata->Book_Name);
				(pdata->BorrowNum)++;
				all_borrowing++;
				printf("�ѽ��\n");
			}
			else
				printf("���ѽ���\n");
		}
		else
			printf(" �Բ�������˺��Ѷ���\n");
	}
	else
		printf("%s������.\n", ID);
	END
}

void printf_borrow(struct rbtree_node* node)
{
	if (!node) return;
	Book*bdata = (Book*)node->data;
	printf("���:           %s\n", bdata->Index);
	printf("����:           %s\n", bdata->Book_Name);
	printf("�����:         %s\n", bdata->LCardNumber);
	printf("��������:       "); read_date(bdata->Borrow_Date);
	printf("��������:       %s\n", bdata->OnlyBorrowCode);
	printf("\n\n");
	if (node->left)
		printf_borrow(node->left);
	if (node->right)
		printf_borrow(node->right);
}

void list_borrow_book(rbtree *tree)
{
	START
		printf_borrow(tree->root);
	END
}

void delte_sign(char A[MAX_AVALIABLE_NUM][MAX_NAME], char D[], int num)
{
	int i = 0;
	for (int i = 0; i < num; i++)
	{
		if (!strcmp(A[i], D))
		{
			strcpy(A[i], A[num]);
			return;
		}
	}
}

int find_sign(char A[MAX_AVALIABLE_NUM][MAX_NAME], char D[], int num)
{
	int i = 0;
	for (int i = 0; i < num; i++)
	{
		if (!strcmp(A[i], D))
		{
			return 1;
		}
	}
	return 0;
}


void return_book(rbtree *stree, rbtree *ptree, rbtree *btree)
{
	START
		char ID[MAX_NAME], Borrow_ID[MAX_NAME];
	printf("����������ID.\n");
	scanf("%s", ID);
	People*pdata = (People*)rbtree_lookup(ptree, ID);
	if (pdata)
	{
		printf("��������.\n", Borrow_ID);
		scanf("%s", Borrow_ID);
		Store*sdata = (Store*)rbtree_lookup(stree, Borrow_ID);
		if (!sdata)
		{
			printf("%s������.\n", Borrow_ID);
			END
				return;
		}
		int i = 0;
		for (i = 0; i < pdata->BorrowNum; i++)
		{
			if (!strcmp(pdata->BorrowID[i], Borrow_ID))
				break;
			if (i + 1 == pdata->BorrowNum) {
				printf("������û���Ȿ��!\n");
				END;
				return;
			}
		}
		char result[MAX_NAME * 2 + 2];
		strcpy(result, pdata->ID);
		strcat(result, sdata->Index);
		char temp[3];
		itoa(i, temp, 10);
		strcat(result, temp);
		Book*bdata = (Book*)rbtree_lookup(btree, result);
		(sdata->Borrownum)--;
		(sdata->Current_Have)++;
		(pdata->BorrowNum)--;
		delte_sign(pdata->BorrowName, bdata->Book_Name, pdata->BorrowNum);
		delte_sign(pdata->BorrowID, bdata->Index, pdata->BorrowNum);
		rbtree_remove(btree, result);
		all_borrowing--;
		printf("�ѻ���\n");
	}
	else
		printf("%s������.\n", ID);
	END
}

void spt(void *node, FILE*fp)
{
	rbtree_node *temp = (rbtree_node*)node;
	Store*sdata = (Store*)temp->data;
	fprintf(fp, "%d ", sdata->AllBorrow);
	fprintf(fp, "%d ", sdata->All_Have);
	fprintf(fp, "%s ", sdata->Author_Name);
	fprintf(fp, "%s ", sdata->Book_Name);
	fprintf(fp, "%d ", sdata->Borrownum);
	fprintf(fp, "%s ", sdata->Category);
	fprintf(fp, "%d ", sdata->Current_Have);
	fprintf(fp, "%s ", sdata->Index);
	fprintf(fp, "%s ", sdata->Press);
	fprintf(fp, "%d ", sdata->Price);
	fprintf(fp, "%d %d %d\n", sdata->Press_Date.Year, sdata->Press_Date.Month, sdata->Press_Date.Day);
}
void ppt(void *node, FILE*fp)
{
	rbtree_node *temp = (rbtree_node*)node;
	People*pdata = (People*)temp->data;
	fprintf(fp, "%d ", pdata->AllAvaliableBorrowNum);
	fprintf(fp, "%d ", pdata->BorrowNum);
	int i = 0;
	for (; i < pdata->BorrowNum; i++)
	{
		fprintf(fp, "%s ", pdata->BorrowID[i]);
		fprintf(fp, "%s ", pdata->BorrowName[i]);
	}
	fprintf(fp, "%d ", pdata->Category);
	fprintf(fp, "%d ", pdata->clas);
	fprintf(fp, "%s ", pdata->ID);
	fprintf(fp, "%d ", pdata->key);
	fprintf(fp, "%s ", pdata->LCardNumber);
	fprintf(fp, "%s \n", pdata->Name);
}
void bpt(void *node, FILE*fp)
{
	rbtree_node *temp = (rbtree_node*)node;
	Book*bdata = (Book*)temp->data;
	fprintf(fp, "%s ", bdata->Book_Name);
	fprintf(fp, "%s ", bdata->OnlyBorrowCode);
	fprintf(fp, "%d %d %d", bdata->Borrow_Date.Year, bdata->Borrow_Date.Month, bdata->Borrow_Date.Day);
	fprintf(fp, "%s ", bdata->LCardNumber);
	fprintf(fp, "%s ", bdata->Index);
	fprintf(fp, "%d\n", bdata->Price);
}
void srt(void *node, FILE*fp)
{
	rbtree_node *temp = (rbtree_node*)node;
	Store*sdata = (Store*)malloc(sizeof(Store));
	fscanf(fp, "%d", &(sdata->AllBorrow));
	fscanf(fp, "%d", &(sdata->All_Have));
	fscanf(fp, "%s", sdata->Author_Name);
	fscanf(fp, "%s", sdata->Book_Name);
	fscanf(fp, "%d", &(sdata->Borrownum));
	fscanf(fp, "%s", sdata->Category);
	fscanf(fp, "%d", &(sdata->Current_Have));
	fscanf(fp, "%s", sdata->Index);
	fscanf(fp, "%s", sdata->Press);
	fscanf(fp, "%d", &(sdata->Price));
	fscanf(fp, "%d %d %d", &(sdata->Press_Date.Year), &(sdata->Press_Date.Month), &(sdata->Press_Date.Day));
	temp->key = sdata->Index;
	temp->data = sdata;
}
void prt(void *node, FILE*fp)
{
	rbtree_node *temp = (rbtree_node*)node;
	People*pdata = (People*)malloc(sizeof(People));
	fscanf(fp, "%d", &(pdata->AllAvaliableBorrowNum));
	fscanf(fp, "%d", &(pdata->BorrowNum));
	int i = 0;
	for (; i < pdata->BorrowNum; i++)
	{
		fscanf(fp, "%s", pdata->BorrowID[i]);
		fscanf(fp, "%s", pdata->BorrowName[i]);
	}
	fscanf(fp, "%d", &(pdata->Category));
	fscanf(fp, "%d", &(pdata->clas));
	fscanf(fp, "%s", pdata->ID);
	fscanf(fp, "%d", &(pdata->key));
	fscanf(fp, "%s", pdata->LCardNumber);
	fscanf(fp, "%s", pdata->Name);
	temp->key = pdata->ID;
	temp->data = pdata;
}
void brt(void *node, FILE*fp)
{
	rbtree_node *temp = (rbtree_node*)node;
	Book*bdata = (Book*)malloc(sizeof(Book));
	fscanf(fp, "%s", bdata->Book_Name);
	fscanf(fp, "%s", bdata->OnlyBorrowCode);
	fscanf(fp, "%d %d %d", &(bdata->Borrow_Date.Year), &(bdata->Borrow_Date.Month), &(bdata->Borrow_Date.Day));
	fscanf(fp, "%s", bdata->LCardNumber);
	fscanf(fp, "%s", bdata->Index);
	fscanf(fp, "%d", &(bdata->Price));
	temp->key = bdata->OnlyBorrowCode;
	temp->data = bdata;

}

void save(rbtree *stree, rbtree *ptree, rbtree *btree)
{
	START
		tree2dot(stree, "STREE", spt);
	tree2dot(ptree, "PTREE", ppt);
	tree2dot(btree, "BTREE", bpt);
	FILE*fp = fopen("ALL", "w");
	fprintf(fp, "%d\n", all_book);
	fprintf(fp, "%d\n", all_people);
	fprintf(fp, "%d\n", all_borrowing);
	fclose(fp);
	printf("�ѱ���\n\n");
	END
}
void empty(rbtree *stree, rbtree *ptree, rbtree *btree);
void load(rbtree *stree, rbtree *ptree, rbtree *btree)
{
	START
		empty(stree, ptree, btree);
	treefdot(stree, "STREE", srt);
	treefdot(ptree, "PTREE", prt);
	treefdot(btree, "BTREE", brt);
	FILE*fp = fopen("ALL", "r");
	if (!fp)
	{
		printf("�����ļ�������.\n");
		END;
		return;
	}
	fscanf(fp, "%d", &all_book);
	fscanf(fp, "%d", &all_people);
	fscanf(fp, "%d", &all_borrowing);
	fclose(fp);
	printf("������\n\n");
	END
}

void help()
{
	START
		printf("1.�������\n2.����\n3.�༭�������\n4.ɾ����\n5.�г���\n6.��ӽ���֤\n7.����\
����֤\n8.ע��\n9.��ʧ\n10.�ⶳ\n11.�г����г�Ա\n12.����\n13.�г������\n14.����\n15.��������\n16.��������\n17.��������\n20.ɾ����·\n");
	END;
}

void empty_tree(rbtree_node *node)
{
	if (node)
	{
		empty_tree(node->left);
		empty_tree(node->right);
		free(node->data);
		free(node);
	}
}

void empty(rbtree *stree, rbtree *ptree, rbtree *btree)
{
	START
		empty_tree(stree->root);
	empty_tree(ptree->root);
	empty_tree(btree->root);
	stree->root = NULL;
	ptree->root = NULL;
	btree->root = NULL;
	all_book = all_borrowing = all_people = 0;
	printf("�����\n");
	END
}


int cmp(const void *a, const void *b)
{
	Store *c = (Store*)a;
	Store *d = (Store*)b;
	return (c->AllBorrow < d->AllBorrow);
}
int current = 0;
void list_book(rbtree_node*node, Store*data)
{
	if (!node) return;
	data[current] = *((Store*)node->data);
	current++;
	list_book(node->left, data);
	list_book(node->right, data);
}

void sort_book(rbtree *tree)
{
	START
		if (!all_book) { END return; }
	Store *data = (Store*)malloc(sizeof(Store)*all_book);
	list_book(tree->root, data);
	int i = 0;
	qsort(data, all_book, sizeof(Store), cmp);
	for (int i = 0; i < all_book; i++)
	{
		printf("����:                    %s\n", data[i].Book_Name);
		printf("����:                    %s\n", data[i].Author_Name);
		printf("������:                  %s\n", data[i].Press);
		printf("���:                    %s\n", data[i].Category);
		printf("��������:                "); read_date(data[i].Press_Date);
		printf("�۸�:                    %d\n", data[i].Price);
		printf("�ܿ��:                  %d\n", data[i].All_Have);
		printf("���:                    %d\n", data[i].Borrownum);
		printf("�ڿ�:                    %d\n", data[i].All_Have - data[i].Borrownum);
		printf("****************************************************************\n");
		printf("�ܽ��:                  %d\n\n", data[i].AllBorrow);
		printf("****************************************************************\n");
	}
	current = 0;
	free(data);
	END
}

void randbook(rbtree *tree)
{
	START
		int n;
	srand(time(NULL));
	printf("Numbers\n");
	scanf("%d", &n);
	/*
	if (!tree->root)
	{
	Store*data = (Store*)malloc(sizeof(Store));
	itoa(0, data->Index, 10);
	itoa(0, data->Book_Name, 10);
	itoa(0, data->Author_Name, 10);
	itoa(0, data->Press, 10);
	itoa(0, data->Category, 10);
	data->Press_Date.Day = rand() % 31;
	data->Press_Date.Month = rand() % 12;
	data->Press_Date.Year = rand() % 2017;
	data->Price = rand() % 1000;
	data->All_Have = rand() % 10;
	data->Borrownum = 0;
	data->Current_Have = data->All_Have;
	data->AllBorrow = 0;
	all_book++;
	}*/
	for (int i = 0; i < n; i++)
	{

		Store*data = (Store*)malloc(sizeof(Store));
		itoa(i, data->Index, 10);
		if (rbtree_lookup(tree, data->Index))
			free(data);
		else
		{
			itoa(i, data->Book_Name, 10);
			itoa(i, data->Author_Name, 10);
			itoa(i, data->Press, 10);
			itoa(i / 100, data->Category, 10);
			data->Press_Date.Day = rand() % 31;
			data->Press_Date.Month = rand() % 12;
			data->Press_Date.Year = rand() % 2017;
			data->Price = rand() % 1000;
			data->All_Have = rand() % 10;
			data->Borrownum = 0;
			data->Current_Have = data->All_Have;
			data->AllBorrow = 0;
			rbtree_insert(tree, data->Index, data);
			all_book++;
			//printf("�����\n\n");
		}
	}
	printf("�ɹ� %d\n", all_book);
	END
}
int top; int real = 0;
void __printf_store(struct rbtree_node* node)
{
	if (!node) return;
	Store*head = (Store*)node->data;
	printf("����:             %s\n", head->Book_Name);
	printf("����:             %s\n", head->Author_Name);
	printf("������:           %s\n", head->Press);
	printf("���:             %s\n", head->Category);
	printf("��������:         "); read_date(head->Press_Date);
	printf("�۸�:             %d\n", head->Price);
	printf("���:             %d\n", head->All_Have);
	printf("���:             %d\n", head->Borrownum);
	printf("�ڿ�:             %d\n", head->All_Have - head->Borrownum);
	printf("�ܽ��:           %d\n\n\n", head->AllBorrow);
	real++;
	if (node->left && real<top)
		__printf_store(node->left);
	if (node->right && real<top)
		__printf_store(node->right);
}

void list_top(rbtree*tree)
{

	START
		printf("Nmbers\n");
	scanf("%d", &top);
	__printf_store(tree->root);
	real = 0;
	END
}
#pragma once
