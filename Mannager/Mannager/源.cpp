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
		case 1:                            //添加新书
			add_book_store(stree);
			break;
		case 2:                            //找书
			find_book_store(stree);
			break;
		case 3:                            //编辑库存资料
			edit_book_store(stree);
			break;
		case 4:                            //删除书
			delete_book_store(stree);
			break;
		case 5:                            //列出书
			list_book_store(stree);
			break;
		case 6:                            //添加借书证
			add_people(ptree);
			break;
		case 7:                            //查找借书证
			find_people(ptree);
			break;
		case 8:                            //注销
			delete_people(ptree);
			break;
		case 9:                            //挂失
			lose(ptree);
			break;
		case 10:                           //解冻
			remain(ptree);
			break;
		case 11:                           //列出所有成员
			list_people(ptree);
			break;
		case 12:                           //借书
			borrow_book(stree, ptree, btree);
			break;
		case 13:                           //列出借的书
			list_borrow_book(btree);
			break;
		case 14:                           //还书
			return_book(stree, ptree, btree);
			break;	
		case 15:                           //加载数据
			load(stree, ptree, btree);
			break;
		case 16:                           //保存数据
			save(stree, ptree, btree);
			break;
		case 17:                           //人气排序
			sort_book(stree);
			break;
		case 20:                           //清空
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