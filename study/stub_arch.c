#include <net/net_namespace.h>

struct tcp_mib g_tcpmib;
struct net init_net = {
	.dev_base_head = LIST_HEAD_INIT(init_net.dev_base_head),
	.mib = {
		.tcp_statistics = &g_tcpmib
	}
};
EXPORT_SYMBOL(init_net);

//struct net_device g_dev = {
//	.nd_net = { &init_net }
//};

struct nsproxy g_nsproxy = {
	.net_ns = &init_net
};

struct cred g_cred = {
};

struct task_struct g_task = {
	.nsproxy = &g_nsproxy,
	.cred = &g_cred
};

struct thread_info g_thread_info = {
	.task = &g_task
};

// arch/um/include/asm/thread_info.h
struct thread_info *current_thread_info(void)
{
	return &g_thread_info;
}

// arch/um/kernel/um_arch.c
unsigned long uml_physmem;
