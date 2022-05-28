#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpmemkv.h>
#include <string.h>
const char PATH[] = "kvfile";
const uint64_t SIZE = 0x1000000;

int get_kv_callback(const char *k, size_t kb, const char *value, size_t value_bytes, void *arg)
{
    printf("%s : %s\n", k, value);
    return 0;
}

int main()
{
    struct pmemkv_db *db;
    pmemkv_config *config = pmemkv_config_new();
    pmemkv_config_put_path(config, PATH);
    pmemkv_config_put_create_if_missing(config, true);
    pmemkv_config_put_size(config, SIZE);
    int error = pmemkv_open("cmap", config, &db);
    if (error != PMEMKV_STATUS_OK) {
        fprintf(stderr, "%s\n", pmemkv_errormsg());
        exit(1);
    }

    if (pmemkv_put(db, "key1", strlen("key1") + 1, "value1", strlen("value1")) != PMEMKV_STATUS_OK) {
        fprintf(stderr, "%s\n", pmemkv_errormsg());
        exit(1);
    }

    if (pmemkv_put(db, "key2", strlen("key2") + 1, "value2", strlen("value2")) != PMEMKV_STATUS_OK) {
        fprintf(stderr, "%s\n", pmemkv_errormsg());
        exit(1);
    }

    if (pmemkv_put(db, "key3", strlen("key3") + 1, "value3", strlen("value3")) != PMEMKV_STATUS_OK) {
        fprintf(stderr, "%s\n", pmemkv_errormsg());
        exit(1);
    }
    
    pmemkv_get_all(db, &get_kv_callback, NULL);
    pmemkv_close(db);
    return 0;
}

