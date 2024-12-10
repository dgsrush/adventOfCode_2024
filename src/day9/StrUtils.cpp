#include"StrUtils.h"
#include<algorithm>
#include<cstdio>
#include<io.h>
#include<iostream>
#include<sys/stat.h>
#include<dirent.h>
#include<functional>

std::string StrUtils::toString(int i)
{
	char buf[100];
	snprintf(buf, 100, "%d", i);
	std::string ss(buf);
	return ss;
}

std::string StrUtils::toString(unsigned int i)
{
	char buf[100];
	snprintf(buf, 100, "%d", i);
	std::string ss(buf);
	return ss;
}

std::string StrUtils::toString(long lng)
{
	char buf[100];
	snprintf(buf, 100, "%ld", lng);
	std::string ss(buf);
	return ss;
}

std::string StrUtils::toString(unsigned long lng)
{
	char buf[100];
	snprintf(buf, 100, "%ld", lng);
	std::string ss(buf);
	return ss;
}

std::string StrUtils::toString(unsigned long long lng)
{
	char buf[100];
	snprintf(buf, 100, "%ld", lng);
	std::string ss(buf);
	return ss;
}

std::string StrUtils::toString(float f)
{
	char buf[100];
	snprintf(buf, 100, "%.2f", f);
	std::string ss(buf);
	return ss;
}

std::string StrUtils::toString(double d)
{
	char buf[100];
	snprintf(buf, 100, "%.2f", d);
	std::string ss(buf);
	return ss;
}

std::string StrUtils::toString(char c)
{
	char buf[2];
	buf[0] = c;
	buf[1] = 0;
	std::string ss(buf);
	return ss;
}

//////////////////////////////////////////////////

void StrUtils::replaceAll(std::string &sstr, const std::string &from, const std::string &to)
{
	if(from.empty()) return;
	std::string wsRet;
	wsRet.reserve(sstr.length());
	size_t start_pos = 0, pos;
	while((pos = sstr.find(from, start_pos)) != std::string::npos)
	{
		wsRet += sstr.substr(start_pos, pos - start_pos);
		wsRet += to;
		pos += from.length();
		start_pos = pos;
	}
	wsRet += sstr.substr(start_pos);
	sstr.swap(wsRet);
}

//////////////////////////////////////////////////

void StrUtils::tokenize(const std::string &str, const std::string &delims, std::vector<std::string> &ll, bool returnDelims)
{
	ll.clear();
	std::string tok("");
	int len = str.length();
	for(int i = 0; i < len; i++)
	{
		std::string chr = toString(str[i]);
		if(delims.find(chr) != std::string::npos)
		{
			if(tok.length() > 0)
			{
				ll.push_back(tok);
				tok = "";
			}
			if(returnDelims)
				ll.push_back(chr);
		}
		else
			tok += chr;
	}
	if(tok.length() > 0)
		ll.push_back(tok);
}

//////////////////////////////////////////////////

bool StrUtils::startsWith(const std::string &inp, const std::string &start)
{
	if(inp.find(start) == 0) return true;
	return false;
}

bool StrUtils::endsWith(const std::string &inp, const std::string &end)
{
	int pos = inp.length() - end.length();
	if(pos < 0) return false;
	int fnd = inp.rfind(end);
	if(fnd == pos) return true;
	return false;
}

std::string StrUtils::toUpperCase(const std::string &inp)
{
	std::string ss(inp);
	std::transform(ss.begin(), ss.end(), ss.begin(), ::toupper);
	return ss;
}

std::string StrUtils::toLowerCase(const std::string &inp)
{
	std::string ss(inp);
	std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
	return ss;
}

bool StrUtils::equalsIgnoreCase(const std::string &s1, const std::string &s2)
{
	std::string ss1(s1);
	std::string ss2(s2);
	ss1 = toLowerCase(ss1);
	ss2 = toLowerCase(ss2);
	return ss1 == ss2;
}

std::string StrUtils::trim(const std::string &s)
{
	return ltrim(rtrim(s));
}

std::string StrUtils::ltrim(const std::string &ss)
{
	std::string s(ss);
	std::function<bool(unsigned char c)> is = StrUtils::isSpace;
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not_fn(is)));
	return s;
}

std::string StrUtils::rtrim(const std::string &ss)
{
	std::string s(ss);
	std::function<bool(unsigned char c)> is = StrUtils::isSpace;
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not_fn(is)).base(), s.end());
	return s;
}

int StrUtils::indexOf(const std::string &inp, const std::string &fnd)
{
	return inp.find(fnd);
}

bool StrUtils::isSpace(unsigned char c)
{
	if(c == ' ') return true;
	return false;
}
