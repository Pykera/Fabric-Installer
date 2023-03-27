//
// Created by paique on 27/03/23.
//
#include "helpers/downloader.h"
#include "helpers/url_verifier.h"
#include "helpers/env_checker.h"
#include <stdlib.h>

int main() {

    char* mc_version = get_minecraft_version();
    char* fabric_version = get_fabric_version();
    char* installer_version = get_installer_version();

    char* download_url = malloc(100 * sizeof(char));
    strcpy(download_url, "https://meta.fabricmc.net/v2/versions/loader/");

    for (int i = 1; i <= 4; i++) {
        if (i == 1) {
            strcat(download_url, mc_version);
        } else if (i == 2) {
            strcat(download_url, fabric_version);
        } else if (i == 3) {
            strcat(download_url, installer_version);
        } else if (i == 4) {
            strcat(download_url, "server/jar");
        }

        if (i != 4) {
            strcat(download_url, "/");
        }
    }


    int url_verification = url_verifier(download_url);
    if (url_verification) {

        printf("A versão do Fabric: %s, e do Minecraft: %s são válidas, prosseguindo com a instalação. \n", fabric_version, mc_version);
        downloader(download_url);
        printf("O Download foi finalizado. \n");
        printf("Não se esqueça de instalar a api do Fabric: https://www.curseforge.com/minecraft/mc-mods/fabric-api \n");
        system("java -jar server.jar --nogui");

    } else {

        printf("Não foi possível realizar o download do Fabric versão %s, na versão do Miencraft %s. \n", fabric_version, mc_version);
        printf("Verifique se as versões estão corretas.");
        exit(255);

    }
}



