#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//////////////////////////////////////////////////////////////////////
string Int2StlString(int iValue);
int StlString2Int(const string & str);

//////////////////////////////////////////////////////////////////////
void funcSo1_SetGlobalValue(int iValue);
int funcSo1_GetGlobalValue();

//////////////////////////////////////////////////////////////////////
class CTSO1
{
public:
    CTSO1(const string & strObjName);
    ~CTSO1();

    int GetTestValue();
    void SetTestValue(int iValue);
    static void PushCatchFile(const string & str);
    static void GetFileList(vector<string> & vecstrlist);

    void ClearVecstr();

private:
    void AddtoList(const string & str);

    string m_strObjName;
    static int m_iValue;
    static vector<string> m_vecstrlist;

};

