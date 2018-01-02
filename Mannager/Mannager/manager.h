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
	char Index[MAX_NAME];          //编号
	char Book_Name[MAX_NAME];      //书名
	char Author_Name[MAX_NAME];    //作者名
	char Press[MAX_NAME];          //出版社
	char Category[MAX_NAME];       //类别
	Date Press_Date;
	int Price;
	int Borrownum;
	int All_Have;
	int Current_Have;
	int AllBorrow;
}Store;

typedef struct book_information {
	char OnlyBorrowCode[MAX_NAME * 2 + 2];
	char Index[MAX_NAME];          //编号
	char Book_Name[MAX_NAME];      //书名
	char LCardNumber[MAX_NAME];    //借书证号
	Date Borrow_Date;
	Date Return_Date;
	int Price;
}Book;

typedef struct people_information {
	char LCardNumber[MAX_NAME];    //借书证号
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
		printf("请输入%d到%d之间的值.\n", start, end);
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
	printf("%s例如 1998 1 1\n", B);
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
	printf("请输入书籍编号.\n");
	scanf("%s", data->Index);
	if (rbtree_lookup(tree, data->Index))
		printf("错误！书籍已存在！\n"), free(data);
	else
	{
		printf("请输入书名.\n");
		scanf("%s", data->Book_Name);
		printf("请输入作者.\n");
		scanf("%s", data->Author_Name);
		printf("请输入出版社.\n");
		scanf("%s", data->Press);
		printf("请输入类别.\n");
		scanf("%s", data->Category);
		write_date(&(data->Press_Date), "请输入出版日期.");
		printf("请输入价格.\n");
		scanf("%d", &(data->Price));
		printf("请输入库存.\n");
		scanf("%d", &(data->All_Have));
		printf("请输入外借数.\n");
		scanf("%d", &(data->Borrownum));
		data->Current_Have = data->All_Have - data->Borrownum;
		printf("请输入总借出数.\n");
		scanf("%d", &(data->AllBorrow));
		rbtree_insert(tree, data->Index, data);
		all_book++;
		printf("已添加\n\n");
	}
	END
}

void find_book_store(rbtree *tree)
{
	START
		char temp[MAX_NAME];
	printf("请输入需要寻找的书籍编号.\n");
	scanf("%s", temp);
	Store*data = (Store*)rbtree_lookup(tree, temp);
	if (data)
	{
		printf("书名:                   %s\n", data->Book_Name);
		printf("作者:                   %s\n", data->Author_Name);
		printf("出版社:                 %s\n", data->Press);
		printf("类别:                   %s\n", data->Category);
		printf("出版日期:               "); read_date(data->Press_Date);
		printf("价格:                   %d\n", data->Price);
		printf("库存:                   %d\n", data->All_Have);
		printf("借出:                   %d\n", data->Borrownum);
		printf("在库:                   %d\n", data->All_Have - data->Borrownum);
		printf("总借出:                 %d\n", data->AllBorrow);
		END
			return;
	}
	printf("%s 不存在!\n", temp);
	END
}

void edit_book_store(rbtree*tree)
{
	START
		char Index[MAX_NAME];
	printf("请输入待编辑书籍编号.\n");
	scanf("%s", Index);
	Store*data = (Store*)rbtree_lookup(tree, Index);
	printf("请输入书名.\n");
	scanf("%s", data->Book_Name);
	printf("请输入作者名.\n");
	scanf("%s", data->Author_Name);
	printf("请输入出版社.\n");
	scanf("%s", data->Press);
	printf("请输入类别.\n");
	scanf("%s", data->Category);
	write_date(&(data->Press_Date), "请输入出版日期.");
	printf("请输入价格.\n");
	scanf("%d", &(data->Price));
	printf("请输入库存.\n");
	scanf("%d", &(data->All_Have));
	printf("请输入外借数.\n");
	scanf("%d", &(data->Borrownum));
	data->Current_Have = data->All_Have - data->Borrownum;
	printf("请输入总借出数.\n");
	scanf("%d", &(data->AllBorrow));
	printf("已修改\n");
	END
}

void delete_book_store(rbtree*tree)
{
	START
		char Index[MAX_NAME];
	printf("请输入需要删除的书籍编号.\n");
	scanf("%s", Index);
	Store*data = (Store*)rbtree_lookup(tree, Index);
	if (data)
	{
		rbtree_remove(tree, Index);
		all_book--;
		printf("%s已删除!\n", Index);
	}
	else
		printf("错误!%s不存在!\n", Index);
	END
}

void printf_store(struct rbtree_node* node)
{
	printf("书名\t\t\t作者\t\t出版社\t\t类别\t出版日期\t价格\t库存\t借出\t在库\t总借出\t\n\n");
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
	printf("请输入需要添加的ID.\n");
	scanf("%s", data->ID);
	if (rbtree_lookup(tree, data->ID))
		printf("错误!用户已存在!\n"), free(data);
	else
	{
		printf("请输入用户类别.   1.学生   0.教师\n");
		data->Category = avaliable(0, 1, 3);
		printf("请输入姓名.\n");
		scanf("%s", data->Name);
		printf("请输入借书号.\n");
		scanf("%s", data->LCardNumber);
		if (data->Category)
		{
			printf("请输入班级\n");
			scanf("%d", &(data->clas));
			data->AllAvaliableBorrowNum = MAX_AVALIABLE_NUM / 2;
		}
		else
			data->AllAvaliableBorrowNum = MAX_AVALIABLE_NUM;
		data->BorrowNum = 0;
		data->key = 1;
		rbtree_insert(tree, data->ID, data);
		all_people++;
		printf("已添加\n\n\n");
	}
	END
}

void find_people(rbtree *tree)
{
	START
		char ID[MAX_NAME];
	printf("请输入查找ID.\n");
	scanf("%s", ID);
	People*data = (People*)rbtree_lookup(tree, ID);
	if (data)
	{
		printf("ID:               %s\n", data->ID);
		printf("借书号:           %s\n", data->LCardNumber);
		printf("姓名:             %s\n", data->Name);
		printf("可借次数:         %d\n", data->AllAvaliableBorrowNum - data->BorrowNum);
		if (data->Category)
			printf("班级:             %d\n", data->clas);
		printf("\n");
		for (int i = 0; i < data->BorrowNum; i++)
			printf("                  %s\n", data->BorrowName[i]);
		printf("\n");
	}
	else
		printf("%s不存在.\n", ID);
	END
}

void delete_people(rbtree *tree)
{
	START
		char ID[MAX_NAME];
	printf("请输入需要删除的ID.\n");
	scanf("%s", ID);
	People*data = (People*)rbtree_lookup(tree, ID);
	if (data)
	{
		rbtree_remove(tree, ID);
		all_people--;
		printf("已删除\n");
	}
	else
		printf("%s不存在.\n", ID);
	END;
}

void lose(rbtree *tree)
{
	START
		char ID[MAX_NAME];
	printf("请输入需要挂失的ID.\n");
	scanf("%s", ID);
	People*data = (People*)rbtree_lookup(tree, ID);
	if (data)
	{
		data->key = 0;
		printf("已挂失\n");
	}
	else
		printf("错误,%s不存在.\n", ID);
	END
}

void remain(rbtree *tree)
{
	START
		char ID[MAX_NAME];
	printf("请输入需要解冻的ID.\n");
	scanf("%s", ID);
	People*data = (People*)rbtree_lookup(tree, ID);
	if (data)
	{
		data->key = 1;
		printf("已解冻\n");
	}
	else
		printf("错误,%s不存在.\n", ID);
	END
}

void printf_people(struct rbtree_node* node)
{
	if (!node) return;
	People*data = (People*)node->data;
	printf("ID:               %s\n", data->ID);
	printf("借书号:           %s\n", data->LCardNumber);
	printf("姓名:             %s\n", data->Name);
	printf("可借次数:         %d\n", data->AllAvaliableBorrowNum - data->BorrowNum);
	printf("可借状态:             %s\n", data->key ? "能" : "否");
	if (data->Category)
		printf("班级:             %d\n", data->clas);
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
	printf("请输入你的ID.\n");
	scanf("%s", ID);
	People*pdata = (People*)rbtree_lookup(ptree, ID);
	if (pdata)
	{
		if (pdata->key)
		{
			printf("请输入书籍编号.\n", Borrow_ID);
			scanf("%s", Borrow_ID);
			Store*sdata = (Store*)rbtree_lookup(stree, Borrow_ID);
			if (!sdata)
			{
				printf("%s不存在.\n", Borrow_ID);
				END
					return;
			}
			if (pdata->BorrowNum >= pdata->AllAvaliableBorrowNum)
			{
				printf("对不起，您的所借数目已达上限.\n");
				END
					return;
			}

			if ((sdata->All_Have - sdata->Borrownum) > 0)
			{
				Book*bdata = (Book*)malloc(sizeof(Book));
				write_date(&(bdata->Borrow_Date), "请输入借书日期.");
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
				printf("已借出\n");
			}
			else
				printf("书已借完\n");
		}
		else
			printf(" 对不起，你的账号已冻结\n");
	}
	else
		printf("%s不存在.\n", ID);
	END
}

void printf_borrow(struct rbtree_node* node)
{
	if (!node) return;
	Book*bdata = (Book*)node->data;
	printf("编号:           %s\n", bdata->Index);
	printf("书名:           %s\n", bdata->Book_Name);
	printf("借书号:         %s\n", bdata->LCardNumber);
	printf("借书日期:       "); read_date(bdata->Borrow_Date);
	printf("借书索引:       %s\n", bdata->OnlyBorrowCode);
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
	printf("请输入您的ID.\n");
	scanf("%s", ID);
	People*pdata = (People*)rbtree_lookup(ptree, ID);
	if (pdata)
	{
		printf("请输入编号.\n", Borrow_ID);
		scanf("%s", Borrow_ID);
		Store*sdata = (Store*)rbtree_lookup(stree, Borrow_ID);
		if (!sdata)
		{
			printf("%s不存在.\n", Borrow_ID);
			END
				return;
		}
		int i = 0;
		for (i = 0; i < pdata->BorrowNum; i++)
		{
			if (!strcmp(pdata->BorrowID[i], Borrow_ID))
				break;
			if (i + 1 == pdata->BorrowNum) {
				printf("错误，你没有这本书!\n");
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
		printf("已还书\n");
	}
	else
		printf("%s不存在.\n", ID);
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
	printf("已保存\n\n");
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
		printf("错误，文件不存在.\n");
		END;
		return;
	}
	fscanf(fp, "%d", &all_book);
	fscanf(fp, "%d", &all_people);
	fscanf(fp, "%d", &all_borrowing);
	fclose(fp);
	printf("已载入\n\n");
	END
}

void help()
{
	START
		printf("1.添加新书\n2.找书\n3.编辑库存资料\n4.删除书\n5.列出书\n6.添加借书证\n7.查找\
借书证\n8.注销\n9.挂失\n10.解冻\n11.列出所有成员\n12.借书\n13.列出借的书\n14.还书\n15.加载数据\n16.保存数据\n17.人气排序\n20.删库跑路\n");
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
	printf("已清空\n");
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
		printf("书名:                    %s\n", data[i].Book_Name);
		printf("作者:                    %s\n", data[i].Author_Name);
		printf("出版社:                  %s\n", data[i].Press);
		printf("类别:                    %s\n", data[i].Category);
		printf("出版日期:                "); read_date(data[i].Press_Date);
		printf("价格:                    %d\n", data[i].Price);
		printf("总库存:                  %d\n", data[i].All_Have);
		printf("借出:                    %d\n", data[i].Borrownum);
		printf("在库:                    %d\n", data[i].All_Have - data[i].Borrownum);
		printf("****************************************************************\n");
		printf("总借出:                  %d\n\n", data[i].AllBorrow);
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
			//printf("已添加\n\n");
		}
	}
	printf("成功 %d\n", all_book);
	END
}
int top; int real = 0;
void __printf_store(struct rbtree_node* node)
{
	if (!node) return;
	Store*head = (Store*)node->data;
	printf("书名:             %s\n", head->Book_Name);
	printf("作者:             %s\n", head->Author_Name);
	printf("出版社:           %s\n", head->Press);
	printf("类别:             %s\n", head->Category);
	printf("出版日期:         "); read_date(head->Press_Date);
	printf("价格:             %d\n", head->Price);
	printf("库存:             %d\n", head->All_Have);
	printf("借出:             %d\n", head->Borrownum);
	printf("在库:             %d\n", head->All_Have - head->Borrownum);
	printf("总借出:           %d\n\n\n", head->AllBorrow);
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
