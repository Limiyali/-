#include "manager.h"



void menu(rbtree *stree, rbtree *ptree, rbtree *btree)
{
	printf("------------��ķ˹���ʻ������پ��޵а�����miniͼ�����ϵͳ------------\n");
	printf("                                                                #### #                                      \n");
	printf("                                                      ####                    ####                          \n");
	printf("                                               ###                                 ###                      \n");
	printf("                                          ##                                           ###                  \n");
	printf("                                ######                           #                        ###               \n");
	printf("                                     ###         #   ###    ##    ##                         ##             \n");
	printf("                                    ##         ####    ##          #### ##          ##   #     #            \n");
	printf("       1.�������                 ##       ##                            #          #          #            \n");
	printf("       2.����                    ##        #       #                       ##        #   ######  #          \n");
	printf("       3.�༭�������           ##       ##      ##                 ##       ###      ########   ##         \n");
	printf("       4.ɾ����                ### ##   ##                                     #      #######     #         \n");
	printf("       5.�г���                   ##   #                                      ##      ####       ##         \n");
	printf("       6.��ӽ���֤                ##  #    #######                  ######  ##      ##          #          \n");
	printf("       7.���ҽ���֤                #   #  ##       ##             ##       ## ##      #           #         \n");
	printf("       8.ע��                     ##   #  #   ##   ##             #   ##   ## ##      #           ##        \n");
	printf("       9.��ʧ                     #    #  # #  ##  ##             # #  ##  ##  #      #            #        \n");
	printf("       10.�ⶳ                   #     #    ##    ##                ##    ##   #      #            #        \n");
	printf("       11.�г����г�Ա          #      #     ######                  ######    ##      #            ##      \n");
	printf("       12.����               ##  ##   #                                        ##      #             #      \n");
	printf("       13.�г������       ##    #   ##                                        #       #             ##     \n");
	printf("       14.����            #        #  ##     ## #      ##           ##         #       #              #     \n");
	printf("       15.��������        #        #     #####      #####    # ######     ### ##      ##               #    \n");
	printf("       16.��������       #############  ######   ########  ##########   #### ##       ###              ##   \n");
	printf("       17.��������      ##############   ######################################       ####              ##  \n");
	printf("       20.ɾ����·         #       ##      ######  #########  ###### #########        ###                ## \n");
	printf("                           #         ##     #                           #   #        ##                   ##\n");

	int choice;
	scanf("%d", &choice);

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
	case -1:                            //�������
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