#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct list_data {
	struct list_data*next, *pre;
	void *data;
}list_data;
typedef struct List {
	list_data *list;
}List;

typedef int(*cmp_f)(void *key_a, void *key_b);
typedef void(*list_print)(void*data);
typedef void(*list_pt_file)(FILE*stream, void *data);
typedef void* (*list_frome_file)(FILE*stream);
list_data* list_insert(list_data*start, void *data)
{
	list_data*newnode = (list_data*)malloc(sizeof(list_data));
	newnode->pre = newnode->next = NULL;
	newnode->data = data;
	if (start)
	{
		start->pre = newnode;
		newnode->next = start;
	}

	return newnode;
}
void list_all(list_data*start, list_print pt)
{
	while (start)
	{
		pt(start->data);
		start = start->next;
	}
}
void _list_delete(list_data*pos)
{
	if (pos->next) pos->next->pre = pos->pre;
	pos->pre->next = pos->next;
	free(pos);
}
void list_delete(List *li, void *data, cmp_f cmp)
{
	if (!li->list) return;
	if (!cmp(li->list->data, data))
	{
		if (li->list->next) li->list->next->pre = NULL;
		li->list = li->list->next;
		return;
	}
	list_data*start = li->list->next;
	while (start)
	{
		if (!cmp(start->data, data)) {
			_list_delete(start);
			return;
		}
		start = start->next;
	}
}
void list_to_file(list_data*start, FILE*pt, list_pt_file print_list)
{
	while (start)
	{
		fprintf(pt, "1 ");
		print_list(pt, start->data);
		start = start->next;
	}
	fprintf(pt, "0 ");
}
list_data* list_f_file(FILE*stream, list_frome_file ffile)
{
	int ico;
	list_data*temp = NULL;
	while (fscanf(stream, "%d", &ico))
	{
		if (ico == 0) return temp;
		void *data = ffile(stream);
		temp = list_insert(temp, data);
	}
	return temp;
}

# if 0    //example
void print_list(void *key)
{
	char * temp = (char*)key;
	printf("%s\n", temp);
}
int cmp(void*key_a, void*key_b)
{
	const char *a = (char*)key_a;
	const char *b = (char*)key_b;
	return strcmp(a, b);
}
void list2file(FILE*stream, void*data)
{
	char *temp = (char*)data;
	fprintf(stream, "%s ", temp);
}
void* ffile(FILE*stream)
{
	char *data = (char*)malloc(sizeof(char) * 20);
	fscanf(stream, "%s", data);
	return (void*)data;
}
int main()
{
	FILE *pt;
	pt = fopen("NAME2INDEX", "r");
	//temp.list = NULL;
	//temp.list = list_f_file(pt, ffile);
	char li1[3][3] = { "1","2","3" };
	List temp, temp2;
	temp.list = NULL; temp2.list = NULL;
	temp.list = list_f_file(pt, ffile);
	temp2.list = list_f_file(pt, ffile);
	//temp.list = list_insert(temp.list, li1[0]);
	//temp.list = list_insert(temp.list, li1[1]);
	//temp.list = list_insert(temp.list, li1[2]);
	//temp2.list = list_insert(temp2.list, li1[2]);
	//temp2.list = list_insert(temp2.list, li1[1]);
	//temp2.list = list_insert(temp2.list, li1[2]);
	list_all(temp.list, print_list);
	list_all(temp2.list, print_list);
	//list_to_file(temp.list, pt,list2file);
	//list_to_file(temp2.list, pt, list2file);
	system("pause");
	return 0;
}

#endif
#pragma once
