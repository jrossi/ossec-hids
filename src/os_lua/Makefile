# Makefile for execd
# Daniel B. Cid <daniel.cid@gmail.com>||<daniel@underlinux.com.br>

PT=../
NAME=ossec-lua

include ../Config.Make


OBJS = ${OS_SHARED} ${OS_NET} ${OS_REGEX} ${OS_XML}
OS_LUA = -I${PT}external/lua/src 
OS_LUA_LINK = ${PT}external/lua/src/liblua.a -lm

all: os_lua.a


lua_handler.o: lua_handler.c lua_handler.h
		${CC}  ${CFLAGS}  ${OS_LUA}  lua_handler.c -c -o lua_handler.o 

os_lua.a: lua_handler.o
		${BUILDLIB} os_lua.a lua_handler.o



		
clean:
		${CLEAN} 
build:
		${BUILD}
