#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

#define NUM_OF_PERSON 5

// birthday struct
typedef struct birthday {
    int name;
	int day;
	int month;
	int year;
	struct list_head list;
}birthday;

// declare & initialize head of linked list
static LIST_HEAD(birthday_list);

// function called when module loaded
int birthdayList_init(void)
{
	// declarations
	struct birthday *person;
	struct birthday *ptr;
	int i = 0;
	
	printk(KERN_INFO "Loading Module\n");

	for(i = 0; i < NUM_OF_PERSON; i++)
	{
		// request malloc to kernel
		person = kmalloc(sizeof(*person), GFP_KERNEL);
	   
		// assign value to struct
        person->name = i+1;
		person->day = i+1;
		person->month = i+1;
		person->year = i+1;
	   
		// initialize list in struct
		INIT_LIST_HEAD(&person->list);
	   
		// add struct to list tail
		list_add_tail(&person->list, &birthday_list);
	}

	printk(KERN_INFO "Display the list:\n");

	// traverse list and print
	list_for_each_entry(ptr, &birthday_list, list)
	{
		printk(KERN_INFO "Person: %d, day: %d, month: %d, year: %d\n",
                ptr->name,
				ptr->day,
				ptr->month,
				ptr->year);
	}

	printk(KERN_INFO "Display complete\n");

			return 0;
}

// function called when module removed
void birthdayList_exit(void)
{
	birthday *ptr, *next;
	printk(KERN_INFO "Removing Module\n");

	// traverse list and remove allocated memory
	list_for_each_entry_safe(ptr, next, &birthday_list, list)
	{
		printk(KERN_INFO "Removing – Person: %d, day: %d, month: %d, year: %d\n",
                ptr->name,
				ptr->day,
				ptr->month,
				ptr->year);
		list_del(&ptr->list);
		kfree(ptr);
	}

	printk(KERN_INFO "Memory removal complete\n");
}

// register module entry and exit point macros
module_init( birthdayList_init );
module_exit( birthdayList_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("BirthdayList Module");
MODULE_AUTHOR("wesley.tomlinson");

