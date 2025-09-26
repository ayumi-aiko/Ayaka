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
#ifndef AYAKA_UTILS_H
#define AYAKA_UTILS_H

// includes:
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <time.h>

// macros!
#define logFilePath "/data/adb/Ayaka/recent_logs"

// externs!
extern const bool useStdoutForAllLogs;
extern const bool disableOutput;

// enums!
enum elogLevel {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_ABORT
};

// function defs!
void consoleLog(enum elogLevel loglevel, const char *service, const char *message, ...);
void abort_instance(const char *service, const char *format, ...);
void printAyakaArt(void);

#endif