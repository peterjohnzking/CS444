#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("Says hello.");
MODULE_AUTHOR(“Peter-John King");
MODULE_LICENSE("GPL");


static int module_init_fn(void) {
  /*printk("Hello from the kernel!");*/
  printk("The value at the null pointer is: %ld", *NULL);
  return 0;
}

static void module_exit_fn(void) {
  printk("Goodbye from the kernel!");
}

module_init(module_init_fn);
module_exit(module_exit_fn);
