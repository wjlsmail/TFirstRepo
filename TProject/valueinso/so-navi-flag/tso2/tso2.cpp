
/*
g++ tso1.cpp -fPIC -shared -o ../bin/libtso1.so

or:

g++ -c -fPIC -shared tso1.cpp
g++ tso1.o -fPIC -shared -o ../bin/libtso1.so

 */

#include "tso2.h"

using namespace std;

int g_iTestTSo2 = 0;
extern int g_iTestTSo1;  // g_iTestTSo1 in so1

//////////////////////////////////////////////////////////////////////
void funcSo2_SetSo2Value(int iValue)
{
    g_iTestTSo2 = iValue;
    return;
}

int funcSo2_GetSo2Value()
{
    return g_iTestTSo2;
}

void funcSo2_SetSo1Value(int iValue)
{
    g_iTestTSo1 = iValue;
    return;
}

int funcSo2_GetSo1Value()
{
    return g_iTestTSo1;
}

//////////////////////////////////////////////////////////////////////
/// \brief CTSO2::CTSO2
/// \param strObjName
///
///

int CTSO2::m_iValue = 0;

CTSO2::CTSO2()
{
}

CTSO2::~CTSO2()
{
}

int CTSO2::GetValue()
{
    cout << "*********[tso2.CTSO2][GetValue][m_iValue]=[" << m_iValue << "]" << endl;
    return m_iValue;
}

void CTSO2::SetValue(int iValue)
{
    m_iValue = iValue;
    cout << "*********[tso2.CTSO2][SetValue][m_iValue]=[" << m_iValue << "]" << endl;
    return;
}
