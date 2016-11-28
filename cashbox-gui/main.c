/* 
 * @FILENAME    main.c
 * @DESCRIPTION the entry of cashbox
 * @AUTHOR      hejiyan
 * @VERSION     0.1
 */
#include "main.h"

extern cb_db_dataset Dat;

int main(int argc, char *argv[])
{
	cb_db_init();
	cb_gui_init(argc, argv);
}
