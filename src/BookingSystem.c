#include "BookingSystem.h"

#pragma warning(disable:6031)
#pragma warning(disable:4013)
#pragma warning(disable:6054)

//ȫ�ֱ���
const char* user_tickets_file_path_part1 = "data_files/user_tickets_data/"; //����û�������Ϣ���ļ���
const char* file_extension = ".dat";                                                             //�����ļ���׺
const char* all_tickets_file_path = "data_files/all_tickets.dat";                     //������л�Ʊ���ݵ��ļ����·��
const char* all_users_file_path = "data_files/all_users.dat";                        //��������û����ݵ��ļ����·��
char account_file_name[PHONE_ACCOUNT_NUM_LEN];                           //�û���/�ֻ���(�û�����������Ϣ�ļ���)
char* user_tickets_file_path;                                                                       //�û���Ʊ�����ļ�·��
const char* Admin_type = "Admin";
const char* User_type = "User";

/**
 * @function: char log_in_to_booking_system(void)
 * @description: ��¼��Ʊϵͳ
 * @param {*}
 * @return {'A'}����Ա��¼
 * @return {'U'}�û���¼
 */
char log_in_to_booking_system(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t[��¼]\n\n");
	FILE* file_log;
	USER read_log;
	char input_account_number[PHONE_ACCOUNT_NUM_LEN];
	char input_password[USER_PASSWORD_LEN];
	printf("\t�˺ţ�");
	scanf_s("%s", &input_account_number, PHONE_ACCOUNT_NUM_LEN);
	//�����ֻ��˺�(��Ϊ�û���Ʊ�����ļ���)
	strcpy_s(account_file_name, sizeof(account_file_name), input_account_number);
	printf("\t���룺");
	get_password(input_password, sizeof(input_password));
	while (fopen_s(&file_log, all_users_file_path, "rb") || !file_log)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//�ж��û����������Ƿ�ƥ��
	while (fread(&read_log, sizeof(USER), 1, file_log))
	{
		//���ƥ��
		if (!strcmp(input_account_number, read_log.phone_account_num) && \
			!strcmp(input_password, read_log.user_password))
		{
			//����ǹ���Ա
			if (!strcmp(read_log.user_type, Admin_type))
			{
				if (fclose(file_log))
				{
					printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
					exit(EXIT_FAILURE);
				}
				return 'A';
			}
			//������û�
			if (!strcmp(read_log.user_type, User_type))
			{
				//����û���Ʊ��Ϣ����ļ�·��
				user_tickets_file_path = build_user_train_file_name_path(account_file_name);
				//strcpy_s(user_tickets_file_path, sizeof(user_tickets_file_path), build_user_train_file_name_path(account_file_name));
				if (fclose(file_log))
				{
					printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
					exit(EXIT_FAILURE);
				}
				return 'U';
			}
		}
	}
	//û��ƥ�䵽���û�
	printf("\n\t=��¼ʧ�ܣ�û�и��û�=\n");
	printf("\n\t>�Ƿ�ע�᣿[ע��='y' ��ע��='�����ַ�']\n");
	getchar();
	printf("\t>��ѡ��");
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
 * @description: ע�����û�
 * @param {char* user_or_admi}ע����û�����User/Admin
 * @return {*}
 */
void registered_new_users(const char* User_or_Admin)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t[ע�����û�]\n\n");
	char again_password[USER_PASSWORD_LEN];
	USER puser_new;
	printf("\t�ֻ��ţ�");
	scanf_s("%s", puser_new.phone_account_num, PHONE_ACCOUNT_NUM_LEN);
	while (strlen(puser_new.phone_account_num) != 11)
	{
		printf("\n\t=�ֻ��Ÿ�ʽ���ԣ�����������=\n");
		printf("\t�ֻ��ţ�");
		scanf_s("%s", puser_new.phone_account_num, PHONE_ACCOUNT_NUM_LEN);
	}
	printf("\t���֤�ţ�");
	scanf_s("%s", puser_new.ID_num, ID_NUM_LEN);
	while (strlen(puser_new.ID_num) != 18)
	{
		printf("\n\t=���֤��ʽ���ԣ�����������=\n");
		printf("\t���֤�ţ�");
		scanf_s("%s", puser_new.ID_num, ID_NUM_LEN);
	}
	//�ж��û��Ƿ��Ѿ�����
	while (!check_whether_the_user_data_exists(puser_new)) //�û��Ѵ���������ע��
	{
		system("cls");
		printf("\n\t=���û��Ѵ��ڣ�������¼��=\n");
		printf("\n\t=============================\n");
		printf("\t\t��Ʊ��Ʊϵͳ\n");
		printf("\t=============================\n");
		printf("\n\t[ע��]\n\n");
		printf("\t�ֻ��ţ�");
		scanf_s("%s", puser_new.phone_account_num, PHONE_ACCOUNT_NUM_LEN);
		while (strlen(puser_new.phone_account_num) != 11)
		{
			printf("\n\t=�ֻ��Ÿ�ʽ���ԣ�����������=\n");
			printf("\t�ֻ��ţ�");
			scanf_s("%s", puser_new.phone_account_num, PHONE_ACCOUNT_NUM_LEN);
		}
		printf("\t���֤�ţ�");
		scanf_s("%s", puser_new.ID_num, ID_NUM_LEN);
		while (strlen(puser_new.ID_num) != 18)
		{
			printf("\n\t=���֤��ʽ���ԣ�����������=\n");
			printf("\t���֤�ţ�");
			scanf_s("%s", puser_new.ID_num, ID_NUM_LEN);
		}
	}
	printf("\t������");
	scanf_s("%s", puser_new.user_name, USER_NAME_LEN);
	printf("\t���룺");
	scanf_s("%s", puser_new.user_password, USER_PASSWORD_LEN);
	while (strlen(puser_new.user_password) >= USER_PASSWORD_LEN)
	{
		printf("\n\t=�˺���С��%d�ַ�������������=\n", USER_PASSWORD_LEN);
		printf("\t���룺");
		scanf_s("%s", puser_new.user_password, USER_PASSWORD_LEN);
	}
	printf("\t�ٴ��������룺");
	scanf_s("%s", again_password, USER_PASSWORD_LEN);
	while (strcmp(again_password, puser_new.user_password))
	{
		printf("\n\t=���һ���������벻��������������=\n");
		printf("\t�ٴ��������룺");
		scanf_s("%s", again_password, USER_PASSWORD_LEN);
	}
	//����û����ͱ�ʶ("User"�û�����)
	if (!strcmp(User_or_Admin, User_type))
		strcpy_s(puser_new.user_type, sizeof(puser_new.user_type), User_type);
	//��ӹ���Ա���ͱ�ʶ("Admin"�û�����)
	if (!strcmp(User_or_Admin, Admin_type))
		strcpy_s(puser_new.user_type, sizeof(puser_new.user_type), Admin_type);
	//������ӵ��û���Ϣ���ļ�
	if (save_a_newly_registered_user_to_the_file(puser_new))
	{
		printf("\n\t=�������ݵ��ļ�ʧ��=\n");
		system("pause"); //��ͣ�ȴ�
		exit(EXIT_FAILURE);
	}
	printf("\n\t==ע��ɹ�==\n\n");
	getchar();
	system("pause");
	main(); //ע��ɹ��ص���¼����
}

/**
 * @function: void display_all_registered_users(void)
 * @description: ��ʾ����ע���û�(��������Ա)
 * @param {*}
 * @return {*}
 */
void display_all_registered_users(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t[��ʾ����ע���û�]\n");
	USER read_users_tmp;
	FILE* file_display_users;
	int list_num = 0;
	while (fopen_s(&file_display_users, all_users_file_path, "rb") || !file_display_users)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t||======================================================||\n");
	printf("\t||���+  ����  +   �ֻ���   +     ���֤��     +�û�����||\n");
	printf("\t||======================================================||\n");
	while (fread(&read_users_tmp, sizeof(USER), 1, file_display_users))
	{
		//�Ƚ�����Ա��Ϣ��ӡ��ʾ
		if (!strcmp(read_users_tmp.user_type, Admin_type))
		{
			printf("\t||%-4d|%-8s|%-12s|%-18s|%-8s||\n", ++list_num, read_users_tmp.user_name,
				read_users_tmp.phone_account_num, read_users_tmp.ID_num, read_users_tmp.user_type);
		}
	}
	printf("\t||======================================================||\n");
	rewind(file_display_users); //���ļ�λ��ָʾ���ƶ��������ļ����Ŀ�ͷ(���ص��ļ���ͷ)
	list_num = 0;
	while (fread(&read_users_tmp, sizeof(USER), 1, file_display_users))
	{
		//�ٽ��û���Ϣ��ӡ��ʾ
		if (!strcmp(read_users_tmp.user_type, User_type))
		{
			printf("\t||%-4d|%-8s|%-12s|%-18s|%-8s||\n", ++list_num, read_users_tmp.user_name,
				read_users_tmp.phone_account_num, read_users_tmp.ID_num, read_users_tmp.user_type);
		}
	}
	printf("\t||======================================================||\n");
	if (fclose(file_display_users))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t==��ʾ���==\n\n");
	system("pause");
	administrator_login_interface_menu();
}

/**
 * @function: void search_for_train_information(void)
 * @description: ��ѯ����Ϣ
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
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t[��ѯ����Ϣ]\n\n");
	printf("\t��������ʼվ��");
	scanf_s("%s", &input_start_station, START_STATION_LEN);
	printf("\t�������յ�վ��");
	scanf_s("%s", &input_arrive_station, ARRIVE_STATION_LEN);
	//���ļ��ȶ��������ʼվ���յ�վ������ʾ����
	file_search_tmp = compare_train_information(input_start_station, input_arrive_station);
	printf("\n\t||=================================================================================||\n");
	printf("\t||���+�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  +��Ʊ||\n");
	printf("\t||=================================================================================||\n");
	while (fread(&read_search_tickets, sizeof(TICKET), 1, file_search_tmp))
	{
		if (strcmp(read_search_tickets.start_station, input_start_station) == 0 &&
			strcmp(read_search_tickets.arrive_station, input_arrive_station) == 0)
		{
			printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f|%-4d||\n", ++list_num, read_search_tickets.train_num,
				read_search_tickets.start_station, read_search_tickets.arrive_station, read_search_tickets.start_time,
				read_search_tickets.arrive_time, read_search_tickets.ticket_price, read_search_tickets.ticket_total);
		}
	}
	printf("\t||=================================================================================||\n");
	if (list_num == 0)
	{
		printf("\n\t=δ�鵽�����Ϣ=\n");
		printf("\n\t>�Ƿ������ѯ��[������ѯ='y' ���ٲ�ѯ='�����ַ�']\n");
		printf("\t>��ѡ��");
		scanf_s("%s", &YorN, 2);
		if (YorN == 'y' || YorN == 'Y')
			search_for_train_information();
		else
		{
			if (login_flag == 'U') //������û���¼
				user_login_interface_menu();
			if (login_flag == 'A') //����ǹ���Ա��¼
				administrator_login_interface_menu();
		}
	}
	printf("\n\t==��ѯ���==\n\n");
	//printf("\n\t>�Ƿ������ѯ��[������ѯ='y' ���ٲ�ѯ='�����ַ�']\n");
	//printf("\t>��ѡ��");
	//scanf_s("%s", &YorN, 2);
	//if (YorN == 'y' || YorN == 'Y')
	//	search_for_train_information();
	//else
	//{
	//	if (login_flag == 'U')//������û���¼
	//		user_login_interface_menu();
	//	if (login_flag == 'A') //����ǹ���Ա��¼
	//		administrator_login_interface_menu();
	//}
}

/**
 * @function: void add_train_information(void)
 * @description: ���ӻ���Ϣ
 * @param {*}
 * @return {*}
 */
void add_train_information(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t[���ӻ���Ϣ]\n\n");
	TICKET ptickets_new;
	printf("\t==���������Ϣ==\n");
	printf("\t�г��ţ�");
	scanf_s("%s", ptickets_new.train_num, TRAIN_NUM_LEN);
	printf("\t��ʼվ��");
	scanf_s("%s", ptickets_new.start_station, START_STATION_LEN);
	printf("\t�յ�վ��");
	scanf_s("%s", ptickets_new.arrive_station, ARRIVE_STATION_LEN);
	printf("\t����ʱ�䣺");
	scanf_s("%s", ptickets_new.start_time, START_TIME_LEN);
	printf("\t��վʱ�䣺");
	scanf_s("%s", ptickets_new.arrive_time, ARRIVE_TIME_LEN);
	//�ж�������г��Ƿ����
	while (!check_whether_the_train_data_exists(ptickets_new)) //�г��Ѵ���������¼��
	{
		system("cls");
		printf("\n\t=���г��Ѵ��ڣ�������¼��=\n");
		printf("\n\t=============================\n");
		printf("\t\t��Ʊ��Ʊϵͳ\n");
		printf("\t=============================\n");
		printf("\n\t[����]\n\n");
		printf("\n\t=�������Ʊ��Ϣ=\n");
		printf("\t�г��ţ�");
		scanf_s("%s", ptickets_new.train_num, TRAIN_NUM_LEN);
		printf("\t��ʼվ��");
		scanf_s("%s", ptickets_new.start_station, START_STATION_LEN);
		printf("\t�յ�վ��");
		scanf_s("%s", ptickets_new.arrive_station, ARRIVE_STATION_LEN);
		printf("\t����ʱ�䣺");
		scanf_s("%s", ptickets_new.start_time, START_TIME_LEN);
		printf("\t��վʱ�䣺");
		scanf_s("%s", ptickets_new.arrive_time, ARRIVE_TIME_LEN);
	}
	printf("\tƱ�ۣ�");
	scanf_s("%f", &ptickets_new.ticket_price);
	while (ptickets_new.ticket_price < 0)
	{
		printf("\n\t=Ʊ�۱������0������������=\n");
		printf("\tƱ�ۣ�");
		scanf_s("%f", &ptickets_new.ticket_price);
	}
	printf("\t��Ʊ��");
	scanf_s("%d", &ptickets_new.ticket_total);
	while (ptickets_new.ticket_total < 0)
	{
		printf("\n\t=��Ʊ�������0������������=\n");
		printf("\t��Ʊ��");
		scanf_s("%d", &ptickets_new.ticket_total);
	}
	//������ӵĻ���Ϣ���ļ�
	if (save_a_newly_train_data_to_the_file(ptickets_new))
	{
		printf("\n\t=�������ݵ��ļ�ʧ��=\n");
		system("pause"); //��ͣ�ȴ��û��ź�
		exit(EXIT_FAILURE);
	}
	printf("\n\t==��ӳɹ�==\n\n");
	printf("\n\t>�Ƿ�������?[�������='y' �������='�����ַ�']\n");
	char YorN = 0;
	printf("\t>��ѡ��");
	scanf_s("%s", &YorN, 2);
	if (YorN == 'y' || YorN == 'Y')
		add_train_information();
	else
		administrator_login_interface_menu();
}

/**
 * @function: fpos_t display_all_train_information(void)
 * @description: ��ʾ���л���Ϣ
 * @param {*}
 * @return {list_num}��ʾ���г���Ϣ����
 */
fpos_t display_all_train_information(void)
{
	//system("cls");
	//printf("\t=============================\n");
	//printf("\t\t��Ʊ��Ʊϵͳ\n");
	//printf("\t=============================\n");
	//printf("\n\t[��ʾ����Ϣ]\n");
	TICKET read_tickets_tmp;
	FILE* file_display_tickets;
	fpos_t total_tickets = 0;
	while (fopen_s(&file_display_tickets, all_tickets_file_path, "rb") || !file_display_tickets)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t||=================================================================================||\n");
	printf("\t||���+�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  +��Ʊ||\n");
	printf("\t||=================================================================================||\n");
	while (fread(&read_tickets_tmp, sizeof(TICKET), 1, file_display_tickets))
	{
		printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f|%-4d||\n", ++total_tickets, read_tickets_tmp.train_num,
			read_tickets_tmp.start_station, read_tickets_tmp.arrive_station, read_tickets_tmp.start_time,
			read_tickets_tmp.arrive_time, read_tickets_tmp.ticket_price, read_tickets_tmp.ticket_total);
	}
	printf("\t||=================================================================================||\n");
	if (fclose(file_display_tickets))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//printf("\n\t==��ʾ���==\n\n");
	return total_tickets;
	//system("pause");
	//menu_interface_of_booking_system();
}

/**
 * @function: void order_train_tickets(void)
 * @description: ������Ʊ
 * @param {*}
 * @return {*}
 * @return {*}
 */
void order_train_tickets(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t[������Ʊ]\n\n");
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
	printf("\t��������ʼվ��");
	scanf_s("%s", &input_start_station, START_STATION_LEN);
	printf("\t�������յ�վ��");
	scanf_s("%s", &input_arrive_station, ARRIVE_STATION_LEN);
	//���ļ��ȶ��������ʼվ���յ�վ
	file_search_data = compare_train_information(input_start_station, input_arrive_station);
	printf("\n\t||=================================================================================||\n");
	printf("\t||���+�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  +��Ʊ||\n");
	printf("\t||=================================================================================||\n");
	//����Ʊ����0���г���Ϣ��ʾ����
	while (fread(&read_tickets_tmp, sizeof(TICKET), 1, file_search_data))
	{
		if (read_tickets_tmp.ticket_total > 0)
		{
			printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f|%-4d||\n", ++total_order, read_tickets_tmp.train_num,
				read_tickets_tmp.start_station, read_tickets_tmp.arrive_station, read_tickets_tmp.start_time,
				read_tickets_tmp.arrive_time, read_tickets_tmp.ticket_price, read_tickets_tmp.ticket_total);
		}
	}
	printf("\t||=================================================================================||\n");
	rewind(file_search_data);
	if (total_order == 0) //���û�г�Ʊ����
	{
		printf("\n\t=δ��ѯ���κ�����=\n\n");
		system("pause");
		order_train_tickets();
	}
	printf("\n\t==��ʾ���==\n\n");
	printf("\n\t=��ѡ����Ҫ�����Ļ�Ʊ���=\n");
	printf("\n\t>��ѡ��");
	scanf_s("%lld", &select_order_num);
	pos = (select_order_num - 1) * sizeof(TICKET); //�����תΪ���ļ�ָ�붨λ����Ҫ��������ݿ�λ��
	//����ı�Ŵ��ڻ���Ϣ������С�ڵ���0��������������
	while (select_order_num > total_order || select_order_num <= 0)
	{
		system("cls");
		printf("\t=============================\n");
		printf("\t\t��Ʊ��Ʊϵͳ\n");
		printf("\t=============================\n");
		printf("\n\t[������Ʊ]\n\n");
		printf("\n\t||=================================================================================||\n");
		printf("\t||���+�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  +��Ʊ||\n");
		printf("\t||=================================================================================||\n");
		//����Ʊ����0���г���Ϣ��ʾ����
		while (fread(&read_tickets_tmp, sizeof(TICKET), 1, file_search_data))
		{
			if (read_tickets_tmp.ticket_total > 0)
			{
				printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f|%-4d||\n", ++total_order, read_tickets_tmp.train_num,
					read_tickets_tmp.start_station, read_tickets_tmp.arrive_station, read_tickets_tmp.start_time,
					read_tickets_tmp.arrive_time, read_tickets_tmp.ticket_price, read_tickets_tmp.ticket_total);
			}
		}
		printf("\t||=================================================================================||\n");
		rewind(file_search_data);
		printf("\t=������г���Ų�����=\n");
		printf("\n\t>�����������ţ�");
		scanf_s("%lld", &select_order_num);
		pos = (select_order_num - 1) * sizeof(TICKET); //�����תΪ���ļ�ָ�붨λ����Ҫ��������ݿ�λ��
	}
	//��λ���ļ�����Ҫ���������ݿ飬������ʾ
	if (fsetpos(file_search_data, &pos))
	{
		printf("\n\t=��λ������ݿ����=\n");
		exit(EXIT_FAILURE);
	}
	//������Ҫ���������ݿ�
	if (!fread(&read_tickets_tmp, sizeof(TICKET), 1, file_search_data))
	{
		printf("\n\t=��ȡ�ļ����ִ���=\n");
		exit(EXIT_FAILURE);
	}
	fclose(file_search_data); //����Ҫ��ʱ�ļ��ˣ�����ر�
	while (fopen_s(&file_save_user_order_data, user_tickets_file_path, "rb") || !file_save_user_order_data)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//�жϸ�Ʊ�Ƿ��Ѿ���������
	while (fread(&read_user_tickets, sizeof(TICKET), 1, file_save_user_order_data))
	{
		if (!strcmp(read_user_tickets.train_num, read_tickets_tmp.train_num) && \
			!strcmp(read_user_tickets.start_station, read_tickets_tmp.start_station) && \
			!strcmp(read_user_tickets.arrive_station, read_tickets_tmp.arrive_station) && \
			!strcmp(read_user_tickets.start_time, read_tickets_tmp.start_time) && \
			!strcmp(read_user_tickets.arrive_time, read_tickets_tmp.arrive_time))
		{
			printf("\n\t=�Ѷ��������л�=\n");
			printf("\n\t>�Ƿ������Ʊ��[������Ʊ='y' ���ٶ�Ʊ='�����ַ�']\n");
			char YorN = 0;
			printf("\t>��ѡ��");
			scanf_s("%s", &YorN, 2);
			if (YorN == 'y' || YorN == 'Y')
				order_train_tickets();
			else
				user_login_interface_menu();
		}
	}
	if (fclose(file_save_user_order_data)) //�ر��ļ�
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//��ʾѡ��Ҫ�������г���Ϣ
	printf("\n\t||============================================================================||\n");
	printf("\t||���+�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  ||\n");
	printf("\t||============================================================================||\n");
	printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f||\n", select_order_num, read_tickets_tmp.train_num,
		read_tickets_tmp.start_station, read_tickets_tmp.arrive_station, read_tickets_tmp.start_time,
		read_tickets_tmp.arrive_time, read_tickets_tmp.ticket_price);
	printf("\t||============================================================================||\n");
	//�򿪶�Ӧ�û��ĳ�Ʊ�����ļ�������Ʊ�����ݴ���
	while (fopen_s(&file_save_user_order_data, user_tickets_file_path, "ab") || !file_save_user_order_data)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//��Ʊ����д�뵽��Ӧ�û��Ĺ�Ʊ�����ļ�
	fwrite_return = fwrite(&read_tickets_tmp, sizeof(TICKET), nmemb, file_save_user_order_data);
	if (fwrite_return != nmemb)
	{
		printf("\n\t=д������ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(file_save_user_order_data)) //�ر��ļ�
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//�����г������ļ��Ķ�Ӧ�����˵ĳ�Ʊ��Ʊ��һ
	if (the_change_of_the_remaining_train_tickets(read_tickets_tmp, -1))
	{
		printf("\n\t=����ԭ�г���Ʊʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t==��Ʊ�ɹ�==\n\n");
	system("pause");
	user_login_interface_menu();
}

/**
 * @function: void return_the_ticket(void)
 * @description: ��Ʊ
 * @param {* }
 * @return {*}
 * @return {*}
 */
void return_the_ticket(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t[��Ʊ]\n\n");
	FILE* file_total_tickets;
	TICKET read_total_user_tickets;
	fpos_t pos;
	fpos_t total_user_ticket = 0;
	fpos_t select_num = 0;
	while (fopen_s(&file_total_tickets, user_tickets_file_path, "rb") || !file_total_tickets)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//��ʾ��ǰ�û������еĶ�Ʊ��Ϣ
	printf("\t||============================================================================||\n");
	printf("\t||���+�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  ||\n");
	printf("\t||============================================================================||\n");
	while (fread(&read_total_user_tickets, sizeof(TICKET), 1, file_total_tickets))
	{
		printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f||\n", ++total_user_ticket,
			read_total_user_tickets.train_num, read_total_user_tickets.start_station,
			read_total_user_tickets.arrive_station, read_total_user_tickets.start_time,
			read_total_user_tickets.arrive_time, read_total_user_tickets.ticket_price);
	}
	printf("\t||============================================================================||\n");
	if (fclose(file_total_tickets))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//ѡ����Ҫ�˵���Ʊ
	printf("\n\t=��������Ҫ��Ʊ���г����=");
	printf("\n\t>�������ţ�");
	scanf_s("%lld", &select_num);
	if (total_user_ticket == 0)
	{
		printf("\n\t=��ǰû�ж�Ʊ��Ϣ=\n");
		system("pause");
		user_login_interface_menu();
	}
	while (select_num > total_user_ticket || select_num <= 0)
	{
		getchar();
		printf("\n\t=����ı�Ų�����=\n");
		printf("\n\t=������������Ҫ��Ʊ���г����=");
		printf("\n\t>�������ţ�");
		scanf_s("%lld", &select_num);
	}
	//���ļ�Ϊ���ҵ�����ʾ����Ʊ�����ݿ�
	while (fopen_s(&file_total_tickets, all_tickets_file_path, "rb") || !file_total_tickets)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_total_tickets);
	pos = (select_num - 1) * sizeof(TICKET); //�����תΪ���ļ�ָ�붨λ����Ҫ��Ʊ�����ݿ�λ��
	//��λ���ļ�����Ҫ��Ʊ�����ݿ飬������ʾ
	if (fsetpos(file_total_tickets, &pos))
	{
		printf("\n\t=��λ������ݿ����=\n");
		exit(EXIT_FAILURE);
	}
	//������Ҫ��Ʊ������
	if (!fread(&read_total_user_tickets, sizeof(TICKET), 1, file_total_tickets))
	{
		printf("\n\t=��ȡ�ļ����ִ���=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(file_total_tickets))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//���û���Ʊ�ļ����Ƴ���ص��г���Ϣ
	remove_train_information(read_total_user_tickets, user_tickets_file_path);
	//����Ʊ�Ļ����ܻ�Ʊ��������Ʊ��һ
	if (the_change_of_the_remaining_train_tickets(read_total_user_tickets, 1))
	{
		printf("\n\t=����ԭ�г���Ʊʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t=��Ʊ�ɹ�=\n");
	printf("\n\t>�Ƿ������Ʊ?[������Ʊ='y' ������Ʊ='�����ַ�']\n");
	char YorN = 0;
	printf("\t>��ѡ��");
	scanf_s("%s", &YorN, 2);
	if (YorN == 'y' || YorN == 'Y')
		return_the_ticket();
	else
		user_login_interface_menu();
}

/**
 * @function: void modify_train_information(void)
 * @description: �޸Ļ���Ϣ
 * @param {*}
 * @return {*}
 */
void modify_train_information(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t[�޸Ļ���Ϣ]\n");
	fpos_t total_trains;
	total_trains = display_all_train_information(); //��ʾ���л���Ϣ���������г���Ϣ����
	fpos_t pos = 0;
	fpos_t select_num;
	TICKET modify_tickets_tmp;
	TICKET after_change_tickets;
	FILE* file_modify_tickets;
	printf("\n\t=��������Ҫ�޸ĵ��г����=");
	printf("\n\t>�������ţ�");
	scanf_s("%lld", &select_num);
	pos = (select_num - 1) * sizeof(TICKET); //�����תΪ���ļ�ָ�붨λ����Ҫ��������ݿ�λ��
	//����ı�Ŵ��ڻ���Ϣ������С�ڵ���0��������������
	while (select_num > total_trains || select_num <= 0)
	{
		system("cls");
		printf("\t=============================\n");
		printf("\t\t��Ʊ��Ʊϵͳ\n");
		printf("\t=============================\n");
		printf("\n\t[�޸Ļ���Ϣ]\n");
		total_trains = display_all_train_information(); //��ʾ���л���Ϣ
		printf("\t=������г���Ų�����=");
		printf("\n\t>�����������ţ�");
		scanf_s("%lld", &select_num);
		pos = (select_num - 1) * sizeof(TICKET);
	}
	//��һ�δ��ļ�Ϊ���ҵ�����ʾ���޸ĵ����ݿ�
	while (fopen_s(&file_modify_tickets, all_tickets_file_path, "rb") || !file_modify_tickets)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_modify_tickets);
	//��һ�ζ�λ���ļ�����Ҫ�޸ĵ����ݿ飬������ʾ
	if (fsetpos(file_modify_tickets, &pos))
	{
		printf("\n\t=��λ������ݿ����=\n");
		exit(EXIT_FAILURE);
	}
	//������Ҫ�޸ĵ����ݿ�
	if (!fread(&modify_tickets_tmp, sizeof(TICKET), 1, file_modify_tickets))
	{
		printf("\n\t=��ȡ�ļ����ִ���=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(file_modify_tickets))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	system("cls");
	printf("\t=============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t=���޸ĵĻ���Ϣ=");
	printf("\n\t||=================================================================================||\n");
	printf("\t||���+�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  +��Ʊ||\n");
	printf("\t||=================================================================================||\n");
	printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f|%-4d||\n", select_num, modify_tickets_tmp.train_num,
		modify_tickets_tmp.start_station, modify_tickets_tmp.arrive_station, modify_tickets_tmp.start_time,
		modify_tickets_tmp.arrive_time, modify_tickets_tmp.ticket_price, modify_tickets_tmp.ticket_total);
	printf("\t||=================================================================================||\n");
	//ѡ���޸Ĳ���
	printf("\n\t======================================================================================\n");
	printf("\t1.�г���/2.��ʼվ/3.�յ�վ/4.����ʱ��/5.��վʱ��/6.Ʊ��/7.��Ʊ/8.��������/9.����������  ");
	printf("\n\t======================================================================================\n");
	printf("\n\t=��ѡ��Ҫ���ĵ�����=\n");
	printf("\t>�����룺");
	size_t change_content;
	scanf_s("%d", &change_content);
	//����¼�������г���Ϣ���������ĺ�����ݷ���
	after_change_tickets = input_the_changed_train_information(modify_tickets_tmp, change_content);
	printf("\n\t=�޸ĺ�Ļ���Ϣ=");
	printf("\n\t||=================================================================================||\n");
	printf("\t||���+�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  +��Ʊ||\n");
	printf("\t||=================================================================================||\n");
	printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f|%-4d||\n", select_num, after_change_tickets.train_num,
		after_change_tickets.start_station, after_change_tickets.arrive_station, after_change_tickets.start_time,
		after_change_tickets.arrive_time, after_change_tickets.ticket_price, after_change_tickets.ticket_total);
	printf("\t||=================================================================================||\n");
	//�ڶ��δ��ļ�Ϊ��д����޸ĵ����ݿ�
	while (fopen_s(&file_modify_tickets, all_tickets_file_path, "rb+") || !file_modify_tickets)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_modify_tickets);
	//�ڶ��ζ�λ���ļ�����Ҫ�޸ĵ����ݿ飬���и���
	if (fsetpos(file_modify_tickets, &pos))
	{
		printf("\n\t=��λ������ݿ����=\n");
		exit(EXIT_FAILURE);
	}
	//д����ĺ�����ݿ鵽�ļ�
	size_t fwrite_return = fwrite(&after_change_tickets, sizeof(TICKET), 1, file_modify_tickets);
	if (fwrite_return != 1)
	{
		printf("\n\t=д���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(file_modify_tickets))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	printf("\t==�޸ĳɹ�==\n");
	printf("\t>�Ƿ�����޸�?[�����޸�='y' �����޸�='�����ַ�']\n");
	char YorN = 0;
	printf("\t>��ѡ��");
	scanf_s("%s", &YorN, 2);
	if (YorN == 'y' || YorN == 'Y')
		modify_train_information();
	else
		administrator_login_interface_menu();
}

/**
 * @function: void delete_train_information(void)
 * @description: ɾ������Ϣ
 * @param {*}
 * @return {*}
 * @return {*}
 */
void delete_train_information(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t[ɾ������Ϣ]\n\n");
	FILE* file_all_tickets_pos;
	TICKET read_delete_tickets;
	fpos_t pos;
	fpos_t select_num = 0;
	fpos_t total_trains = 0;
	total_trains = display_all_train_information(); //��ʾ���л���Ϣ
	printf("\n\t=��������Ҫɾ�����г����=");
	printf("\n\t>�������ţ�");
	scanf_s("%lld", &select_num);
	while (select_num > total_trains || select_num <= 0)
	{
		printf("\n\t=������������Ҫɾ�����г����=");
		printf("\n\t>�������ţ�");
		scanf_s("%lld", &select_num);
	}
	pos = (select_num - 1) * sizeof(TICKET); //�����תΪ���ļ�ָ�붨λ����Ҫ��������ݿ�λ��
	//���ļ�Ϊ���ҵ�����ʾ��ɾ�������ݿ�
	while (fopen_s(&file_all_tickets_pos, all_tickets_file_path, "rb") || !file_all_tickets_pos)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_all_tickets_pos);
	//��λ���ļ�����Ҫɾ�������ݿ�
	if (fsetpos(file_all_tickets_pos, &pos))
	{
		printf("\n\t=��λ������ݿ����=\n");
		exit(EXIT_FAILURE);
	}
	//������Ҫɾ�������ݿ�
	if (!fread(&read_delete_tickets, sizeof(TICKET), 1, file_all_tickets_pos))
	{
		printf("\n\t=��ȡ�ļ����ִ���=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(file_all_tickets_pos))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t=��ɾ����Ϣ=\n");
	printf("\n\t||=================================================================================||\n");
	printf("\t||���+�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  +��Ʊ||\n");
	printf("\t||=================================================================================||\n");
	printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f|%-4d||\n", select_num, read_delete_tickets.train_num,
		read_delete_tickets.start_station, read_delete_tickets.arrive_station, read_delete_tickets.start_time,
		read_delete_tickets.arrive_time, read_delete_tickets.ticket_price, read_delete_tickets.ticket_total);
	printf("\t||=================================================================================||\n");
	//�Ƴ���ص��г���Ϣ
	remove_train_information(read_delete_tickets, all_tickets_file_path);
	printf("\n\t=ɾ���ɹ�=\n");
	printf("\t>�Ƿ����ɾ��?[����ɾ��='y' ����ɾ��='�����ַ�']\n");
	char YorN = 0;
	printf("\t>��ѡ��");
	scanf_s("%s", &YorN, 2);
	if (YorN == 'y' || YorN == 'Y')
		delete_train_information();
	else
		administrator_login_interface_menu();
}

/**
 * @function: void remove_train_information(TICKET delete_ticket_data, const char* which_file)
 * @description: �Ƴ���صĻ���Ϣ
 * @param {TICKET delete_ticket_data}��ɾ���Ļ�Ʊ��Ϣ
 * @param {char* which_file}��ɾ����Ʊ��Ϣ���ļ���
 * @return {*}
 * @return {*}
 */
void remove_train_information(TICKET delete_ticket_data, const char* which_file)
{
	FILE* file_total_tickets_del;
	FILE* tmpfile_dont_delete;
	TICKET read_dont_delete;
	TICKET read_back_file;
	tmpfile_s(&tmpfile_dont_delete); //������ʱ�ļ������ݴ治ɾ��������
	//���ܵĻ������ļ���������ɾ���������ȷ���ʱ�ļ���
	while (fopen_s(&file_total_tickets_del, which_file, "rb") || !file_total_tickets_del)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_total_tickets_del);
	while (fread(&read_dont_delete, sizeof(TICKET), 1, file_total_tickets_del))
	{
		//���²���Ҫɾ����
		if (strcmp(delete_ticket_data.train_num, read_dont_delete.train_num) ||
			strcmp(delete_ticket_data.start_station, read_dont_delete.start_station) ||
			strcmp(delete_ticket_data.arrive_station, read_dont_delete.arrive_station) ||
			strcmp(delete_ticket_data.start_time, read_dont_delete.start_time) ||
			strcmp(delete_ticket_data.arrive_time, read_dont_delete.arrive_time))
		{
			fwrite(&read_dont_delete, sizeof(TICKET), 1, tmpfile_dont_delete); //������Ҫɾ���Ļ����ݴ�����ʱ�ļ�
		}
	}
	if (fclose(file_total_tickets_del))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//����ʱ�ļ��еĲ���Ҫɾ���Ļ�������ȫ���Ż��ܵĻ������ļ�
	while (fopen_s(&file_total_tickets_del, which_file, "wb") || !file_total_tickets_del)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	rewind(tmpfile_dont_delete);
	//������Ҫɾ���Ļ����ݷŻ��ܵĻ������ļ�
	while (fread(&read_back_file, sizeof(TICKET), 1, tmpfile_dont_delete))
	{
		fwrite(&read_back_file, sizeof(TICKET), 1, file_total_tickets_del);
	}
	if (fclose(file_total_tickets_del))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	if (fclose(tmpfile_dont_delete))
	{
		printf("\n\t=�ر���ʱ�ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: void display_user_booking_information(void)
 * @description: ��ʾ�û�������Ϣ
 * @param {*}
 * @return {*}
 */
void display_user_booking_information(void)
{
	system("cls");
	printf("\t=============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t=============================\n");
	printf("\n\t[��ʾ�û�������Ϣ]\n\n");
	FILE* file_display_booking;
	FILE* file_user;
	TICKET read_display_booking;
	USER read_user;
	fpos_t total_user_ticket = 0;
	//���û��ļ�����ʾ��ǰ�û���Ϣ
	while (fopen_s(&file_user, all_users_file_path, "rb") || !file_user)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t||=================================================||\n");
	printf("\t||  ����  +   �ֻ���   +     ���֤��     +�û�����||\n");
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
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//���û���Ʊ�����ļ�	
	while (fopen_s(&file_display_booking, user_tickets_file_path, "rb") || !file_display_booking)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	//��ʾ��ǰ�û������еĶ�Ʊ��Ϣ
	printf("\t||============================================================================||\n");
	printf("\t||���+�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  ||\n");
	printf("\t||============================================================================||\n");
	while (fread(&read_display_booking, sizeof(TICKET), 1, file_display_booking))
	{
		printf("\t||%-4lld|%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f||\n", ++total_user_ticket,
			read_display_booking.train_num, read_display_booking.start_station,
			read_display_booking.arrive_station, read_display_booking.start_time,
			read_display_booking.arrive_time, read_display_booking.ticket_price);
	}
	printf("\t||============================================================================||\n");
	if (fclose(file_display_booking))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\t==��ʾ���==\n\n");
	system("pause");
	user_login_interface_menu();
}

/**
 * @function: int save_a_newly_train_data_to_the_file(TICKET save_new_ticket)
 * @description: ����һ���µĻ����ݵ��ļ�
 * @return {MY_FAIL}��Ӵ���
 * @return {MY_SUCCESS}��ӳɹ�
 */
int save_a_newly_train_data_to_the_file(TICKET save_new_ticket)
{
	FILE* file_save_ticket;
	size_t nmemb = 1;
	size_t fwrite_return;
	while (fopen_s(&file_save_ticket, all_tickets_file_path, "ab") || !file_save_ticket)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		return MY_FAIL;
	}
	fwrite_return = fwrite(&save_new_ticket, sizeof(TICKET), nmemb, file_save_ticket); //д�����ݵ��ļ�
	if (fwrite_return != nmemb)
		return MY_FAIL;
	if (fclose(file_save_ticket)) //�ر��ļ�
		return MY_FAIL;
	printf("\n\t||============================================================================||\n");
	printf("\t||�г���+  ��ʼվ  +  �յ�վ  +    ����ʱ��    +    ��վʱ��    +  Ʊ��  +��Ʊ||\n");
	printf("\t||============================================================================||\n");
	printf("\t||%-6s|%-10s|%-10s|%-16s|%-16s|��%-6.1f|%-4d||\n", save_new_ticket.train_num,
		save_new_ticket.start_station, save_new_ticket.arrive_station, save_new_ticket.start_time,
		save_new_ticket.arrive_time, save_new_ticket.ticket_price, save_new_ticket.ticket_total);
	printf("\t||============================================================================||\n");
	return MY_SUCCESS;
}

/**
 * @function: int save_a_newly_registered_user_to_the_file(USER save_new_user)
 * @description: ����һ����ע����û����ļ�
 * @param {USER psave_new_user}��ע����û�����
 * @return {MY_FAIL}��Ӵ���
 * @return {MY_SUCCESS}��ӳɹ�
 */
int save_a_newly_registered_user_to_the_file(USER save_new_user)
{
	FILE* file_save_user;
	size_t nmemb = 1;
	size_t fwrite_return;
	while (fopen_s(&file_save_user, all_users_file_path, "ab") || !file_save_user)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	fwrite_return = fwrite(&save_new_user, sizeof(USER), nmemb, file_save_user); //д�����ݵ��ļ�
	if (fwrite_return != nmemb)
		return MY_FAIL;
	if (fclose(file_save_user)) //�ر��ļ�
		return MY_FAIL;
	printf("\n\t||=================================================||\n");
	printf("\t||  ����  +   �ֻ���   +     ���֤��     +�û�����||\n");
	printf("\t||=================================================||\n");
	printf("\t||%-8s|%-12s|%-18s|%-8s||\n", save_new_user.user_name,
		save_new_user.phone_account_num, save_new_user.ID_num, save_new_user.user_type);
	printf("\t||=================================================||\n");
	return MY_SUCCESS;
}

/**
 * @function: char build_user_train_file_name_path(char* account_file_name)
 * @description: ͨ���û��������û��𳵶��������ļ�·��
 * @param {char* account_file_name}�û���
 * @return {user_tickets_file_path}�û����ļ�·��
 */
char* build_user_train_file_name_path(char* account_file_name)
{
	static char user_ticket_file_path_part1_tmp[USER_TICKET_FILE_PATH_LEN];
	strcpy_s(user_ticket_file_path_part1_tmp, sizeof(user_ticket_file_path_part1_tmp), user_tickets_file_path_part1);
	strcat_s(user_ticket_file_path_part1_tmp, sizeof(user_ticket_file_path_part1_tmp), account_file_name); //�û��������û����������ļ���·������
	strcat_s(user_ticket_file_path_part1_tmp, sizeof(user_ticket_file_path_part1_tmp), file_extension);    //�û������ļ����µ��û������ļ���.dat��׺����
	return user_ticket_file_path_part1_tmp;
}

/**
 * @function: int check_whether_the_train_data_exists(TICKET check_ticket_data)
 * @description: ����г������Ƿ��Ѿ�����
 * @param {TICKET check_ticket_data}�����Ľṹ������
 * @return {MY_FAIL}�ȶ�ʧ��
 * @return {MY_SUCCESS}�ȶԳɹ�
 */
int check_whether_the_train_data_exists(TICKET check_ticket_data)
{
	FILE* file_check_ticket;
	TICKET read_tickets_tmp;
	while (fopen_s(&file_check_ticket, all_tickets_file_path, "ab+") || !file_check_ticket)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_check_ticket); //���ļ�λ��ָʾ���ƶ��������ļ����Ŀ�ͷ(���ص��ļ���ͷ)
	while (fread(&read_tickets_tmp, sizeof(TICKET), 1, file_check_ticket))
	{
		//�������ͬ���г���Ϣ
		if (!strcmp(check_ticket_data.train_num, read_tickets_tmp.train_num) &&
			!strcmp(check_ticket_data.start_station, read_tickets_tmp.start_station) &&
			!strcmp(check_ticket_data.arrive_station, read_tickets_tmp.arrive_station) &&
			!strcmp(check_ticket_data.start_time, read_tickets_tmp.start_time) &&
			!strcmp(check_ticket_data.arrive_time, read_tickets_tmp.arrive_time))
		{
			if (fclose(file_check_ticket))
			{
				printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
				exit(EXIT_FAILURE);
			}
			return MY_SUCCESS;
		}
	}
	if (fclose(file_check_ticket))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	return MY_FAIL;
}

/**
 * @function: int check_whether_the_user_data_exists(USER check_user_data)
 * @description: ����û������Ƿ��Ѿ�����
 * @param {USER check_user_data}�������û�����
 * @return {MY_FAIL}�ȶ�ʧ�ܣ�������
 * @return {MY_SUCCESS}�ȶԳɹ����Ѵ���
 */
int check_whether_the_user_data_exists(USER check_user_data)
{
	FILE* file_check_user;
	USER read_users_tmp;
	while (fopen_s(&file_check_user, all_users_file_path, "rb") || !file_check_user)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	while (fread(&read_users_tmp, sizeof(USER), 1, file_check_user))
	{
		if (!strcmp(check_user_data.phone_account_num, read_users_tmp.phone_account_num) ||
			!strcmp(check_user_data.ID_num, read_users_tmp.ID_num)) //�������ͬ���ֻ��˺�
		{
			if (fclose(file_check_user))
			{
				printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
				exit(EXIT_FAILURE);
			}
			return MY_SUCCESS;
		}
	}
	if (fclose(file_check_user))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	return MY_FAIL;
}

/**
 * @function: TICKET* input_the_changed_train_information(TICKET change_train, int select_num)
 * @description: ������ĵ����л�����
 * @param {TICKET change_train}�����ĵĻ�����
 * @param {int select_num}�����ĵĲ���[1.�г���/2.��ʼվ/3.�յ�վ/4.����ʱ��/5.��վʱ��/6.Ʊ��/7.��Ʊ/8.��������]
 * @return {TICKET}�����޸ĺ�Ļ���Ϣ
 */
TICKET input_the_changed_train_information(TICKET change_train, int select_num)
{
	switch (select_num)
	{
	case 1: //�����г���
		printf("\n\t=�������µ�[�г���]=\n");
		printf("\t�г��ţ�");
		scanf_s("%s", change_train.train_num, TRAIN_NUM_LEN);
		while (!check_whether_the_train_data_exists(change_train)) //�г��Ѵ��ڣ�������¼��
		{
			printf("\n\t=���г��Ѵ��ڣ�������¼��=\n");
			printf("\n\t=�������µ�[�г���]=\n");
			printf("\t�г��ţ�");
			scanf_s("%s", change_train.train_num, TRAIN_NUM_LEN);
		}
		break;
	case 2: //������ʼվ
		printf("\n\t=�������µ�[��ʼվ]=\n");
		printf("\t��ʼվ��");
		scanf_s("%s", change_train.start_station, START_STATION_LEN);
		while (!check_whether_the_train_data_exists(change_train)) //�г��Ѵ��ڣ�������¼��
		{
			printf("\n\t=���г��Ѵ��ڣ�������¼��=\n");
			printf("\n\t=�������µ�[��ʼվ]=\n");
			printf("\t��ʼվ��");
			scanf_s("%s", change_train.start_station, START_STATION_LEN);
		}
		break;
	case 3: //�����յ�վ
		printf("\n\t=�������µ�[�յ�վ]=\n");
		printf("\t�յ�վ��");
		scanf_s("%s", change_train.arrive_station, ARRIVE_STATION_LEN);
		while (!check_whether_the_train_data_exists(change_train)) //�г��Ѵ��ڣ�������¼��
		{
			printf("\n\t=���г��Ѵ��ڣ�������¼��=\n");
			printf("\n\t=�������µ�[�յ�վ]=\n");
			printf("\t��ʼվ��");
			scanf_s("%s", change_train.start_station, ARRIVE_STATION_LEN);
		}
		break;
	case 4: //���ķ���ʱ��
		printf("\n\t=�������µ�[����ʱ��]=\n");
		printf("\t����ʱ�䣺");
		scanf_s("%s", change_train.start_time, START_TIME_LEN);
		while (!check_whether_the_train_data_exists(change_train)) //�г��Ѵ��ڣ�������¼��
		{
			printf("\n\t=���г��Ѵ��ڣ�������¼��=\n");
			printf("\n\t=�������µ�[����ʱ��]=\n");
			printf("\t��ʼվ��");
			scanf_s("%s", change_train.start_station, START_TIME_LEN);
		}
		break;
	case 5: //���ĵ�վʱ��
		printf("\n\t=�������µ�[��վʱ��]=\n");
		printf("\t��վʱ�䣺");
		scanf_s("%s", change_train.arrive_time, ARRIVE_TIME_LEN);
		while (!check_whether_the_train_data_exists(change_train)) //�г��Ѵ��ڣ�������¼��
		{
			printf("\n\t=���г��Ѵ��ڣ�������¼��=\n");
			printf("\n\t=�������µ�[��վʱ��]=\n");
			printf("\t��վʱ�䣺");
			scanf_s("%s", change_train.arrive_time, ARRIVE_TIME_LEN);
		}
		break;
	case 6: //����Ʊ��
		printf("\n\t=�������µ�[Ʊ��]=\n");
		printf("\tƱ�ۣ�");
		scanf_s("%f", &change_train.ticket_price);
		while (change_train.ticket_price < 0)
		{
			printf("\n\t=Ʊ�۱������0������������=\n");
			printf("\tƱ�ۣ�");
			scanf_s("%f", &change_train.ticket_price);
		}
		break;
	case 7: //������Ʊ
		printf("\n\t=�������µ�[��Ʊ]=\n");
		printf("\t��Ʊ��");
		scanf_s("%d", &change_train.ticket_total);
		while (change_train.ticket_total < 0)
		{
			printf("\n\t=��Ʊ�������0������������=\n");
			printf("\t��Ʊ��");
			scanf_s("%d", &change_train.ticket_total);
		}
		break;
	case 8: //����ȫ���г���Ϣ
		printf("\n\t=������[ȫ��]�Ļ���Ϣ=\n");
		printf("\t�г��ţ�");
		scanf_s("%s", change_train.train_num, TRAIN_NUM_LEN);
		printf("\t��ʼվ��");
		scanf_s("%s", change_train.start_station, START_STATION_LEN);
		printf("\t�յ�վ��");
		scanf_s("%s", change_train.arrive_station, ARRIVE_STATION_LEN);
		printf("\t����ʱ�䣺");
		scanf_s("%s", change_train.start_time, START_TIME_LEN);
		printf("\t��վʱ�䣺");
		scanf_s("%s", change_train.arrive_time, ARRIVE_TIME_LEN);
		//�ж�������г��Ƿ����
		while (!check_whether_the_train_data_exists(change_train)) //�г��Ѵ��ڣ�������¼��
		{
			printf("\n\t=���г��Ѵ��ڣ�������¼��=\n");
			printf("\n\t=����������[ȫ��]�Ļ���Ϣ=\n");
			printf("\t�г��ţ�");
			scanf_s("%s", change_train.train_num, TRAIN_NUM_LEN);
			printf("\t��ʼվ��");
			scanf_s("%s", change_train.start_station, START_STATION_LEN);
			printf("\t�յ�վ��");
			scanf_s("%s", change_train.arrive_station, ARRIVE_STATION_LEN);
			printf("\t����ʱ�䣺");
			scanf_s("%s", change_train.start_time, START_TIME_LEN);
			printf("\t��վʱ�䣺");
			scanf_s("%s", change_train.arrive_time, ARRIVE_TIME_LEN);
		}
		printf("\tƱ�ۣ�");
		scanf_s("%f", &change_train.ticket_price);
		while (change_train.ticket_price < 0)
		{
			printf("\n\t=Ʊ�۱������0������������=\n");
			printf("\tƱ�ۣ�");
			scanf_s("%f", &change_train.ticket_price);
		}
		printf("\t��Ʊ��");
		scanf_s("%d", &change_train.ticket_total);
		while (change_train.ticket_total < 0)
		{
			printf("\n\t=��Ʊ�������0������������=\n");
			printf("\t��Ʊ��");
			scanf_s("%d", &change_train.ticket_total);
		}
		break;
	case 9: //����������
		administrator_login_interface_menu();
	default:
		getchar(); //�ӱ�׼���� stdin ��ȡһ���ַ�<һ���޷����ַ�>(�������Ĵ�����Ϣ���´�����ĸ���)
		printf("\n\t=����ı�Ŵ�������������=\n");
		printf("\n\t======================================================================================\n");
		printf("\t1.�г���/2.��ʼվ/3.�յ�վ/4.����ʱ��/5.��վʱ��/6.Ʊ��/7.��Ʊ/8.��������/9.����������  ");
		printf("\n\t======================================================================================\n");
		printf("\n\t=��ѡ��Ҫ���ĵ�����=\n");
		printf("\t>�����룺");
		size_t change_content;
		scanf_s("%d", &change_content);
		input_the_changed_train_information(change_train, change_content);
	}
	return change_train;
}

/**
 * @function: FILE* compare_train_information(char* input_start_station, char* input_arrive_station)
 * @description: �ȶԻ���Ϣ,�����رȶԷ��������Ļ���Ϣ����
 * @param {char* input_start_station}���ȶԵ���ʼվ
 * @param {char* input_arrive_station}���ȶԵ��յ�վ
 * @return {tmp_file}������ʱ�ļ����ļ���ָ��(�ȶԷ��ϵ�Ԫ��)
 */
FILE* compare_train_information(char* input_start_station, char* input_arrive_station)
{
	TICKET read_tickets_tmp;
	FILE* compare_file;
	FILE* tmp_file;
	fpos_t list_num = 0;
	if (tmpfile_s(&tmp_file))
	{
		printf("\n\t=������ʱ�ļ����ִ���=\n");
		exit(EXIT_FAILURE);
	}
	while (fopen_s(&compare_file, all_tickets_file_path, "rb") || !compare_file)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	while (fread(&read_tickets_tmp, sizeof(TICKET), 1, compare_file))
	{
		if (strcmp(input_start_station, read_tickets_tmp.start_station) == 0 &&
			strcmp(input_arrive_station, read_tickets_tmp.arrive_station) == 0)
			fwrite(&read_tickets_tmp, sizeof(TICKET), 1, tmp_file); //���Աȳɹ��Ļ����ݴ�����ʱ�ļ�
	}
	if (fclose(compare_file))
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	rewind(tmp_file); //���ļ�λ��ָʾ���ƶ��������ļ����Ŀ�ͷ(���ص��ļ���ͷ)
	return tmp_file;
}

/**
 * @function: int the_change_of_the_remaining_train_tickets(TICKET read_tickets_tmp, int add_or_sub)
 * @description: ����Ʊ��Ϣ�Ӽ��仯
 * @param {TICKET read_tickets_tmp}��������Ʊ�����ݿ�
 * @param {int add_or_sub}���ӻ��Ǽ���(1 or -1)
 * @return {MY_FAIL}��Ʊ����ʧ��
 * @return {MY_SUCCESS}��Ʊ���ĳɹ�
 */
int the_change_of_the_remaining_train_tickets(TICKET read_tickets_tmp, int add_or_sub)
{
	FILE* file_ticket_total_change;
	TICKET read_all_tickets;
	fpos_t pos;
	fpos_t order_pot = 0;	
	size_t nmemb = 1;
	size_t fwrite_return;
	//�����л������ļ�����Ʊ��һ
	//��ʾ����ȡ�����ÿ��ܵ� null ָ�롣 �����ָ���ֵ��Ч��������δ����ġ� ��Ҫ��������⣬����ʹ��֮ǰ��ָ֤��
	while (fopen_s(&file_ticket_total_change, all_tickets_file_path, "rb+") || !file_ticket_total_change)
	{
		printf("\n\t=���ļ�ʱ���ִ���=\n");
		exit(EXIT_FAILURE);
	}
	rewind(file_ticket_total_change);
	//�ҵ��Ѿ������˵ĳ�Ʊ
	while (fread(&read_all_tickets, sizeof(TICKET), 1, file_ticket_total_change))
	{
		++order_pot;
		if (!strcmp(read_all_tickets.train_num, read_tickets_tmp.train_num) &&
			!strcmp(read_all_tickets.start_station, read_tickets_tmp.start_station) &&
			!strcmp(read_all_tickets.arrive_station, read_tickets_tmp.arrive_station) &&
			!strcmp(read_all_tickets.start_time, read_tickets_tmp.start_time) &&
			!strcmp(read_all_tickets.arrive_time, read_tickets_tmp.arrive_time))
		{
			break; //�ҵ��˶����˵�Ʊ
		}
	}
	if (add_or_sub == 1)
		read_all_tickets.ticket_total++; //�����˵Ļ����ܵĻ������ļ��е���Ʊ��һ
	if (add_or_sub == -1)
		read_all_tickets.ticket_total--; //�����˵Ļ����ܵĻ������ļ��е���Ʊ��һ
	rewind(file_ticket_total_change);
	pos = (order_pot - 1) * sizeof(TICKET);
	if (fsetpos(file_ticket_total_change, &pos))
	{
		printf("\n\t=��λ������ݿ����=\n");
		//exit(EXIT_FAILURE);
		return MY_FAIL;
	}
	fwrite_return = fwrite(&read_all_tickets, sizeof(TICKET), nmemb, file_ticket_total_change);
	if (fwrite_return != nmemb)
	{
		printf("\n\t=д������ʱ���ִ���=\n");
		//exit(EXIT_FAILURE);
		return MY_FAIL;
	}
	if (fclose(file_ticket_total_change)) //�ر��ļ�
	{
		printf("\n\t=�ر��ļ�ʱ���ִ���=\n");
		//exit(EXIT_FAILURE);
		return MY_FAIL;
	}
	return MY_SUCCESS;
}

/**
 * @function: void get_password(char* password, int password_len)
 * @description: �����������Ǻ���ʾ
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
		if (ch == '\r')   //�س���������
		{
			printf("\n");
			break;
		}
		if (ch == '\b' && i > 0) //����ɾ����
		{
			i--;
			printf("\b \b");
		}
		else if (isprint(ch))  //����ɴ�ӡ�ַ�
		{
			password[i] = ch;
			printf("*");
			i++;
		}
	}
	password[i] = '\0';
}
