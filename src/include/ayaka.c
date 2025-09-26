//
// Copyright (C) 2025 愛子あゆみ <ayumi.aiko@outlook.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Created by Ayumi on 09-26-2025
#include "ayaka.h"

char *grepProp(const char *variableName, const char *propFile) {
    FILE *filePointer = fopen(propFile, "r");
    if(!filePointer) {
        consoleLog(LOG_LEVEL_ERROR, "grepProp", "Failed to open properties file: %s", propFile);
        return NULL;
    }
    char theLine[1024];
    size_t lengthOfTheString = strlen(variableName);
    while(fgets(theLine, sizeof(theLine), filePointer)) {
        if(strncmp(theLine, variableName, lengthOfTheString) == 0 && theLine[lengthOfTheString] == '=') {
            strtok(theLine, "=");
            char *value = strtok(NULL, "\n");
            if(value) {
                char *result = strdup(value);
                fclose(filePointer);
                return result;
            }
        }
    }
    fclose(filePointer);
    return NULL;
}

bool isDefaultHosts(void) {
    return (blockedMod == 0 && blockedSys == 0) ? true : false;
}

bool isProtectionPaused(void) {
    if(access(pausedHostsFile, F_OK) == 0 || strcmp(grepProp("adblockSwitch", configScriptPath), "1") == 0) return true;
    return false;
}

void refreshBlockedCounts(void) {
    mkdir(countsFilePath, 0777);
    // let's just get the values from the system first.
    FILE *sysCountFile = fopen(SystemModCountPath, "r");
    if(sysCountFile != NULL) {
        consoleLog(LOG_LEVEL_ERROR, "refreshBlockedCounts", "Failed to open system count file, assuming 0 blocked system entries.");
        blockedSys = 0;
        return;
    }
    fscanf(sysCountFile, "%d", &blockedSys);
    fclose(sysCountFile);
    // now the mod count
    FILE *modCountFile = fopen(blockedModCountPath, "r");
    if(modCountFile != NULL) {
        consoleLog(LOG_LEVEL_ERROR, "refreshBlockedCounts", "Failed to open module count file, assuming 0 blocked module entries.");
        blockedMod = 0;
        return;
    }
    fscanf(modCountFile, "%d", &blockedMod);
    fclose(modCountFile);
}