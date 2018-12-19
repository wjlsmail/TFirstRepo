
/*
g++ p2.cpp -I./../tso1/ -L./../tso1/ -ltso1 -lpthread -o ../bin/p2

or: (when libtso1.so in ../bin/.)
g++ p2.cpp -I./../tso1/ -L./../bin/  -ltso1 -lpthread -o ../bin/p2

to run ./bin/p2, do export LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH} first.

 */


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "tso1.h"
#include "tso2.h"

using namespace std;
extern int g_iTestTSo1;
extern int g_iTestTSo2;

void* func_thd_onlyrd_so1(void* data)
{
//    cout << "[pthread_self_id=" << pthread_self() << "]" << endl;
//    cout << "[SYS_gettid  _id=" << syscall(SYS_gettid) << "]" << endl;
//    cout << "[getpid      _id=" << getpid() << "]" << endl;

    while(true)
    {
        cout << "[p2][Get]g_iTestTSo1=[" << g_iTestTSo1 << "]" << endl;
        cout << "[p2][func_thd_onlyrd_so1][funcSo1_GetGlobalValue]=[" << funcSo1_GetGlobalValue() << "]" << endl;
        cout << "-----------------------------------------------------------" << endl;
        usleep(200000);
    }

    return NULL;
}

////////////////////////////////////////////////////////////////
void* func_thdCTSo1RD(void* data)
{
    CTSO1 tso1_thd_RD("tso1_thd_RD");
    while(true)
    {
        cout << "[p2][Call][CTSO1.GetTestValue]=[" << tso1_thd_RD.GetTestValue() << "]" << endl << endl;
        usleep(200000); // 200ms
    }

    return NULL;
}

/////////////////////////////////////////
/// \brief func_thdTSo1Vecstr
/// \param data
/// \return
///
void ShowVecStr(vector<string> vecstrlist)
{
    if (vecstrlist.empty())
    {
        cout << "[p2][ShowVecStr] vecstrlist is empty!" << endl;
        return;
    }

    cout << "[p2][ShowVecStr][vecstrlist.size]=[" << vecstrlist.size() << "]" << endl;
    vector<string>::iterator itor = vecstrlist.begin();
    for (itor = vecstrlist.begin(); itor != vecstrlist.end(); itor++)
    {
        cout << "[p2][ShowVecStr][(*itor)]=[" << (*itor) << "]" << endl;
    }
    cout << "[p2][ShowVecStr][vecstrlist.size]=[" << vecstrlist.size() << "]" << endl;

    return;
}

void TestCTSO1()
{
    pthread_t thdSo1RD;
    pthread_create(&thdSo1RD, NULL, &func_thdCTSo1RD, NULL);

    CTSO1 tso1("p2-tso1");
    CTSO1 tso2("p2-tso2");

    cout << "[p2][Call][CTSO1.GetValue]=[" << tso2.GetTestValue() << "]" << endl;
    //--------------------------------------------------------------------------------------


    usleep(30000000); // wait for p2 write 30s then get vecstr
    vector<string> vecstrlist = {};
    CTSO1::GetFileList(vecstrlist);
    ShowVecStr(vecstrlist);

    return;
}

void func_so1()
{
    pthread_t thd1;
    pthread_create(&thd1, NULL, &func_thd_onlyrd_so1, NULL);

    cout << "---------------------------------------------------------------" << endl;

    TestCTSO1();
    cout << "---------------------------------------------------------------" << endl;

    return;
}

////////////////////////////////////////////////////////////////
void* func_thd_onlyrd_so2(void* data)
{
//    cout << "[pthread_self_id=" << pthread_self() << "]" << endl;
//    cout << "[SYS_gettid  _id=" << syscall(SYS_gettid) << "]" << endl;
//    cout << "[getpid      _id=" << getpid() << "]" << endl;

    while(true)
    {
        cout << "[p2][Get]g_iTestTSo2=[" << g_iTestTSo2 << "]" << endl;
        cout << "[p2][func_thd_onlyrd_so2][funcSo2_GetSo2Value]=[" << funcSo2_GetSo2Value() << "]" << endl;
        cout << "[p2][func_thd_onlyrd_so2][funcSo2_GetSo1Value]=[" << funcSo2_GetSo1Value() << "]" << endl;
        cout << "-----------------------------------------------------------" << endl;
        usleep(200000);
    }

    return NULL;
}

void* func_thdCTSo2RD(void* data)
{
    CTSO2 tso2_thd_RD;
    while(true)
    {
        cout << "[p2][Call][CTSO2.GetValue]=[" << tso2_thd_RD.GetValue() << "]" << endl << endl;
        usleep(200000); // 200ms
    }

    return NULL;
}

void TestCTSO2()
{
    pthread_t thdSo2RD;
    pthread_create(&thdSo2RD, NULL, &func_thdCTSo2RD, NULL);

    return;
}

void func_so2()
{
    pthread_t thdRSo2;
    pthread_create(&thdRSo2, NULL, &func_thd_onlyrd_so2, NULL);

    cout << "---------------------------------------------------------------" << endl;

    TestCTSO2();
    cout << "---------------------------------------------------------------" << endl;

    return;

}

////////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{

//    cout << "[main][pthread_self_id=" << pthread_self() << "]" << endl;
//    cout << "[main][SYS_gettid  _id=" << syscall(SYS_gettid) << "]" << endl;
//    cout << "[main][getpid      _id=" << getpid() << "]" << endl;
//    cout << "---------------------------------------------------------------" << endl;

    func_so1();
    func_so2();

    while(true)
    {
        usleep(10000000);
    }

    return 0;
}

