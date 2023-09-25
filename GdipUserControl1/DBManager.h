#ifndef DB_MANAGER_H_
#define DB_MANAGER_H_

// #include <mysql.h>

class DBManager
{
	// MySQL에 접속해서 CRUD
private:
	DBManager();				// 싱글턴
	~DBManager();

	// 멤버변수
	//MYSQL m_conn;
	//MYSQL* m_mysql_conn;
	//MYSQL_RES* m_last_query_result;

public:
	// 싱글턴
	DBManager(const DBManager&) = delete;
	DBManager& operator=(const DBManager&) = delete;

	static DBManager& GetInstance();
	
	// 메서드
	int DBConnect(const char* a_host, const char* a_user, const char* a_passwd, const char* a_dbname, unsigned int a_port);				// 연결
	void DBClose();				// 연결해제
	
	int Insert(const char* a_table, const char* a_columns, const char* a_values);
	int Update(const char* a_table, const char* a_changes, const char* a_condition);
	int Delete(const char* a_table, const char* a_condition);
	//MYSQL_RES* Select(const char* a_table, const char* a_columns = "*", const char* a_condition = NULL);

	//MYSQL_RES* GetLastQueryResult() const;							// 마지막 쿼리의 결과를 반환
	//int NumOfRows();				// 마지막 Select한 행의 갯수를 얻는다
	//void ParseSelect(void* ap_struct, int a_rows_num);							// Parsing (각 구조체에 맞게 조정하면 됨)
};

#endif			DB_MANAGER_H_