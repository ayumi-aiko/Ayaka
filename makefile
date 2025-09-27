#
# Copyright (C) 2025 愛子あゆみ <ayumi.aiko@outlook.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# build wen no args diddyblud
ifeq ($(MAKECMDGOALS),)
	.DEFAULT_GOAL := ayaka-cli-android
endif

# compiler and it's arguments.
CC_ROOT = /home/ayumi/android-ndk-r27d/toolchains/llvm/prebuilt/linux-x86_64/bin
ifeq ($(ARCH),arm64)
	CC := $(CC_ROOT)/aarch64-linux-android$(SDK)-clang
endif
ifeq ($(ARCH),arm)
	CC := $(CC_ROOT)/armv7a-linux-androideabi$(SDK)-clang
endif
ifeq ($(ARCH),x86)
	CC := $(CC_ROOT)/i686-linux-android$(SDK)-clang
endif
ifeq ($(ARCH),x86_64)
	CC := $(CC_ROOT)/x86_64-linux-android$(SDK)-clang
endif
CFLAGS = -O3 -static

# common variables
BUILD_BINARY_OUTPUT_DIR = ./local_build/binaries
COMPILER_OUTPUT = ./local_build/ayaka.build.logs

# Source files for each target 
AYAKA_CLI_INCLUDE_DIR = ./src/ayaka-cli-android/include
AYAKA_CLI_SRCS = ./src/ayaka-cli-android/include/ayaka.c ./src/ayaka-cli-android/include/ayaka_utils.c
AYAKA_CLI_MAIN = ./src/ayaka-cli-android/ayaka-main/main.c
AYAKA_OUTPUT_NAME = ayaka-cli-android

# Checks if the android ndk compiler toolchain exists
check_compiler: checkArgs
	@[ -x "$(CC)" ] || { \
		printf "\033[0;31mmake: Error: Compiler '%s' not found or not executable. Please check the path or install it.\033[0m\n" "$(shell basename $(CC))"; \
		exit 1; \
	}

# checks args
checkArgs:
	@if [ -z "$(SDK)" ]; then \
	  printf "\033[0;31mmake: Error: SDK is not set. Please specify the Android API level, e.g., 'SDK=30'\033[0m\n"; \
	  exit 1; \
	fi; \
	if [ -z "$(ARCH)" ]; then \
	  printf "\033[0;31mmake: Error: ARCH is not set. Please specify the target architecture, e.g., 'ARCH=arm64'\033[0m\n"; \
	  exit 1; \
	fi

# checks if given sdk version deprecated or not.
checkDeprecated:
	@if [ "$(SDK)" -le "27" ]; then \
		echo "\e[0;31mmake: Error: Any Android version, which is below than 8.0 Oreo is deprecated.\e[0;37m"; \
		echo "\e[0;31mmake: Error: Android 9.0 Pie and above are the targets that are supported.\e[0;37m"; \
		exit 1; \
	fi

# builds ayaka-cli-android
ayaka-cli-android: check_compiler
	@rm -f $(COMPILER_OUTPUT)
	@echo "\e[0;33mmake: Info: Building ayaka-cli-android\e[0;37m"
	@$(CC) $(CFLAGS) -I$(AYAKA_CLI_INCLUDE_DIR) $(AYAKA_CLI_SRCS) $(AYAKA_CLI_MAIN) -o $(BUILD_BINARY_OUTPUT_DIR)/$(AYAKA_OUTPUT_NAME) >$(COMPILER_OUTPUT) 2>&1 && \
	echo "\e[0;33mmake: Info: Build finished successfully\e[0;37m" || echo "\e[0;31mmake: Error: Compilation failed. Check $(COMPILER_OUTPUT) for details.\e[0;37m";

# cleans build files
clean:
	@echo "\e[0;33mmake: Info: Cleaning build files...\e[0;37m"
	@rm -f $(BUILD_BINARY_OUTPUT_DIR)/$(AYAKA_OUTPUT_NAME) $(COMPILER_OUTPUT)
	@echo "\e[0;33mmake: Info: Clean finished.\e[0;37m"