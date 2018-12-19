#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//////////////////////////////////////////////////////////////////////
void funcSo2_SetSo2Value(int iValue);
int funcSo2_GetSo2Value();
void funcSo2_SetSo1Value(int iValue);
int funcSo2_GetSo1Value();

//////////////////////////////////////////////////////////////////////
class CTSO2
{
public:
    CTSO2();
    ~CTSO2();

    int GetValue();
    void SetValue(int iValue);

private:
    static int m_iValue;

};

