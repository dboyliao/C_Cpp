#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

#undef unix
struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = __stringify(KBUILD_MODNAME),
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0x65b4e613, "struct_module" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0xd7474566, "__copy_to_user_ll" },
	{ 0x49e79940, "__cond_resched" },
	{ 0x9925ce9c, "__might_sleep" },
	{ 0x8351fe8e, "wake_up_process" },
	{ 0x1b7d4074, "printk" },
	{ 0x6506d836, "register_chrdev" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

