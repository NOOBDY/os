#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

MODULE_LICENSE("GPL");

static int jykuo_init(void);
static void jykuo_exit(void);

static int jykuo_init(void) {
  pr_info("hello\n");
  return 0;
}

static void jykuo_exit(void) { pr_info("bye\n"); }

module_init(jykuo_init);
module_exit(jykuo_exit);
