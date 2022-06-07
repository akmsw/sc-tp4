#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>


#define BUFFER_LENGTH       32

static dev_t first; 		// Global variable for the first device number
static struct cdev c_dev; 	// Global variable for the character device structure
static struct class *cl; 	// Global variable for the device class

static char buffer[BUFFER_LENGTH];

static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "sensor_kernel: open()\n");
    return 0;
}
static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "sensor_kernel: close()\n");
    return 0;
}

static ssize_t my_read(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "sensor_kernel: read()\n");

    if ( copy_from_user(buffer, buf, len ))
        return -EFAULT;
    else{
        char cmd_path[] = "/usr/bin/sensor_reader";
        char* cmd_argv[] = {cmd_path,buffer,NULL};
        char* cmd_envp[] = {"HOME=/", "PATH=/sbin:/bin:/usr/bin", NULL};
        int result = call_usermodehelper(cmd_path, cmd_argv, cmd_envp, UMH_WAIT_PROC);
        printk(KERN_DEBUG "test driver init exec! there result of call_usermodehelper is %d\n", result);
        return len;
    }
        
}

static struct file_operations pugs_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .write = my_read
};

static int __init drv4_init(void) /* Constructor */
{
    int ret;
    struct device *dev_ret;
    printk(KERN_INFO "sensor_kernel: Registrado exitosamente..!!\n");

    if ((ret = alloc_chrdev_region(&first, 0, 1, "sensor_kernel")) < 0)
    {
        return ret;
    }

    if (IS_ERR(cl = class_create(THIS_MODULE, "sensor_kernel")))
    {
        unregister_chrdev_region(first, 1);
        return PTR_ERR(cl);
    }

    if (IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "sensor_kernel")))
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

static void __exit drv4_exit(void) /* Destructor */
{
    cdev_del(&c_dev);
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    printk(KERN_INFO "sensor_kernel: Desinstalado exitosamente!!\n");
}

module_init(drv4_init);
module_exit(drv4_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Codebusters");
MODULE_DESCRIPTION("Driver para sensor de temperatura y humedad");