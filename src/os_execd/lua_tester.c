
#include <stdio.h>
#include "shared.h"
#include "debug_op.h"
#include "lua_handler.h"


void print_version(const char *prog)
{
    printf("\n");
    printf("\n");
    printf("%s %s - %s (%s)\n", __ossec_name, __version, __author, __contact);
    printf("%s\n", __site);
    printf("\n");
}

void print_help(const char *prog)
{
    print_version(prog);
    printf("  %s: -[Vh] -l <lua_script> -t <text_script>\n", prog);
    printf("    -V          Version and license message\n");
    printf("    -l          Lua ossec-execd script to test\n");
    printf("    -t          Test Script to play\n");
    printf(" \n");
    exit(1);
}


int main(int argc, char **argv)
{
    int c; 
    char *test_script = NULL;
    char *lua_script = NULL; 
    while((c = getopt(argc, argv, "Vht:l:")) != -1){
        switch(c) {
        case 'V':
            print_version(ARGV0);
            break;
        case 'h':
            print_help(ARGV0);
            break;
        case 't':
            test_script = optarg;
            break;
        case 'l':
            lua_script = optarg;
            break;
        default:
            print_help(ARGV0);
            break;
        }
    }
    if (lua_script == NULL && test_script == NULL) {

        printf("Both lua_script and test_script are required\n");
        return 1; 
    }

    printf ("starting new\n");
    lua_handler_t *tester = lua_handler_new("test-script");
    lua_handler_load(tester, lua_script);
    if (tester) {
        printf ("tester-starting init\n");
        lua_handler_init(tester);
        printf ("tester-starting add\n");
        lua_handler_add(tester, "jrossi","1.1.1.1");
        printf ("tester-starting delete\n");
        lua_handler_delete(tester, "jrossi", "1.1.1.1");
        printf ("tester-starting destory\n");
        lua_handler_destroy(&tester);
        return 0;
    } else { 
        return 1; 
    }

    return 0;
}
