/* SAMPLE DRIVER */


#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/usb.h>

#define USB_VENDOR_ID 0xabcd
#define USB_PRODUCT_ID 0x2233

struct usb_class_driver usb_cd;

static int usb_drv_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	struct usb_host_interface *interface_desc;
	struct usb_endpoint_descriptor *endpoint;
	int ret;
	
		interface_desc = interface->cur_altsetting;

		printk(KERN_INFO "USB info %d now probed: (%04X: %04)\n",interface_desc->desc.bInterfaceNumber, id->idVendor,id->idProduct);
		printk(KERN_INFO "ID->bNumEnPoints : %02X\n",interface_desc->desc.bNumEndpoints);
		ret =usb_register_dev(interface,&usb_cd);
		
		if(ret)
		{
			printk(KERN_INFO "Not able to get minor number.. \n");
		}
		else
		{
			printk(KERN_INFO "minor number=%d\n", interface->minor);
		}
	return 0;
}

static void usb_drv_disconnect(struct usb_interface *interface)
{
	
	printk(KERN_INFO " USB device disconnected\n");
	usb_deregister_dev(interface,&usb_cd);

}



static struct usb_device_id usb_drv_table[] = {
	{
		USB_DEVICE(USB_VENDOR_ID,USB_PRODUCT_ID) 
	},
	{}

};

MODULE_DEVICE_TABLE(usb, usb_drv_table);

static struct usb_driver usb_drv_struct = {

		.name 		= "Sample USB driver",
		.probe 		= usb_drv_probe,
		.disconnect	= usb_drv_disconnect,
		.id_table	= usb_drv_table,
};





static int __init usb_test_init(void)
{

	printk(KERN_INFO "Register the usb driver with the usb  subsystem\n");
	usb_register(&usb_drv_struct);
	return 0;
}


static void __exit usb_test_exit(void)
{

	printk(KERN_INFO "Exited the usb driver with the usb  subsystem\n");
	usb_deregister(&usb_drv_struct);

}




module_init(usb_test_init);
module_exit(usb_test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Santhosh");
MODULE_DESCRIPTION("USB test driver");











