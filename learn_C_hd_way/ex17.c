#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//#define MAX_DATA 512
//#define MAX_ROWS 100
struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    struct Address *rows;
    int max_data;
    int max_rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char *message,struct Connection* conn)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    Database_close(conn);
    exit(EXIT_FAILURE);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    rewind(conn->file);
    fread(&conn->db->max_data, sizeof(int), 1, conn->file);
    fread(&conn->db->max_rows, sizeof(int), 1, conn->file);

    conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);
    for(int i = 0; i < conn->db->max_rows; i++) {

        struct Address *addr = &conn->db->rows[i];

        fread(&addr->id, sizeof(int), 1, conn->file);
        fread(&addr->set, sizeof(int), 1, conn->file);
        addr->name = malloc(conn->db->max_data);
        addr->email = malloc(conn->db->max_data);
        fread(addr->name, conn->db->max_data, 1, conn->file);
        fread(addr->email, conn->db->max_data, 1, conn->file);
    }
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error", NULL);

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error", conn);

    conn->db->rows = NULL;
    
    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    if(!conn->file) die("Failed to open the file", conn);

    return conn;
}

void Database_close(struct Connection *conn)
{   
    if(!conn) return;
    
    if(conn->file) fclose(conn->file);

    if(conn) {
        if(conn->db) {
        if(conn->db->rows) {
            for(int i = 0; i < conn->db->max_rows; i++) {
                free(conn->db->rows[i].email);
                free(conn->db->rows[i].name);
            }
            free(conn->db->rows);
        }
        free(conn->db);
        }
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{   
    int rc = 0;
    rewind(conn->file);
    /*int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to write database.", conn);*/
    fwrite(&conn->db->max_data, sizeof(int), 1, conn->file);
    fwrite(&conn->db->max_rows, sizeof(int), 1, conn->file);

    for(int i = 0; i < conn->db->max_rows; i++) {

        struct Address *addr = &conn->db->rows[i];

        fwrite(&addr->id, sizeof(int), 1, conn->file);
        fwrite(&addr->set, sizeof(int), 1, conn->file);

        fwrite(addr->name, conn->db->max_data, 1, conn->file);
        fwrite(addr->email, conn->db->max_data, 1, conn->file);
    }

    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn, int max_data, int max_rows)
{
    conn->db->max_data = max_data;
    conn->db->max_rows = max_rows;

    conn->db->rows = calloc(max_rows, sizeof(struct Address));
    if(!conn->db->rows) die("Memory error", conn);

    for(int i = 0; i < max_rows; i++) {
        conn->db->rows[i].id = i;
        conn->db->rows[i].set = 0;
        conn->db->rows[i].name = calloc(max_data, 1);
        conn->db->rows[i].email = calloc(max_data, 1);
        if(!conn->db->rows[i].name || !conn->db->rows[i].email)
            die("Memory error", conn);
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first", conn);

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, conn->db->max_data - 1);
    conn->db->rows[id].name[conn->db->max_data - 1] = '\0';
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed", conn);

    res = strncpy(addr->email, email, conn->db->max_data - 1);
    if(!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];
    if(!addr) die("Failed to get Address", conn);
    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}

/*注意action为d时, 由于创建了临时变量addr以覆盖row[id],而结构体内含有指针
  需要先释放掉之前存在dat文件并且被struct database读取的内存. */
void Database_delete(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        free(addr->name);
        free(addr->email);
        addr->name = calloc(conn->db->max_data, 1);
        addr->email = calloc(conn->db->max_data, 1);
        if(!addr->name || !addr->email) die("Memory error", conn);
        addr->set = 0;
    }
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < conn->db->max_rows; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0, max_data = 0, max_rows = 0;

    switch(action) {
        case 'c':
            if(argc != 5) die("USAGE: ex17.exe <dbfile> <action> max_data max_rows", conn);
            else {
                max_data = atoi(argv[3]);
                max_rows = atoi(argv[4]);
            }
            Database_create(conn, max_data, max_rows);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get", conn);
            if(argc > 3) {
                id = atoi(argv[3]);
            }
            if(id >= conn->db->max_rows) die("There's not that many records.", conn);
            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set", conn);
            if(argc > 3) {
                id = atoi(argv[3]);
            }
            if(id >= conn->db->max_rows) die("There's not that many records.", conn);
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete", conn);
            if(argc > 3) {
                id = atoi(argv[3]);
            }
            if(id >= conn->db->max_rows) die("There's not that many records.", conn);
            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
    }

    Database_close(conn);

    return 0;
}