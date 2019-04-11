/**
 * rt-data
 * Copyright (C) 2019 Guillem Castro
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/random.h>

#define DEVICE_NAME "stubdevice"
#define CLASS_NAME "stub"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Guillem Castro");
MODULE_DESCRIPTION("Stub char device");
MODULE_VERSION("0.1");

static int majorNumber;
static struct class* stubClass = NULL;
static struct device* stubDevice = NULL;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};

static int __init stub_init(void) {
    printk(KERN_INFO "StubDevice: Initializing the Stub Device\n");

    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber < 0) {
        printk(KERN_ALERT "Stub Device failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "StubDevice: registered correctly with major number %d\n", majorNumber);

    stubClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(stubClass)) {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(stubClass);
    }
    printk(KERN_INFO "StubDevice: device class registered correctly");

    stubDevice = device_create(stubClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(stubDevice)) {
        class_destroy(stubClass);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(stubDevice);
    }
    printk(KERN_INFO "StubDevice: device initialized!");
    return 0;
}

static void __exit stub_exit(void) {
    device_destroy(stubClass, MKDEV(majorNumber, 0));
    class_unregister(stubClass);
    class_destroy(stubClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "StubDevice: device destroyed!");
}

static int dev_open(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "StubDevice: Device has been opened\n");
   return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int error_count = 0, count = 0;
    char buff[50];
    int num;
    if(*offset == 0) {
        get_random_bytes(&num, sizeof(num));
        num = num % 1024; // Simulate a random 10-bit number
        if (num < 0) {
            num *= -1;
        }
        count = snprintf(buff, 50, "%d", num);
        if (len < count) {
            return 0;
        }
        error_count = copy_to_user(buffer, buff, count);
        if (error_count == 0) {
            (*offset) += count;
            printk(KERN_INFO "StubDevice: sent number %d to the user", num);
            return (count);
        }
        else {
            printk(KERN_INFO "StubDevice: Failed to send number %d to the user", num);
            return -EFAULT;
        }
    }
    else {
        return 0;
    }
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "StubDevice: Device successfully closed\n");
   return 0;
}

module_init(stub_init);
module_exit(stub_exit);