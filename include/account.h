#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#define USER_OK			1
#define PASSWD_OK		3	
#define PASSWD_ERR		2
#define USER_ERR		4
#define EMAIL_ERR		5

#define REGISTER_OK		6
#define USER_EXIST		7
#define NAME_SIZE 		20
#define PASSWD_SIZE		20
#define EMAIL_SIZE		40
#define EMAIL_OK		50
#include <sqlite3.h>
typedef struct account{
	char name[NAME_SIZE];
	char passwd[PASSWD_SIZE];
}ACCOUNT;
int account_register(sqlite3 *db,char *username,char *passwd);
int account_verify(sqlite3 *db,char *username,char *passwd);
int account_verify_passwd(sqlite3 *db,char *passwd);
int account_modify_passwd(sqlite3 *db,char *username,char *passwd);
int account_modify_user(sqlite3 *db,char *username,char *email,char *passwd);
int account_get_user(sqlite3 *db,char *username,char *email);
int account_get_passwd(sqlite3 *db,char *user,char *passwd);
#endif
