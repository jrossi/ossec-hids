
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "ar_action.h"
#include "lua_handler.h"
#include "lua_ar_lib.h"


static void stack_dump(lua_State *L)
{
    int i;
    int top = lua_gettop(L);

    for (i = 1; i <= top; i++) {
        int t = lua_type(L, i);
        switch(t) {
        case LUA_TSTRING:
            printf(" %d: %s\n", i, lua_tostring(L, i));
            break;
        case LUA_TNUMBER:
            printf(" %d: %g\n", i,  lua_tonumber(L, i));
            break;
        default:
            printf(" %d: %s\n", i, lua_typename(L, t));
            break;
        }
    }
}



lua_handler_t *lua_handler_getself(lua_State *L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, LUA_HANDLER_REG_NAME);
    lua_handler_t *self = lua_touserdata(L, -1);
    return self;
}


/*
static int ossec_log_debug(lua_State, *L)
{
    
}

static int ossec_log_info(lua_State, *L)
{
    
}

static const struct luaL_Reg ossec_log_functs[] = {
    {"debug",    ossec_log_debug},
    {"info",     ossec_log_info},
    {NULL, NULL},
};

*/


lua_handler_t *lua_handler_new(const char *name)
{

    lua_handler_t *self = (lua_handler_t *)malloc(sizeof(lua_handler_t));
    self->deleter = 0;
    self->adder = 0;
    self->timer = 0;
    self->failure_max = LUA_HANDLE_DEFAULT_FAILURE_MAX;
    self->failure_count = 0; 

    self->timer_freq = 0;

    if (self == NULL) {
        goto error;
    }
    self->L = luaL_newstate();
    self->name = strdup(name);

    luaL_openlibs(self->L);
    lua_pushlightuserdata(self->L, self);
    lua_setfield(self->L, LUA_REGISTRYINDEX, LUA_HANDLER_REG_NAME);
    //lua_handler_lib_add(self, "ar", ar_functs);

    return self;

error:
    //printf("goto: error in new\n");
    if (self) {
        lua_handler_destroy(&self);
    }
    return NULL;
}

int lua_handler_lib_add(lua_handler_t *self, const char *lib_name, const luaL_Reg *lib_functs)
{
    luaL_newlib(self->L, lib_functs);
    lua_setglobal(self->L, lib_name);
    return 0; 
}

int lua_handler_load(lua_handler_t *self, const char *fname) 
{
    // Loadfile **********************************************
    //
    //printf("\n\n");
    if(luaL_loadfile(self->L, fname)) {
        printf("Could not load the file: %s\n", lua_tostring(self->L, -1));
        goto error;
    } 

    if(lua_pcall(self->L, 0, 0, 0) != 0) {
        printf("lua_handler_new error for %s in loadfile pcall: %s\n", fname, lua_tostring(self->L, -1));
        goto error;
    }
    return 0;

error:
    return -1;
}

/*
int lua_handler_limit_count(lua_handler_t *self, lua_Debug *ar, int count) 
{
    self->ar = ar; 
    self->limit_count = count; 
    return lua_sethook(self->L, &ar, LUA_MASKCOUNT, count);
}
*/


void lua_handler_destroy(lua_handler_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        lua_handler_t *self = *self_p;
        lua_close(self->L);
        free(self->name);
        free (self);
        *self_p = NULL;
    }
}




int lua_handler_pcall(lua_handler_t *self, int action_func, int nargs, int nresults, int errfunc) {
    //stack_dump(self->L);
    //lua_rawgeti(self->L, LUA_REGISTRYINDEX, action_func);
    //stack_dump(self->L);
    if(lua_pcall(self->L, nargs, nresults, errfunc ) != 0 ) {
        printf("lau_handler_pcall error for %s in pcall: %s\n", 
                self->name, 
                lua_tostring(self->L, -1));
        //pcall failed exit error
        lua_pop(self->L, 1);
        return 1;
    } else {
        return 0;
    }
}

int lua_handler_tick(lua_handler_t *self) 
{

    if (self->timer) {
        lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->timer);
        return lua_handler_pcall(self, self->timer, 0, 0, 0);
    }
    return 0;
}

int lua_handler_init(lua_handler_t *self)
{
    if (self->init) {
        lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->init);
        return lua_handler_pcall(self, self->startup, 0, 0, 0);
    } 
    return 0;
}

int lua_handler_startup(lua_handler_t *self)
{
    if (self->startup) {
        lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->startup);
        return lua_handler_pcall(self, self->startup, 0, 0, 0);
    } 
    return 0;
}



int lua_handler_shutdown(lua_handler_t *self)
{
    if (self->shutdown) {
        lua_rawgeti(self->L, LUA_REGISTRYINDEX, self->shutdown);
        return lua_handler_pcall(self, self->shutdown, 0, 0, 0);
    } 
    return 0;
}

