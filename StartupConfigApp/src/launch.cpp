#pragma comment(lib, "SHELL32.LIB")
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <ShlObj.h>
#include <Shlwapi.h>
#include <objbase.h>
#include "XMLParse.h"

using namespace std;

int myrun (std::string prog)
{
	LPCSTR azCmd;
	LPCSTR a,b;
	string buildstr,prestr;
	prestr = "/s /k C:\\EPICS\\config_env.bat && ";
	buildstr = prestr.c_str();
	buildstr += prog.c_str();
	azCmd = (LPCSTR)buildstr.c_str();
	a = "open";
	b = "cmd";
	ShellExecute( NULL, a, b, azCmd, NULL, SW_HIDE );

	return 0;

}