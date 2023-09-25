#ifndef DB_MANAGER_H_
#define DB_MANAGER_H_

// #include <mysql.h>

class DBManager
{
	// MySQL�� �����ؼ� CRUD
private:
	DBManager();				// �̱���
	~DBManager();

	// �������
	//MYSQL m_conn;
	//MYSQL* m_mysql_conn;
	//MYSQL_RES* m_last_query_result;

public:
	// �̱���
	DBManager(const DBManager&) = delete;
	DBManager& operator=(const DBManager&) = delete;

	static DBManager& GetInstance();
	
	// �޼���
	int DBConnect(const char* a_host, const char* a_user, const char* a_passwd, const char* a_dbname, unsigned int a_port);				// ����
	void DBClose();				// ��������
	
	int Insert(const char* a_table, const char* a_columns, const char* a_values);
	int Update(const char* a_table, const char* a_changes, const char* a_condition);
	int Delete(const char* a_table, const char* a_condition);
	//MYSQL_RES* Select(const char* a_table, const char* a_columns = "*", const char* a_condition = NULL);

	//MYSQL_RES* GetLastQueryResult() const;							// ������ ������ ����� ��ȯ
	//int NumOfRows();				// ������ Select�� ���� ������ ��´�
	//void ParseSelect(void* ap_struct, int a_rows_num);							// Parsing (�� ����ü�� �°� �����ϸ� ��)
};

#endif			DB_MANAGER_H_