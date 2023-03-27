//
// Created by paique on 27/03/23.
//

#include <stdio.h>
#include <curl/curl.h>

#ifndef FABRIC_INSTALLER_DOWNLOADER_H
#define FABRIC_INSTALLER_DOWNLOADER_H

void downloader(char* url) {

    CURL *curl;
    FILE *fp;
    char outfilename[FILENAME_MAX] = "server.jar";
    curl = curl_easy_init();

    if (curl) {
        fp = fopen(outfilename, "wb");
        curl_easy_setopt(curl,CURLOPT_URL ,url);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION ,NULL);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

#endif //FABRIC_INSTALLER_DOWNLOADER_H
