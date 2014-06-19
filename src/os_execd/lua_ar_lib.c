#include "lua_handler.h"


static int ar_register_timer(lua_State *L)
{
    lua_handler_t *self = lua_handler_getself(L);

    self->timer_freq  = lua_tointeger(L, 1);
    lua_pop(L, 1);
    self->timer = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;

}
static int ar_register_init(lua_State *L)
{
    int l_fun = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_handler_t *self = lua_handler_getself(L);
    self->init = l_fun;


    return 0;
}
static int ar_register_add(lua_State *L)
{
    int l_fun = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_handler_t *self = lua_handler_getself(L);
    self->adder = l_fun;

    return 0;
}
static int ar_register_delete(lua_State *L)
{
    int l_fun = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_handler_t *self = lua_handler_getself(L);
    self->deleter = l_fun;
    return 0;
}

static int ar_register_startup(lua_State *L)
{
    int l_fun = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_handler_t *self = lua_handler_getself(L);
    self->startup = l_fun;
    return 0;
}

static int ar_register_shutdown(lua_State *L)
{
    int l_fun = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_handler_t *self = lua_handler_getself(L);
    self->startup = l_fun;
    return 0;
}


static const struct luaL_Reg ar_functs[] = {
    {"register_timer",   ar_register_timer},
    {"register_add",     ar_register_add},
    {"register_delete",  ar_register_delete},
    {"register_init",    ar_register_init},
    {"register_startup", ar_register_startup},
    {"register_shutdown",ar_register_shutdown},
    {NULL, NULL},
};

int lua_lib_ar(lua_handler_t *self) 
{
    return lua_handler_lib_add(self, "ar", ar_functs);
}
