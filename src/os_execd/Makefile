# Makefile for execd
# Daniel B. Cid <daniel.cid@gmail.com>||<daniel@underlinux.com.br>

PT=../
NAME=ossec-execd

include ../Config.Make

LOCAL = execd.c exec.c config.c

OBJS = ${OS_SHARED} ${OS_NET} ${OS_REGEX} ${OS_XML}

all: addclient ossec-execd-luatest

addclient:
		${CC} ${CFLAGS} ${OS_LINK} ${LOCAL} ${OBJS} -o ${NAME}
		${CC} ${CFLAGS} -c ${LOCAL}


lua_handler.o: lua_tester.c 
		${CC}  ${OS_SHARED} -I../external/lua/src/   lua_handler.c -c -o lua_handler.o 

ossec-execd-luatest: lua_handler.o 
		${CC}  ${CFLAGS} ${OS_LINK} ${OS_SHARED} -I../external/lua/src/   lua_handler.o lua_tester.c -o ossec-execd-luatest ../external/lua/src/liblua.a -lm

clean:
		${CLEAN} lua_tester 
build:
		${BUILD}
