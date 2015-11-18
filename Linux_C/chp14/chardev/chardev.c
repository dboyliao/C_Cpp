#include <linux/kernel.h> 
#include <linux/fs.h>                  
#include <linux/module.h> 
#include <asm/uaccess.h>               
#include <linux/cdev.h>                 
         
static int char_read(struct file *filp,char __user *buffer,size_t,loff_t *);        
static int char_open(struct inode *,struct file *);                                      
static int char_write(struct file *filp,const char __user *buffer,size_t ,loff_t*); 
static int char_release(struct inode *,struct file *);                                   
  
static int device_open_count;                     
static int major;

static const struct file_operations file_ops = { 
.read = char_read, 
.write = char_write, 
.open = char_open, 
.release = char_release, 
}; 
  
static int __init char_init(void) 
{ 
	int value;
	major = 0;
	value = register_chrdev(major, "chardev", &file_ops);
	if (value < 0) {
		printk("無法註冊設備");
		return value;
	}
	if (major == 0) 
		major = value;
	return 0; 
} 
  
static int char_open(struct inode *inode,struct file *file) 
{ 
  if(device_open_count == 0) 
	device_open_count++; 
  else{ 
     printk("設備已經被打開\n"); 
     return -1; 
  } 
  try_module_get(THIS_MODULE); 
  return 0; 
} 
  
static int char_release(struct inode *inode,struct file *file) 
{ 
    device_open_count--; 
    module_put(THIS_MODULE); 
    return 0; 
} 
  
static int char_read(struct file *filp,char __user *buffer,size_t length,loff_t *offset) 
{ 
	if(length < 0)
		return -1;
	else if(length > 12)
		length = 12;

	if(copy_to_user(buffer,"Hello Linux!",length))
		return length;
	return -1;
} 
  
static int char_write(struct file *filp,const char __user  *buffer,size_t length,loff_t *offset) 
{ 
	return 0; 
} 
  
static void __exit module_close(void) 
{ 
	unregister_chrdev(major, "chardev");
} 
  
module_init(char_init); 
module_exit(module_close);
