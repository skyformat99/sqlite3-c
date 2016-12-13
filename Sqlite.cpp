#include "Sqlite.h"
#include <stdio.h>
typedef long long int sqlite3_int64;
typedef unsigned long long int sqlite3_uint64;
typedef struct _sqlite3 sqlite3;
typedef struct _sqlite3_stmt sqlite3_stmt;

static void * adr[50] = {0};
static int sqlite3_init_library(const char *dll) {
	HMODULE lib = LoadLibrary(dll);
	if (lib == 0) return 0;
	adr[0] = (void*)GetProcAddress(lib, "sqlite3_close");
	adr[1] = (void*)GetProcAddress(lib, "sqlite3_exec");
	adr[2] = (void*)GetProcAddress(lib, "sqlite3_last_insert_rowid");
	adr[3] = (void*)GetProcAddress(lib, "sqlite3_changes");
	adr[4] = (void*)GetProcAddress(lib, "sqlite3_get_table");
	adr[5] = (void*)GetProcAddress(lib, "sqlite3_free_table");
	adr[6] = (void*)GetProcAddress(lib, "sqlite3_free");
	adr[7] = (void*)GetProcAddress(lib, "sqlite3_progress_handler");
	adr[8] = (void*)GetProcAddress(lib, "sqlite3_open");
	adr[9] = (void*)GetProcAddress(lib, "sqlite3_errmsg");
	adr[10] = (void*)GetProcAddress(lib, "sqlite3_prepare");
	adr[11] = (void*)GetProcAddress(lib, "sqlite3_bind_blob");
	adr[12] = (void*)GetProcAddress(lib, "sqlite3_bind_double");
	adr[13] = (void*)GetProcAddress(lib, "sqlite3_bind_int");
	adr[14] = (void*)GetProcAddress(lib, "sqlite3_bind_int64");
	adr[15] = (void*)GetProcAddress(lib, "sqlite3_bind_text");
	adr[16] = (void*)GetProcAddress(lib, "sqlite3_bind_parameter_count");
	adr[17] = (void*)GetProcAddress(lib, "sqlite3_clear_bindings");
	adr[18] = (void*)GetProcAddress(lib, "sqlite3_column_count");
	adr[19] = (void*)GetProcAddress(lib, "sqlite3_column_name");
	adr[20] = (void*)GetProcAddress(lib, "sqlite3_column_origin_name");
	adr[21] = (void*)GetProcAddress(lib, "sqlite3_step");
	adr[22] = (void*)GetProcAddress(lib, "sqlite3_data_count");
	adr[23] = (void*)GetProcAddress(lib, "sqlite3_column_double");
	adr[24] = (void*)GetProcAddress(lib, "sqlite3_column_int");
	adr[25] = (void*)GetProcAddress(lib, "sqlite3_column_int64");
	adr[26] = (void*)GetProcAddress(lib, "sqlite3_column_text");
	adr[27] = (void*)GetProcAddress(lib, "sqlite3_finalize");
	adr[28] = (void*)GetProcAddress(lib, "sqlite3_reset");
	adr[29] = (void*)GetProcAddress(lib, "sqlite3_column_blob");
	adr[30] = (void*)GetProcAddress(lib, "sqlite3_column_bytes");

	return 1;
}

static int sqlite3_close(sqlite3* db) {
	return ((int (*)(sqlite3*))adr[0])(db);
}
static int sqlite3_exec(sqlite3* db,  const char *sql, int (*cb)(void*,int,char**,char**), void * dat, char **errmsg) {
	return ((int (*)(sqlite3*, const char *, int (*)(void*,int,char**,char**), void*, char**))adr[1])(db, sql,cb, dat, errmsg);
}
static sqlite3_int64 sqlite3_last_insert_rowid(sqlite3* db) {
	return ((sqlite3_int64 (*)(sqlite3*))adr[2])(db);
}
static int sqlite3_changes(sqlite3* db) {
	return ((int (*)(sqlite3*))adr[3])(db);
}
static int sqlite3_get_table(sqlite3 *db,  const char *zSql,  char ***pazResult, int *pnRow,  int *pnColumn,  char **pzErrmsg) {
	return ((int (*)(sqlite3*,const char *,char ***, int *, int *, char**))adr[4])(db, zSql, pazResult, pnRow, pnColumn, pzErrmsg);
}
static void sqlite3_free_table(char **result) {
	((void (*)(char **))adr[5])(result);
}
static void sqlite3_free(void* d) {
	((void (*)(void*))adr[6])(d);
}
static void sqlite3_progress_handler(sqlite3* db, int a, int(*b)(void*), void* d) {
	((void (*)(sqlite3*, int, int(*)(void*), void*))adr[7])(db, a, b, d);
}
static int sqlite3_open( const char *filename, sqlite3 **ppDb) {
	return ((int (*)(const char *, sqlite3 **))adr[8])(filename, ppDb);
}
static const char *sqlite3_errmsg(sqlite3* db) {
	return ((const char * (*)(sqlite3*))adr[9])(db);
}
static int sqlite3_prepare( sqlite3 *db,  const char *zSql,  int nByte, sqlite3_stmt **ppStmt, const char **pzTail) {
	return ((int (*)( sqlite3 *,  const char *,  int , sqlite3_stmt **, const char ** ))adr[10])(db, zSql, nByte,ppStmt,  pzTail);
}
static int sqlite3_bind_blob(sqlite3_stmt* a, int b , const void* c , int n, void(*d)(void*)) {
	return ((int (*)(sqlite3_stmt*, int, const void*, int, void(*)(void*)))adr[11])(a, b, c, n, d);
}
static int sqlite3_bind_double(sqlite3_stmt* a, int b, double c) {
	return ((int (*)(sqlite3_stmt*, int, double))adr[12])(a, b, c);
}
static int sqlite3_bind_int(sqlite3_stmt* a, int b, int c) {
	return ((int (*)(sqlite3_stmt*, int, int))adr[13])(a, b, c);
}
static int sqlite3_bind_int64(sqlite3_stmt* a, int b, sqlite3_int64 c) {
	return ((int (*)(sqlite3_stmt*, int, sqlite3_int64))adr[14])(a, b, c);
}
static int sqlite3_bind_text(sqlite3_stmt* a,int b ,const char* c,int n,void(*d)(void*)) {
	return ((int (*)(sqlite3_stmt*, int, const char*,int,void(*)(void*)))adr[15])(a, b, c, n, d);
}
static int sqlite3_bind_parameter_count(sqlite3_stmt* a) {
	return ((int (*)(sqlite3_stmt*))adr[16])(a);
}
static int sqlite3_clear_bindings(sqlite3_stmt* a) {
	return ((int (*)(sqlite3_stmt*))adr[17])(a);
}
// ?
static int sqlite3_column_count(sqlite3_stmt *a) {
	return ((int (*)(sqlite3_stmt*))adr[18])(a);
}
static const char *sqlite3_column_name(sqlite3_stmt* a, int b) {
	return ((const char * (*)(sqlite3_stmt*, int))adr[19])(a, b);
}
static const char *sqlite3_column_origin_name(sqlite3_stmt* a,int b) {
	return ((const char * (*)(sqlite3_stmt*, int))adr[20])(a, b);
}
static int sqlite3_step(sqlite3_stmt* a) {
	return ((int (*)(sqlite3_stmt*))adr[21])(a);
}
static int sqlite3_data_count(sqlite3_stmt *a) {
	return ((int (*)(sqlite3_stmt*))adr[22])(a);
}
static void *sqlite3_column_blob(sqlite3_stmt* a, int iCol) {
	return ((void* (*)(sqlite3_stmt*, int))adr[29])(a, iCol);
}
static int sqlite3_column_bytes(sqlite3_stmt* a, int iCol) {
	return ((int (*)(sqlite3_stmt*, int))adr[30])(a, iCol);
}
static double sqlite3_column_double(sqlite3_stmt* a, int iCol) {
	return ((double (*)(sqlite3_stmt*, int))adr[23])(a, iCol);
}
static int sqlite3_column_int(sqlite3_stmt* a, int iCol) {
	return ((int (*)(sqlite3_stmt*, int))adr[24])(a, iCol);
}
static sqlite3_int64 sqlite3_column_int64(sqlite3_stmt* a, int iCol) {
	return ((sqlite3_int64 (*)(sqlite3_stmt*, int))adr[25])(a, iCol);
}
static const unsigned char *sqlite3_column_text(sqlite3_stmt* a, int iCol) {
	return ((const unsigned char * (*)(sqlite3_stmt*, int))adr[26])(a, iCol);
}
static int sqlite3_finalize(sqlite3_stmt *a) {
	return ((int (*)(sqlite3_stmt*))adr[27])(a);
}
// Reset A Prepared Statement Object
static int sqlite3_reset(sqlite3_stmt *a) {
	return ((int (*)(sqlite3_stmt*))adr[28])(a);
}

//------------------------------------------------------------------------------
Statement::Statement(void *obj) : mObj(obj) {
}
int Statement::bindBlob(int idx, const void* val, int len) {
	return sqlite3_bind_blob((sqlite3_stmt*)mObj, idx, val, len, 0);
}
int Statement::bindDouble(int idx, double val) {
	return sqlite3_bind_double((sqlite3_stmt*)mObj, idx, val);
}
int Statement::bindInt(int idx, int val) {
	return sqlite3_bind_int((sqlite3_stmt*)mObj, idx, val);
}
int Statement::bindInt64(int idx, int64 val) {
	return sqlite3_bind_int64((sqlite3_stmt*)mObj, idx, val);
}
int Statement::bindText(int idx, const char* val, int len) {
	return sqlite3_bind_text((sqlite3_stmt*)mObj, idx, val, len, 0);
}
int Statement::getBindParameterCount() {
	return sqlite3_bind_parameter_count((sqlite3_stmt*)mObj);
}
int Statement::clearBindings() {
	return sqlite3_clear_bindings((sqlite3_stmt*)mObj);
}
//int getColumnCount();  ??
const char *Statement::getColumnName(int iCol) {
	return sqlite3_column_name((sqlite3_stmt*)mObj, iCol);
}
const char *Statement::getColumnOriginName(int iCol) {
	return sqlite3_column_origin_name((sqlite3_stmt*)mObj, iCol);
}
int Statement::step() {
	return sqlite3_step((sqlite3_stmt*)mObj);
}
int Statement::getDataCount() {
	return sqlite3_data_count((sqlite3_stmt*)mObj);
}
void *Statement::getColumnBlob(int iCol) {
	return sqlite3_column_blob((sqlite3_stmt*)mObj, iCol);
}
int Statement::getColumnBytes(int iCol) {
	return sqlite3_column_bytes((sqlite3_stmt*)mObj, iCol);
}
double Statement::getColumnDouble(int iCol) {
	return sqlite3_column_double((sqlite3_stmt*)mObj, iCol);
}
int Statement::getColumnInt(int iCol) {
	return sqlite3_column_int((sqlite3_stmt*)mObj, iCol);
}
int64 Statement::getColumnInt64(int iCol) {
	return sqlite3_column_int64((sqlite3_stmt*)mObj, iCol);
}
const unsigned char *Statement::getColumnText(int iCol) {
	return sqlite3_column_text((sqlite3_stmt*)mObj, iCol);
}
int Statement::finalize() {
	return sqlite3_finalize((sqlite3_stmt*)mObj);
}
// Reset A Prepared Statement Object
int Statement::reset() {
	return sqlite3_reset((sqlite3_stmt*)mObj);
}
//----------------------------------------------------------------------
static char* dup(const char *str) {
	if (str == 0) return 0;
	int len = strlen(str);
	char *p = (char*)malloc(len + 1);
	strcpy(p, str);
	return p;
}
class Record::RecordData {
public:
	const static int PAGE_SIZE = 512/4 - 1;
	RecordData() : mColNum(0), mRowSize(0), mPageNum(0), mData(0) {
	}

	void** getPage(int idx) {
		if (idx >= mPageNum)
			return 0;
		void **d = (void**)mData;
		for (int i = 0; i < idx; ++i) {
			void **last = d + PAGE_SIZE;
			d = last;
		}
		return d;
	}
	
	void inc() {
		if (mRowSize < mPageNum * PAGE_SIZE)
			return;
		if (mPageNum == 0) {
			mData = malloc(sizeof(void*) * (PAGE_SIZE + 1));
		} else {
			void **d = getPage(mPageNum - 1);
			void **last = d + PAGE_SIZE;
			*last = malloc(sizeof(void*) * (PAGE_SIZE + 1));
		}
		++mPageNum;
	}
	
	void append(char **colVal) {
		inc();
		void **d = getPage(mRowSize / PAGE_SIZE);
		d += mRowSize % PAGE_SIZE;
		++mRowSize;
		char **row = (char**)(malloc(sizeof(char*) * mColNum));
		*d = row;
		for (int i = 0; i < mColNum; ++i)
			row[i] = dup(colVal[i]);
	}
	
	int getSize(int page) {
		if (page < mPageNum - 1)
			return PAGE_SIZE;
		return mRowSize % PAGE_SIZE;
	}
	
	char *getColVal(int row, int col) {
		if (row >= mRowSize || col >= mColNum)
			return 0;
		void **pd = getPage(row / PAGE_SIZE);
		void **rd = (void**)pd[row % PAGE_SIZE];
		return (char*)rd[col];
	}
	
	void freeRow(void **row) {
		for (int i = 0; i < mColNum; ++i)
			free(row[i]);
		free((void*)row);
	}
	
	~RecordData() {
		for (int i = mPageNum - 1; i >= 0; --i) {
			void **pd = getPage(i);
			for (int j = 0; j < getSize(i); ++j) {
				freeRow((void**)pd[j]);
			}
			free(pd);
		}
	}
	
	int mColNum;
	int mRowSize;
	int mPageNum;
	void *mData;
};
Record::Record() : mData(new RecordData()) {
}
int Record::getColNum() {
	return mData->mColNum;
}
int Record::getRowNum() {
	return mData->mRowSize;
}
char* Record::getColTitle(int col) {
	if (col < getColNum()) return mTitles[col];
	return 0;
}
char *Record::getColVal(int row, int col) {
	return mData->getColVal(row, col);
}
Record::~Record() {
	delete mData;
	for (int i = 0; i < mData->mColNum; ++i) {
		free(mTitles[i]);
	}
	free(mTitles);
}

//----------------------------------------------------------------------
Sqlite::Sqlite() : mObj(0), mTransOk(0) {
}
int Sqlite::initLibrary(const char *dllPath) {
	return sqlite3_init_library(dllPath);
}
int Sqlite::open(const char *filename) {
	return sqlite3_open(filename, (sqlite3 **)&mObj);
}
int Sqlite::close() {
	return sqlite3_close((sqlite3 *)mObj);
}
int Sqlite::exec(const char *sql, int (*callback)(void*,int,char**,char**), void * param, char **errmsg) {
	return sqlite3_exec((sqlite3 *)mObj, sql, callback, param, errmsg);
}
int Sqlite::execCallback(void* udat, int colNum, char** colVal, char** colTitle) {
	Record *r = (Record*)udat;
	if (colNum > 0 && r->mTitles == 0) {
		r->mData->mColNum = colNum;
		r->mTitles = (char**)malloc(sizeof(char*) * colNum);
		for (int i = 0; i < colNum; ++i)
			r->mTitles[i] = dup(colTitle[i]);
	}
}
Record *Sqlite::query(const char *sql) {
	Record* r = new Record();
	int v = exec(sql, &execCallback, (void*)r, 0);
	if (v == SQLITE_OK) {
		return r;
	}
	delete r;
	return 0;
}
int64 Sqlite::lastInsertRowid() {
	return sqlite3_last_insert_rowid((sqlite3 *)mObj);
}
int Sqlite::changes() {
	return sqlite3_changes((sqlite3 *)mObj);
}
int Sqlite::getTable(const char *sql, char ***pazResult, int *pnRow, int *pnColumn, char **pzErrmsg) {
	return sqlite3_get_table((sqlite3 *)mObj, sql, pazResult, pnRow, pnColumn, pzErrmsg);
}
void Sqlite::freeTable(char **result) {
	return sqlite3_free_table(result);
}
void Sqlite::mfree(void* p) {
	sqlite3_free(p);
}
void Sqlite::progressHandler(int a, int(*b)(void*), void* c) {
	sqlite3_progress_handler((sqlite3 *)mObj, a, b, c);
}

const char *Sqlite::getErrMsg() {
	return sqlite3_errmsg((sqlite3 *)mObj);
}

// SQL statement, ssql is UTF-8 encoded
Statement* Sqlite::prepare(const char *sql) {
	Statement *s = 0;
	sqlite3_stmt *stmt = 0;
	int v = sqlite3_prepare((sqlite3 *)mObj, sql, strlen(sql), &stmt, 0);
	if (stmt != 0) {
		s = new Statement((void*)stmt);
	}
	return s;
}

int Sqlite::beginTransaction() {
	mTransOk = 0;
	return sqlite3_exec((sqlite3 *)mObj, "begin transaction", NULL, NULL, NULL);
}
void Sqlite::transactionSuccess() {
	mTransOk = 1;
}
int Sqlite::endTransaction() {
	if (mTransOk == 1) {
		mTransOk = 0;
		return sqlite3_exec ((sqlite3 *)mObj ,"commit transaction", NULL , NULL , NULL);
	}
	return  sqlite3_exec((sqlite3 *)mObj, "rollback transaction", NULL , NULL , NULL);
}



