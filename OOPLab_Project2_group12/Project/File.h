#pragma once
#include<fstream>
#include<string>

class File
{
public:
	File();
	~File();
	static bool readFile(std::string pos);
	static bool writeFile(std::string pos);

private:
	static std::wfstream f;
};

