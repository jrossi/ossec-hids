
#ifndef __AR_ACTION_H_INCLUDED__
#define __AR_ACTION_H_INCLUDED__

#define AR_ACTION_ADD 1
#define AR_ACTION_DEL 2

typedef struct _ar_action_t {
    int action;
    char *user;
    char *ipaddr;
    char *alert_id;
    char *rule_id; 
    char *agent_detail; 
    char *name;
} ar_action_t;

ar_action_t * ar_action_new(const char *action, 
                            const char *user, 
                            const char *ipaddr,
                            const char *alert_id,
                            const char *rule_id, 
                            const char *agent_detail);

void ar_action_destroy(lua_handler_t **self_p);


/* 
 * Push onto the LUA stack the ar_action details.  
 */
int ar_action_asluatable(ar_action_t *self, lua_State *L);

#endif 
