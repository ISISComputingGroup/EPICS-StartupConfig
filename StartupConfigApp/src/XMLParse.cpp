#include <string>
#include "XMLParse.h"
#include <fstream>


void main()
{
	cfg_parse ();
}

void cfg_parse()
{
	//load the config file
	tinyxml2::XMLDocument doc;
	doc.LoadFile("C:/EPICS/ISIS/StartupConfig/StartupConfigApp/src/ProtoConfig.xml");
	
	//Set things up ready to build the st.cmd file
	std::ifstream tempstf("C:/EPICS/ISIS/StartupConfig/StartupConfigApp/src/templatest.cmd");
	std::string  tempst( (std::istreambuf_iterator<char>(tempstf)),(std::istreambuf_iterator<char>()));
	std::string newst, head, ports, recs, middle, seqs, remainder;
	size_t split1, split2, split3;
	split1 = tempst.find("REP1");
	head = tempst.substr(0,split1);
	remainder = tempst.substr(split1+5);
	split2 = remainder.find("REP2");
	recs = remainder.substr(0,split2);
	remainder = remainder.substr(split2+5);
	split3 = remainder.find("REP3");
	middle = remainder.substr(0,split3);
	seqs = remainder.substr(split3+5);

	//Get the config name - likely to be removed in the future?
	tinyxml2::XMLElement* element = doc.FirstChildElement("config")->FirstChildElement("cfgname");
	const char* cfgname = element->GetText();
	
	//get ready to start some real work
	vector<iocdet> iocs;
	iocs.clear();
	iocdet currioc;

	//Loop through the config file and get the ioc data - this is very likely to be altered in time
	for (const tinyxml2::XMLNode* node=doc.FirstChildElement()->FirstChildElement("IOCs")->FirstChildElement(); node; node=node->NextSiblingElement())
	{
		const char* iocname = node->FirstChildElement("iocname")->GetText();
		currioc.name=iocname;
		const char* iocapp = node->FirstChildElement("apppath")->GetText();
		currioc.app = iocapp;
		const char* iocst = node->FirstChildElement("stpath")->GetText();
		currioc.st = iocst;
		const char* iocport= node->FirstChildElement("port")->GetText();
		currioc.port = iocport;
		const char* ioclogfile= node->FirstChildElement("logfile")->GetText();
		currioc.logfile = ioclogfile;
		iocs.push_back(currioc);
	}

	//For each IOC in the config file (once it's in a more useful structure)
	for (size_t i=0; i < iocs.size(); i++)
	{
		currioc = iocs[i];
		
		//create the command to run the IOC via procserv
		ostringstream ioccmd;
		ioccmd << "cd " << currioc.st << " && C:\\EPICS\\support\\procserver\\procServ.exe -e " << currioc.app << " --allow --noautorestart -n " << currioc.name << " -L " << currioc.logfile 
			<< " " << currioc.port << " ./st.cmd && exit";
		
		//some string manipulation to make it all work - this can probably be refactored!
		string wantpath;
		wantpath = ioccmd.str();
		string torun;
		torun.assign(wantpath.begin(),wantpath.end());
		myrun(torun);
		
		//generate the entries for the st.cmd file, again this can probably be refactored
		string port, rec, seq, seqrec;
		port = "drvAsynIPPortConfigure(\"";
		port += currioc.name;
		port += "\", \"localhost:";
		port += currioc.port;
		port += "\", 100, 0, 0)\n";
		seqrec = "\"P=$(MYPVPREFIX)";
		seqrec += currioc.name;
		seqrec += ", PORT=";
		seqrec += currioc.name;
		seqrec += "\")\n";
		rec = "dbLoadRecords(\"db/isis_example.db\", ";
		rec += seqrec;
		seq = "seq(procServControl,";
		seq += seqrec;
		
		//Add each entry to the lists
		ports += port;
		recs += rec;
		seqs += seq;
	}

	//Build the new st.cmd file and write it a file
	ofstream stfile;
	newst = head + ports + recs + middle + seqs;
	//A local st.cmd file for use with testing
	//stfile.open("st.cmd");
	//Path to a st.cmd file for loading these with the isis_example IOC for procserv
	stfile.open("C:/EPICS/support/procServControl/1-2/iocs/isis_example/iocBoot/iocisis_example/st.cmd");
	stfile << newst << endl;
	stfile.close();
}


