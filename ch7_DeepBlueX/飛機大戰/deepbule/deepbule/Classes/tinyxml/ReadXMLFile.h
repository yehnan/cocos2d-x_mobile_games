#ifndef _READ_XML_FILE_H_
#define _READ_XML_FILE_H_

#include "cocos2d.h"
#include "tinyxml.h"

using namespace std;
using namespace cocos2d;

class ReadXMLFile
{
public:
	~ReadXMLFile();

	static TiXmlDocument initXMLFile(const char* fileName);
	void readData(string FileName);

private:
	ReadXMLFile() {}
	static std::string m_sFilePath;
	TiXmlDocument doc;
};

#endif
