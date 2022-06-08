#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define BUFFER_LENGTH 32

static dev_t first;
static struct cdev c_dev;
static struct class *cl;
static char buffer[BUFFER_LENGTH];

static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "display_driver: open()\n");

    return 0;
}

static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "display_driver: close()\n");

    return 0;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "display_driver: write()\n");

    if (copy_from_user(buffer, buf, len))
        return -EFAULT;
    else
    {
        buffer[len - 1] = '\0';

        char cmd_path[] = "/usr/bin/lcdwriter";
        char *cmd_argv[] = {cmd_path, buffer, NULL};
        char *cmd_envp[] = {"HOME=/", "PATH=/sbin:/bin:/usr/bin", NULL};

        call_usermodehelper(cmd_path, cmd_argv, cmd_envp, UMH_WAIT_PROC);

        memset(buffer, 0, BUFFER_LENGTH);

        return len;
    }
}

static struct file_operations pugs_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .write = my_write
};

static int __init display_driver_init(void)
{
    int ret;

    struct device *dev_ret;

    printk(KERN_INFO "display_driver: registrado exitosamente");

    if ((ret = alloc_chrdev_region(&first, 0, 1, "display_driver")) < 0)
        return ret;

    if (IS_ERR(cl = class_create(THIS_MODULE, "display_driver")))
    {
        unregister_chrdev_region(first, 1);

        return PTR_ERR(cl);
    }

    if (IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "display_driver")))
    {
        class_destroy(cl);

        unregister_chrdev_region(first, 1);

        return PTR_ERR(dev_ret);
    }

    cdev_init(&c_dev, &pugs_fops);

    if ((ret = cdev_add(&c_dev, first, 1)) < 0)
    {
        device_destroy(cl, first);

        class_destroy(cl);

        unregister_chrdev_region(first, 1);

        return ret;
    }

    return 0;
}

static void __exit display_driver_exit(void)
{
    cdev_del(&c_dev);

    device_destroy(cl, first);

    class_destroy(cl);

    unregister_chrdev_region(first, 1);

    printk(KERN_INFO "display_driver: desinstalado exitosamente");
}

module_init(display_driver_init);
module_exit(display_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CodeBusters");
MODULE_DESCRIPTION("Driver para mostrar por un display LCD 16x2 mediciones de un sensor DHT11");