/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2018, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * Download a given URL into a local file named page.out.
 * </DESC>
 
g++ u2.cpp -I/home/vagrant/work/external/curl/include -L/home/vagrant/work/external/curl/lib -lcurl -o u2

 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

int main(int argc, char *argv[])
{
    CURL *curl_handle;
    char * pcURL = "http://10.10.87.47:8170/MBA_Plus/______MsdfAP/Level00/1st5339/2nd0406/MP4211123000.mba";
    char * pagefilename = "page.out";

    curl_global_init(CURL_GLOBAL_ALL);

    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, pcURL);

    /* Switch on full protocol/debug output while testing */
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);

    /* disable progress meter, set to 0L to enable and disable debug output */
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);


    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

    FILE * pagefile = fopen(pagefilename, "wb");
    CURLcode res_perform;
    if(pagefile)
    {

        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
        res_perform = curl_easy_perform(curl_handle);
        fclose(pagefile);
    }

    if(!res_perform)
    {
        struct curl_certinfo *certinfo;
        res_perform = curl_easy_getinfo(curl_handle, CURLINFO_CERTINFO, &certinfo);
        if(!res_perform && certinfo)
        {
            int i;
            int iCerts = certinfo->num_of_certs;
            printf("%d certs!\n", iCerts);
            for(i = 0; i < iCerts; i++)
            {
                struct curl_slist *slist;
                for(slist = certinfo->certinfo[i]; slist; slist = slist->next)
                    printf("%s\n", slist->data);
            }
        }
    }	
	
    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);

    curl_global_cleanup();

    return 0;
}
