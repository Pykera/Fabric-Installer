//
// Created by paique on 27/03/23.
//

#ifndef FABRIC_INSTALLER_GET_LATEST_MC_H
#define FABRIC_INSTALLER_GET_LATEST_MC_H

#include <curl/curl.h>
#include <malloc.h>
#include <string.h>
#include <json-c/json.h>
struct MemoryStruct {
    char *memory;
    size_t size;
};
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {

    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

char* get_json(char* url) {
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;


    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    res = curl_easy_perform(curl);


    return chunk.memory;


}

char* get_latest_minecraft(char* url) {

    char* json_response = get_json(url);

    json_object *jobj = json_tokener_parse(json_response);
    json_object *value;
    if (json_object_object_get_ex(jobj, "latest", &value)) {

        if (json_object_object_get_ex(value ,"release",&value)) {
            if (json_object_get_string(value) != NULL) {
             return json_object_get_string(value);
            } else {
                printf("Versão mais recente do Minecraft não encontrada na database! \n");
                exit(255);
            }
        } else {
            printf("Algo de errado ocorreu! \n");
            exit(255);
        }
    } else {
        printf("Algo de errado ocorreu! \n");
        exit(255);
    }
}

char* get_latest_fabric(char* url) {

    char* json_response = get_json(url);

    json_object *jobj = json_tokener_parse(json_response);
    json_object *obj = json_object_array_get_idx(jobj, 0);
    json_object *version_obj = json_object_object_get(json_object_object_get(obj, "loader"), "version");
    const char *version_str = json_object_get_string(version_obj);

    if (version_str != NULL) {
        return version_str;
    } else
    {
        printf("Um erro ocorreu! \nVerifique se a versão do Minecraft escolhida é válida.");
        exit(1);
    }
}

char* get_latest_installer(char* url) {

    char* json_response = get_json(url);

    json_object *jobj = json_tokener_parse(json_response);
    json_object *first_obj = json_object_array_get_idx(jobj, 0);
    json_object *version_obj = json_object_object_get(first_obj, "version");
    const char *version_str = json_object_get_string(version_obj);
    if (version_str != NULL) {
        return version_str;
    } else
    {
        printf("Um erro ocorreu!");
        exit(1);
    }
}



#endif //FABRIC_INSTALLER_GET_LATEST_MC_H
