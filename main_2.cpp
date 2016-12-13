#include <stdio.h>
#include "Sqlite.h"

int callback(void* data,int col, char** colVal, char** colName) {
	for (int i = 0; i < col; ++i) {
		printf("[%s = %s]  ", colName[i], colVal[i]);
	}
	printf("\n");
	return 0;
}

int main(int argc, char **argv) {
	Sqlite::initLibrary("sqlite3.dll");
	
	Sqlite db;
	db.open("hello2.db");
	
	const char *sql = "create table MM(_id integer primary key, _name varchar(20), _old int)";
	char *err = 0;
	int cc = db.exec(sql, 0, 0, &err);
	if (cc != Sqlite::SQLITE_OK) { printf("1. error: %s \n", err);}
	
	//sql = "insert into MM(_name,_old) values('aaa', 10);insert into MM(_name,_old) values('bbb', 11);";
	//cc = db.exec(sql, 0, 0, &err);
	//if (cc != Sqlite::SQLITE_OK) { printf("2. error: %s \n", err);}

	sql = "insert into MM(_name,_old) values('aaa%d', %d)";
	char sb[100];
	for (int i = 0; 0 && i < 300; ++i) {
		sprintf(sb, sql, i, i + 10000);
		db.exec(sb, 0, 0, &err);
	}

	sql = "select * from mm";
	//cc = db.exec(sql, callback, 0, &err);
	//if (cc != Sqlite::SQLITE_OK) { printf("4. error: %s \n", err);}
	
	db.close();
	
	return 0;
}
