#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} kv_pair;

typedef struct {
    char *path;
    kv_pair *pairs;
    size_t count;
} url_query;

void free_url_query(url_query *linking) {
    for (int i=0; i < linking->count; i++) {
        free(linking->pairs[i].key);
        free(linking->pairs[i].value);
    }
    free(linking->pairs);
    linking->pairs = NULL;
    linking->path = NULL;
    linking->count = 0;
}


int url_decode(char *url, url_query *result) {
    if (!url || *url == '\0' || !result) {
        return -1;
    }

    char *save;
    char *path = strtok_r(url, "?", &save);
    if (!path) return -1;

    result->path = path;

    char *query = strtok_r(NULL, "?", &save);

    if (!query) {
        result->count = 0;
        result->pairs = NULL;
        return 0;
    }

    result->pairs = NULL;
    result->count = 0;

    char *saveptr;
    char *tok = strtok_r(query, "&", &saveptr);

    while (tok) {

        char *save2;
        char *key = strtok_r(tok, "=", &save2);
        if(!key) free_url_query(result);
        char *val = strtok_r(NULL, "=", &save2);
        //if(!val) free_url_query(result);
        result->pairs = realloc(result->pairs, (result->count + 1) * sizeof(kv_pair));
        result->pairs[result->count].key = strdup(key);
        result->pairs[result->count].value = val ? strdup(val) : strdup(""); // value could be NULL maybe
        result->count++;

        tok = strtok_r(NULL, "&", &saveptr);
    }

    return 0;
}

int main() {
    url_query linking;
    char buf[] = "http://www.google.com/s?wd=linux&cl=3"; //等号右边本身存放在.rodata
    if (url_decode(buf, &linking) == 0) {
        printf("path: %s\n", linking.path);

        for (size_t i = 0; i < linking.count; i++)
            printf("%s = %s\n",
                   linking.pairs[i].key,
                   linking.pairs[i].value);

        free_url_query(&linking);
    }
}


