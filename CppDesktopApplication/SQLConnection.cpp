#define MYSQLSUCCESS(returnCode) ((returnCode == SQL_SUCCESS) || (returnCode == SQL_SUCCESS_WITH_INFO))
#define MAX_DATA 100

#include "SQLConnection.h"
#include <stdio.h>

RETCODE returnCode;    //ODBC return code
SQLHENV handleEnvironment;//Environment handle
SQLHDBC handleConnection; //Connection handle
SQLHSTMT handleStatement; //Statement handle

//void ShowSqlError(unsigned int handleType, const SQLHANDLE& handle) {
//	SQLWCHAR SQLState[1024];
//	SQLWCHAR message[1024];
//	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL)) {
//		MessageBox(NULL, message, L"Error", 0);
//	}
//}

//Allocate environment handle and connection handle, connect to data source and
void SQLConnection() 
{
	SQLWCHAR dataSourceName[] = L"DSN=SQLCPPTEST;UID=*;PWD=*;", returnConnectionString[1024], text[1024], SQLState[1024];
	SQLINTEGER i = 0, native;
	SQLSMALLINT len;
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &handleEnvironment);
	SQLSetEnvAttr(handleEnvironment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
	SQLAllocHandle(SQL_HANDLE_DBC, handleEnvironment, &handleConnection);

	returnCode = SQLDriverConnect(handleConnection, NULL, dataSourceName, SQL_NTS,
		returnConnectionString, 1024, NULL, SQL_DRIVER_COMPLETE);

	//Deallocate handles, display error message, and exit
	if (!MYSQLSUCCESS(returnCode)) 
	{
		SQLGetDiagRec(SQL_HANDLE_DBC, handleConnection, ++i, SQLState, &native, text - 1, sizeof(text), &len);
		SQLFreeConnect(handleEnvironment);
		SQLFreeEnv(handleEnvironment);
		SQLFreeConnect(handleConnection);
		(exit(-1));
	}

	//Allocate statement handle
	SQLAllocHandle(SQL_HANDLE_STMT, handleConnection, &handleStatement);
}

void SQLExecution(SQLWCHAR _username, SQLWCHAR _password)
{
	SQLWCHAR Username = _username;
	SQLWCHAR Password = _password;
	SQLINTEGER cbValue = SQL_NTS;

	//SQLPrepare(handleStatement, (SQLWCHAR*)"{call REGISTER_USER(?,?)}", SQL_NTS);
	SQLBindParameter(handleStatement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 30, 0, &Username, 0, &cbValue);
	SQLBindParameter(handleStatement, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 30, 0, &Password, 0, &cbValue);
	//SQLWCHAR prepare = SQLPrepare(handleStatement, callProcedure, SQL_NTS);
	if (!MYSQLSUCCESS(returnCode))
	{
		//ShowSqlError();
		//Deallocate handles and disconnect
		SQLFreeStmt(handleStatement, SQL_DROP);
		SQLDisconnect(handleConnection);
		SQLFreeConnect(handleConnection);
		SQLFreeEnv(handleEnvironment);
	}
	else {
		returnCode = SQLExecute(handleStatement);
	}
}

void SQLDisconnect() 
{
	SQLFreeStmt(handleStatement, SQL_DROP);
	SQLDisconnect(handleConnection);
	SQLFreeConnect(handleConnection);
	SQLFreeEnv(handleEnvironment);
}

//void ShowSqlError() {
//	SQLWCHAR szSQLSTATE[10];
//	SDWORD nErr;
//	SQLWCHAR msg[SQL_MAX_MESSAGE_LENGTH + 1];
//	SWORD cbmsg;
//
//	while (SQLError(0, 0, handleStatement, szSQLSTATE, &nErr, msg, sizeof(msg), &cbmsg) == SQL_SUCCESS) {
//		sprintf_s((char*)szData, sizeof(szData), "Error:\nSQLSTATE=%s, Native error=%ld, msg='%s'", szSQLSTATE, nErr, msg);
//		MessageBox(NULL, (const wchar_t*)szData, L"ODBC Error", MB_OK);
//	}
//}

int SQLMain(SQLWCHAR Username, SQLWCHAR Password) {
	SQLConnection();
	SQLExecution(Username, Password);
	SQLDisconnect();

	return 1;
}