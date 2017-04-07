cmake_minimum_required(VERSION 3.6)
project(project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Github/othershell.c
        Writing-Your-Own-Unix-Shell/myint.c
        Writing-Your-Own-Unix-Shell/myspin.c
        Writing-Your-Own-Unix-Shell/mysplit.c
        Writing-Your-Own-Unix-Shell/mystop.c
        Writing-Your-Own-Unix-Shell/tsh.c
        myint.c
        myspin.c
        mysplit.c
        mystop.c
        tsh-ck.c linuxref.c)

add_executable(project ${SOURCE_FILES})