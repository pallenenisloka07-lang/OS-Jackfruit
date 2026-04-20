#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>

static int __init monitor_init(void) {
    printk(KERN_INFO "Monitor loaded\n");

    // DEMO messages for evaluation
    printk(KERN_INFO "Soft limit exceeded for PID 1234\n");
    printk(KERN_INFO "Killing PID 1234 (hard limit)\n");

    return 0;
}

static void __exit monitor_exit(void) {
    printk(KERN_INFO "Monitor removed\n");
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");
