#include "ReadXMLFile.h"

static char* xml_file_name = 0;

using namespace cocos2d;

/**
 * implements of ReadXMLFile
 */

string ReadXMLFile::m_sFilePath = string("");


ReadXMLFile::~ReadXMLFile()
{
}

//-------------------------------------------------------------------------------------------------------
// 初始化檔案
TiXmlDocument ReadXMLFile::initXMLFile(const char* fileName)
{
	TiXmlDocument doc;
	unsigned long uSize = 0;
	
	const char * tempFileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(fileName,"");
	unsigned char* pFileData =
	CCFileUtils::sharedFileUtils()->getFileData(tempFileName, "rb", &uSize);
	
	if( NULL == pFileData){
		//CCLOG("open file [%s] failed",path.c_str());
		return NULL;
	}
	// 直接傳入buff
	doc.Parse((char*)pFileData);

	return  doc;
}


void ReadXMLFile::readData(string FileName)
{

}
