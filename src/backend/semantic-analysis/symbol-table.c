#include "symbol-table.h"
#include "../support/shared.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

KHASH_MAP_INIT_STR(variables_hash_map, Variable*)

static khash_t(variables_hash_map) * variables_hm;

static Variable * create_new_var(char* name, Token * type);

void init_symbol_table(void) {
    variables_hm = kh_init(variables_hash_map);
}

void free_symbol_table(void) {
    Variable* var;
    kh_foreach_value(variables_hm, var, free(var));
    kh_destroy(variables_hash_map, variables_hm);
}

Variable* symbol_table_put(char* name, Token* type) {
    if (!symbol_table_exists(name)) {

        Variable* new = create_new_var(name, type);

        int ret;
        khiter_t k = kh_put(variables_hash_map, variables_hm, name, &ret);
        if (ret == -1) {
            return NULL;
        }

        kh_val(variables_hm, k) = new;
        return new;
    }
    
    return NULL;
}

boolean symbol_table_exists(char* name) {
    khiter_t k = kh_get(variables_hash_map, variables_hm, name);
    return k != kh_end(variables_hm);
}

Variable* symbol_table_get(char* name) {
    khiter_t k = kh_get(variables_hash_map, variables_hm, name);
    if (k != kh_end(variables_hm)) {
        return kh_val(variables_hm, k);
    }

    return NULL;
}

static Variable* create_new_var(char* name, Token * type) {
    Variable* new = malloc(sizeof(*new));
    new->type = type;
    new->name = name;
    return new;
}