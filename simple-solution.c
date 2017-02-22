#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

struct birthday {
  int day;
  int month;
  int year;
  char *name; 
  struct list_head list;
};

static LIST_HEAD(birthday_list);

//function is called when the module is being loaded and struct is initialized
int simple_init(void) {
 
  struct birthday *person, *ptr;

  //person 1
  person = kmalloc(sizeof(struct birthday), GFP_KERNEL);
  person->name = "Enrico Elizan"; 
  person->day = 1;
  person->month = 1;
  person->year = 1992;
  INIT_LIST_HEAD(&person->list);
  list_add_tail(&person->list, &birthday_list);

  //person 2
  person = kmalloc(sizeof(struct birthday), GFP_KERNEL);
  person->name = "Sarah"; 	
  person->day = 5;
  person->month = 7;
  person->year = 1964;
  INIT_LIST_HEAD(&person->list);
  list_add_tail(&person->list, &birthday_list);

  //person 3
  person = kmalloc(sizeof(struct birthday), GFP_KERNEL);
  person->name = "John"; 
  person->day = 11;
  person->month = 8;
  person->year = 1990;
  INIT_LIST_HEAD(&person->list);
  list_add_tail(&person->list, &birthday_list);

  //person 4
  person = kmalloc(sizeof(struct birthday), GFP_KERNEL);
  person->name = "Mick"; 
  person->day = 30;
  person->month = 5;
  person->year = 1992;
  INIT_LIST_HEAD(&person->list);
  list_add_tail(&person->list, &birthday_list);

  //person 5
  person = kmalloc(sizeof(struct birthday), GFP_KERNEL);
  person->name = "David"; 
  person->day = 19;
  person->month = 6;
  person->year = 1982;
  INIT_LIST_HEAD(&person->list);
  list_add_tail(&person->list, &birthday_list);

  printk(KERN_INFO "Loading Module\n");

  //prints person information
  list_for_each_entry(ptr, &birthday_list, list) {
    printk(KERN_INFO "Name:%s Birthday - DAY:%d MONTH:%d YEAR:%d\n", ptr->name, ptr->day, ptr->month, ptr->year);
  }

  return 0;
}


//function is called when the module is being removed 
void simple_exit(void) {
  struct birthday *ptr, *next;

  printk(KERN_INFO "Removing Module\n");

  //prints person information that is being removed   
  list_for_each_entry_safe(ptr, next, &birthday_list, list) {
    printk(KERN_INFO "DELETING NAME:%s Brithday - DAY:%d MONTH:%d YEAR:%d\n", ptr->name, ptr->day, ptr->month, ptr->year);
    list_del(&ptr->list);
    kfree(ptr);
  }
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
