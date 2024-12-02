#pragma once

#include<string>
#include<vector>

class StrUtils
{
public:
	static std::string toString(int);
	static std::string toString(unsigned int);
	static std::string toString(long);
	static std::string toString(unsigned long);
	static std::string toString(unsigned long long);
	static std::string toString(float);
	static std::string toString(double);
	static std::string toString(char);

	static void replaceAll(std::string &str, const std::string &from, const std::string &to);
	static void tokenize(const std::string &str, const std::string &delims, std::vector<std::string> &output, bool returnDelims=false);

	static bool startsWith(const std::string &inp, const std::string &start);
	static bool endsWith(const std::string &inp, const std::string &end);
	static bool equalsIgnoreCase(const std::string &, const std::string &);
	static std::string toUpperCase(const std::string &);
	static std::string toLowerCase(const std::string &);
	static std::string trim(const std::string &);
	static std::string ltrim(const std::string &);
	static std::string rtrim(const std::string &);
	static int indexOf(const std::string &inp, const std::string &fnd);
	static bool isSpace(unsigned char c);
};
