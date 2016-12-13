#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"


int callback(void* data,int col, char** colVal, char** colName) {
	for (int i = 0; i < col; ++i) {
		printf("[%s = %s]  ", colName[i], colVal[i]);
	}
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]) {
	sqlite3_init_library("sqlite3.dll");
	
	sqlite3 *db = NULL;
	sqlite3_open("hello.db", &db);
	
	char *err = NULL;
	int cc = 0;
	
	const char *sql = "create table MM(_id integer primary key, _name varchar(20), _old int)";
	cc = sqlite3_exec(db, sql, callback, NULL, &err);
	if (cc != SQLITE_OK) { printf("1. error: %s \n", err);}
	
	sql = "insert into MM(_name,_old) values('aaa', 10);insert into MM(_name,_old) values('bbb', 11);";
	cc = sqlite3_exec(db, sql, callback, NULL, &err);
	if (cc != SQLITE_OK) { printf("2. error: %s \n", err);}
	
	sql = "select * from mm";
	cc = sqlite3_exec(db, sql, callback, NULL, &err);
	if (cc != SQLITE_OK) { printf("4. error: %s \n", err);}
	
	sqlite3_close(db);
    return 0;
}
