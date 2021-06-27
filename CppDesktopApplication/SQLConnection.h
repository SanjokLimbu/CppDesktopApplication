#pragma once
#define MAX_DATA 100

#include <Windows.h>
#include <sqlext.h>

//unsigned char szData[MAX_DATA]; //Returned data storage
//SDWORD cbData;                  //Output length of data

int SQLMain(SQLVARCHAR, SQLVARCHAR);