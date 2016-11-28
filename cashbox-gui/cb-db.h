/* 
 * @FILENAME    cb-db.h
 * @DESCRIPTION headers for cb-db.c
 * @AUTHOR      hejiyan
 * @VERSION     0.1
 */

#ifndef _CB_DB_
#define _CB_DB_

#define MAX_TEXT_LEN   100       /* max len of text in cb_db_item */
#define DATE_FILENAME  "db.dat"  /* filename of db file           */

/* WARNING: OLD DATA CANT BE DECRYPTED BY NEW KEY*/

#define CB_DB_KEY      2333333   /* the key for encrypt & decrypt */

typedef struct cb_db_item{
	time_t time;
	int money;
	char text[MAX_TEXT_LEN];
} cb_db_item;


typedef struct node{
	cb_db_item* v;
	struct node* next;
} node;

typedef struct cb_db_dataset{
	int n;
	node* head;
} cb_db_dataset;

int  _cb_db_read_number(FILE* fl);
void _cb_db_encrypt(cb_db_item* x);
void _cb_db_decrypt(cb_db_item* x);
void _cb_db_save_number(int n, FILE* fl);
void _cb_db_read_items(cb_db_item* items, int n, FILE* fl);
void _cb_db_save_items(cb_db_item* items, int n, FILE* fl);


void cb_db_init();
void cb_db_read_db();
void cb_db_save_db();
void cb_db_add_item(const cb_db_item* x);
void cb_db_del_item(const int k);

void add_item(time_t t, int money, const char* s);
void del_item(const int k);
void init_db();
void save_db();
#endif
