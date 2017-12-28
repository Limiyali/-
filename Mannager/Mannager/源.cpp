#include <stdio.h>
#include <stdlib.h>
#include <string>
#define MAX_NAME 21
#define MAX_AVALIABLE_NUM 10
#define START printf("------------------------------------start----------------------------------\n\n");
#define END printf("--------------------------------------end----------------------------------\n\n");
#pragma warning(disable:4996)

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

typedef struct SInformation {
	struct SInformation*next;
	Store value;
}SList;

typedef struct BInformation {
	struct BInformation*next;
	Book value;
}BList;

typedef struct PInformation {
	struct PInformation*next;
	People value;
}PList;

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
	printf("%d %d %d\n", A.Year, A.Month, A.Day);
}

void init(SList*head1, BList*head2, PList*head3)
{
	head1->next = NULL;
	head2->next = NULL;
	head3->next = NULL;

	strcpy(head1->value.Index, "0");
	strcpy(head1->value.Book_Name, "0");
	strcpy(head1->value.Author_Name, "0");
	strcpy(head1->value.Press, "0");
	strcpy(head1->value.Category, "0");
	init_date(&(head1->value.Press_Date));
	head1->value.Price = 0;
	head1->value.Borrownum = 0;
	head1->value.All_Have = 0;
	head1->value.Current_Have = 0;
	head1->value.AllBorrow = 0;

	strcpy(head2->value.Index, "0");
	strcpy(head2->value.Book_Name, "0");
	strcpy(head2->value.LCardNumber, "0");
	init_date(&(head2->value.Borrow_Date));
	init_date(&(head2->value.Return_Date));
	head2->value.Price = 0;

	strcpy(head3->value.LCardNumber, "0");
	strcpy(head3->value.Name, "0");
	strcpy(head3->value.ID, "0");
	head3->value.clas = -1;
}

SList* find_store_book(SList *head, char Find[])
{
	while (head->next)
		if (!strcmp(head->next->value.Index, Find))
			return head;
		else
			head = head->next;
	return NULL;
}

void add_book_store(SList *head)
{
	START
		SList *added = (SList*)malloc(sizeof(SList));
	printf("请输入书籍编号.\n");
	scanf("%s", added->value.Index);
	if (find_store_book(head, added->value.Index))
		printf("错误！书籍已存在！\n"), free(added);
	else
	{
		printf("请输入书名.\n");
		scanf("%s", added->value.Book_Name);
		printf("请输入作者.\n");
		scanf("%s", added->value.Author_Name);
		printf("请输入出版社.\n");
		scanf("%s", added->value.Press);
		printf("请输入类别.\n");
		scanf("%s", added->value.Category);
		write_date(&(added->value.Press_Date), "请输入出版日期.");
		printf("请输入价格.\n");
		scanf("%d", &(added->value.Price));
		printf("请输入库存.\n");
		scanf("%d", &(added->value.All_Have));
		printf("请输入外借数.\n");
		scanf("%d", &(added->value.Borrownum));
		added->value.Current_Have = added->value.All_Have - added->value.Borrownum;
		printf("请输入总借出数.\n");
		scanf("%d", &(added->value.AllBorrow));
		while (head->next)   head = head->next;
		added->next = NULL;
		head->next = added;
		printf("已添加\n\n");
	}
	END
}

void find_book_store(SList*head)
{
	START
		char temp[MAX_NAME];
	printf("请输入需要寻找的书籍编号.\n");
	scanf("%s", temp);
	SList *result = find_store_book(head, temp);
	if (result)
	{
		result = result->next;
		printf("书名:                   %s\n", result->value.Book_Name);
		printf("作者:                   %s\n", result->value.Author_Name);
		printf("出版社:                 %s\n", result->value.Press);
		printf("类别:                   %s\n", result->value.Category);
		printf("出版日期:               "); read_date(result->value.Press_Date);
		printf("价格:                   %d\n", result->value.Price);
		printf("库存:                   %d\n", result->value.All_Have);
		printf("借出:                   %d\n", result->value.Borrownum);
		printf("在库:                   %d\n", result->value.All_Have - result->value.Borrownum);
		printf("总借出:                 %d\n", result->value.AllBorrow);
		return;
	}
	printf("%s 不存在!\n", temp);
	END
}

void edit_book_store(SList *head)
{
	START
		char Index[MAX_NAME];
	printf("请输入待编辑书籍编号.\n");
	scanf("%s", Index);
	SList *result = find_store_book(head, Index);
	result = result->next;
	printf("请输入书名.\n");
	scanf("%s", result->value.Book_Name);
	printf("请输入作者名.\n");
	scanf("%s", result->value.Author_Name);
	printf("请输入出版社.\n");
	scanf("%s", result->value.Press);
	printf("请输入类别.\n");
	scanf("%s", result->value.Category);
	write_date(&(result->value.Press_Date), "请输入出版日期.");
	printf("请输入价格.\n");
	scanf("%d", &(result->value.Price));
	printf("请输入库存.\n");
	scanf("%d", &(result->value.All_Have));
	printf("请输入外借数.\n");
	scanf("%d", &(result->value.Borrownum));
	result->value.Current_Have = result->value.All_Have - result->value.Borrownum;
	printf("请输入总借出数.\n");
	scanf("%d", &(result->value.AllBorrow));
	printf("已修改\n");
	END
}

void delete_book_store(SList*head)
{
	START
		char Index[MAX_NAME];
	printf("请输入需要删除的书籍编号.\n");
	scanf("%s", Index);
	SList *pre = find_store_book(head, Index);
	SList *current = pre->next;
	if (current)
	{
		pre->next = current->next;
		free(current);
		printf("%s已删除!\n", Index);
	}
	else
		printf("错误!%s不存在!\n", Index);
	END
}

void list_book_store(SList *head)
{
	START
		while (head->next)
		{
			head = head->next;
			printf("书名:             %s\n", head->value.Book_Name);
			printf("作者:             %s\n", head->value.Author_Name);
			printf("出版社:           %s\n", head->value.Press);
			printf("类别:             %s\n", head->value.Category);
			printf("出版日期:         "); read_date(head->value.Press_Date);
			printf("价格:             %d\n", head->value.Price);
			printf("库存:             %d\n", head->value.All_Have);
			printf("借出:             %d\n", head->value.Borrownum);
			printf("在库:             %d\n", head->value.All_Have - head->value.Borrownum);
			printf("总借出:           %d\n\n\n", head->value.AllBorrow);
		}
	END
}

PList*find_people_information_byID(PList *head, char ID[])
{
	while (head->next)
	{
		if (!(strcmp(head->next->value.ID, ID)))
			return head;
		else
			head = head->next;
	}
	return NULL;
}

void add_people(PList *head)
{
	START
		PList *temp = (PList*)malloc(sizeof(PList));
	temp->next = NULL;
	char ID[MAX_NAME];
	printf("请输入需要添加的ID.\n");
	scanf("%s", temp->value.ID);
	if (find_people_information_byID(head, temp->value.ID))
		printf("错误!用户已存在!\n"), free(temp);
	else
	{
		printf("请输入用户类别.   1.学生   0.教师\n");
		temp->value.Category = avaliable(0, 1, 3);
		printf("请输入姓名.\n");
		scanf("%s", temp->value.Name);
		printf("请输入借书号.\n");
		scanf("%s", temp->value.LCardNumber);
		if (temp->value.Category)
		{
			printf("请输入班级\n");
			scanf("%d", &(temp->value.clas));
			temp->value.AllAvaliableBorrowNum = MAX_AVALIABLE_NUM / 2;
		}
		else
			temp->value.AllAvaliableBorrowNum = MAX_AVALIABLE_NUM;
		temp->value.BorrowNum = 0;
		temp->value.key = 1;
		while (head->next) head = head->next;
		head->next = temp;
		printf("已添加\n\n\n");
	}
	END
}

void find_people(PList*head)
{
	START
		char ID[MAX_NAME];
	printf("请输入查找ID.\n");
	scanf("%s", ID);
	PList*current = find_people_information_byID(head, ID);
	if (current)
	{
		current = current->next;
		printf("ID:               %s\n", current->value.ID);
		printf("借书号:           %s\n", current->value.LCardNumber);
		printf("姓名:             %s\n", current->value.Name);
		printf("可借次数:         %d\n", current->value.AllAvaliableBorrowNum - current->value.BorrowNum);
		if (current->value.Category)
			printf("班级:             %d\n", current->value.clas);
		printf("\n");
		for (int i = 0; i < current->value.BorrowNum; i++)
			printf("                  %s\n", current->value.BorrowName[i]);
		printf("\n");
	}
	else
		printf("%s不存在.\n", ID);
	END
}

void delete_people(PList*head)
{
	START
		char ID[MAX_NAME];
	printf("请输入需要删除的ID.\n");
	scanf("%s", ID);
	PList*result = find_people_information_byID(head, ID);
	if (result)
	{
		PList*pre = result;
		result = result->next;
		pre->next = result->next;
		free(result);
		printf("已删除\n");
	}
	else
		printf("%s不存在.\n", ID);
	END;
}

void lose(PList*head)
{
	START
		char ID[MAX_NAME];
	printf("请输入需要挂失的ID.\n");
	scanf("%s", ID);
	PList*result = find_people_information_byID(head, ID);
	if (result)
	{
		result = result->next;
		result->value.key = 0;
		printf("已挂失\n");
	}
	else
		printf("错误,%s不存在.\n", ID);
	END
}

void remain(PList*head)
{
	START
		char ID[MAX_NAME];
	printf("请输入需要解冻的ID.\n");
	scanf("%s", ID);
	PList*result = find_people_information_byID(head, ID);
	if (result)
	{
		result = result->next;
		result->value.key = 1;
		printf("已解冻\n");
	}
	else
		printf("错误,%s不存在.\n", ID);
	END
}

void list_people(PList *head)
{
	START
		while (head->next)
		{
			head = head->next;
			printf("ID:               %s\n", head->value.ID);
			printf("借书号:           %s\n", head->value.LCardNumber);
			printf("姓名:             %s\n", head->value.Name);
			printf("可借次数:         %d\n", head->value.AllAvaliableBorrowNum - head->value.BorrowNum);
			if (head->value.Category)
			    printf("班级:             %d\n", head->value.clas);
			printf("\n");
			for (int i = 0; i < head->value.BorrowNum; i++)
				printf("                  %s\n", head->value.BorrowName[i]);
			printf("\n");
		}
	END
}

void borrow_book(BList *bhead, SList *shead, PList *phead)
{
	START
		char ID[MAX_NAME], Borrow_ID[MAX_NAME];
	printf("请输入你的ID.\n");
	scanf("%s", ID);
	PList *presult = find_people_information_byID(phead, ID);
	if (presult)
	{
		presult = presult->next;
		if (presult->value.key)
		{
			printf("请输入书籍编号.\n", Borrow_ID);
			scanf("%s", Borrow_ID);
			SList*sresult = find_store_book(shead, Borrow_ID);
			if (!sresult)
			{
				printf("%s不存在.\n", Borrow_ID);
				END
					return;
			}
			if (presult->value.BorrowNum >= presult->value.AllAvaliableBorrowNum)
			{
				printf("对不起，您的所借数目已达上限.\n");
				END
					return;
			}
			sresult = sresult->next;
			if ((sresult->value.All_Have - sresult->value.Borrownum) > 0)
			{
				BList*temp = (BList*)malloc(sizeof(BList));
				write_date(&(temp->value.Borrow_Date), "请输入借书日期.");
				temp->next = NULL;
				strcpy(temp->value.Book_Name, sresult->value.Book_Name);
				strcpy(temp->value.Index, sresult->value.Index);
				strcpy(temp->value.LCardNumber, presult->value.LCardNumber);
				temp->value.Price = sresult->value.Price;
				while (bhead->next) bhead = bhead->next;
				bhead->next = temp;
				(sresult->value.AllBorrow)++;
				(sresult->value.Current_Have)--;
				(sresult->value.Borrownum)++;
				strcpy(presult->value.BorrowID[presult->value.BorrowNum], sresult->value.Index);
				strcpy(presult->value.BorrowName[presult->value.BorrowNum], sresult->value.Book_Name);
				(presult->value.BorrowNum)++;
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

void list_borrow_book(BList *head)
{
	START
		while (head->next)
		{
			head = head->next;
			printf("编号:           %s\n", head->value.Index);
			printf("书名:           %s\n", head->value.Book_Name);
			printf("借书号:         %s\n", head->value.LCardNumber);
			printf("借书日期:       "); read_date(head->value.Borrow_Date);
			printf("\n\n");
		}
	END
}

BList*find_borrowbook_byID(BList*head, char index[])
{
	while (head->next)
	{
		if (!(strcmp(head->next->value.Index, index)))
			return head;
		else
			head = head->next;
	}
	return NULL;
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

void return_book(BList *bhead, SList *shead, PList *phead)
{
	START
		char ID[MAX_NAME], Borrow_ID[MAX_NAME];
	printf("请输入您的ID.\n");
	scanf("%s", ID);
	PList *presult = find_people_information_byID(phead, ID);
	if (presult)
	{
		presult = presult->next;
		printf("请输入编号.\n", Borrow_ID);
		scanf("%s", Borrow_ID);
		SList*sresult = find_store_book(shead, Borrow_ID);
		if (!sresult)
		{
			printf("%s不存在.\n", Borrow_ID);
			END
				return;
		}
		sresult = sresult->next;
		BList*bresult = find_borrowbook_byID(bhead, Borrow_ID);
#if 0
		if (!bresult)
		{
			printf("%s is returned.\n", Borrow_ID);
			END;
			return;
		}
#endif
		if (!find_sign(presult->value.BorrowID, Borrow_ID, presult->value.BorrowNum))
		{
			printf("错误，你没有这本书!\n");
			END;
			return;
		}
		(sresult->value.Borrownum)--;
		(sresult->value.Current_Have)++;
		(presult->value.BorrowNum)--;
		delte_sign(presult->value.BorrowName, bresult->next->value.Book_Name, presult->value.BorrowNum);
		delte_sign(presult->value.BorrowID, bresult->next->value.Index, presult->value.BorrowNum);
		BList*current = bresult->next;
		bresult->next = current->next;
		free(current);
		printf("已还书\n");
	}
	else
		printf("%s不存在.\n", ID);
	END
}

void save(BList *bhead, SList *shead, PList *phead)
{
	START
		FILE *fp;
	if ((fp = fopen("BList", "w")) == NULL)
		printf("错误! 不能创建文件.\n");
	else
	{
		while (bhead->next)
		{
			bhead = bhead->next;
			fprintf(fp, "%s\n", bhead->value.Book_Name);
			fprintf(fp, "%d %d %d\n", bhead->value.Borrow_Date.Year, bhead->value.Borrow_Date.Month, bhead->value.Borrow_Date.Day);
			fprintf(fp, "%s\n", bhead->value.LCardNumber);
			fprintf(fp, "%s\n", bhead->value.Index);
			fprintf(fp, "%d\n", bhead->value.Price);
		}
	}
	fclose(fp);
	if ((fp = fopen("SList", "w")) == NULL)
		printf("错误! 不能创建文件.\n");
	else
	{
		while (shead->next)
		{
			shead = shead->next;
			fprintf(fp, "%d\n", shead->value.AllBorrow);
			fprintf(fp, "%d\n", shead->value.All_Have);
			fprintf(fp, "%s\n", shead->value.Author_Name);
			fprintf(fp, "%s\n", shead->value.Book_Name);
			fprintf(fp, "%d\n", shead->value.Borrownum);
			fprintf(fp, "%s\n", shead->value.Category);
			fprintf(fp, "%d\n", shead->value.Current_Have);
			fprintf(fp, "%s\n", shead->value.Index);
			fprintf(fp, "%s\n", shead->value.Press);
			fprintf(fp, "%d\n", shead->value.Price);
			fprintf(fp, "%d %d %d\n", shead->value.Press_Date.Year, shead->value.Press_Date.Month, shead->value.Press_Date.Day);
		}
		fclose(fp);
	}
	if ((fp = fopen("PList", "w")) == NULL)
		printf("错误! 不能创建文件.\n");
	else
	{
		while (phead->next)
		{
			phead = phead->next;
			fprintf(fp, "%d\n", phead->value.AllAvaliableBorrowNum);
			fprintf(fp, "%d\n", phead->value.BorrowNum);
			int i = 0;
			for (; i < phead->value.BorrowNum; i++)
			{
				fprintf(fp, "%s\n", phead->value.BorrowID[i]);
				fprintf(fp, "%s\n", phead->value.BorrowName[i]);
			}
			fprintf(fp, "%d\n", phead->value.Category);
			fprintf(fp, "%d\n", phead->value.clas);
			fprintf(fp, "%s\n", phead->value.ID);
			fprintf(fp, "%d\n", phead->value.key);
			fprintf(fp, "%s\n", phead->value.LCardNumber);
			fprintf(fp, "%s\n", phead->value.Name);
		}
		fclose(fp);
	}
	printf("已保存\n\n");
	END
}

void load(BList *bhead, SList *shead, PList *phead)
{
	START
		FILE *fp;
	if ((fp = fopen("BList", "r")) == NULL)
		printf("错误! 不能打开文件.\n");
	else
	{
		char temp[MAX_NAME];
		while (~fscanf(fp, "%s", temp))
		{
			BList*bcurrent = (BList*)malloc(sizeof(BList));
			strcpy(bcurrent->value.Book_Name, temp);
			bcurrent->next = NULL;
			fscanf(fp, "%d %d %d", &(bcurrent->value.Borrow_Date.Year), &(bcurrent->value.Borrow_Date.Month), &(bcurrent->value.Borrow_Date.Day));
			fscanf(fp, "%s", bcurrent->value.LCardNumber);
			fscanf(fp, "%s", bcurrent->value.Index);
			fscanf(fp, "%d", &(bcurrent->value.Price));
			bhead->next = bcurrent;
			bhead = bcurrent;
		}
		fclose(fp);
	}

	if ((fp = fopen("SList", "r")) == NULL)
		printf("错误! 不能打开文件.\n");
	else
	{
		int temp;
		while (~fscanf(fp, "%d", &temp))
		{
			SList*scurrent = (SList*)malloc(sizeof(SList));
			(scurrent->value.AllBorrow) = temp;
			scurrent->next = NULL;
			fscanf(fp, "%d", &(scurrent->value.All_Have));
			fscanf(fp, "%s", scurrent->value.Author_Name);
			fscanf(fp, "%s", scurrent->value.Book_Name);
			fscanf(fp, "%d", &(scurrent->value.Borrownum));
			fscanf(fp, "%s", scurrent->value.Category);
			fscanf(fp, "%d", &(scurrent->value.Current_Have));
			fscanf(fp, "%s", scurrent->value.Index);
			fscanf(fp, "%s", scurrent->value.Press);
			fscanf(fp, "%d", &(scurrent->value.Price));
			fscanf(fp, "%d %d %d", &(scurrent->value.Press_Date.Year), &(scurrent->value.Press_Date.Month), &(scurrent->value.Press_Date.Day));
			shead->next = scurrent;
			shead = scurrent;
		}
		fclose(fp);
	}
	if ((fp = fopen("PList", "r")) == NULL)
		printf("错误! 不能打开文件.\n");
	else
	{
		int temp;
		while (~fscanf(fp, "%d", &temp))
		{
			PList*pcurrent = (PList*)malloc(sizeof(PList));
			pcurrent->value.AllAvaliableBorrowNum = temp;
			pcurrent->next = NULL;
			fscanf(fp, "%d", &(pcurrent->value.BorrowNum));
			int i = 0;
			for (; i < pcurrent->value.BorrowNum; i++)
			{
				fscanf(fp, "%s", pcurrent->value.BorrowID[i]);
				fscanf(fp, "%s", pcurrent->value.BorrowName[i]);
			}
			fscanf(fp, "%d", &(pcurrent->value.Category));
			fscanf(fp, "%d", &(pcurrent->value.clas));
			fscanf(fp, "%s", pcurrent->value.ID);
			fscanf(fp, "%d", &(pcurrent->value.key));
			fscanf(fp, "%s", pcurrent->value.LCardNumber);
			fscanf(fp, "%s", pcurrent->value.Name);
			phead->next = pcurrent;
			phead = pcurrent;
		}
		fclose(fp);
	}
	printf("已载入\n\n");
	END
}

void help()
{
	START
		printf("0.显示帮助\n1.添加新书\n2.找书\n3.编辑库存资料\n4.删除书\n5.列出书\n6.添加借书证\n7.查找\
借书证\n8.注销\n9.挂失\n10.解冻\n11.列出所有成员\n12.借书\n13.列出借的书\n14.还书\n15.加载数据\n16.保存数据\n17.人气排序\n20.删库跑路\n");
	END;
}

void emplty(BList *bhead, SList *shead, PList *phead)
{
	START
		BList *btemp = bhead;
	SList *stemp = shead;
	PList *ptemp = phead;
	if (bhead->next)
	{
		bhead = bhead->next;
		BList*bnext;
		while (bhead)
		{
			bnext = bhead->next;
			free(bhead);
			bhead = bnext;
		}
	}
	if (shead->next)
	{
		shead = shead->next;
		SList*snext;
		while (shead)
		{
			snext = shead->next;
			free(shead);
			shead = snext;
		}
	}
	if (phead->next)
	{
		phead = phead->next;
		PList*pnext;
		while (phead)
		{
			pnext = phead->next;
			free(phead);
			phead = pnext;
		}
	}
	btemp->next = NULL; stemp->next = NULL; ptemp->next = NULL;
	printf("已清空\n");
	END
}

int cmp(const void *a,const void *b)
{
	SList *c = (SList*)a;
	SList *d = (SList*)b;
	return (c->value.AllBorrow < d->value.AllBorrow);
}

void sort_book(SList *head)
{
	START
		int all = 0;
	SList*temp = head;
	while (head->next) all++, head = head->next;
	SList *Data = (SList*)malloc(sizeof(SList)*all);
	int i = 0;
	head = temp;
	while (head->next)
	{
		Data[i] = *(head->next);
		head = head->next;
		i++;
	}
	qsort(Data, all, sizeof(SList), cmp);
	for (int i = 0; i < all; i++)
	{
		printf("书名:                    %s\n", Data[i].value.Book_Name);
		printf("作者:                    %s\n", Data[i].value.Author_Name);
		printf("出版社:                  %s\n", Data[i].value.Press);
		printf("类别:                    %s\n", Data[i].value.Category);
		printf("出版日期:                "); read_date(Data[i].value.Press_Date);
		printf("价格:                    %d\n", Data[i].value.Price);
		printf("总库存:                  %d\n", Data[i].value.All_Have);
		printf("借出:                    %d\n", Data[i].value.Borrownum);
		printf("在库:                    %d\n", Data[i].value.All_Have - Data[i].value.Borrownum);
		printf("****************************************************************\n");
		printf("总借出:                  %d\n\n", Data[i].value.AllBorrow);
		printf("****************************************************************\n");
	}
	END
}

int main()
{
	SList *SHead = (SList*)malloc(sizeof(SList));
	BList *BHead = (BList*)malloc(sizeof(BList));
	PList *PHead = (PList*)malloc(sizeof(PList));
	init(SHead, BHead, PHead);
	help();
	int choice;
#if 1
	while (~scanf("%d", &choice))
	{
		switch (choice)
		{
		case 0:
			help();
			break;
		case 1:                            //添加新书
			add_book_store(SHead);
			break;
		case 2:                            //找书
			find_book_store(SHead);
			break;
		case 3:                            //编辑库存资料
			edit_book_store(SHead);
			break;
		case 4:                            //删除书
			delete_book_store(SHead);
			break;
		case 5:                            //列出书
			list_book_store(SHead);
			break;
		case 6:                            //添加借书证
			add_people(PHead);
			break;
		case 7:                            //查找借书证
			find_people(PHead);
			break;
		case 8:                            //注销
			delete_people(PHead);
			break;
		case 9:                            //挂失
			lose(PHead);
			break;
		case 10:                           //解冻
			remain(PHead);
			break;
		case 11:                           //列出所有成员
			list_people(PHead);
			break;
		case 12:                           //借书
			borrow_book(BHead, SHead, PHead);
			break;
		case 13:                           //列出借的书
			list_borrow_book(BHead);
			break;
		case 14:                           //还书
			return_book(BHead, SHead, PHead);
			break;
		case 15:                           //加载数据
			load(BHead, SHead, PHead);
			break;
		case 16:                           //保存数据
			save(BHead, SHead, PHead);
			break;
		case 17:                           //人气排序
			sort_book(SHead);
			break;
		case 20:                           //清空
			emplty(BHead, SHead, PHead);
			break;
		default:
			break;
		}
	}
#endif
	system("pause");
	return 0;
}