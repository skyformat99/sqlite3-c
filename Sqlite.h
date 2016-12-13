#pragma once
#include <windows.h>

typedef long long int int64;
//typedef unsigned long long int uint64;

class Statement {
public:
	Statement(void *obj);
	int bindBlob(int idx, const void* val, int len);
	int bindDouble(int idx, double val);
	int bindInt(int idx, int val);
	int bindInt64(int idx, int64 val);
	int bindText(int idx, const char* val, int len);
	
	int getBindParameterCount();
	int clearBindings();
	//int getColumnCount();  ? ?
	const char *getColumnName(int iCol);
	const char *getColumnOriginName(int iCol);
	
	int step();
	//  Number of columns in a result set
	int getDataCount();
	// Result Values From A Query
	void *getColumnBlob(int iCol);
	int getColumnBytes(int iCol);
	double getColumnDouble(int iCol);
	int getColumnInt(int iCol);
	int64 getColumnInt64(int iCol);
	const unsigned char *getColumnText(int iCol);

	int finalize();

	// Reset A Prepared Statement Object
	int reset();
	
private:
	void *mObj;
};

class Record {
public:
	Record();
	int getColNum();
	int getRowNum();
	char* getColTitle(int col);
	char *getColVal(int row, int col);
	~Record();
private:
	class RecordData;
	RecordData *mData;
	char** mTitles;
	friend class Sqlite;
};

class Sqlite {
public:
	enum {
		SQLITE_OK = 0,
		SQLITE_ROW = 100,  /* sqlite3_step() has another row ready */
		SQLITE_DONE = 101  /* sqlite3_step() has finished executing */
	};
	Sqlite();
	static int initLibrary(const char *dllPath);
	
	// Database filename (UTF-8)
	int open(const char *fileName);
	
	int close();
	
	int exec(const char *sql,
		int (*callback)(void*,int,char**,char**),   /* Callback function */
		void *, /* 1st argument to callback */
		char **errmsg /* Error msg written here */);

	Record *query(const char *sql);

	int64 lastInsertRowid();
	
	// Count The Number Of Rows Modified
	int changes();
	
	int getTable(const char *sql,
		char ***pazResult,    /* Results of the query */
		int *pnRow,           /* Number of result rows written here */
		int *pnColumn,        /* Number of result columns written here */
		char **pzErrmsg       /* Error msg written here */);
		
	static void freeTable(char **result);
	static void mfree(void*);
	
	// Query Progress Callbacks
	void progressHandler(int, int(*)(void*), void*);
	
	const char *getErrMsg();
	
	// SQL statement, ssql is UTF-8 encoded
	// return Statement obj must delete by yourself
	Statement* prepare(const char *sql);
	
	int beginTransaction();
	void transactionSuccess();
	int endTransaction();
private:
	static int execCallback(void* udat, int colNum, char** colVal, char** colTitle);
	
private:
	void *mObj;
	int mTransOk;
};
