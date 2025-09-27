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
#ifndef AYAKA_H
#define AYAKA_H

//includes:
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ayaka_utils.h"

// pre-defined macros:
#define persistDirectory "/data/adb/Ayaka"
#define systemHostsFile "/system/etc/hosts"
#define tempHostsFile "/data/local/tmp/hosts_ayaka_temp"
#define countsFilePath persistDirectory "/counts"
#define blockedModCountPath countsFilePath "/mod.count"
#define SystemModCountPath countsFilePath "/system.count"
#define pausedHostsFile persistDirectory "/hosts.paused"
#define configScriptPath persistDirectory "/configs"

// pre-defined variables and undefined variables:
extern int blockedMod;
extern int blockedSys;

// function defs:
char *grepProp(const char *variableName, const char *propFile);
bool isDefaultHosts(void);
bool isProtectionPaused(void);
void refreshBlockedCounts(void);

#endif 