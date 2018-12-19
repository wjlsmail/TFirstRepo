/*
g++ GetRemoteDBFileCurl.cpp -I/home/vagrant/work/external/curl/include -I/home/vagrant/work/external/boost/include -L/home/vagrant/work/external/curl/lib -L/home/vagrant/work/external/boost/lib.linux_x64 -lcurl -lboost_filesystem -o GetRemoteDBFileCurl

  */


#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include <curl/curl.h>

using namespace std;

string& trim_path(string &s)
{
    if (s.empty())
    {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

size_t WriteFileFunc(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  return fwrite(ptr, size, nmemb, stream);
}

int GetRemoteDBFile(const char * pcFullName)
{
    int iRet = 1;

    string strFullName = string(pcFullName);
    strFullName = trim_path(strFullName);
    cout << "strFullName=[" << strFullName << "]" << endl;
    int iPos = strFullName.find("/opt/mapdata/");
    cout << "iPos=" << iPos << endl;
    if (iPos != 0)
    {
        cout << "Not match db file" << endl;
        return iRet;
    }

    cout << "-----------------------------------" << endl;
    boost::filesystem::path filename(strFullName);
    boost::filesystem::path parentpath = filename.parent_path();

    if (!(boost::filesystem::exists(parentpath) && boost::filesystem::is_directory(parentpath)))
    {
        printf("mkdir\n");
        string strMkpath("");
        strMkpath = string("mkdir -p ") + parentpath.string();
        system(strMkpath.c_str());
    }

    string strRoot("http://10.10.87.47:8170");
    string strFileName = strRoot + strFullName;

    cout << "strFullName:" << strFullName << endl;
    cout << "strFileName:" << strFileName << endl;
    cout << "-----------------------------------" << endl;

    CURL *curl_handle = NULL;
    CURLcode res_perform;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    if(!curl_handle)
    {
        return iRet;
    }

    FILE *fpWrite = fopen(strFullName.c_str(), "wb");
    if (!fpWrite)
    {
        return iRet;
    }

    curl_easy_setopt(curl_handle, CURLOPT_URL,   strFileName.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteFileFunc);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, fpWrite);

    res_perform = curl_easy_perform(curl_handle);
    if(res_perform != CURLE_OK)
    {
        return iRet;
    }

    fclose(fpWrite);
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();

    return 0;
}

int main(int argc, char * args[])
{
    GetRemoteDBFile("[");
    GetRemoteDBFile("/aopt/mapdata/MBA_Plus/MAP/Level00/1st5339/2nd0406/MP4211123000.mba");
    GetRemoteDBFile("/opt/mapdata/MBA_Plus/MAP/Level00/1st5339/2nd0406/MP4211123000.mba");
    
    return 0;
}


