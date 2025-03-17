#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

int __makeSQL__(sqlite3* db, char* sql)
{

	char* errmsg = NULL;
	int result;
	
	result = sqlite3_exec(db, sql, 0, 0, &errmsg);
	if (result != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", errmsg);
		sqlite3_free(errmsg);
		return 1;
	}

	sqlite3_free(errmsg);
	return 0;
}

int create_faculty(sqlite3* db)
{
	char* sql = "CREATE TABLE IF NOT EXISTS faculty("	
				"faculty_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"faculty_name TEXT"
				");";
	
	return __makeSQL__(db, sql);	
}

int create_direction(sqlite3* db)
{
	char* sql = "CREATE TABLE IF NOT EXISTS direction("
				"direction_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"direction_name TEXT,"
				"faculty_id INTEGER,"
				"FOREIGN KEY (faculty_id) REFERENCES faculty (faculty_id) ON DELETE CASCADE"
				");";

	return __makeSQL__(db, sql);	
}

int create_group(sqlite3* db)
{
	char* sql = "CREATE TABLE IF NOT EXISTS groups("
				"group_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"direction_id INTEGER,"
				"FOREIGN KEY (direction_id) REFERENCES direction (direction_id) ON DELETE CASCADE"
				");";

	__makeSQL__(db, sql);
}

int create_student(sqlite3* db)
{
	char* sql = "CREATE TABLE IF NOT EXISTS student("
				"student_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"student_name TEXT,"
				"group_number INTEGER,"
				"group_id INTEGER,"
				"FOREIGN KEY (group_id) REFERENCES groups (group_id) ON DELETE CASCADE"
				");";

	return __makeSQL__(db, sql);
}

int create_subject(sqlite3* db)
{
	char* sql = "CREATE TABLE IF NOT EXISTS subject("
				"subject_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"subject_name TEXT);";
	return __makeSQL__(db, sql);	
}

int create_subject_direction(sqlite3* db)
{
	char* sql = "CREATE TABLE IF NOT EXISTS subject_direction("
				"subject_direction_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"subject_id INTEGER,"
				"direction_id INTEGER,"
				"FOREIGN KEY (direction_id) REFERENCES direction (direction_id),"
				"FOREIGN KEY (subject_id) REFERENCES subject (subject_id)"
				");";
	return __makeSQL__(db, sql);
}

int create_question(sqlite3* db)
{
	char* sql = "CREATE TABLE IF NOT EXISTS question("
				"question_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"question_name TEXT,"
				"subject_id INTEGER,"
				"FOREIGN KEY (subject_id) REFERENCES subject (subject_id) ON DELETE CASCADE"
				");";

	return __makeSQL__(db, sql);	
}

int create_answer(sqlite3* db)
{
	char* sql = "CREATE TABLE IF NOT EXISTS answer("
				"answer_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"answer_name TEXT,"
				"question_id INTEGER,"
				"is_correct INTEGER,"	
				"FOREIGN KEY (question_id) REFERENCES question (question_id) ON DELETE CASCADE"
				");";

	return __makeSQL__(db, sql);
}
int create_attempt(sqlite3* db)
{
	char* sql = "CREATE TABLE IF NOT EXISTS attempt("
				"attempt_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"student_id INTEGER,"
				"subject_id INTEGER,"
				"attempt_date TEXT,"
				"result INTEGER,"
				"FOREIGN KEY (student_id) REFERENCES student (student_id) ON DELETE CASCADE,"
				"FOREIGN KEY (subject_id) REFERENCES subject (subject_id) ON DELETE CASCADE"
				");";
		

	return __makeSQL__(db, sql);
}

int create_tests(sqlite3* db)
{
	char* sql = "CREATE TABLE IF NOT EXISTS tests("
				"tests_id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"attempt_id INTEGER,"
				"question_id INTEGER,"
				"answer_id INTEGER,"
				"FOREIGN KEY (attempt_id) REFERENCES attempt (attempt_id) ON DELETE CASCADE"
				");";
	return __makeSQL__(db, sql);		
}


