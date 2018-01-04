#include "manager.h"



void menu(rbtree *stree, rbtree *ptree, rbtree *btree)
{
	printf("------------阿姆斯特朗回旋加速局无敌棒棒糖mini图书管理系统------------\n");
	printf("                                                                #### #                                      \n");
	printf("                                                      ####                    ####                          \n");
	printf("                                               ###                                 ###                      \n");
	printf("                                          ##                                           ###                  \n");
	printf("                                ######                           #                        ###               \n");
	printf("                                     ###         #   ###    ##    ##                         ##             \n");
	printf("                                    ##         ####    ##          #### ##          ##   #     #            \n");
	printf("       1.添加新书                 ##       ##                            #          #          #            \n");
	printf("       2.找书                    ##        #       #                       ##        #   ######  #          \n");
	printf("       3.编辑库存资料           ##       ##      ##                 ##       ###      ########   ##         \n");
	printf("       4.删除书                ### ##   ##                                     #      #######     #         \n");
	printf("       5.列出书                   ##   #                                      ##      ####       ##         \n");
	printf("       6.添加借书证                ##  #    #######                  ######  ##      ##          #          \n");
	printf("       7.查找借书证                #   #  ##       ##             ##       ## ##      #           #         \n");
	printf("       8.注销                     ##   #  #   ##   ##             #   ##   ## ##      #           ##        \n");
	printf("       9.挂失                     #    #  # #  ##  ##             # #  ##  ##  #      #            #        \n");
	printf("       10.解冻                   #     #    ##    ##                ##    ##   #      #            #        \n");
	printf("       11.列出所有成员          #      #     ######                  ######    ##      #            ##      \n");
	printf("       12.借书               ##  ##   #                                        ##      #             #      \n");
	printf("       13.列出借的书       ##    #   ##                                        #       #             ##     \n");
	printf("       14.还书            #        #  ##     ## #      ##           ##         #       #              #     \n");
	printf("       15.加载数据        #        #     #####      #####    # ######     ### ##      ##               #    \n");
	printf("       16.保存数据       #############  ######   ########  ##########   #### ##       ###              ##   \n");
	printf("       17.人气排序      ##############   ######################################       ####              ##  \n");
	printf("       20.删库跑路         #       ##      ######  #########  ###### #########        ###                ## \n");
	printf("                           #         ##     #                           #   #        ##                   ##\n");

	int choice;
	scanf("%d", &choice);

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
	case -1:                            //随机生成
		randbook(stree);
		break;
	case -2:
		list_top(stree);
		break;
	default:
		break;

	}


	system("pause");

	menu(stree, ptree, btree);

}

int main()
{
	struct rbtree* stree = rbtree_init(compare);
	struct rbtree* ptree = rbtree_init(compare);
	struct rbtree* btree = rbtree_init(compare);
	int choice;
#if 1
	menu(stree, ptree, btree);
#endif

	return 0;
}