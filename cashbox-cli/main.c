/* 
 * @FILENAME    main.c
 * @DESCRIPTION the entry of cashbox
 * @AUTHOR      hejiyan
 * @VERSION     0.1
 */
#include "main.h"

extern cb_db_dataset Dat;

void print_db()
{
	char time_str[MAX_TEXT_LEN];
	int i = 0;
	int total = 0;
	
	puts("******************************");

	printf("* [id]        [time]        [money]   [text]\n");
	for (node* p = Dat.head; p ; p = p -> next)
	{
		time_to_str(p->v->time, time_str);
		printf("* [%2d] %s %d %s\n", i++, time_str, p->v->money, p->v->text);

		total += p->v->money;
	}

	printf("* Items: %d, Total money: %d.\n", Dat.n, total);
	puts("******************************");

}

void print_long_tips()
{
	puts("[cashbox]Welcome!");
	puts("[cashbox]Enter `p` to show the cashbox;");
	puts("[cashbox]Enter `a` to add an item (with current time);");
	puts("[cashbox]Enter `t` to add an item (with custom time);");
	puts("[cashbox]Enter `d` to delete an item;");
	puts("[cashbox]Enter `h` to view help text;");
	puts("[cashbox]Enter `q` to quit.");
}

void print_tips()
{
	puts("[cashbox]Enter command [p|a|t|d|h|q]:");
}

int main()
{
	cb_db_init();
	char c;
	int money, id;
	time_t t;
	char text[MAX_TEXT_LEN];
	print_long_tips();
	while((c = getchar()) != 'q')
	{
		switch(c)
		{
			case 'p':
				print_db();
				print_tips();
				break;
			case 'a':
				printf("[cashbox.add]Enter money:");
				scanf("%d", &money);
				printf("[cashbox.add]Enter text:");
				scanf("%s", text);
				
				add_item(get_cur_time(), money, text);
				print_db();
				print_tips();
				break;
			case 't':
				printf("[cashbox.add]Enter time(eg. 1998/04/11-12:34:56) :");
				scanf("%s", text);
				t = str_to_time(text);
				
				printf("[cashbox.add]Enter money:");
				scanf("%d", &money);
				printf("[cashbox.add]Enter text:");
				scanf("%s", text);

				add_item(t, money, text);
				print_db();
				print_tips();
				break;
			case 'd':
				printf("[cashbox.del]Enter the id :");
				scanf("%d", &id);
				
				del_item(id);
				print_db();
				print_tips();
				break;
			case 'h':
				print_long_tips();
				break;
		}
	}
	return 0;
}