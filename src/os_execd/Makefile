# Makefile for execd
# Daniel B. Cid <daniel.cid@gmail.com>||<daniel@underlinux.com.br>

PT=../
NAME=ossec-execd

include ../Config.Make

LOCAL = execd.c exec.c config.c

OBJS = ${OS_SHARED} ${OS_NET} ${OS_REGEX} ${OS_XML}

all: ${NAME} ossec-execd-luatest

${NAME}:
		${CC} ${CFLAGS} ${OS_LINK} ${LOCAL} ${OBJS} -o ${NAME}
		${CC} ${CFLAGS} -c ${LOCAL}

lua_handler.o: ar_action.c ar_action.h
		${CC}  ${OS_SHARED} -I../external/lua/src/   lua_handler.c -c -o lua_handler.o 

lua_handler.o: lua_handler.c lua_handler.h
		${CC}  ${OS_SHARED} -I../external/lua/src/   lua_handler.c -c -o lua_handler.o 

ossec-execd-luatest: lua_tester.c lua_handler.o ar_action.o
		${CC}  ${CFLAGS} ${OS_CJSON} ${OS_LINK} ${OS_SHARED} -I../external/lua/src/   ar_action.o lua_handler.o lua_tester.c -o ossec-execd-luatest ../external/lua/src/liblua.a -lm

check: all 
		./ossec-execd-luatest -l test/test_1.lua -t test/test_1.json
		./ossec-execd-luatest -l test/test_2.lua -t test/test_2.json
		
clean:
		${CLEAN} 
build:
		${BUILD}
