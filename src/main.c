#include "main.h"

#pragma warning(disable:6031)
char login_flag = 0;
//主函数
int main(void)
{
	//登录订票系统
	login_flag = log_in_to_booking_system();
	while (login_flag == 'U' || login_flag == 'A')
	{
		if (login_flag == 'U') //如果是用户登录
			user_login_interface_menu();
		if (login_flag == 'A') //如果是管理员登录
			administrator_login_interface_menu();
	}
	return 0;
}

/**
 * @function: void user_login_interface_menu(void)
 * @description: 用户登录界面菜单
 * @param {*}
 * @return {*}
 */
void user_login_interface_menu(void)
{
	system("cls");
	printf("\t===============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t===============================\n");
	printf("\t\t1.显示所有火车信息\n\t\t2.查询火车信息\n\t\t3.显示用户订票信息\n");
	printf("\t\t4.订购火车票\n\t\t5.退票\n\t\t6.注册新用户\n\t\t7.退出\n");
	printf("\t===============================\n");
	printf("\t[用户]\n");
	printf("\n\t>请选择功能：");
	size_t select_funs;
	char YorN = 0;
	scanf_s("%d", &select_funs);
	switch (select_funs)
	{
	case 1:
		system("cls");
		printf("\t===============================\n");
		printf("\t\t火车票订票系统\n");
		printf("\t===============================\n");
		printf("\n\t[显示火车信息]\n");
		display_all_train_information(); //显示所有火车信息(user/administrators)
		printf("\n\t==显示完成==\n\n");
		system("pause");
		user_login_interface_menu();
		break;
	case 2:
		search_for_train_information(); //查询火车信息(user/administrators)
		printf("\n\t>是否继续查询？[继续查询='y' 不再查询='任意字符']\n");
		getchar();
		printf("\t>请选择：");
		scanf_s("%s", &YorN, 2);
		if (YorN == 'y' || YorN == 'Y')
			search_for_train_information();
		else
			user_login_interface_menu();
		break;
	case 3:
		display_user_booking_information(); //显示用户订单信息(user)
		break;
	case 4:
		order_train_tickets(); //订购火车票(user)
		break;
	case 5:
		return_the_ticket(); //退票(user)
		break;
	case 6:
		registered_new_users(User_type); //注册新用户(user)
		break;
	case 7:
		main();
		break;
	default:
		printf("\n==请选择正确的功能编号(1~6)==\n");
		getchar();
		system("pause");
		user_login_interface_menu();
		break;
	}
}

/**
 * @function: void administrator_login_interface_menu(void)
 * @description: 管理员登录界面菜单
 * @param {*}
 * @return {*}
 */
void administrator_login_interface_menu(void)
{
	system("cls");
	printf("\t===============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t===============================\n");
	printf("\t\t1.显示所有火车信息\n\t\t2.查询火车信息\n\t\t3.增加火车信息\n\t\t4.修改火车票信息\n");
	printf("\t\t5.删除火车票信息\n\t\t6.查看所有注册用户\n\t\t7.添加管理员\n\t\t8.退出\n");
	printf("\t===============================\n");
	printf("\t[管理员]\n");
	printf("\n\t>请选择功能：");
	size_t select_funs;
	char YorN = 0;
	scanf_s("%d", &select_funs);
	switch (select_funs)
	{
	case 1:
		system("cls");
		printf("\t===============================\n");
		printf("\t\t火车票订票系统\n");
		printf("\t===============================\n");
		printf("\n\t[显示火车信息]\n");
		display_all_train_information(); //显示所有火车信息(user/administrators)
		printf("\n\t==显示完成==\n\n");
		system("pause");
		administrator_login_interface_menu();
		break;
	case 2:
		search_for_train_information(); //查询火车信息(user/administrators)
		getchar();
		printf("\n\t>是否继续查询？[继续查询='y' 不再查询='任意字符']\n");
		printf("\t>请选择：");
		scanf_s("%s", &YorN, 2);
		if (YorN == 'y' || YorN == 'Y')
			search_for_train_information();
		else
			user_login_interface_menu();
		break;
	case 3:
		add_train_information(); //增加火车信息(administrators)
		break;
	case 4:
		modify_train_information(); //修改火车票信息(administrators)
		break;
	case 5:
		delete_train_information(); //删除火车信息(administrators)
		break;
	case 6:
		display_all_registered_users(); //显示所有注册用户(administrators)
		break;
	case 7:
		registered_new_users(Admin_type); //添加管理员(administrators)
		break;
	case 8:
		main();
		break;
	default:
		printf("\n==请选择正确的功能编号(1~7)==\n");
		getchar();
		system("pause");
		administrator_login_interface_menu();
		break;
	}
}
