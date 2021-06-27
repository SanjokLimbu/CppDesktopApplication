#ifndef UNICODE
#define UNICODE
#endif

#define MYSQLSUCCESS(returnCode) ((returnCode == SQL_SUCCESS) || (returnCode == SQL_SUCCESS_WITH_INFO))
#define MAX_DATA 100

#include "SQLConnection.h"
#include <stdio.h>
#include <iostream>

RETCODE returnCode;       //ODBC return code
SQLHENV handleEnvironment;//Environment handle
SQLHDBC handleConnection; //Connection handle
SQLHSTMT handleStatement; //Statement handle
SQLHDESC handleDescriptor;//Descriptor handle

void SQLDisconnect()
{
	SQLFreeStmt(handleStatement, SQL_DROP);
	SQLDisconnect(handleConnection);
	SQLFreeConnect(handleConnection);
	SQLFreeEnv(handleEnvironment);
}

//Allocate environment handle and connection handle, connect to data source and
void SQLConnection() 
{
	SQLWCHAR dataSourceName[] = L"DSN=SQLCPPTESTNATIVE;UID=sa;PWD=Illidian9", returnConnectionString[1024], text[1024], SQLState[1024];
	SQLINTEGER native;
	SQLSMALLINT i = 0, len;
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

void SQLExecution(SQLVARCHAR _username, SQLVARCHAR _password)
{
	SQLVARCHAR Username = _username, Password = _password;
	SQLWCHAR text[1024], SQLState[1024];
	SQLINTEGER native, cbValue = SQL_NTS;
	SQLSMALLINT i = 0, len;

	SQLWCHAR queryRegisterUser[] = L"{call REGISTER_USER(?,?)}";

	returnCode = SQLPrepare(handleStatement, queryRegisterUser, SQL_NTS);
	if (!MYSQLSUCCESS(returnCode))
	{
		//Deallocate handles and disconnect
		SQLGetDiagRec(SQL_HANDLE_STMT, handleStatement, ++i, SQLState, &native, text - 1, sizeof(text), &len);
		SQLDisconnect();
	}

	returnCode = SQLBindParameter(handleStatement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 30, 0, &Username, sizeof(Username), &cbValue);
	if (!MYSQLSUCCESS(returnCode))
	{
		//Deallocate handles and disconnect
		SQLGetDiagRec(SQL_HANDLE_STMT, handleStatement, ++i, SQLState, &native, text - 1, sizeof(text), &len);
		SQLDisconnect();
	}
	//returnCode = SQLGetStmtAttr(handleStatement, SQL_ATTR_IMP_PARAM_DESC, &handleDescriptor, 0, 0);
	//returnCode = SQLSetDescField(handleDescriptor, 1, SQL_DESC_NAME, "@Username", SQL_NTS);

	returnCode = SQLBindParameter(handleStatement, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 30, 0, &Password, sizeof(Password), &cbValue);
	if (!MYSQLSUCCESS(returnCode))
	{
		//Deallocate handles and disconnect
		SQLGetDiagRec(SQL_HANDLE_STMT, handleStatement, ++i, SQLState, &native, text - 1, sizeof(text), &len);
		SQLDisconnect();
	}
	returnCode = SQLExecute(handleStatement);
	if (!MYSQLSUCCESS(returnCode))
	{
		//Deallocate handles and disconnect
		SQLGetDiagRec(SQL_HANDLE_STMT, handleStatement, ++i, SQLState, &native, text - 1, sizeof(text), &len);
		SQLDisconnect();
	}
}

int SQLMain(SQLVARCHAR Username, SQLVARCHAR Password)
{
	SQLConnection();
	SQLExecution(Username, Password);
	SQLDisconnect();
	MessageBox(NULL, L"Please close the message box and Login to continue.", L"Registration Successful", MB_OK);
	return 0;
}