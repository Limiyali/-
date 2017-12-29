#include"manager.h"

int main()
{
	struct rbtree* stree = rbtree_init(compare);
	struct rbtree* ptree = rbtree_init(compare);
	struct rbtree* btree = rbtree_init(compare);
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
		case 1:                            //�������
			add_book_store(stree);
			break;
		case 2:                            //����
			find_book_store(stree);
			break;
		case 3:                            //�༭�������
			edit_book_store(stree);
			break;
		case 4:                            //ɾ����
			delete_book_store(stree);
			break;
		case 5:                            //�г���
			list_book_store(stree);
			break;
		case 6:                            //��ӽ���֤
			add_people(ptree);
			break;
		case 7:                            //���ҽ���֤
			find_people(ptree);
			break;
		case 8:                            //ע��
			delete_people(ptree);
			break;
		case 9:                            //��ʧ
			lose(ptree);
			break;
		case 10:                           //�ⶳ
			remain(ptree);
			break;
		case 11:                           //�г����г�Ա
			list_people(ptree);
			break;
		case 12:                           //����
			borrow_book(stree, ptree, btree);
			break;
		case 13:                           //�г������
			list_borrow_book(btree);
			break;
		case 14:                           //����
			return_book(stree, ptree, btree);
			break;	
		case 15:                           //��������
			load(stree, ptree, btree);
			break;
		case 16:                           //��������
			save(stree, ptree, btree);
			break;
		case 17:                           //��������
			sort_book(stree);
			break;
		case 20:                           //���
			empty(stree, ptree, btree);
			break;
		default:
			break;
		}
	}
#endif
	system("pause");
	return 0;
}