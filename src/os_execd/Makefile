# Makefile for execd
# Daniel B. Cid <daniel.cid@gmail.com>||<daniel@underlinux.com.br>

PT=../
NAME=ossec-execd

include ../Config.Make

LOCAL = execd.c exec.c config.c

OBJS = ${OS_SHARED} ${OS_NET} ${OS_REGEX} ${OS_XML}
OS_LUA = -I${PT}external/lua/src  -I${PT}os_lua 
OS_LUA_LINK = ${PT}external/lua/src/liblua.a -lm ${PT}os_lua/os_lua.a

all: ${NAME} ossec-execd-luatest

${NAME}:
		${CC} ${CFLAGS} ${OS_LUA} ${OS_LINK} ${LOCAL} ${OBJS} -o ${NAME}
		${CC} ${CFLAGS} ${OS_LUA} -c ${LOCAL}

ar_action.o: ar_action.c ar_action.h
		#${CC}  ${CFLAGS} ${OS_SHARED} ${OS_CJSON} -I../external/lua/src/   ar_action.c -c -o ar_action.o 
		${CC}  ${CFLAGS} ${OS_LUA}  ar_action.c -c -o ar_action.o 

lua_ar_lib.o: lua_ar_lib.c lua_ar_lib.h 
		${CC}  ${CFLAGS}  ${OS_LUA}  lua_ar_lib.c -c -o lua_ar_lib.o


ossec-execd-luatest: lua_tester.c ar_action.o lua_ar_lib.o 
		${CC}  ${CFLAGS} ${OS_LUA} ${OS_SHARED} ${OS_CJSON} ${OS_LINK} ${OS_SHARED} ar_action.o lua_ar_lib.o lua_tester.c -o ossec-execd-luatest ${OS_LUA_LINK} ../shared/lib_shared.a ../external/libcJSON.a

check: all 
		./ossec-execd-luatest -l test/test_1.lua -t test/test_1.json
		./ossec-execd-luatest -l test/test_2.lua -t test/test_2.json
		
clean:
		${CLEAN} 
build:
		${BUILD}
