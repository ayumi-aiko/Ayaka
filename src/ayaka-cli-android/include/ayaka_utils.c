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
#include <ayaka_utils.h>

void consoleLog(enum elogLevel loglevel, const char *service, const char *message, ...) {
    // prevent logging if disabled
    if(disableOutput) return;
    va_list args;
    va_start(args, message);
    FILE *out = NULL;
    bool toFile = false;
    if(useStdoutForAllLogs) {
        out = stdout;
        if(loglevel == LOG_LEVEL_ERROR || loglevel == LOG_LEVEL_WARN || loglevel == LOG_LEVEL_DEBUG || loglevel == LOG_LEVEL_ABORT) out = stderr;
    }
    else {
        out = fopen(logFilePath, "a");
        if(!out) exit(EXIT_FAILURE);
        toFile = true;
    }
    switch(loglevel) {
        case LOG_LEVEL_INFO:
            if(!toFile) fprintf(out, "\033[2;30;47mINFO: ");
            else fprintf(out, "INFO: %s: ", service);
        break;
        case LOG_LEVEL_WARN:
            if(!toFile) fprintf(out, "\033[1;33mWARNING: ");
            else fprintf(out, "WARNING: %s: ", service);
        break;
        case LOG_LEVEL_DEBUG:
            if(!toFile) fprintf(out, "\033[0;36mDEBUG: ");
            else fprintf(out, "DEBUG: %s: ", service);
        break;
        case LOG_LEVEL_ERROR:
            if(!toFile) fprintf(out, "\033[0;31mERROR: ");
            else fprintf(out, "ERROR: %s: ", service);
        break;
        case LOG_LEVEL_ABORT:
            if(!toFile) fprintf(out, "\033[0;31mABORT: ");
            else fprintf(out, "ABORT: %s: ", service);
        break;
    }
    vfprintf(out, message, args);
    if(!toFile) fprintf(out, "\033[0m\n");
    else fprintf(out, "\n");
    if(!useStdoutForAllLogs && out) fclose(out);
    va_end(args);
}

void abort_instance(const char *service, const char *format, ...) {
    va_list args;
    va_start(args, format);
    consoleLog(LOG_LEVEL_ABORT, "%s", "%s %s", service, format, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

void printAyakaArt(void) {
    const char *art1 =
"  :::.  .-:.     ::-.:::.      :::  .    :::.     \n"
"  ;;`;;  ';;.   ;;;;';;`;;     ;;; .;;,. ;;`;;    \n"
" ,[[ '[[,  '[[,[[[' ,[[ '[[,   [[[[[/'  ,[[ '[[,  \n"
"c$$$cc$$$c   c$$\"  c$$$cc$$$c _$$$$,   c$$$cc$$$c \n"
" 888   888,,8P\"`    888   888,\"888\"88o, 888   888,\n"
" YMM   \"\"`mM\"       YMM   \"\"`  MMM \"MMP\"YMM   \"\"` \n";

    const char *art2 =
"  :::.  .-:.     ::-.:::.      :::  .    :::.     \n"
"  ;;`;;  ';;.   ;;;;';;`;;     ;;; .;;,. ;;`;;    \n"
" ,[[ '[[,  '[[,[[[' ,[[ '[[,   [[[[[/'  ,[[ '[[,  \n"
"c$$$cc$$$c   c$$\"  c$$$cc$$$c _$$$$,   c$$$cc$$$c \n"
" 888   888,,8P\"`    888   888,\"888\"88o, 888   888,\n"
" YMM   \"\"`mM\"       YMM   \"\"`  MMM \"MMP\"YMM   \"\"` \n";

    const char *art3 =
" .d8b.  db    db  .d8b.  db   dD  .d8b.  \n"
"d8' `8b `8b  d8' d8' `8b 88 ,8P' d8' `8b \n"
"88ooo88  `8bd8'  88ooo88 88,8P   88ooo88 \n"
"88~~~88    88    88~~~88 88`8b   88~~~88 \n"
"88   88    88    88   88 88 `88. 88   88 \n"
"YP   YP    YP    YP   YP YP   YD YP   YP \n";
    const char *arts[] = {art1, art2, art3};
    srand((unsigned)time(NULL));
    printf("%s", arts[rand() % sizeof(arts) / sizeof(arts[0])]);
}