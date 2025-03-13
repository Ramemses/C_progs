#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


int get_string(char* buff)
{
	int c;
	int cnt = 0;
	while ((c = getchar()) != EOF){
		if (c == '\n') break;
		buff[cnt++] = c;
	}	

	return 0;
}


int get_user_data(char* name, char* sur_name, char* birthday, char* job)
{
	printf("Enter the name: ");
	get_string(name);

	printf("Enter the sur_name: ");
	get_string(sur_name);

	printf("Enter the birthday (YYYY.mm.dd) : ");
	get_string(birthday);
	
	printf("Enter the job: ");
	get_string(job);


	return 0;
}


int callback(void* notUsed, int colCount, char** columns, char** colNames)
{
	for (int i = 0; i < colCount; i++)
		printf("%s = %s\n", colNames[i], columns[i] ? columns[i] : "NULL");

	printf("\n");
	return 0 ;
}




int user_create(sqlite3* db)
{
	char* err_msg;
	char* create_user_sql = "DROP TABLE IF EXISTS user;"
							"CREATE TABLE user(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, sur_name TEXT, birthday TEXT, job TEXT);";
	int result = sqlite3_exec(db, create_user_sql, 0, 0, &err_msg);

	if (result != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		return 1;
	}

	printf("Table created\n");
	return 0;
}


int user_add(sqlite3* db, char* name, char* sur_name, char* birthday, char* job)
{
	sqlite3_stmt* expr;
	char* add_user_sql = "INSERT INTO user (name, sur_name, birthday, job) VALUES (?, ?, ?, ?);";

	int result = sqlite3_prepare_v2(db, add_user_sql, -1, &expr, 0);
	if (result != SQLITE_OK){
		fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
		return 1;
	}

	
	sqlite3_bind_text(expr, 1, name, -1, SQLITE_STATIC);
	sqlite3_bind_text(expr, 2, sur_name, -1, SQLITE_STATIC);
	sqlite3_bind_text(expr, 3, birthday, -1, SQLITE_STATIC);
	sqlite3_bind_text(expr, 4, job, -1, SQLITE_STATIC);


	if (sqlite3_step(expr) != SQLITE_DONE){
		fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
		return 1;
	}

	printf("User has been added\n");
	sqlite3_finalize(expr);
	return 0;
}

int user_select(sqlite3* db)
{
	char* select_user_sql = "SELECT name, sur_name, birthday, job FROM user;";
	char* err_msg = NULL;

	
	int result = sqlite3_exec(db, select_user_sql, callback, 0, &err_msg);
	if (result != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		return 1;
	}
	
	return 0;	
}


int main(void)
{
	sqlite3* db;

	int result = sqlite3_open("test.db", &db);
	if (result != SQLITE_OK){
		fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	result = user_create(db);
	if (result != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char name[30];
	char sur_name[30];
	char birthday[30];
	char job[30];


	result = get_user_data(name, sur_name, birthday, job);
	if (result != 0){
		fprintf(stderr, "Error input!\n");
		return 2;
	}

	result = user_add(db, name, sur_name, birthday, job);
	if (result != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	result = user_select(db);
	if (result != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	

	
	sqlite3_close(db);

	return 0;
}
