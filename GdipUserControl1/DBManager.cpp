#include "pch.h"
#include "common_struct.h"
#include "DBManager.h"

//#pragma comment(lib, "libmysql.lib")

/*
MySQL include : C:\Program Files\MySQL\MySQL Server 8.0\include
MySQL lib : C:\Program Files\MySQL\MySQL Server 8.0\lib
MySQL dll : PATH=C:\Program Files\MySQL\MySQL Server 8.0\lib;%PATH%
MySQL input : libmysql.lib
*/

DBManager::DBManager()
{
	//mysql_init(&m_conn);
	//m_mysql_conn = NULL;
}

DBManager& DBManager::GetInstance()
{
	static DBManager instance;
	return instance;
}

int DBManager::DBConnect(const char* a_host, const char* a_user, const char* a_passwd, const char* a_dbname, unsigned int a_port)
{
	int func_result = FALSE;
	//m_mysql_conn = mysql_readl_connect(&m_conn, a_host, a_user, a_passwd, a_dbname, a_port, NULL, 0);

	//if (m_mysql_conn != NULL) {
	//	func_result = TRUE;
	//}

	return func_result;
}

void DBManager::DBClose()
{
	//if (m_mysql_conn != NULL) {
		//mysql_close(m_mysql_conn);
		//m_mysql_conn = NULL;
	//}
}

int DBManager::Insert(const char* a_table, const char* a_columns, const char* a_values)
{
	int func_result = FALSE;
	char query[512] = { 0, };
	sprintf_s(query, 512, "INSERT INTO %s (%s) VALUES (%s);", a_table, a_columns, a_values);
	//if (mysql_query(m_mysql_conn, query) == 0) {
	//	func_result = TRUE;
	//}
	return func_result;
}

int DBManager::Update(const char* a_table, const char* a_changes, const char* a_condition)
{
	int func_result = FALSE;
	char query[512] = { 0, };
	sprintf_s(query, 512, "UPDATE %s SET %s WHERE %s;", a_table, a_changes, a_condition);
	//if (mysql_query(m_mysql_conn, query) == 0) {
	//	func_result = TRUE;
	//}
	return func_result;
}

int DBManager::Delete(const char* a_table, const char* a_condition)
{
	int func_result = FALSE;
	char query[512] = { 0, };
	sprintf_s(query, 512, "DELETE FROM %s WHERE %s;", a_table, a_condition);
	//if (mysql_query(m_mysql_conn, query) == 0) {
	//	func_result = TRUE;
	//}
	return func_result;
}

//int DBManager::NumOfRows()
//{
//	int func_result = 0;
//	if (m_last_query_result != NULL) {
//		func_result = mysql_num_rows(m_last_query_result);
//	}
//	return func_result;
//}

//void DBManager::ParseSelect(void* ap_struct, int a_rows_num)
//{
//	if (m_last_query_result != NULL && ap_struct != NULL) {
//		int row_index = 0;
//		char* p = (char*)ap_struct;
//
//		MYSQL_ROW row = mysql_fetch_row(m_last_query_result);
//		while (row) {		
//			//memcpy(p, row[0], 44);
//			//p += 45;
//			//memcpy(datetime, row[1], 19);
//			//p += 20;
//			//float temp = atof(row[2]);
//			//p += sizeof(float);
//			//int humi = atoi(row[3]);
//			//p += sizeof(int);
// 
//			row = mysql_fetch_row(m_last_query_result);					// 다음 행
//		}
//
//		mysql_free_result(m_last_query_result);						// Select한 메모리를 해제한다
//		m_last_query_result = NULL;
//	}
//}

//MYSQL_RES* DBManager::GetLastQueryResult() const
//{
//	return m_last_query_result;
//}

//MYSQL_RES* DBManager::Select(const char* a_table, const char* a_columns, const char* a_condition)
//{
//	char query[512] = { 0, };
//
//	if (a_condition != NULL) {
//		sprintf_s(query, 512, "SELECT %s FROM %s WHERE %s;", a_columns, a_table, a_condition);
//	}
//	else {
//		sprintf_s(query, 512, "SELECT %s FROM %s;", a_columns, a_table);
//	}
//
//	if (mysql_query(m_mysql_conn, query) == 0) {
//		m_last_query_result = mysql_store_result(m_mysql_conn);
//		return m_last_query_result;
//	}
//	else {
//		return NULL;
//	}
//}

DBManager::~DBManager()
{
	DBClose();
}
