/* 
 * @FILENAME    cb-db.c
 * @DESCRIPTION functions about database
 * @AUTHOR      hejiyan
 * @VERSION     0.1
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cb-db.h"

cb_db_dataset Dat;


/* read 1 int from fl */
int _cb_db_read_number(FILE* fl)
{
	int n;
	if (1 == fread(&n, sizeof(int), 1, fl))
		return n;
	return 0;
}

/* encrypt cb_db_item */
void _cb_db_encrypt(cb_db_item* x)
{
	x->time ^= CB_DB_KEY;
	x->money ^= CB_DB_KEY;
	int len = strlen(x->text);
	for (int i = 0; i < len; i++)
	{
		x->text[i] ^= CB_DB_KEY;
	}
}

/* decrypt cb_db_item */
void _cb_db_decrypt(cb_db_item* x)
{
	_cb_db_encrypt(x);
}

/* write 1 int into fl */
void _cb_db_save_number(int n, FILE* fl)
{
	fwrite(&n, sizeof(int), 1, fl);
}

/* read n cb_db_item from fl */
void _cb_db_read_items(cb_db_item* items, int n, FILE* fl)
{
	fread(items, sizeof(cb_db_item), n, fl);
	for (cb_db_item* p = items; p < items + n; p++)
		_cb_db_decrypt(p);
}

/* write n cb_db_item into fl */
void _cb_db_save_items(cb_db_item* items, int n, FILE* fl)
{
	for (cb_db_item* p = items; p < items + n; p++)
		_cb_db_encrypt(p);
	
	fwrite(items, sizeof(cb_db_item), n, fl);
	
	for (cb_db_item* p = items; p < items + n; p++)
		_cb_db_decrypt(p);
}

/* call this first if you want use db */
void cb_db_init()
{
	cb_db_read_db();
}

/* read data file into Dat */
void cb_db_save_db()
{
	FILE* fl = fopen(DATE_FILENAME, "wb");
	if (!fl) printf("Err: can't open " DATE_FILENAME), exit(0);
	_cb_db_save_number(Dat.n, fl);
	for (node* p = Dat.head; p; p = p -> next)
	{
		_cb_db_save_items(p->v, 1, fl);
	}
	fclose(fl);
}

/* save Dat into data file */
void cb_db_read_db()
{
	memset(&Dat, 0, sizeof(cb_db_dataset));
	FILE* fl = fopen(DATE_FILENAME, "rb");
	if (!fl) cb_db_save_db(), fl = fopen(DATE_FILENAME, "rb");
	if (!fl) printf("Err: can't open " DATE_FILENAME), exit(0);

	int n = _cb_db_read_number(fl);
	
	for (int i = 0; i < n; i++)
	{
		cb_db_item* t = (cb_db_item*)malloc(sizeof(cb_db_item));
		_cb_db_read_items(t, 1, fl);
		cb_db_add_item(t);
	}
	fclose(fl);
}

/* add item at the tail of the linklist
void cb_db_add_item_TAIL(const cb_db_item* x)
{
	if (NULL == x) return;
	Dat.n++;
	node* t = (node*)malloc(sizeof(node));
	t->v = (cb_db_item*)x; t->next = NULL;
	if (NULL == Dat.head){
		Dat.head = t;
	} else {
		node* p = Dat.head;
		while(p->next) p = p->next;
		p->next = t;
	}
}
*/

/* add item in the linklist (ACS by `time`, assume the linklist is already ACS) */
void cb_db_add_item(const cb_db_item* x)
{
	if (NULL == x) return;
	Dat.n++;
	node* t = (node*)malloc(sizeof(node));
	t->v = (cb_db_item*)x; t->next= NULL;
	if (NULL == Dat.head)
	{
		Dat.head = t;
	} else 
	{
		node *pre, *cur;
		pre = cur = Dat.head;
		while(cur && cur->v->time < x->time){
			pre = cur;
			cur = cur->next;
		}
		if (cur == Dat.head)
		{
			t->next = cur;
			Dat.head = t;
		}
		else
		{
			t->next = cur;
			pre->next = t;
		}
	}
}

/* del k-th item in the linklist (k = 0,1,...) */
void cb_db_del_item(const int k)
{
	int i = 0;
	node *pre, *cur;
	pre = cur = Dat.head;
	while (cur)
	{
		if (i++ == k) break;	
		pre = cur;
		cur = cur->next;
	}
	if (NULL == cur) return;
	if (cur == Dat.head) Dat.head = cur->next;
	pre->next = cur->next;
	free(cur->v);
	free(cur);
	Dat.n--;
}

/* add item then save database */
void add_item(time_t t, int money, const char* s)
{
	cb_db_item* x = (cb_db_item*)malloc(sizeof(cb_db_item));
	x->time = t; x->money = money;
	strcpy(x->text, s);
	cb_db_add_item(x);
	cb_db_save_db();
}

/* del item then save database */
void del_item(const int k)
{
	cb_db_del_item(k);
	cb_db_save_db();
}

/* init database */
void init_db()
{
	cb_db_init();
}

/* init database */
void save_db()
{
	cb_db_save_db();
}