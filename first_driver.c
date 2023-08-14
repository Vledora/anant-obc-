#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

static int __init initial(void) 
{
    printk(KERN_INFO "hello world");

    return 0;
}

static void __exit end(void) 
{
    printk(KERN_INFO "goodbye world");
}

module_init(initial);
module_exit(end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kartik");
MODULE_DESCRIPTION("first driver");
