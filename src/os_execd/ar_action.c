
#include <stdlib.h>
#include "shared.h"
#include "debug_op.h"

#include "lua_handler.h"
#include "ar_action.h"



ar_action_t * ar_action_new(int action, 
                            const char *user, 
                            const char *ipaddr,
                            const char *alert_id,
                            const char *rule_id, 
                            const char *agent_detail) 
{

    ar_action_t *self = (ar_action_t *)malloc(sizeof(ar_action_t));
    if (self == NULL) {
        printf("malloc failed\n");
        goto error;
    }


    self->action = action;

    if(user != NULL) { os_strdup(user, self->user); } 
    else { self->user = NULL; }

    if(ipaddr != NULL) {  os_strdup(ipaddr, self->ipaddr); }
    else { self->ipaddr = NULL; }

    if(alert_id != NULL) {  os_strdup(alert_id, self->alert_id); }
    else { self->alert_id = NULL; }

    if(rule_id != NULL) { os_strdup(rule_id, self->rule_id); }
    else { self->rule_id = NULL; }

    if(agent_detail != NULL)  { os_strdup(agent_detail, self->agent_detail); }
    else { self->agent_detail = NULL; }

    //printf("self-name");
    /*snprintf(self->name, 127, "%d-%s-%s-%s-%s", 
                              self->action,
                              self->user,
                              self->ipaddr ,
                              self->alert_id ,
                              self->rule_id );
                              */
    return self; 

error:
    if (self) {
        ar_action_destroy(&self);
    }
    return NULL;
}


void ar_action_destroy(ar_action_t **self_p)
{
    if (*self_p) {
        ar_action_t *self = *self_p;
        if(self->user)         { free(self->user); }
        if(self->ipaddr)       { free(self->ipaddr); }
        if(self->alert_id)     { free(self->alert_id); }
        if(self->rule_id)      { free(self->rule_id); }
        if(self->agent_detail) { free(self->agent_detail); }
        if(self->name)         { free(self->name); }
        free (self);
        *self_p = NULL;
    }
}

int ar_action_asluatable(ar_action_t *self, lua_handler_t *handler)
{
    lua_newtable(handler->L);
    if(self->user != NULL) {
        lua_pushstring(handler->L, "user");
        lua_pushstring(handler->L, self->user);
        lua_rawset(handler->L, -3);
    }
    if(self->ipaddr != NULL) {
        lua_pushstring(handler->L, "ipaddr");
        lua_pushstring(handler->L, self->ipaddr);
        lua_rawset(handler->L, -3);
    }
    if(self->alert_id != NULL) {
        lua_pushstring(handler->L, "alert-id");
        lua_pushstring(handler->L, self->alert_id);
        lua_rawset(handler->L, -3);
    }
    if(self->rule_id != NULL) {
        lua_pushstring(handler->L, "rule-id");
        lua_pushstring(handler->L, self->rule_id);
        lua_rawset(handler->L, -3);
    }
    if(self->agent_detail != NULL) {
        lua_pushstring(handler->L, "agent-detail");
        lua_pushstring(handler->L, self->agent_detail);
        lua_rawset(handler->L, -3);
    }
    return 0;
}

int ar_action_run_lua(ar_action_t *self, lua_handler_t *handler) 
{
    int action;
    switch (self->action) {
        case AR_ACTION_ADD:
            action = handler->adder;
            break;
        case AR_ACTION_DEL:
            action = handler->deleter;
            break;
        default:
            return -1;
    }
    lua_rawgeti(handler->L, LUA_REGISTRYINDEX, action);
    if((ar_action_asluatable(self, handler) == 0)) {
        return lua_handler_pcall(handler, action, 1, 0, 0);
    }
    return -1; 
}
