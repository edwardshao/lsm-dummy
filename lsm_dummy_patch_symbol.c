#include <linux/lsm_hooks.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/uaccess.h>
#include <linux/kallsyms.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Edward Shao <laface.tw@gmail.com>");
MODULE_DESCRIPTION("Dummy LSM module");

#define DEFAULT_SECURITY_HOOK_HEADS_NAME "security_hook_heads"
unsigned long addr_sec_hook_heads;
static void **p_addr_sec_hook_heads = NULL;
static struct security_hook_heads my_security_hook_heads;
#define MY_LSM_HOOK_INIT(HEAD, HOOK) \
	{ .head = &my_security_hook_heads.HEAD, .hook = { .HEAD = HOOK } }

static int dummy_path_mkdir(struct path *dir, struct dentry *dentry,
			       umode_t mode)
{
	printk(KERN_DEBUG "mkdir: %s/%s\n", dir->dentry->d_iname, dentry->d_iname);
	return 0;
}

static struct security_hook_list dummy_hooks[] = {
	MY_LSM_HOOK_INIT(path_mkdir, dummy_path_mkdir),
};

static int __init lsm_dummy_init(void)
{
	printk(KERN_DEBUG "dummy lsm init\n");

	addr_sec_hook_heads = kallsyms_lookup_name(DEFAULT_SECURITY_HOOK_HEADS_NAME);
	printk(KERN_DEBUG "addr = %p\n", addr_sec_hook_heads);
//	p_addr_sec_hook_heads = (void **)addr_sec_hook_heads;
//	my_security_hook_heads = *((struct security_hook_heads *)*p_addr_sec_hook_heads);

//	security_add_hooks(dummy_hooks, ARRAY_SIZE(dummy_hooks));

	return 0;
}

static void __exit lsm_dummy_exit(void)
{
//	security_delete_hooks(dummy_hooks, ARRAY_SIZE(dummy_hooks));
	printk(KERN_DEBUG "dummy lsm exit\n");
}

module_init(lsm_dummy_init);
module_exit(lsm_dummy_exit);
