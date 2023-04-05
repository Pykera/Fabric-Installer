//
// Created by paique on 27/03/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <zip.h>
#include <inttypes.h>
#include <ctype.h>

#ifndef FABRIC_INSTALLER_JAVA_DETECTOR_H
#define FABRIC_INSTALLER_JAVA_DETECTOR_H

int detect_java(int installing) {
    printf("Detectando versão do Java, isto pode demorar um pouco.\n");

    FILE *fp;
    char *buffer;
    char *endptr;
    int result;

    if (installing == 1) {
    system("java -jar ./server.jar 1> /dev/null 2> /dev/null");
    }

    fp = popen("javap -verbose -cp ./.fabric/server/*-server.jar net.minecraft.bundler.Main | grep \"major version\" | awk '{print $3}'", "r");
    fseek(fp, 0, SEEK_END);
    fseek(fp, 0, SEEK_SET);
    buffer = malloc(sizeof(fp));
    fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);
    result = strtol(buffer,&endptr, 10);
    free(buffer);
    return result;

}

void start_server(char* xmx_java) {
    int java_version = detect_java(0);
    char* temp_var;
    char *start_cmd = malloc(700 * sizeof(char));

    printf("Major version do .jar: %d \n", java_version);

    if (java_version < 60) {
        temp_var = "java-8";
        printf("Java 8 detectado! \n");
    } else if (java_version == 60) {
        temp_var = "java-16";
        printf("Java 16 detectado! \n");
    } else if (java_version == 61) {
        temp_var = "java";
        printf("Java 17 detectado! \n");
    } else {
        printf("Não foi possível detectar a versão do Java, provavelmente existe algum problema na instalação do Fabric. \n");
        exit(-1);
    }
    strcpy(start_cmd, temp_var);
    strcat(start_cmd, " -jar -Xmx");
    strcat(start_cmd, xmx_java);
    strcat(start_cmd, "M -Xms128M -jar server.jar");
    system(start_cmd);
}


#endif //FABRIC_INSTALLER_JAVA_DETECTOR_H
