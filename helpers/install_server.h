//
// Created by paique on 03/04/23.
//
#include "helpers/downloader.h"
#include "helpers/url_verifier.h"
#include "helpers/get_latest_mc.h"
#include "helpers/env_checker.h"
#include "helpers/start_server.h"
void start_install() {
    char* mc_version = get_minecraft_version();
    char* fabric_version = get_fabric_version();
    char* installer_version = get_installer_version();

    if (strcmp(mc_version, "latest") >= 0 || strcmp(mc_version, "última") >= 0 || strcmp(mc_version, "recente") >= 0) {
        mc_version = get_latest_minecraft("https://piston-meta.mojang.com/mc/game/version_manifest_v2.json");
    } else {

    }

    if (strcmp(fabric_version, "latest") >= 0 || strcmp(fabric_version, "última") >= 0 || strcmp(fabric_version, "recente") >= 0) {
        char* url_fabric = malloc(100 * sizeof(char));
        snprintf(url_fabric, 100, "https://meta.fabricmc.net/v2/versions/loader/%s", mc_version);
        fabric_version = get_latest_fabric(url_fabric);
    }else {

    }

    if (strcmp(installer_version, "latest") >= 0 || strcmp(installer_version, "última") >= 0 || strcmp(installer_version, "recente") >= 0) {
        installer_version = get_latest_installer("https://meta.fabricmc.net/v2/versions/installer");
    }else {

    }

    int downloadPrealocate = 100;
    char* download_url = malloc(downloadPrealocate * sizeof(char));
        snprintf(download_url, downloadPrealocate, "https://meta.fabricmc.net/v2/versions/loader/%s/%s/%s/server/jar", mc_version, fabric_version, installer_version);


    int url_verification = url_verifier(download_url);
    if (url_verification) {

        printf("A versão do Fabric: %s, e do Minecraft: %s são válidas, prosseguindo com a instalação. \n", fabric_version, mc_version);
        downloader(download_url);
        printf("O Download foi finalizado. \n");
        printf("Não se esqueça de instalar a api do Fabric: https://www.curseforge.com/minecraft/mc-mods/fabric-api \n");
        detect_java(1);
        start_server(get_docker_ram());
    } else {

        printf("Não foi possível realizar o download do Fabric versão %s, na versão do Miencraft %s. \n", fabric_version, mc_version);
        printf("Verifique se as versões estão corretas.");
        exit(255);

    }

}

#ifndef FABRIC_INSTALLER_INSTALL_SERVER_H
#define FABRIC_INSTALLER_INSTALL_SERVER_H

#endif //FABRIC_INSTALLER_INSTALL_SERVER_H
