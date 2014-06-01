
#ifndef __LUA_HANDLER_H_INCLUDED__
#define __LUA_HANDLER_H_INCLUDED__

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef struct _lua_handler_t {
    lua_State *L;
    char *name;
    int init;
    int adder;
    int deleter;
    int startup;
    int shutdown; 
    int timer;
    int limit_count; 
    lua_Debug *ar;
    double timer_freq;
} lua_handler_t;


void lua_handler_destroy(lua_handler_t **self);

lua_handler_t *lua_handler_new(const char *name);

int lua_handler_add(lua_handler_t *self, const char *user, const char *ipaddr);

int lua_handler_delete(lua_handler_t *self, const char *user, const char *ipaddr);

int lua_handler_load(lua_handler_t *self, const char *fname);

int lua_handler_init(lua_handler_t *self); 

int lua_handler_startup(lua_handler_t *self); 

int lua_handler_shutdown(lua_handler_t *self); 


#endif
