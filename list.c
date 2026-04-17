#include "list.h"

struct _Node {
    void *info;
    struct _Node *next;
};
typedef struct _Node Node;

struct _List {
    Node *first;
    Node *last;
    int size;
};

List *list_new() {
    List *l = (List *)malloc(sizeof(List));
    if (!l) return NULL;
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
}

Bool list_isEmpty(const List *pl) {
    if (!pl || pl->size == 0) return TRUE;
    return FALSE;
}

Status list_pushFront(List *pl, const void *e) {
    Node *n;
    if (!pl || !e) return ERROR;
    n = (Node *)malloc(sizeof(Node));
    if (!n) return ERROR;
    
    n->info = (void *)e;
    n->next = pl->first;
    pl->first = n;
    
    if (pl->size == 0) pl->last = n;
    pl->size++;
    return OK;
}

Status list_pushBack(List *pl, const void *e) {
    Node *n;
    if (!pl || !e) return ERROR;
    n = (Node *)malloc(sizeof(Node));
    if (!n) return ERROR;
    
    n->info = (void *)e;
    n->next = NULL;
    
    if (pl->size == 0) {
        pl->first = n;
    } else {
        pl->last->next = n;
    }
    pl->last = n;
    pl->size++;
    return OK;
}

void *list_popFront(List *pl) {
    Node *n;
    void *e;
    if (!pl || list_isEmpty(pl)) return NULL;
    
    n = pl->first;
    e = n->info;
    pl->first = n->next;
    
    if (pl->size == 1) pl->last = NULL;
    pl->size--;
    free(n);
    return e;
}

void *list_popBack(List *pl) {
    Node *n, *prev = NULL;
    void *e;
    if (!pl || list_isEmpty(pl)) return NULL;
    
    n = pl->last;
    e = n->info;
    
    if (pl->size == 1) {
        pl->first = NULL;
        pl->last = NULL;
    } else {
        prev = pl->first;
        while (prev->next != pl->last) {
            prev = prev->next;
        }
        prev->next = NULL;
        pl->last = prev;
    }
    pl->size--;
    free(n);
    return e;
}

void *list_getFront(List *pl) {
    if (!pl || list_isEmpty(pl)) return NULL;
    return pl->first->info;
}

void *list_getBack(List *pl) {
    if (!pl || list_isEmpty(pl)) return NULL;
    return pl->last->info;
}

void list_free(List *pl) {
    if (!pl) return;
    while (!list_isEmpty(pl)) {
        list_popFront(pl);
    }
    free(pl);
}

int list_size(const List *pl) {
    if (!pl) return -1;
    return pl->size;
}

int list_print(FILE *fp, const List *pl, p_list_ele_print f) {
    Node *n;
    int count = 0, res;
    if (!fp || !pl || !f) return -1;
    
    for (n = pl->first; n != NULL; n = n->next) {
        res = f(fp, n->info);
        if (res < 0) return -1;
        count += res;
        fprintf(fp, " ");
    }
    return count;
}