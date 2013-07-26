#pragma once
#ifndef XML_DEF_GUARD
#define XML_DEF_GUARD
#include <stdio.h>
#include "tinyxml2.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>


using namespace tinyxml2;
using namespace std;

int myrun(std::string prog);

struct iocdet
{
	const char* name;
	const char* app;
	const char* st;
	const char* port;
	const char* logfile;
};

void cfg_parse ();

#endif