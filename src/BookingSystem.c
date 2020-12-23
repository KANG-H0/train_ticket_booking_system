#include "BookingSystem.h"

#pragma warning(disable:6031)
#pragma warning(disable:4013)
#pragma warning(disable:6054)

//全局变量
const char* user_tickets_file_path_part1 = "data_files/user_tickets_data/"; //存放用户订单信息的文件夹
const char* file_extension = ".dat";                                                             //数据文件后缀
const char* all_tickets_file_path = "data_files/all_tickets.dat";                     //存放所有火车票数据的文件相对路径
const char* all_users_file_path = "data_files/all_users.dat";                        //存放所有用户数据的文件相对路径
char account_file_name[PHONE_ACCOUNT_NUM_LEN];                           //用户名/手机号(用户们做订单信息文件名)
char* user_tickets_file_path;                                                                       //用户订票数据文件路径
const char* Admin_type = "Admin";
const char* User_type = "User";

/**
 * @function: char log_in_to_booking_system(void)
 * @description: 登录订票系统
 * @param {*}
 * @return {'A'}管理员登录
 * @return {'U'}用户登录
 */
char log_in_to_booking_system(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t[登录]\n\n");
	FILE* file_log;
	USER read_log;
	char input_account_number[PHONE_ACCOUNT_NUM_LEN];
	char input_password[USER_PASSWORD_LEN];
	printf("\t账号：");
	scanf_s("%s", &input_account_number, PHONE_ACCOUNT_NUM_LEN);
	//存下手机账号(作为用户火车票数据文件名)
	strcpy_s(account_file_name, sizeof(account_file_name), input_account_number);
	printf("\t密码：");
	get_password(input_password, sizeof(input_password));
	while (fopen_s(&file_log, all_users_file_path, "rb") || !file_log)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//判断用户名和密码是否匹配
	while (fread(&read_log, sizeof(USER), 1, file_log))
	{
		//如果匹配
		if (!strcmp(input_account_number, read_log.phone_account_num) && \
			!strcmp(input_password, read_log.user_password))
		{
			//如果是管理员
			if (!strcmp(read_log.user_type, Admin_type))
			{
				if (fclose(file_log))
				{
					printf("\n\t=关闭文件时出现错误=\n");
					exit(EXIT_FAILURE);
				}
				return 'A';
			}
			//如果是用户
			if (!strcmp(read_log.user_type, User_type))
			{
				//获得用户车票信息存放文件路径
				user_tickets_file_path = build_user_train_file_name_path(account_file_name);
				//strcpy_s(user_tickets_file_path, sizeof(user_tickets_file_path), build_user_train_file_name_path(account_file_name));
				if (fclose(file_log))
				{
					printf("\n\t=关闭文件时出现错误=\n");
					exit(EXIT_FAILURE);
				}
				return 'U';
			}
		}
	}
	//没有匹配到该用户
	printf("\n\t=登录失败，没有该用户=\n");
	printf("\n\t>是否注册？[注册='y' 不注册='任意字符']\n");
	getchar();
	printf("\t>请选择：");
	char YorN;
	scanf_s("%s", &YorN, 2);
	if (YorN == 'y' || YorN == 'Y')
		registered_new_users(User_type);
	else
		log_in_to_booking_system();
	return (char)MY_FAIL;
}

/**
 * @function: void registered_new_users(const char* User_or_Admin)
 * @description: 注册新用户
 * @param {char* user_or_admi}注册的用户类型User/Admin
 * @return {*}
 */
void registered_new_users(const char* User_or_Admin)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t[注册新用户]\n\n");
	char again_password[USER_PASSWORD_LEN];
	USER puser_new;
	printf("\t手机号：");
	scanf_s("%s", puser_new.phone_account_num, PHONE_ACCOUNT_NUM_LEN);
	while (strlen(puser_new.phone_account_num) != 11)
	{
		printf("\n\t=手机号格式不对，请重新输入=\n");
		printf("\t手机号：");
		scanf_s("%s", puser_new.phone_account_num, PHONE_ACCOUNT_NUM_LEN);
	}
	printf("\t身份证号：");
	scanf_s("%s", puser_new.ID_num, ID_NUM_LEN);
	while (strlen(puser_new.ID_num) != 18)
	{
		printf("\n\t=身份证格式不对，请重新输入=\n");
		printf("\t身份证号：");
		scanf_s("%s", puser_new.ID_num, ID_NUM_LEN);
	}
	//判断用户是否已经存在
	while (!check_whether_the_user_data_exists(puser_new)) //用户已存在则重新注册
	{
		system("cls");
		printf("\n\t=该用户已存在，请重新录入=\n");
		printf("\n\t=============================\n");
		printf("\t\t火车票订票系统\n");
		printf("\t=============================\n");
		printf("\n\t[注册]\n\n");
		printf("\t手机号：");
		scanf_s("%s", puser_new.phone_account_num, PHONE_ACCOUNT_NUM_LEN);
		while (strlen(puser_new.phone_account_num) != 11)
		{
			printf("\n\t=手机号格式不对，请重新输入=\n");
			printf("\t手机号：");
			scanf_s("%s", puser_new.phone_account_num, PHONE_ACCOUNT_NUM_LEN);
		}
		printf("\t身份证号：");
		scanf_s("%s", puser_new.ID_num, ID_NUM_LEN);
		while (strlen(puser_new.ID_num) != 18)
		{
			printf("\n\t=身份证格式不对，请重新输入=\n");
			printf("\t身份证号：");
			scanf_s("%s", puser_new.ID_num, ID_NUM_LEN);
		}
	}
	printf("\t姓名：");
	scanf_s("%s", puser_new.user_name, USER_NAME_LEN);
	printf("\t密码：");
	scanf_s("%s", puser_new.user_password, USER_PASSWORD_LEN);
	while (strlen(puser_new.user_password) >= USER_PASSWORD_LEN)
	{
		printf("\n\t=账号需小于%d字符，请重新输入=\n", USER_PASSWORD_LEN);
		printf("\t密码：");
		scanf_s("%s", puser_new.user_password, USER_PASSWORD_LEN);
	}
	printf("\t再次输入密码：");
	scanf_s("%s", again_password, USER_PASSWORD_LEN);
	while (strcmp(again_password, puser_new.user_password))
	{
		printf("\n\t=与第一次输入密码不符，请重新输入=\n");
		printf("\t再次输入密码：");
		scanf_s("%s", again_password, USER_PASSWORD_LEN);
	}
	//添加用户类型标识("User"用户类型)
	if (!strcmp(User_or_Admin, User_type))
		strcpy_s(puser_new.user_type, sizeof(puser_new.user_type), User_type);
	//添加管理员类型标识("Admin"用户类型)
	if (!strcmp(User_or_Admin, Admin_type))
		strcpy_s(puser_new.user_type, sizeof(puser_new.user_type), Admin_type);
	//保存添加的用户信息到文件
	if (save_a_newly_registered_user_to_the_file(puser_new))
	{
		printf("\n\t=保存数据到文件失败=\n");
		system("pause"); //暂停等待
		exit(EXIT_FAILURE);
	}
	printf("\n\t==注册成功==\n\n");
	getchar();
	system("pause");
	main(); //注册成功回到登录界面
}

/**
 * @function: void display_all_registered_users(void)
 * @description: 显示所有注册用户(包含管理员)
 * @param {*}
 * @return {*}
 */
void display_all_registered_users(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t[显示所有注册用户]\n");
	USER read_users_tmp;
	FILE* file_display_users;
	int list_num = 0;
	while (fopen_s(&file_display_users, all_users_file_path, "rb") || !file_display_users)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t||======================================================||\n");
	printf("\t||编号+  姓名  +   手机号   +     身份证号     +用户类型||\n");
	printf("\t||======================================================||\n");
	while (fread(&read_users_tmp, sizeof(USER), 1, file_display_users))
	{
		//先将管理员信息打印显示
		if (!strcmp(read_users_tmp.user_type, Admin_type))
		{
			printf("\t||%-4d|%-8s|%-12s|%-18s|%-8s||\n", ++list_num, read_users_tmp.user_name,
				read_users_tmp.phone_account_num, read_users_tmp.ID_num, read_users_tmp.user_type);
		}
	}
	printf("\t||======================================================||\n");
	rewind(file_display_users); //将文件位置指示器移动到给定文件流的开头(光标回到文件开头)
	list_num = 0;
	while (fread(&read_users_tmp, sizeof(USER), 1, file_display_users))
	{
		//再将用户信息打印显示
		if (!strcmp(read_users_tmp.user_type, User_type))
		{
			printf("\t||%-4d|%-8s|%-12s|%-18s|%-8s||\n", ++list_num, read_users_tmp.user_name,
				read_users_tmp.phone_account_num, read_users_tmp.ID_num, read_users_tmp.user_type);
		}
	}
	printf("\t||======================================================||\n");
	if (fclose(file_display_users))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t==显示完成==\n\n");
	system("pause");
	administrator_login_interface_menu();
}

/**
 * @function: void search_for_train_information(void)
 * @description: 查询火车信息
 * @param {*}
 * @return {*}
 */
void search_for_train_information(void)
{
	system("cls");
	char YorN = 0;
	FILE* file_search_tmp;
	TICKET read_search_tickets;
	fpos_t list_num = 0;
	char input_start_station[START_STATION_LEN];
	char input_arrive_station[ARRIVE_STATION_LEN];
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t[查询火车信息]\n\n");
	printf("\t请输入起始站：");
	scanf_s("%s", &input_start_station, START_STATION_LEN);
	printf("\t请输入终点站：");
	scanf_s("%s", &input_arrive_station, ARRIVE_STATION_LEN);
	//从文件比对输入的起始站和终点站，并显示出来
	file_search_tmp = compare_train_information(input_start_station, input_arrive_station);
	printf("\n\t||=================================================================================||\n");
	printf("\t||编号+列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  +余票||\n");
	printf("\t||=================================================================================||\n");
	while (fread(&read_search_tickets, sizeof(TICKET), 1, file_search_tmp))
	{
		if (strcmp(read_search_tickets.start_station, input_start_station) == 0 &&
			strcmp(read_search_tickets.arrive_station, input_arrive_station) == 0)
		{
			printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f|%-4d||\n", ++list_num, read_search_tickets.train_num,
				read_search_tickets.start_station, read_search_tickets.arrive_station, read_search_tickets.start_time,
				read_search_tickets.arrive_time, read_search_tickets.ticket_price, read_search_tickets.ticket_total);
		}
	}
	printf("\t||=================================================================================||\n");
	if (list_num == 0)
	{
		printf("\n\t=未查到如何信息=\n");
		printf("\n\t>是否继续查询？[继续查询='y' 不再查询='任意字符']\n");
		printf("\t>请选择：");
		scanf_s("%s", &YorN, 2);
		if (YorN == 'y' || YorN == 'Y')
			search_for_train_information();
		else
		{
			if (login_flag == 'U') //如果是用户登录
				user_login_interface_menu();
			if (login_flag == 'A') //如果是管理员登录
				administrator_login_interface_menu();
		}
	}
	printf("\n\t==查询完成==\n\n");
	//printf("\n\t>是否继续查询？[继续查询='y' 不再查询='任意字符']\n");
	//printf("\t>请选择：");
	//scanf_s("%s", &YorN, 2);
	//if (YorN == 'y' || YorN == 'Y')
	//	search_for_train_information();
	//else
	//{
	//	if (login_flag == 'U')//如果是用户登录
	//		user_login_interface_menu();
	//	if (login_flag == 'A') //如果是管理员登录
	//		administrator_login_interface_menu();
	//}
}

/**
 * @function: void add_train_information(void)
 * @description: 增加火车信息
 * @param {*}
 * @return {*}
 */
void add_train_information(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t[增加火车信息]\n\n");
	TICKET ptickets_new;
	printf("\t==请输入火车信息==\n");
	printf("\t列车号：");
	scanf_s("%s", ptickets_new.train_num, TRAIN_NUM_LEN);
	printf("\t起始站：");
	scanf_s("%s", ptickets_new.start_station, START_STATION_LEN);
	printf("\t终点站：");
	scanf_s("%s", ptickets_new.arrive_station, ARRIVE_STATION_LEN);
	printf("\t发车时间：");
	scanf_s("%s", ptickets_new.start_time, START_TIME_LEN);
	printf("\t到站时间：");
	scanf_s("%s", ptickets_new.arrive_time, ARRIVE_TIME_LEN);
	//判断输入的列车是否存在
	while (!check_whether_the_train_data_exists(ptickets_new)) //列车已存在则重新录入
	{
		system("cls");
		printf("\n\t=该列车已存在，请重新录入=\n");
		printf("\n\t=============================\n");
		printf("\t\t火车票订票系统\n");
		printf("\t=============================\n");
		printf("\n\t[增加]\n\n");
		printf("\n\t=请输入火车票信息=\n");
		printf("\t列车号：");
		scanf_s("%s", ptickets_new.train_num, TRAIN_NUM_LEN);
		printf("\t起始站：");
		scanf_s("%s", ptickets_new.start_station, START_STATION_LEN);
		printf("\t终点站：");
		scanf_s("%s", ptickets_new.arrive_station, ARRIVE_STATION_LEN);
		printf("\t发车时间：");
		scanf_s("%s", ptickets_new.start_time, START_TIME_LEN);
		printf("\t到站时间：");
		scanf_s("%s", ptickets_new.arrive_time, ARRIVE_TIME_LEN);
	}
	printf("\t票价：");
	scanf_s("%f", &ptickets_new.ticket_price);
	while (ptickets_new.ticket_price < 0)
	{
		printf("\n\t=票价必须大于0，请重新输入=\n");
		printf("\t票价：");
		scanf_s("%f", &ptickets_new.ticket_price);
	}
	printf("\t余票：");
	scanf_s("%d", &ptickets_new.ticket_total);
	while (ptickets_new.ticket_total < 0)
	{
		printf("\n\t=余票必须大于0，请重新输入=\n");
		printf("\t余票：");
		scanf_s("%d", &ptickets_new.ticket_total);
	}
	//保存添加的火车信息到文件
	if (save_a_newly_train_data_to_the_file(ptickets_new))
	{
		printf("\n\t=保存数据到文件失败=\n");
		system("pause"); //暂停等待用户信号
		exit(EXIT_FAILURE);
	}
	printf("\n\t==添加成功==\n\n");
	printf("\n\t>是否继续添加?[继续添加='y' 不再添加='任意字符']\n");
	char YorN = 0;
	printf("\t>请选择：");
	scanf_s("%s", &YorN, 2);
	if (YorN == 'y' || YorN == 'Y')
		add_train_information();
	else
		administrator_login_interface_menu();
}

/**
 * @function: fpos_t display_all_train_information(void)
 * @description: 显示所有火车信息
 * @param {*}
 * @return {list_num}显示的列车信息总数
 */
fpos_t display_all_train_information(void)
{
	//system("cls");
	//printf("\t=============================\n");
	//printf("\t\t火车票订票系统\n");
	//printf("\t=============================\n");
	//printf("\n\t[显示火车信息]\n");
	TICKET read_tickets_tmp;
	FILE* file_display_tickets;
	fpos_t total_tickets = 0;
	while (fopen_s(&file_display_tickets, all_tickets_file_path, "rb") || !file_display_tickets)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t||=================================================================================||\n");
	printf("\t||编号+列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  +余票||\n");
	printf("\t||=================================================================================||\n");
	while (fread(&read_tickets_tmp, sizeof(TICKET), 1, file_display_tickets))
	{
		printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f|%-4d||\n", ++total_tickets, read_tickets_tmp.train_num,
			read_tickets_tmp.start_station, read_tickets_tmp.arrive_station, read_tickets_tmp.start_time,
			read_tickets_tmp.arrive_time, read_tickets_tmp.ticket_price, read_tickets_tmp.ticket_total);
	}
	printf("\t||=================================================================================||\n");
	if (fclose(file_display_tickets))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//printf("\n\t==显示完成==\n\n");
	return total_tickets;
	//system("pause");
	//menu_interface_of_booking_system();
}

/**
 * @function: void order_train_tickets(void)
 * @description: 订购火车票
 * @param {*}
 * @return {*}
 * @return {*}
 */
void order_train_tickets(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t[订购火车票]\n\n");
	FILE* file_search_data;
	FILE* file_save_user_order_data;
	TICKET read_tickets_tmp;
	TICKET read_user_tickets;
	fpos_t select_order_num;
	fpos_t pos;
	fpos_t total_order = 0;
	size_t nmemb = 1;
	size_t fwrite_return;
	char input_start_station[START_STATION_LEN];
	char input_arrive_station[ARRIVE_STATION_LEN];
	printf("\t请输入起始站：");
	scanf_s("%s", &input_start_station, START_STATION_LEN);
	printf("\t请输入终点站：");
	scanf_s("%s", &input_arrive_station, ARRIVE_STATION_LEN);
	//从文件比对输入的起始站和终点站
	file_search_data = compare_train_information(input_start_station, input_arrive_station);
	printf("\n\t||=================================================================================||\n");
	printf("\t||编号+列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  +余票||\n");
	printf("\t||=================================================================================||\n");
	//将余票大于0的列车信息显示出来
	while (fread(&read_tickets_tmp, sizeof(TICKET), 1, file_search_data))
	{
		if (read_tickets_tmp.ticket_total > 0)
		{
			printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f|%-4d||\n", ++total_order, read_tickets_tmp.train_num,
				read_tickets_tmp.start_station, read_tickets_tmp.arrive_station, read_tickets_tmp.start_time,
				read_tickets_tmp.arrive_time, read_tickets_tmp.ticket_price, read_tickets_tmp.ticket_total);
		}
	}
	printf("\t||=================================================================================||\n");
	rewind(file_search_data);
	if (total_order == 0) //如果没有车票数据
	{
		printf("\n\t=未查询到任何内容=\n\n");
		system("pause");
		order_train_tickets();
	}
	printf("\n\t==显示完成==\n\n");
	printf("\n\t=请选择需要订购的火车票编号=\n");
	printf("\n\t>请选择：");
	scanf_s("%lld", &select_order_num);
	pos = (select_order_num - 1) * sizeof(TICKET); //将编号转为将文件指针定位到需要输出的数据块位置
	//输入的编号大于火车信息总数或小于等于0，则重新输入编号
	while (select_order_num > total_order || select_order_num <= 0)
	{
		system("cls");
		printf("\t=============================\n");
		printf("\t\t火车票订票系统\n");
		printf("\t=============================\n");
		printf("\n\t[订购火车票]\n\n");
		printf("\n\t||=================================================================================||\n");
		printf("\t||编号+列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  +余票||\n");
		printf("\t||=================================================================================||\n");
		//将余票大于0的列车信息显示出来
		while (fread(&read_tickets_tmp, sizeof(TICKET), 1, file_search_data))
		{
			if (read_tickets_tmp.ticket_total > 0)
			{
				printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f|%-4d||\n", ++total_order, read_tickets_tmp.train_num,
					read_tickets_tmp.start_station, read_tickets_tmp.arrive_station, read_tickets_tmp.start_time,
					read_tickets_tmp.arrive_time, read_tickets_tmp.ticket_price, read_tickets_tmp.ticket_total);
			}
		}
		printf("\t||=================================================================================||\n");
		rewind(file_search_data);
		printf("\t=输入的列车编号不存在=\n");
		printf("\n\t>请重新输入编号：");
		scanf_s("%lld", &select_order_num);
		pos = (select_order_num - 1) * sizeof(TICKET); //将编号转为将文件指针定位到需要输出的数据块位置
	}
	//定位到文件中需要订购的数据块，进行显示
	if (fsetpos(file_search_data, &pos))
	{
		printf("\n\t=定位输出数据块出错=\n");
		exit(EXIT_FAILURE);
	}
	//读出需要订购的数据块
	if (!fread(&read_tickets_tmp, sizeof(TICKET), 1, file_search_data))
	{
		printf("\n\t=读取文件出现错误=\n");
		exit(EXIT_FAILURE);
	}
	fclose(file_search_data); //不需要临时文件了，将其关闭
	while (fopen_s(&file_save_user_order_data, user_tickets_file_path, "rb") || !file_save_user_order_data)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//判断该票是否已经订购过了
	while (fread(&read_user_tickets, sizeof(TICKET), 1, file_save_user_order_data))
	{
		if (!strcmp(read_user_tickets.train_num, read_tickets_tmp.train_num) && \
			!strcmp(read_user_tickets.start_station, read_tickets_tmp.start_station) && \
			!strcmp(read_user_tickets.arrive_station, read_tickets_tmp.arrive_station) && \
			!strcmp(read_user_tickets.start_time, read_tickets_tmp.start_time) && \
			!strcmp(read_user_tickets.arrive_time, read_tickets_tmp.arrive_time))
		{
			printf("\n\t=已订购过这列火车=\n");
			printf("\n\t>是否继续订票？[继续订票='y' 不再订票='任意字符']\n");
			char YorN = 0;
			printf("\t>请选择：");
			scanf_s("%s", &YorN, 2);
			if (YorN == 'y' || YorN == 'Y')
				order_train_tickets();
			else
				user_login_interface_menu();
		}
	}
	if (fclose(file_save_user_order_data)) //关闭文件
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//显示选中要订购的列车信息
	printf("\n\t||============================================================================||\n");
	printf("\t||编号+列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  ||\n");
	printf("\t||============================================================================||\n");
	printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f||\n", select_order_num, read_tickets_tmp.train_num,
		read_tickets_tmp.start_station, read_tickets_tmp.arrive_station, read_tickets_tmp.start_time,
		read_tickets_tmp.arrive_time, read_tickets_tmp.ticket_price);
	printf("\t||============================================================================||\n");
	//打开对应用户的车票数据文件，将订票火车数据存入
	while (fopen_s(&file_save_user_order_data, user_tickets_file_path, "ab") || !file_save_user_order_data)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//订票数据写入到对应用户的购票数据文件
	fwrite_return = fwrite(&read_tickets_tmp, sizeof(TICKET), nmemb, file_save_user_order_data);
	if (fwrite_return != nmemb)
	{
		printf("\n\t=写入数据时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(file_save_user_order_data)) //关闭文件
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//将总列车数据文件的对应订购了的车票余票减一
	if (the_change_of_the_remaining_train_tickets(read_tickets_tmp, -1))
	{
		printf("\n\t=更新原列车余票时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t==订票成功==\n\n");
	system("pause");
	user_login_interface_menu();
}

/**
 * @function: void return_the_ticket(void)
 * @description: 退票
 * @param {* }
 * @return {*}
 * @return {*}
 */
void return_the_ticket(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t[退票]\n\n");
	FILE* file_total_tickets;
	TICKET read_total_user_tickets;
	fpos_t pos;
	fpos_t total_user_ticket = 0;
	fpos_t select_num = 0;
	while (fopen_s(&file_total_tickets, user_tickets_file_path, "rb") || !file_total_tickets)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//显示当前用户的所有的订票信息
	printf("\t||============================================================================||\n");
	printf("\t||编号+列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  ||\n");
	printf("\t||============================================================================||\n");
	while (fread(&read_total_user_tickets, sizeof(TICKET), 1, file_total_tickets))
	{
		printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f||\n", ++total_user_ticket,
			read_total_user_tickets.train_num, read_total_user_tickets.start_station,
			read_total_user_tickets.arrive_station, read_total_user_tickets.start_time,
			read_total_user_tickets.arrive_time, read_total_user_tickets.ticket_price);
	}
	printf("\t||============================================================================||\n");
	if (fclose(file_total_tickets))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//选择需要退掉的票
	printf("\n\t=请输入需要退票的列车编号=");
	printf("\n\t>请输入编号：");
	scanf_s("%lld", &select_num);
	if (total_user_ticket == 0)
	{
		printf("\n\t=当前没有订票信息=\n");
		system("pause");
		user_login_interface_menu();
	}
	while (select_num > total_user_ticket || select_num <= 0)
	{
		getchar();
		printf("\n\t=输入的编号不存在=\n");
		printf("\n\t=请重新输入需要退票的列车编号=");
		printf("\n\t>请输入编号：");
		scanf_s("%lld", &select_num);
	}
	//打开文件为了找到并显示待退票的数据块
	while (fopen_s(&file_total_tickets, all_tickets_file_path, "rb") || !file_total_tickets)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_total_tickets);
	pos = (select_num - 1) * sizeof(TICKET); //将编号转为将文件指针定位到需要退票的数据块位置
	//定位到文件中需要退票的数据块，进行显示
	if (fsetpos(file_total_tickets, &pos))
	{
		printf("\n\t=定位输出数据块出错=\n");
		exit(EXIT_FAILURE);
	}
	//读出需要退票的数据
	if (!fread(&read_total_user_tickets, sizeof(TICKET), 1, file_total_tickets))
	{
		printf("\n\t=读取文件出现错误=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(file_total_tickets))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//在用户订票文件中移除相关的列车信息
	remove_train_information(read_total_user_tickets, user_tickets_file_path);
	//待退票的火车在总火车票数据中余票加一
	if (the_change_of_the_remaining_train_tickets(read_total_user_tickets, 1))
	{
		printf("\n\t=更新原列车余票时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t=退票成功=\n");
	printf("\n\t>是否继续退票?[继续退票='y' 不再退票='任意字符']\n");
	char YorN = 0;
	printf("\t>请选择：");
	scanf_s("%s", &YorN, 2);
	if (YorN == 'y' || YorN == 'Y')
		return_the_ticket();
	else
		user_login_interface_menu();
}

/**
 * @function: void modify_train_information(void)
 * @description: 修改火车信息
 * @param {*}
 * @return {*}
 */
void modify_train_information(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t[修改火车信息]\n");
	fpos_t total_trains;
	total_trains = display_all_train_information(); //显示所有火车信息，并返回列车信息总数
	fpos_t pos = 0;
	fpos_t select_num;
	TICKET modify_tickets_tmp;
	TICKET after_change_tickets;
	FILE* file_modify_tickets;
	printf("\n\t=请输入需要修改的列车编号=");
	printf("\n\t>请输入编号：");
	scanf_s("%lld", &select_num);
	pos = (select_num - 1) * sizeof(TICKET); //将编号转为将文件指针定位到需要输出的数据块位置
	//输入的编号大于火车信息总数或小于等于0，则重新输入编号
	while (select_num > total_trains || select_num <= 0)
	{
		system("cls");
		printf("\t=============================\n");
		printf("\t\t火车票订票系统\n");
		printf("\t=============================\n");
		printf("\n\t[修改火车信息]\n");
		total_trains = display_all_train_information(); //显示所有火车信息
		printf("\t=输入的列车编号不存在=");
		printf("\n\t>请重新输入编号：");
		scanf_s("%lld", &select_num);
		pos = (select_num - 1) * sizeof(TICKET);
	}
	//第一次打开文件为了找到并显示待修改的数据块
	while (fopen_s(&file_modify_tickets, all_tickets_file_path, "rb") || !file_modify_tickets)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_modify_tickets);
	//第一次定位到文件中需要修改的数据块，进行显示
	if (fsetpos(file_modify_tickets, &pos))
	{
		printf("\n\t=定位输出数据块出错=\n");
		exit(EXIT_FAILURE);
	}
	//读出需要修改的数据块
	if (!fread(&modify_tickets_tmp, sizeof(TICKET), 1, file_modify_tickets))
	{
		printf("\n\t=读取文件出现错误=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(file_modify_tickets))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	system("cls");
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t=待修改的火车信息=");
	printf("\n\t||=================================================================================||\n");
	printf("\t||编号+列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  +余票||\n");
	printf("\t||=================================================================================||\n");
	printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f|%-4d||\n", select_num, modify_tickets_tmp.train_num,
		modify_tickets_tmp.start_station, modify_tickets_tmp.arrive_station, modify_tickets_tmp.start_time,
		modify_tickets_tmp.arrive_time, modify_tickets_tmp.ticket_price, modify_tickets_tmp.ticket_total);
	printf("\t||=================================================================================||\n");
	//选择修改部分
	printf("\n\t======================================================================================\n");
	printf("\t1.列车号/2.起始站/3.终点站/4.发车时间/5.到站时间/6.票价/7.余票/8.所有数据/9.返回主界面  ");
	printf("\n\t======================================================================================\n");
	printf("\n\t=请选择要更改的数据=\n");
	printf("\t>请输入：");
	size_t change_content;
	scanf_s("%d", &change_content);
	//重新录入所有列车信息，并将更改后的数据返回
	after_change_tickets = input_the_changed_train_information(modify_tickets_tmp, change_content);
	printf("\n\t=修改后的火车信息=");
	printf("\n\t||=================================================================================||\n");
	printf("\t||编号+列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  +余票||\n");
	printf("\t||=================================================================================||\n");
	printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f|%-4d||\n", select_num, after_change_tickets.train_num,
		after_change_tickets.start_station, after_change_tickets.arrive_station, after_change_tickets.start_time,
		after_change_tickets.arrive_time, after_change_tickets.ticket_price, after_change_tickets.ticket_total);
	printf("\t||=================================================================================||\n");
	//第二次打开文件为了写入待修改的数据块
	while (fopen_s(&file_modify_tickets, all_tickets_file_path, "rb+") || !file_modify_tickets)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_modify_tickets);
	//第二次定位到文件中需要修改的数据块，进行更改
	if (fsetpos(file_modify_tickets, &pos))
	{
		printf("\n\t=定位输出数据块出错=\n");
		exit(EXIT_FAILURE);
	}
	//写入更改后的数据块到文件
	size_t fwrite_return = fwrite(&after_change_tickets, sizeof(TICKET), 1, file_modify_tickets);
	if (fwrite_return != 1)
	{
		printf("\n\t=写入文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(file_modify_tickets))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	printf("\t==修改成功==\n");
	printf("\t>是否继续修改?[继续修改='y' 不再修改='任意字符']\n");
	char YorN = 0;
	printf("\t>请选择：");
	scanf_s("%s", &YorN, 2);
	if (YorN == 'y' || YorN == 'Y')
		modify_train_information();
	else
		administrator_login_interface_menu();
}

/**
 * @function: void delete_train_information(void)
 * @description: 删除火车信息
 * @param {*}
 * @return {*}
 * @return {*}
 */
void delete_train_information(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t[删除火车信息]\n\n");
	FILE* file_all_tickets_pos;
	TICKET read_delete_tickets;
	fpos_t pos;
	fpos_t select_num = 0;
	fpos_t total_trains = 0;
	total_trains = display_all_train_information(); //显示所有火车信息
	printf("\n\t=请输入需要删除的列车编号=");
	printf("\n\t>请输入编号：");
	scanf_s("%lld", &select_num);
	while (select_num > total_trains || select_num <= 0)
	{
		printf("\n\t=请重新输入需要删除的列车编号=");
		printf("\n\t>请输入编号：");
		scanf_s("%lld", &select_num);
	}
	pos = (select_num - 1) * sizeof(TICKET); //将编号转为将文件指针定位到需要输出的数据块位置
	//打开文件为了找到并显示待删除的数据块
	while (fopen_s(&file_all_tickets_pos, all_tickets_file_path, "rb") || !file_all_tickets_pos)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_all_tickets_pos);
	//定位到文件中需要删除的数据块
	if (fsetpos(file_all_tickets_pos, &pos))
	{
		printf("\n\t=定位输出数据块出错=\n");
		exit(EXIT_FAILURE);
	}
	//读出需要删除的数据块
	if (!fread(&read_delete_tickets, sizeof(TICKET), 1, file_all_tickets_pos))
	{
		printf("\n\t=读取文件出现错误=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(file_all_tickets_pos))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t=待删除信息=\n");
	printf("\n\t||=================================================================================||\n");
	printf("\t||编号+列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  +余票||\n");
	printf("\t||=================================================================================||\n");
	printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f|%-4d||\n", select_num, read_delete_tickets.train_num,
		read_delete_tickets.start_station, read_delete_tickets.arrive_station, read_delete_tickets.start_time,
		read_delete_tickets.arrive_time, read_delete_tickets.ticket_price, read_delete_tickets.ticket_total);
	printf("\t||=================================================================================||\n");
	//移除相关的列车信息
	remove_train_information(read_delete_tickets, all_tickets_file_path);
	printf("\n\t=删除成功=\n");
	printf("\t>是否继续删除?[继续删除='y' 不再删除='任意字符']\n");
	char YorN = 0;
	printf("\t>请选择：");
	scanf_s("%s", &YorN, 2);
	if (YorN == 'y' || YorN == 'Y')
		delete_train_information();
	else
		administrator_login_interface_menu();
}

/**
 * @function: void remove_train_information(TICKET delete_ticket_data, const char* which_file)
 * @description: 移除相关的火车信息
 * @param {TICKET delete_ticket_data}待删除的火车票信息
 * @param {char* which_file}待删除火车票信息的文件夹
 * @return {*}
 * @return {*}
 */
void remove_train_information(TICKET delete_ticket_data, const char* which_file)
{
	FILE* file_total_tickets_del;
	FILE* tmpfile_dont_delete;
	TICKET read_dont_delete;
	TICKET read_back_file;
	tmpfile_s(&tmpfile_dont_delete); //创建临时文件用来暂存不删除的内容
	//打开总的火车数据文件，将不需删除的数据先放临时文件中
	while (fopen_s(&file_total_tickets_del, which_file, "rb") || !file_total_tickets_del)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_total_tickets_del);
	while (fread(&read_dont_delete, sizeof(TICKET), 1, file_total_tickets_del))
	{
		//存下不需要删除的
		if (strcmp(delete_ticket_data.train_num, read_dont_delete.train_num) ||
			strcmp(delete_ticket_data.start_station, read_dont_delete.start_station) ||
			strcmp(delete_ticket_data.arrive_station, read_dont_delete.arrive_station) ||
			strcmp(delete_ticket_data.start_time, read_dont_delete.start_time) ||
			strcmp(delete_ticket_data.arrive_time, read_dont_delete.arrive_time))
		{
			fwrite(&read_dont_delete, sizeof(TICKET), 1, tmpfile_dont_delete); //将不需要删除的火车数据存入临时文件
		}
	}
	if (fclose(file_total_tickets_del))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//把临时文件中的不需要删除的火车数据再全部放回总的火车数据文件
	while (fopen_s(&file_total_tickets_del, which_file, "wb") || !file_total_tickets_del)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	rewind(tmpfile_dont_delete);
	//将不需要删除的火车数据放回总的火车数据文件
	while (fread(&read_back_file, sizeof(TICKET), 1, tmpfile_dont_delete))
	{
		fwrite(&read_back_file, sizeof(TICKET), 1, file_total_tickets_del);
	}
	if (fclose(file_total_tickets_del))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(tmpfile_dont_delete))
	{
		printf("\n\t=关闭临时文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: void display_user_booking_information(void)
 * @description: 显示用户订单信息
 * @param {*}
 * @return {*}
 */
void display_user_booking_information(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t火车票订票系统\n");
	printf("\t=============================\n");
	printf("\n\t[显示用户订单信息]\n\n");
	FILE* file_display_booking;
	FILE* file_user;
	TICKET read_display_booking;
	USER read_user;
	fpos_t total_user_ticket = 0;
	//打开用户文件，显示当前用户信息
	while (fopen_s(&file_user, all_users_file_path, "rb") || !file_user)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t||=================================================||\n");
	printf("\t||  姓名  +   手机号   +     身份证号     +用户类型||\n");
	printf("\t||=================================================||\n");
	while (fread(&read_user, sizeof(USER), 1, file_user))
	{
		if (!strcmp(read_user.phone_account_num, account_file_name))
		{
			printf("\t||%-8s|%-12s|%-18s|%-8s||\n", read_user.user_name,
				read_user.phone_account_num, read_user.ID_num, read_user.user_type);
			break;
		}
	}
	if (fclose(file_user))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//打开用户订票数据文件	
	while (fopen_s(&file_display_booking, user_tickets_file_path, "rb") || !file_display_booking)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	//显示当前用户的所有的订票信息
	printf("\t||============================================================================||\n");
	printf("\t||编号+列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  ||\n");
	printf("\t||============================================================================||\n");
	while (fread(&read_display_booking, sizeof(TICKET), 1, file_display_booking))
	{
		printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f||\n", ++total_user_ticket,
			read_display_booking.train_num, read_display_booking.start_station,
			read_display_booking.arrive_station, read_display_booking.start_time,
			read_display_booking.arrive_time, read_display_booking.ticket_price);
	}
	printf("\t||============================================================================||\n");
	if (fclose(file_display_booking))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t==显示完成==\n\n");
	system("pause");
	user_login_interface_menu();
}

/**
 * @function: int save_a_newly_train_data_to_the_file(TICKET save_new_ticket)
 * @description: 保存一个新的火车数据到文件
 * @return {MY_FAIL}添加错误
 * @return {MY_SUCCESS}添加成功
 */
int save_a_newly_train_data_to_the_file(TICKET save_new_ticket)
{
	FILE* file_save_ticket;
	size_t nmemb = 1;
	size_t fwrite_return;
	while (fopen_s(&file_save_ticket, all_tickets_file_path, "ab") || !file_save_ticket)
	{
		printf("\n\t=打开文件时出现错误=\n");
		return MY_FAIL;
	}
	fwrite_return = fwrite(&save_new_ticket, sizeof(TICKET), nmemb, file_save_ticket); //写入数据到文件
	if (fwrite_return != nmemb)
		return MY_FAIL;
	if (fclose(file_save_ticket)) //关闭文件
		return MY_FAIL;
	printf("\n\t||============================================================================||\n");
	printf("\t||列车号+  起始站  +  终点站  +    发车时间    +    到站时间    +  票价  +余票||\n");
	printf("\t||============================================================================||\n");
	printf("\t||%-6s|%-10s|%-10s|%-16s|%-16s|￥%-6.1f|%-4d||\n", save_new_ticket.train_num,
		save_new_ticket.start_station, save_new_ticket.arrive_station, save_new_ticket.start_time,
		save_new_ticket.arrive_time, save_new_ticket.ticket_price, save_new_ticket.ticket_total);
	printf("\t||============================================================================||\n");
	return MY_SUCCESS;
}

/**
 * @function: int save_a_newly_registered_user_to_the_file(USER save_new_user)
 * @description: 保存一个新注册的用户到文件
 * @param {USER psave_new_user}新注册的用户数据
 * @return {MY_FAIL}添加错误
 * @return {MY_SUCCESS}添加成功
 */
int save_a_newly_registered_user_to_the_file(USER save_new_user)
{
	FILE* file_save_user;
	size_t nmemb = 1;
	size_t fwrite_return;
	while (fopen_s(&file_save_user, all_users_file_path, "ab") || !file_save_user)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	fwrite_return = fwrite(&save_new_user, sizeof(USER), nmemb, file_save_user); //写入数据到文件
	if (fwrite_return != nmemb)
		return MY_FAIL;
	if (fclose(file_save_user)) //关闭文件
		return MY_FAIL;
	printf("\n\t||=================================================||\n");
	printf("\t||  姓名  +   手机号   +     身份证号     +用户类型||\n");
	printf("\t||=================================================||\n");
	printf("\t||%-8s|%-12s|%-18s|%-8s||\n", save_new_user.user_name,
		save_new_user.phone_account_num, save_new_user.ID_num, save_new_user.user_type);
	printf("\t||=================================================||\n");
	return MY_SUCCESS;
}

/**
 * @function: char build_user_train_file_name_path(char* account_file_name)
 * @description: 通过用户名生成用户火车订单数据文件路径
 * @param {char* account_file_name}用户名
 * @return {user_tickets_file_path}用户火车文件路径
 */
char* build_user_train_file_name_path(char* account_file_name)
{
	static char user_ticket_file_path_part1_tmp[USER_TICKET_FILE_PATH_LEN];
	strcpy_s(user_ticket_file_path_part1_tmp, sizeof(user_ticket_file_path_part1_tmp), user_tickets_file_path_part1);
	strcat_s(user_ticket_file_path_part1_tmp, sizeof(user_ticket_file_path_part1_tmp), account_file_name); //用户名与存放用户订单数据文件夹路径连接
	strcat_s(user_ticket_file_path_part1_tmp, sizeof(user_ticket_file_path_part1_tmp), file_extension);    //用户订单文件夹下的用户订单文件与.dat后缀连接
	return user_ticket_file_path_part1_tmp;
}

/**
 * @function: int check_whether_the_train_data_exists(TICKET check_ticket_data)
 * @description: 检测列车数据是否已经存在
 * @param {TICKET check_ticket_data}待检测的结构体数据
 * @return {MY_FAIL}比对失败
 * @return {MY_SUCCESS}比对成功
 */
int check_whether_the_train_data_exists(TICKET check_ticket_data)
{
	FILE* file_check_ticket;
	TICKET read_tickets_tmp;
	while (fopen_s(&file_check_ticket, all_tickets_file_path, "ab+") || !file_check_ticket)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_check_ticket); //将文件位置指示器移动到给定文件流的开头(光标回到文件开头)
	while (fread(&read_tickets_tmp, sizeof(TICKET), 1, file_check_ticket))
	{
		//如果有相同的列车信息
		if (!strcmp(check_ticket_data.train_num, read_tickets_tmp.train_num) &&
			!strcmp(check_ticket_data.start_station, read_tickets_tmp.start_station) &&
			!strcmp(check_ticket_data.arrive_station, read_tickets_tmp.arrive_station) &&
			!strcmp(check_ticket_data.start_time, read_tickets_tmp.start_time) &&
			!strcmp(check_ticket_data.arrive_time, read_tickets_tmp.arrive_time))
		{
			if (fclose(file_check_ticket))
			{
				printf("\n\t=关闭文件时出现错误=\n");
				exit(EXIT_FAILURE);
			}
			return MY_SUCCESS;
		}
	}
	if (fclose(file_check_ticket))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	return MY_FAIL;
}

/**
 * @function: int check_whether_the_user_data_exists(USER check_user_data)
 * @description: 检测用户数据是否已经存在
 * @param {USER check_user_data}待检测的用户数据
 * @return {MY_FAIL}比对失败，不存在
 * @return {MY_SUCCESS}比对成功，已存在
 */
int check_whether_the_user_data_exists(USER check_user_data)
{
	FILE* file_check_user;
	USER read_users_tmp;
	while (fopen_s(&file_check_user, all_users_file_path, "rb") || !file_check_user)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	while (fread(&read_users_tmp, sizeof(USER), 1, file_check_user))
	{
		if (!strcmp(check_user_data.phone_account_num, read_users_tmp.phone_account_num) ||
			!strcmp(check_user_data.ID_num, read_users_tmp.ID_num)) //如果有相同的手机账号
		{
			if (fclose(file_check_user))
			{
				printf("\n\t=关闭文件时出现错误=\n");
				exit(EXIT_FAILURE);
			}
			return MY_SUCCESS;
		}
	}
	if (fclose(file_check_user))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	return MY_FAIL;
}

/**
 * @function: TICKET* input_the_changed_train_information(TICKET change_train, int select_num)
 * @description: 输入更改的所有火车数据
 * @param {TICKET change_train}待更改的火车数据
 * @param {int select_num}待更改的部分[1.列车号/2.起始站/3.终点站/4.发车时间/5.到站时间/6.票价/7.余票/8.所有数据]
 * @return {TICKET}返回修改后的火车信息
 */
TICKET input_the_changed_train_information(TICKET change_train, int select_num)
{
	switch (select_num)
	{
	case 1: //更改列车号
		printf("\n\t=请输入新的[列车号]=\n");
		printf("\t列车号：");
		scanf_s("%s", change_train.train_num, TRAIN_NUM_LEN);
		while (!check_whether_the_train_data_exists(change_train)) //列车已存在，则重新录入
		{
			printf("\n\t=该列车已存在，请重新录入=\n");
			printf("\n\t=请输入新的[列车号]=\n");
			printf("\t列车号：");
			scanf_s("%s", change_train.train_num, TRAIN_NUM_LEN);
		}
		break;
	case 2: //更改起始站
		printf("\n\t=请输入新的[起始站]=\n");
		printf("\t起始站：");
		scanf_s("%s", change_train.start_station, START_STATION_LEN);
		while (!check_whether_the_train_data_exists(change_train)) //列车已存在，则重新录入
		{
			printf("\n\t=该列车已存在，请重新录入=\n");
			printf("\n\t=请输入新的[起始站]=\n");
			printf("\t起始站：");
			scanf_s("%s", change_train.start_station, START_STATION_LEN);
		}
		break;
	case 3: //更改终点站
		printf("\n\t=请输入新的[终点站]=\n");
		printf("\t终点站：");
		scanf_s("%s", change_train.arrive_station, ARRIVE_STATION_LEN);
		while (!check_whether_the_train_data_exists(change_train)) //列车已存在，则重新录入
		{
			printf("\n\t=该列车已存在，请重新录入=\n");
			printf("\n\t=请输入新的[终点站]=\n");
			printf("\t起始站：");
			scanf_s("%s", change_train.start_station, ARRIVE_STATION_LEN);
		}
		break;
	case 4: //更改发车时间
		printf("\n\t=请输入新的[发车时间]=\n");
		printf("\t发车时间：");
		scanf_s("%s", change_train.start_time, START_TIME_LEN);
		while (!check_whether_the_train_data_exists(change_train)) //列车已存在，则重新录入
		{
			printf("\n\t=该列车已存在，请重新录入=\n");
			printf("\n\t=请输入新的[发车时间]=\n");
			printf("\t起始站：");
			scanf_s("%s", change_train.start_station, START_TIME_LEN);
		}
		break;
	case 5: //更改到站时间
		printf("\n\t=请输入新的[到站时间]=\n");
		printf("\t到站时间：");
		scanf_s("%s", change_train.arrive_time, ARRIVE_TIME_LEN);
		while (!check_whether_the_train_data_exists(change_train)) //列车已存在，则重新录入
		{
			printf("\n\t=该列车已存在，请重新录入=\n");
			printf("\n\t=请输入新的[到站时间]=\n");
			printf("\t到站时间：");
			scanf_s("%s", change_train.arrive_time, ARRIVE_TIME_LEN);
		}
		break;
	case 6: //更改票价
		printf("\n\t=请输入新的[票价]=\n");
		printf("\t票价：");
		scanf_s("%f", &change_train.ticket_price);
		while (change_train.ticket_price < 0)
		{
			printf("\n\t=票价必须大于0，请重新输入=\n");
			printf("\t票价：");
			scanf_s("%f", &change_train.ticket_price);
		}
		break;
	case 7: //更改余票
		printf("\n\t=请输入新的[余票]=\n");
		printf("\t余票：");
		scanf_s("%d", &change_train.ticket_total);
		while (change_train.ticket_total < 0)
		{
			printf("\n\t=余票必须大于0，请重新输入=\n");
			printf("\t余票：");
			scanf_s("%d", &change_train.ticket_total);
		}
		break;
	case 8: //更改全部列车信息
		printf("\n\t=请输入[全新]的火车信息=\n");
		printf("\t列车号：");
		scanf_s("%s", change_train.train_num, TRAIN_NUM_LEN);
		printf("\t起始站：");
		scanf_s("%s", change_train.start_station, START_STATION_LEN);
		printf("\t终点站：");
		scanf_s("%s", change_train.arrive_station, ARRIVE_STATION_LEN);
		printf("\t发车时间：");
		scanf_s("%s", change_train.start_time, START_TIME_LEN);
		printf("\t到站时间：");
		scanf_s("%s", change_train.arrive_time, ARRIVE_TIME_LEN);
		//判断输入的列车是否存在
		while (!check_whether_the_train_data_exists(change_train)) //列车已存在，则重新录入
		{
			printf("\n\t=该列车已存在，请重新录入=\n");
			printf("\n\t=请重新输入[全新]的火车信息=\n");
			printf("\t列车号：");
			scanf_s("%s", change_train.train_num, TRAIN_NUM_LEN);
			printf("\t起始站：");
			scanf_s("%s", change_train.start_station, START_STATION_LEN);
			printf("\t终点站：");
			scanf_s("%s", change_train.arrive_station, ARRIVE_STATION_LEN);
			printf("\t发车时间：");
			scanf_s("%s", change_train.start_time, START_TIME_LEN);
			printf("\t到站时间：");
			scanf_s("%s", change_train.arrive_time, ARRIVE_TIME_LEN);
		}
		printf("\t票价：");
		scanf_s("%f", &change_train.ticket_price);
		while (change_train.ticket_price < 0)
		{
			printf("\n\t=票价必须大于0，请重新输入=\n");
			printf("\t票价：");
			scanf_s("%f", &change_train.ticket_price);
		}
		printf("\t余票：");
		scanf_s("%d", &change_train.ticket_total);
		while (change_train.ticket_total < 0)
		{
			printf("\n\t=余票必须大于0，请重新输入=\n");
			printf("\t余票：");
			scanf_s("%d", &change_train.ticket_total);
		}
		break;
	case 9: //返回主界面
		administrator_login_interface_menu();
	default:
		getchar(); //从标准输入 stdin 获取一个字符<一个无符号字符>(清除输入的错误信息对下次输入的干扰)
		printf("\n\t=输入的编号错误，请重新输入=\n");
		printf("\n\t======================================================================================\n");
		printf("\t1.列车号/2.起始站/3.终点站/4.发车时间/5.到站时间/6.票价/7.余票/8.所有数据/9.返回主界面  ");
		printf("\n\t======================================================================================\n");
		printf("\n\t=请选择要更改的数据=\n");
		printf("\t>请输入：");
		size_t change_content;
		scanf_s("%d", &change_content);
		input_the_changed_train_information(change_train, change_content);
	}
	return change_train;
}

/**
 * @function: FILE* compare_train_information(char* input_start_station, char* input_arrive_station)
 * @description: 比对火车信息,并返回比对符合条件的火车信息数据
 * @param {char* input_start_station}待比对的起始站
 * @param {char* input_arrive_station}待比对的终点站
 * @return {tmp_file}返回临时文件的文件流指针(比对符合的元素)
 */
FILE* compare_train_information(char* input_start_station, char* input_arrive_station)
{
	TICKET read_tickets_tmp;
	FILE* compare_file;
	FILE* tmp_file;
	fpos_t list_num = 0;
	if (tmpfile_s(&tmp_file))
	{
		printf("\n\t=创建临时文件出现错误=\n");
		exit(EXIT_FAILURE);
	}
	while (fopen_s(&compare_file, all_tickets_file_path, "rb") || !compare_file)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	while (fread(&read_tickets_tmp, sizeof(TICKET), 1, compare_file))
	{
		if (strcmp(input_start_station, read_tickets_tmp.start_station) == 0 &&
			strcmp(input_arrive_station, read_tickets_tmp.arrive_station) == 0)
			fwrite(&read_tickets_tmp, sizeof(TICKET), 1, tmp_file); //将对比成功的火车数据存入临时文件
	}
	if (fclose(compare_file))
	{
		printf("\n\t=关闭文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	rewind(tmp_file); //将文件位置指示器移动到给定文件流的开头(光标回到文件开头)
	return tmp_file;
}

/**
 * @function: int the_change_of_the_remaining_train_tickets(TICKET read_tickets_tmp, int add_or_sub)
 * @description: 火车余票信息加减变化
 * @param {TICKET read_tickets_tmp}待更改余票的数据块
 * @param {int add_or_sub}增加还是减少(1 or -1)
 * @return {MY_FAIL}余票更改失败
 * @return {MY_SUCCESS}余票更改成功
 */
int the_change_of_the_remaining_train_tickets(TICKET read_tickets_tmp, int add_or_sub)
{
	FILE* file_ticket_total_change;
	TICKET read_all_tickets;
	fpos_t pos;
	fpos_t order_pot = 0;	
	size_t nmemb = 1;
	size_t fwrite_return;
	//打开所有火车数据文件，余票减一
	//表示代码取消引用可能的 null 指针。 如果该指针的值无效，则结果是未定义的。 若要解决此问题，请在使用之前验证指针
	while (fopen_s(&file_ticket_total_change, all_tickets_file_path, "rb+") || !file_ticket_total_change)
	{
		printf("\n\t=打开文件时出现错误=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_ticket_total_change);
	//找到已经订购了的车票
	while (fread(&read_all_tickets, sizeof(TICKET), 1, file_ticket_total_change))
	{
		++order_pot;
		if (!strcmp(read_all_tickets.train_num, read_tickets_tmp.train_num) &&
			!strcmp(read_all_tickets.start_station, read_tickets_tmp.start_station) &&
			!strcmp(read_all_tickets.arrive_station, read_tickets_tmp.arrive_station) &&
			!strcmp(read_all_tickets.start_time, read_tickets_tmp.start_time) &&
			!strcmp(read_all_tickets.arrive_time, read_tickets_tmp.arrive_time))
		{
			break; //找到了订购了的票
		}
	}
	if (add_or_sub == 1)
		read_all_tickets.ticket_total++; //订购了的火车在总的火车数据文件中的余票加一
	if (add_or_sub == -1)
		read_all_tickets.ticket_total--; //订购了的火车在总的火车数据文件中的余票减一
	rewind(file_ticket_total_change);
	pos = (order_pot - 1) * sizeof(TICKET);
	if (fsetpos(file_ticket_total_change, &pos))
	{
		printf("\n\t=定位输出数据块出错=\n");
		//exit(EXIT_FAILURE);
		return MY_FAIL;
	}
	fwrite_return = fwrite(&read_all_tickets, sizeof(TICKET), nmemb, file_ticket_total_change);
	if (fwrite_return != nmemb)
	{
		printf("\n\t=写入数据时出现错误=\n");
		//exit(EXIT_FAILURE);
		return MY_FAIL;
	}
	if (fclose(file_ticket_total_change)) //关闭文件
	{
		printf("\n\t=关闭文件时出现错误=\n");
		//exit(EXIT_FAILURE);
		return MY_FAIL;
	}
	return MY_SUCCESS;
}

/**
 * @function: void get_password(char* password, int password_len)
 * @description: 输入的密码变星号显示
 * @param {*}
 * @return {*}
 */
void get_password(char* password, int password_len)
{
	char ch = 0;
	int i = 0;
	while (i < password_len)
	{
		ch = getch();
		if (ch == '\r')   //回车结束输入
		{
			printf("\n");
			break;
		}
		if (ch == '\b' && i > 0) //按下删除键
		{
			i--;
			printf("\b \b");
		}
		else if (isprint(ch))  //输入可打印字符
		{
			password[i] = ch;
			printf("*");
			i++;
		}
	}
	password[i] = '\0';
}
