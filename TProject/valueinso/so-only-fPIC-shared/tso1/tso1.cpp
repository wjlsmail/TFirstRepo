
/*
g++ tso1.cpp -fPIC -shared -o ../bin/libtso1.so

or:

g++ -c -fPIC -shared tso1.cpp
g++ tso1.o -fPIC -shared -o ../bin/libtso1.so

 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "tso1.h"

using namespace std;

int g_iTestTSo1 = 0;

//////////////////////////////////////////////////////////////////////
string Int2StlString(int iValue)
{
    stringstream ss;
    ss << iValue;
    string str("");
    ss >> str;
    return str;
}

int StlString2Int(const string & str)
{
    stringstream ss;
    ss << str;
    int iRet = -1;
    ss >> iRet;
    return iRet;
}

//////////////////////////////////////////////////////////////////////
void funcSo1_SetGlobalValue(int iValue)
{
    g_iTestTSo1 = iValue;
    cout << "----[tso1.global][funcSo1_SetGlobalValue][g_iTestTSo1]=[" << g_iTestTSo1 << "]" << endl;

    return;
}

int funcSo1_GetGlobalValue()
{
    cout << "----[tso1.global][funcSo1_GetGlobalValue][g_iTestTSo1]=[" << g_iTestTSo1 << "]" << endl;
    return g_iTestTSo1;
}

//////////////////////////////////////////////////////////////////////
/// \brief CTSO1::CTSO1
/// \param strObjName
///
///

int CTSO1::m_iValue = 0;
vector<string> CTSO1::m_vecstrlist = {};

CTSO1::CTSO1(const string & strObjName)
    :m_strObjName(strObjName)
{
    AddtoList(m_strObjName);
    cout << "----[tso1.CTSO1][Constructor] with [" << m_strObjName << "]" << endl;
}

CTSO1::~CTSO1()
{
    cout << "----[tso1.CTSO1][Destructor] destory [" << m_strObjName << "]" << endl;
    m_strObjName = "";
}

int CTSO1::GetTestValue()
{
    cout << "----[tso1.CTSO1][Obj=" << m_strObjName << "]" << "[CTSO1::GetTestValue][m_iValue]=[" << m_iValue << "]" << endl;
    return m_iValue;
}

void CTSO1::SetTestValue(int iValue)
{
    m_iValue = iValue;
    cout << "----[tso1.CTSO1][Obj=" << m_strObjName << "]" << "[CTSO1::SetTestValue][m_iValue]=[" << m_iValue << "]" << endl;
}

void CTSO1::PushCatchFile(const string & str)
{
    m_vecstrlist.push_back(str);
    cout << "----[tso1.CTSO1][PushCatchFile][str]=[" << str << "]" << endl;
    return;
}

void CTSO1::GetFileList(vector<string> & vecstrlist)
{
    if (m_vecstrlist.empty())
    {
        cout << "----[tso1.CTSO1][GetFileList] m_vecstrlist is empty!" << endl;
        return;
    }

    vecstrlist.clear();
    cout << "----[tso1.CTSO1][GetFileList][m_vecstrlist.size]=[" << m_vecstrlist.size() << "]" << endl;
    cout << "----[tso1.CTSO1][GetFileList][vecstrlist.size]=[" << vecstrlist.size() << "]" << endl;
    vector<string>::iterator itor = m_vecstrlist.begin();
    for (itor = m_vecstrlist.begin(); itor != m_vecstrlist.end(); itor++)
    {
        vecstrlist.push_back((*itor));
        cout << "----[tso1.CTSO1][GetFileList][(*itor)]=[" << (*itor) << "]" << endl;
//        m_vecstrlist.erase(itor);
//        itor--;
    }
    cout << "----[tso1.CTSO1][GetFileList][vecstrlist.size]=[" << vecstrlist.size() << "]" << endl;

    return;
}

void CTSO1::AddtoList(const string & str)
{
    m_vecstrlist.push_back(str);
    cout << "----[tso1.CTSO1][Obj=" << m_strObjName << "]" << "[CTSO1::AddtoList][str]=[" << str << "]" << endl;
}

void CTSO1::ClearVecstr()
{
    m_vecstrlist.clear();
    cout << "----[tso1.CTSO1][Obj=" << m_strObjName << "]" << "[CTSO1::CleanVecstr][m_vecstrlist.size]=[" << m_vecstrlist.size() << "]" << endl;
}

