//
// Created by paique on 27/03/23.
//

#ifndef FABRIC_INSTALLER_ENV_CHECKER_H
#define FABRIC_INSTALLER_ENV_CHECKER_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* fix_env(char* env_name) {

    char* fixed_env = malloc(10 * sizeof(char*));
    printf("Qual é a versão desejada do %s? (Digite abaixo, e dê enter)\n", env_name);
    scanf("%s", fixed_env);

    return fixed_env;
}

char* get_minecraft_version() {
    char* env_mc_version = getenv("MC_VERSION");
    if (env_mc_version != NULL ) {
        return env_mc_version;
    } else {
        env_mc_version = fix_env("Minecraft");

        return env_mc_version;
    }

}

char* get_fabric_version() {
    char* env_fabric_version = getenv("FABRIC_VERSION");
    if (env_fabric_version != NULL) {
        return env_fabric_version;
    } else {
        env_fabric_version = fix_env("Fabric");
        return env_fabric_version;
    }
}

char* get_installer_version() {
    char * env_installer_version = getenv("INSTALLER_VERSION");
    if (env_installer_version != NULL) {
        return env_installer_version;
    } else {
        env_installer_version = fix_env("instalador do Fabric");
        return env_installer_version;
    }
}

#endif //FABRIC_INSTALLER_ENV_CHECKER_H
