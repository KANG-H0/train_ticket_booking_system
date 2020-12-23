#include "main.h"

#pragma warning(disable:6031)
char login_flag = 0;
//������
int main(void)
{
	//��¼��Ʊϵͳ
	login_flag = log_in_to_booking_system();
	while (login_flag == 'U' || login_flag == 'A')
	{
		if (login_flag == 'U') //������û���¼
			user_login_interface_menu();
		if (login_flag == 'A') //����ǹ���Ա��¼
			administrator_login_interface_menu();
	}
	return 0;
}

/**
 * @function: void user_login_interface_menu(void)
 * @description: �û���¼����˵�
 * @param {*}
 * @return {*}
 */
void user_login_interface_menu(void)
{
	system("cls");
	printf("\t===============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t===============================\n");
	printf("\t\t1.��ʾ���л���Ϣ\n\t\t2.��ѯ����Ϣ\n\t\t3.��ʾ�û���Ʊ��Ϣ\n");
	printf("\t\t4.������Ʊ\n\t\t5.��Ʊ\n\t\t6.ע�����û�\n\t\t7.�˳�\n");
	printf("\t===============================\n");
	printf("\t[�û�]\n");
	printf("\n\t>��ѡ���ܣ�");
	size_t select_funs;
	char YorN = 0;
	scanf_s("%d", &select_funs);
	switch (select_funs)
	{
	case 1:
		system("cls");
		printf("\t===============================\n");
		printf("\t\t��Ʊ��Ʊϵͳ\n");
		printf("\t===============================\n");
		printf("\n\t[��ʾ����Ϣ]\n");
		display_all_train_information(); //��ʾ���л���Ϣ(user/administrators)
		printf("\n\t==��ʾ���==\n\n");
		system("pause");
		user_login_interface_menu();
		break;
	case 2:
		search_for_train_information(); //��ѯ����Ϣ(user/administrators)
		printf("\n\t>�Ƿ������ѯ��[������ѯ='y' ���ٲ�ѯ='�����ַ�']\n");
		getchar();
		printf("\t>��ѡ��");
		scanf_s("%s", &YorN, 2);
		if (YorN == 'y' || YorN == 'Y')
			search_for_train_information();
		else
			user_login_interface_menu();
		break;
	case 3:
		display_user_booking_information(); //��ʾ�û�������Ϣ(user)
		break;
	case 4:
		order_train_tickets(); //������Ʊ(user)
		break;
	case 5:
		return_the_ticket(); //��Ʊ(user)
		break;
	case 6:
		registered_new_users(User_type); //ע�����û�(user)
		break;
	case 7:
		main();
		break;
	default:
		printf("\n==��ѡ����ȷ�Ĺ��ܱ��(1~6)==\n");
		getchar();
		system("pause");
		user_login_interface_menu();
		break;
	}
}

/**
 * @function: void administrator_login_interface_menu(void)
 * @description: ����Ա��¼����˵�
 * @param {*}
 * @return {*}
 */
void administrator_login_interface_menu(void)
{
	system("cls");
	printf("\t===============================\n");
	printf("\t\t��Ʊ��Ʊϵͳ\n");
	printf("\t===============================\n");
	printf("\t\t1.��ʾ���л���Ϣ\n\t\t2.��ѯ����Ϣ\n\t\t3.���ӻ���Ϣ\n\t\t4.�޸Ļ�Ʊ��Ϣ\n");
	printf("\t\t5.ɾ����Ʊ��Ϣ\n\t\t6.�鿴����ע���û�\n\t\t7.��ӹ���Ա\n\t\t8.�˳�\n");
	printf("\t===============================\n");
	printf("\t[����Ա]\n");
	printf("\n\t>��ѡ���ܣ�");
	size_t select_funs;
	char YorN = 0;
	scanf_s("%d", &select_funs);
	switch (select_funs)
	{
	case 1:
		system("cls");
		printf("\t===============================\n");
		printf("\t\t��Ʊ��Ʊϵͳ\n");
		printf("\t===============================\n");
		printf("\n\t[��ʾ����Ϣ]\n");
		display_all_train_information(); //��ʾ���л���Ϣ(user/administrators)
		printf("\n\t==��ʾ���==\n\n");
		system("pause");
		administrator_login_interface_menu();
		break;
	case 2:
		search_for_train_information(); //��ѯ����Ϣ(user/administrators)
		getchar();
		printf("\n\t>�Ƿ������ѯ��[������ѯ='y' ���ٲ�ѯ='�����ַ�']\n");
		printf("\t>��ѡ��");
		scanf_s("%s", &YorN, 2);
		if (YorN == 'y' || YorN == 'Y')
			search_for_train_information();
		else
			user_login_interface_menu();
		break;
	case 3:
		add_train_information(); //���ӻ���Ϣ(administrators)
		break;
	case 4:
		modify_train_information(); //�޸Ļ�Ʊ��Ϣ(administrators)
		break;
	case 5:
		delete_train_information(); //ɾ������Ϣ(administrators)
		break;
	case 6:
		display_all_registered_users(); //��ʾ����ע���û�(administrators)
		break;
	case 7:
		registered_new_users(Admin_type); //��ӹ���Ա(administrators)
		break;
	case 8:
		main();
		break;
	default:
		printf("\n==��ѡ����ȷ�Ĺ��ܱ��(1~7)==\n");
		getchar();
		system("pause");
		administrator_login_interface_menu();
		break;
	}
}
