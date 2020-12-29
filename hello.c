#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/slab.h>

#include <linux/ktime.h>

struct my_list_head {
struct my_list_head *next;
ktime_t time;
};


MODULE_AUTHOR("Yushchenko Yevhenii <>");
MODULE_DESCRIPTION("Lab №7");
MODULE_LICENSE("Dual BSD/GPL");

static struct my_list_head *header;


static uint times;
module_param(times, uint, 0444);
MODULE_PARM_DESC(times, "The amount of times to print hello world");

static int __init hello(void)
{
uint i;

struct my_list_head *first_var, *second_var;
pr_info("times: %d\n", times);

if (times == 0) {
	pr_warn("The parameter is 0 \n");
} else if (times >= 5 && times <= 10) {
	pr_warn("The parameter is between 5 and 10 \n");
} 
BUG_ON (times > 10);


header = kmalloc(sizeof(struct my_list_head *), GFP_KERNEL);
first_var = header;

for (i = 0; i < times; i++) {
	if ( i == 7){ first_var = NULL; }
	first_var->next = kmalloc(sizeof(struct my_list_head), GFP_KERNEL);
	first_var->time = ktime_get();
	pr_info("Hello World!\n");
	second_var = first_var;
	first_var = first_var->next;
	
}
if (times != 0) {
	kfree(second_var->next);
	second_var->next = NULL;
}

return 0;
}


static void __exit hello_exit(void)
{
struct my_list_head *var;

while (header != NULL && times != 0) {
	var = header;
	pr_info("Time : %lld", var->time);
	header = var->next;
	kfree(var);
}

if (times == 0)
	pr_info("Time is 0 because print wasn't used\n");

pr_info("");
}


module_init(hello);
module_exit(hello_exit);
