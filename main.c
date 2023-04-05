//
// Created by paique on 27/03/23.
//

#include "helpers/env_checker.h"
#include "helpers/start_server.h"
#include "helpers/install_server.h"
#include <dirent.h>

int main() {
    DIR* fabric_folder = opendir(".fabric");
    DIR* libraries_folder = opendir("libraries");

    if (fabric_folder && libraries_folder) {
        closedir(fabric_folder);
        closedir(libraries_folder);
        printf("Foi detectada uma instalação do Fabric, inicializando o servidor. \n");
        start_server(get_docker_ram());
    } else {
        closedir(fabric_folder);
        closedir(libraries_folder);
        printf("Um ou mais arquivos não foram encontrados. \nIniciando a instalação! \n");
        start_install();
    }
}
