#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>


#define BUFFER_LENGTH       32


static struct proc_dir_entry *proc_entry;
static char buffer[BUFFER_LENGTH];

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "lcd_display: write()\n");

    if ( copy_from_user(buffer, buf, len ))
        return -EFAULT;
    else{
        //llamar a la python shit
        printk("lcd_display: se va a imprimir: %s",buffer);
        char cmd_path[] = "/usr/bin/lcdwriter";
        char* cmd_argv[] = {cmd_path,buffer,NULL};
        char* cmd_envp[] = {"HOME=/", "PATH=/sbin:/bin:/usr/bin", NULL};
        int result = call_usermodehelper(cmd_path, cmd_argv, cmd_envp, UMH_WAIT_PROC);
        printk(KERN_DEBUG "test driver init exec! there result of call_usermodehelper is %d\n", result);
        return len;
    }
        
}

static const struct file_operations proc_entry_fops = {
    .write = my_write,    
};

int display_init(void) /* Constructor */
{
    proc_entry = proc_create( "lcd_display", 0666, NULL, &proc_entry_fops);
    if (proc_entry == NULL) {
      ret = -ENOMEM;
      vfree(buffer);
      printk(KERN_INFO "lcd_display: No puede crear entrada en /proc..!!\n");
    } else {
      printk(KERN_INFO "lcd_display: Modulo cargado..!!\n");
    }

  return ret;
}


void display_exit(void) /* Destructor */
{
  remove_proc_entry("lcd_display", NULL);
  vfree(buffer);
  printk(KERN_INFO "lcd_display: Modulo descargado..!!\n");
}

module_init(display_init);
module_exit(display_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Codebusters");
MODULE_DESCRIPTION("Driver para manejar un LCD Display 16x2");