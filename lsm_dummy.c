#include <linux/lsm_hooks.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Edward Shao <laface.tw@gmail.com>");
MODULE_DESCRIPTION("Dummy LSM module");

static int dummy_path_mkdir(struct path *dir, struct dentry *dentry,
			       umode_t mode)
{
	printk(KERN_DEBUG "mkdir: %s/%s\n", dir->dentry->d_iname, dentry->d_iname);
	return 0;
}

static struct security_hook_list dummy_hooks[] = {
	LSM_HOOK_INIT(path_mkdir, dummy_path_mkdir),
};

static int __init lsm_dummy_init(void)
{
	printk(KERN_DEBUG "dummy lsm init\n");
	security_add_hooks(dummy_hooks, ARRAY_SIZE(dummy_hooks));

	return 0;
}

static void __exit lsm_dummy_exit(void)
{
	security_delete_hooks(dummy_hooks, ARRAY_SIZE(dummy_hooks));
	printk(KERN_DEBUG "dummy lsm exit\n");
}

module_init(lsm_dummy_init);
module_exit(lsm_dummy_exit);
