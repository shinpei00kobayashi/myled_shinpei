/*!
[myled_shinpei]
Copyright (c) [2022][Kobayashi Shinpei]

This software is released under the  [GNU GENERAL PUBLIC LICNSE Ver3.0]

see[http://www.gnu.org/licenses/]

*/




#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/io.h>
#include<linux/delay.h>
MODULE_AUTHOR("Shinpei Kobayashi");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");





static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;







static ssize_t led_write(struct file* flip, const char* buf, size_t count,loff_t* pos)

{
	char c;
	int  i,t;
	if(copy_from_user(&c,buf,sizeof(char)))
		return -EFAULT;

	if(c == '0'){ // all off
		gpio_base[10] = 1 << 25;//gpiobase[10]=出力オフ。1<<25→pinの指定
		gpio_base[10] = 1 << 15;
		gpio_base[10] = 1 << 10;
		}


	else if(c == '1'){ // all on
		gpio_base[7]  = 1 << 25;//gpiobase[7]=出力
		gpio_base[7]  = 1 << 15;
		gpio_base[7]  = 1 << 10;
		}





	else if(c == '2'){ //crouch start

		t = 1;
		gpio_base[10] = 1 << 25;
		gpio_base[10] = 1 << 15;
		gpio_base[10] = 1 << 10;


		ssleep(t);
		gpio_base[7] = 1 << 25;//3
		
		ssleep(t);
		gpio_base[10]= 1 << 25;//2
		gpio_base[7] = 1 << 15;//2
		
		ssleep(t);
		gpio_base[10]= 1 << 15;//1
		gpio_base[7] = 1 << 10;//1
		
		ssleep(t);
		gpio_base[7] = 1 << 25;//go
		gpio_base[7] = 1 << 15;//go
		
		t = 3;
		ssleep(t);
		gpio_base[10]= 1 << 25;
		gpio_base[10]= 1 << 15;
		gpio_base[10]= 1 << 10;
		}






	else if(c == '3'){ //wave
		t = 200;
		gpio_base[10]= 1 << 25;
		gpio_base[10]= 1 << 15;
		gpio_base[10]= 1 << 10;

	for(i = 1; i <= 7; i++){
		
		gpio_base[7] = 1 << 25;
		msleep(t);
		gpio_base[10]= 1 << 25;
		gpio_base[7] = 1 << 15;
		msleep(t);
		gpio_base[10]= 1 << 15;
		gpio_base[7] = 1 << 10;
		msleep(t);
		gpio_base[10]= 1 << 10;
		gpio_base[7] = 1 << 15;
		msleep(t);
		gpio_base[10]= 1 << 15;
		gpio_base[7] = 1 << 25;
			
		}
		gpio_base[10]= 1 << 25;
		}






	else if(c == '4'){ //ブレーキランプ５回愛してるのサイン
		
		t = 1;
		gpio_base[10]= 1 << 25;
		gpio_base[10]= 1 << 15;
		gpio_base[10]= 1 << 10;

	for(i = 1;i <= 5;i++){

		gpio_base[7]= 1 << 25;
		gpio_base[7]= 1 << 10;
 

		if(i == 1){
		printk(KERN_DEFAULT"ア\n");}
		else if(i == 2){
		printk(KERN_DEFAULT"イ\n");}
		else if(i == 3){
		printk(KERN_DEFAULT"シ\n");}
		else if(i == 4){
		printk(KERN_DEFAULT"テ\n");}
		else if(i == 5){
		printk(KERN_DEFAULT"ル\n");}

		ssleep(t);
		gpio_base[10]= 1 << 25;
		gpio_base[10]= 1 << 10;
		ssleep(t);
		}
	}






	return 1;
}









static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write
};








static int __init init_mod(void)
{
	int retval;
	gpio_base = ioremap_nocache(0x3f200000, 0xA0);

	const u32 led     = 25;
	const u32 index   = led/10;
	const u32 shift   = (led%10)*3;
	const u32 mask    = ~(0x7 << shift);
	gpio_base[index]  = (gpio_base[index] & mask) | (0x1 << shift);
        
	const u32 led2    = 10;
	const u32 index2  = led2/10;
	const u32 shift2  = (led2%10)*3;
	const u32 mask2   = ~(0x7 << shift2);
	gpio_base[index2] = (gpio_base[index2] & mask2) | (0x1 << shift2);

	const u32 led3    = 15;
	const u32 index3  = led3/10;
	const u32 shift3  = (led3%10)*3;
	const u32 mask3   = ~(0x7 << shift3);
	gpio_base[index3] = (gpio_base[index3] & mask3) | (0x1 << shift3);


	retval = alloc_chrdev_region(&dev, 0, 1, "myled");

	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}







	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	cdv.owner = THIS_MODULE;
	retval = cdev_add(&cdv, dev,1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d,minor:%d",MAJOR(dev),MINOR(dev));
		return retval;
	}







	cls =class_create(THIS_MODULE,"myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));
	return 0;
	}






static void __exit cleanup_mod(void)
{

		cdev_del(&cdv);
		device_destroy(cls, dev);
		class_destroy(cls);
		unregister_chrdev_region(dev, 1);
	        printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__, MAJOR(dev));
                iounmap(gpio_base);

}


module_init(init_mod);
module_exit(cleanup_mod);

