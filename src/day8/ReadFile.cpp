#include"ReadFile.h"
#include<cstring>

ReadFile::ReadFile(const char *flname)
{
	if(flname==NULL)
	{
		ok=false;
		return;
	}
	filename=flname;
	ok=true;

	inf.open(filename,std::ios::in);

	if(!inf.good()) ok=false;
	if(inf.fail()) ok=false;
}

ReadFile::ReadFile(const std::string &flname) : filename(flname)
{
	ok=true;
	inf.open(filename,std::ios::in);
	if(!inf.good()) ok=false;
	if(inf.fail()) ok=false;
}

ReadFile::~ReadFile()
{
	inf.close();
}

bool ReadFile::isOk()
{
	return ok;
}

bool ReadFile::isEof()
{
	return inf.eof();
}

//returns true if not EOF
bool ReadFile::readLine(std::string &rr)
{
	rr.clear();
	if(!ok) return false;
	if(inf.eof()) return false;
	char ss[5000];
	inf.getline(ss,5000);
	int ii=strlen(ss);
	if(ss[ii-1]=='\n') ss[ii-1]='\0';
	rr=ss;
	return true;
}

void ReadFile::close()
{
	inf.close();
}
