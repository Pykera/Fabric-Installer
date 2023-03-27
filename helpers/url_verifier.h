//
// Created by paique on 27/03/23.
//

#ifndef FABRIC_INSTALLER_URL_VERIFIER_H
#define FABRIC_INSTALLER_URL_VERIFIER_H

#include <curl/curl.h>

int url_verifier(char* url) {

CURL *curl;
CURLcode res;
curl = curl_easy_init();

if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, NULL);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 1000L);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        printf("curl_easy_perform() falhou em url_verifier.h: %s\n", curl_easy_strerror(res));
    }

    long http_code = 0;
    res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    if (res != CURLE_OK) {
        printf("curl_easy_getinfo() falhou em url_verifier.h: %s\n", curl_easy_strerror(res));
        printf("Verifique se a versão do Minecraft/Forge é válida.");
    }

    printf("Código de resposta do servidor: %ld\n", http_code);

    curl_easy_cleanup(curl);

    if(http_code == 200) {

        return 1;

    } else {

        return 0;

    }


}

}

#endif //FABRIC_INSTALLER_URL_VERIFIER_H
