
/*
g++ p1.cpp -I./../tso1/ -L./../tso1/ -ltso1 -lpthread -o ../bin/p1

or: (when libtso1.so in ../bin/.)
g++ p1.cpp -I./../tso1/ -L./../bin/  -ltso1 -lpthread -o ../bin/p1

to run ./bin/p1, do:
    export LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH}
first.

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
extern int g_iTestTSo1;     // in so1
extern int g_iTestTSo2;     // in so2

void* func_thdSo1WRglobal(void* data)
{
//    cout << "[pthread_self_id=" << pthread_self() << "]" << endl;
//    cout << "[SYS_gettid  _id=" << syscall(SYS_gettid) << "]" << endl;
//    cout << "[getpid      _id=" << getpid() << "]" << endl;
//    cout << "////////////////////////////////////////////////////////////////" << endl;

    while(true)
    {
        g_iTestTSo1++;
        cout << "[p1][Set]g_iTestTSo1=[" << g_iTestTSo1 << "]" << endl;
        funcSo1_SetGlobalValue(g_iTestTSo1++);
        cout << "[p1][funcSo1_GetGlobalValue]=[" << funcSo1_GetGlobalValue() << "]" << endl;
        usleep(1000000);
    }

    return NULL;
}

////////////////////////////////////////////////////////////////
///
void* func_thdCTSo1WR(void* data)
{
    static int iTestCTSo1 = 0;
    CTSO1 tso1_thd_WR("tso1_thd_WR");
    while(true)
    {
        iTestCTSo1++;
        tso1_thd_WR.SetTestValue(iTestCTSo1);

        cout << "[p1][CTSO1::SetTestValue]=[" << iTestCTSo1 << "]" << endl << endl;
        usleep(200000); // 200ms
    }

    return NULL;
}

void* func_thdCTSo1RD(void* data)
{
    CTSO1 tso1_thd_RD("tso1_thd_RD");
    while(true)
    {
        cout << "[p1][CTSO1.GetTestValue]=[" << tso1_thd_RD.GetTestValue() << "]" << endl << endl;
        usleep(1000000); // 1000ms
    }

    return NULL;
}

/////////////////////////////////////////
///
bool g_bPush =false;
void* func_thdTSo1VecstrRW(void* data)
{
    int i = 0;
    while (true)
    {
        usleep(10000); // 10ms

        if (!g_bPush)
        {
            cout << "[p1][func_thdTSo1VecstrRW] g_bPush is false, not push vecstr!" << endl << endl;
            continue;
        }

        i++;
        string str("");
        str = "CTSO1----ObjNamed----" + Int2StlString(i);
        CTSO1::PushCatchFile(str);
        cout << "[p1][func_thdTSo1VecstrRW][CTSO1::PushCatchFile]=[" << str << "]" << endl << endl;
    }

    return NULL;
}

void ShowVecStr(vector<string> vecstrlist)
{
    if (vecstrlist.empty())
    {
        cout << "[p1][ShowVecStr] vecstrlist is empty!" << endl;
        return;
    }

    cout << "[p1][ShowVecStr][vecstrlist.size]=[" << vecstrlist.size() << "]" << endl;
    vector<string>::iterator itor = vecstrlist.begin();
    for (itor = vecstrlist.begin(); itor != vecstrlist.end(); itor++)
    {
        cout << "[p1][ShowVecStr][(*itor)]=[" << (*itor) << "]" << endl;
    }
    cout << "[p1][ShowVecStr][vecstrlist.size]=[" << vecstrlist.size() << "]" << endl;

    return;
}

void TestCTSO1()
{
    //--------------------------------------------------------------------------------------
    // static int
    //
    pthread_t thdWR;
    pthread_create(&thdWR, NULL, &func_thdCTSo1WR, NULL);
    pthread_t thdRD;
    pthread_create(&thdRD, NULL, &func_thdCTSo1RD, NULL);

    CTSO1 tso1("tso1");
    CTSO1 tso2("tso2");

    tso1.SetTestValue(1000);
    cout << "[p1][tso1.SetTestValue(1000)][tso2.GetTestValue()]=[" << tso2.GetTestValue() << "]" << endl;

    //--------------------------------------------------------------------------------------
    // static vector<string>
    //

    // write
    g_bPush = true;
    pthread_t thdCTSo1VecstrRW;
    pthread_create(&thdCTSo1VecstrRW, NULL, &func_thdTSo1VecstrRW, NULL);

    // read
    usleep(20000000); // wait for 20s then get vecstr
    vector<string> vecstrlist = {};
    CTSO1::GetFileList(vecstrlist);
    ShowVecStr(vecstrlist);

    // clear and read
    g_bPush = false;
    CTSO1 tso1_cleanvec("tso1_cleanvec");
    tso1_cleanvec.ClearVecstr();
    vecstrlist.clear();
    CTSO1::GetFileList(vecstrlist);
    ShowVecStr(vecstrlist);

    // re write
    usleep(2000000); // wait for 2s for restart push_back vecstr
    g_bPush = true;

    return;
}

///////////////////////////////////
void func_so1()
{
    pthread_t thd1so1;
    pthread_create(&thd1so1, NULL, &func_thdSo1WRglobal, NULL);
    //pthread_t thd2so1;
    //pthread_create(&thd2so1, NULL, &func_thdSo1WRglobal, NULL);
    cout << "---------------------------------------------------------------" << endl;

    TestCTSO1();
    cout << "---------------------------------------------------------------" << endl;

    return;
}

////////////////////////////////////////////////////////////////
/// \brief func_so2
///

void* func_thdSo2WRglobal(void* data)
{
//    cout << "[pthread_self_id=" << pthread_self() << "]" << endl;
//    cout << "[SYS_gettid  _id=" << syscall(SYS_gettid) << "]" << endl;
//    cout << "[getpid      _id=" << getpid() << "]" << endl;
//    cout << "////////////////////////////////////////////////////////////////" << endl;

    while(true)
    {
        g_iTestTSo2++;
        cout << "[p1][Set]g_iTestTSo2=[" << g_iTestTSo2 << "]" << endl;
        funcSo2_SetSo2Value(g_iTestTSo2++);
        cout << "[p1][Call][funcSo2_GetSo2Value]=[" << funcSo2_GetSo2Value() << "]" << endl;
        cout << "-----------------------------------------------------------" << endl << endl;
        usleep(1000000);
    }

    return NULL;
}

void* func_thd2so2_gSo1(void* data)
{
//    cout << "[pthread_self_id=" << pthread_self() << "]" << endl;
//    cout << "[SYS_gettid  _id=" << syscall(SYS_gettid) << "]" << endl;
//    cout << "[getpid      _id=" << getpid() << "]" << endl;
//    cout << "////////////////////////////////////////////////////////////////" << endl;

    while(true)
    {
        funcSo2_SetSo1Value(g_iTestTSo1 + g_iTestTSo2);
        cout << "[p1][funcSo2_SetSo1Value, then funcSo2_GetSo1Value]=[" << funcSo2_GetSo1Value() << "]" << endl;
        cout << "[p1][func_thd2so2_gSo1->g_iTestTSo1]=[" << g_iTestTSo1 << "]" << endl;
        usleep(10000000); // 10s
    }

    return NULL;
}

void* func_thdCTSo2WR(void* data)
{
    static int iTestCTSo1 = 0;
    CTSO2 tso2_thd_WR;
    while(true)
    {
        iTestCTSo1++;
        tso2_thd_WR.SetValue(iTestCTSo1);
        cout << "[p1][func_thdCTSo2WR][GetValue]=[" << tso2_thd_WR.GetValue() << "]" << endl << endl;
        usleep(200000); // 200ms
    }

    return NULL;
}

void TestCTSO2()
{
    //--------------------------------------------------------------------------------------
    // static int
    //
    pthread_t thdCTSo2WR;
    pthread_create(&thdCTSo2WR, NULL, &func_thdCTSo2WR, NULL);

    return;
}

void func_so2()
{
    pthread_t thd1so2;
    pthread_create(&thd1so2, NULL, &func_thdSo2WRglobal, NULL);

    pthread_t thd2so2_gSo1;
    pthread_create(&thd2so2_gSo1, NULL, &func_thd2so2_gSo1, NULL);
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
    cout << "************************************************************************" << endl;
    func_so2();

    while(true)
    {
        usleep(10000000);
    }

    return 0;
}

