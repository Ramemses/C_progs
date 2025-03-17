#ifndef TESTS_DATABASE_CREATED
#define TESTS_DATABASE_CREATED 1


	
int __makeSQL__(sqlite3*, char*);

int create_faculty(sqlite3*);
int create_direction(sqlite3*);
int create_student(sqlite3*);
int create_subject(sqlite3*);
int create_subject_direction(sqlite3*);
int create_question(sqlite3*);
int create_answer(sqlite3*);
int create_attempt(sqlite3*);
int create_tests(sqlite3*);



















#endif 
