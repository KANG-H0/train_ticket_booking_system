#pragma once
#include "main.h"

#define MY_SUCCESS 0
#define MY_FAIL (-1)
#define USER_TICKET_FILE_PATH_LEN 60
#define USER_PASSWORD_LEN 20
#define PHONE_ACCOUNT_NUM_LEN 12
#define ID_NUM_LEN 19
#define USER_NAME_LEN 20
#define TRAIN_NUM_LEN 10
#define START_STATION_LEN 20
#define ARRIVE_STATION_LEN 20
#define START_TIME_LEN 20
#define ARRIVE_TIME_LEN 20

//火车票信息结构体链表数据信息
typedef struct TicketsInformation
{
	char train_num[TRAIN_NUM_LEN];              //列车号
	char start_station[START_STATION_LEN];     //起始站
	char arrive_station[ARRIVE_STATION_LEN]; //终点站
	char start_time[START_TIME_LEN];               //发车时间
	char arrive_time[ARRIVE_TIME_LEN];           //到站时间
	float ticket_price;                                          //票价
	size_t ticket_total;                                         //余票
} TICKET;

//用户信息结构体链表数据信息
typedef struct UserInformation
{
	char phone_account_num[PHONE_ACCOUNT_NUM_LEN]; //手机账号
	char user_password[USER_PASSWORD_LEN];                     //密码
	char user_name[USER_NAME_LEN];                                    //用户姓名
	char ID_num[ID_NUM_LEN];                                               //身份证号
	char user_type[6];                                                               //用户类型User/Admin
} USER;

extern const char* user_tickets_file_path_part1;
extern const char* file_extension;
extern const char* all_tickets_file_path;
extern const char* all_users_file_path;
extern char account_file_name[PHONE_ACCOUNT_NUM_LEN];
extern char* user_tickets_file_path;
extern const char* Admin_type;
extern const char* User_type;

char log_in_to_booking_system(void);
void registered_new_users(const char* User_or_Admin);
void display_all_registered_users(void);
void search_for_train_information(void);
void add_train_information(void);
fpos_t display_all_train_information(void);
void order_train_tickets(void);
void return_the_ticket(void);
void modify_train_information(void);
void delete_train_information(void);
void display_user_booking_information(void);

int save_a_newly_train_data_to_the_file(TICKET save_new_ticket);
int save_a_newly_registered_user_to_the_file(USER save_new_user);
char* build_user_train_file_name_path(char* account_file_name);
int check_whether_the_train_data_exists(TICKET check_ticket_data);
int check_whether_the_user_data_exists(USER check_user_data);
TICKET input_the_changed_train_information(TICKET change_train, int select_num);
FILE* compare_train_information(char* input_start_station, char* input_arrive_station);
int the_change_of_the_remaining_train_tickets(TICKET read_tickets_tmp, int add_or_sub);
void remove_train_information(TICKET delete_ticket_data, const char* which_file);
void get_password(char* password, int password_len);
