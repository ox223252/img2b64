# flags for alls targets
FLAGS= -D'BY_LINUX_MAKEFILE'
# -D'FOE_WITHOUT_DLL'
# -D'FOE_WITHOUT_THREAD'

# tools / flags / libs only for native target
CC=gcc
CXX=g++
natif_FLAGS=
natif_LIBS=

# tools / flags / libs only for arm target
LABEL=arm
arm_CROSS_CC=arm-linux-gnueabi-gcc
arm_CROSS_CXX=arm-linux-gnueabi-g++
arm_FLAGS=
arm_LIBS=
arm_EXEC_AFTER=

# tools / flags / libs only for w64 target
LABEL=w64
w64_CROSS_CC=i686-w64-mingw32-gcc
w64_CROSS_CXX=i686-w64-mingw32-g++
w64_FLAGS=
w64_LIBS=
w64_EXEC_AFTER=
