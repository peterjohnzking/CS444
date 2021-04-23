#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
int sleep_duration = 10000;
module_param(sleep_duration, int, S_IRUGO);
#define KBD_DATA_REG        0x60    /* I/O port for keyboard data */
#define KBD_CONTROL_REG        0x64 
#define DELAY do { mdelay(1); if (++delay > 10) break; } while(0)

static void disable_keyboard(void)
{
	long delay = 0;
	//wait till the input buffer is empty
	while (inb(KBD_CONTROL_REG) & 0x02)
		DELAY;
	outb(0xAD, KBD_CONTROL_REG);
}

static void enable_keyboard(void)
{
	long delay = 0;
	//wait till the input buffer is empty
	while (inb(KBD_CONTROL_REG) & 0x02)
		DELAY;
	outb(0xAE, KBD_CONTROL_REG);
}

static int test_kbd_disable_init(void)
{
	pr_info("%s: In init\n", __func__);
	disable_keyboard();
	msleep(sleep_duration);
	enable_keyboard();
	return 0;
}

static void test_kbd_disable_exit(void)
{
        pr_info("%s: In exit\n", __func__);
}

module_init(test_kbd_disable_init);
module_exit(test_kbd_disable_exit);