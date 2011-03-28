/**
 * @file memory.c
 * @brief Physical memory pages frames management
 * @author Victor Borges
 * @date Mar 23, 2011
 **/

#include <mem/memory.h>
#include <assert.h>
#include <types.h>
#include <errno.h>
#include <clist.h>

#define PAGE_ALIGN_INF(val) 									\
	((unsigned)(val) & (~(PAGE_SIZE-1)))
	
#define PAGE_ALIGN_SUP(val) 									\
	((((unsigned)(val)-1) & (~((unsigned int)PAGE_SIZE - 1))) 	\
		+ (unsigned int)PAGE_SIZE)

/**
 * The corresponding memory address shift
 * @note 4kB = 2^12
 **/
#define PAGE_SHIFT		12

/** 
 * The corresponding page memory mask 
 **/
#define PAGE_MASK  		((1<<12) - 1)

/** 
 * The physical page frame descriptor
 **/
struct ppage
{
	paddr 		ppaddr;			/**< The physical page address */
	count_t 	ref;			/**< The reference count */
	struct ppage *prev;			/**< Previous page frame */
	struct ppage *next;			/**< Next page frame */
};

/**
 * Physical pages frames types for memory mapping
 **/ 
typedef enum 
{
	PPAGE_RESERVED,		/**< First page frame in memory */
	PPAGE_FREE,			/**< Free memory page */
	PPAGE_USED,			/**< Used memory page */
	PPAGE_KERNEL,		/**< Kernel memory page */
	PPAGE_HWMAP			/**< BIOS mapping */
} ppage_type;

#define PPAGE_DESCR_SIZE 	sizeof(struct ppage)
#define PPAGE_DESCR_ARRAY	((paddr)(&__e_kernel))

/**
 * Begin and end of kernel code
 **/
extern char __b_kernel, __e_kernel;

static struct ppage * ppage_descr_array;

static struct ppage * free_ppages;

static struct ppage * used_ppages;

static count_t ppage_total, ppage_used;

static paddr pbase, ptop;

result memory_setup_ppages (size_t mem_size, paddr* kbase, paddr* ktop)
{
	struct ppage* ppage;
	paddr		  ppaddr;
	
	mem_size = PAGE_ALIGN_INF(mem_size);
	
	free_ppages = used_ppages = NULL;
	ppage_total = ppage_used = 0;
	
	/* Calculate kernel boundaries */
	*kbase = PAGE_ALIGN_INF((paddr)&__b_kernel);
	*ktop = PAGE_ALIGN_SUP(PPAGE_DESCR_ARRAY + (mem_size >> PAGE_SHIFT)*PPAGE_DESCR_SIZE);
	if (*ktop > mem_size)
		return ENOMEM;
		
	/* Initialize some global variables */
	pbase = PAGE_SIZE;
	ptop = mem_size;
	ppage_descr_array = (struct ppage *)PPAGE_DESCR_ARRAY; 
	
	/* Mapping of physical memory */
	for (ppaddr = 0, ppage = ppage_descr_array;
		ppaddr < ptop; ppaddr += PAGE_SIZE, ppage++)
	{
		ppage_type type;
		
		ppage->ppaddr = ppaddr;
		
		if (ppaddr < pbase)
			type = PPAGE_RESERVED;
		else if (ppaddr < BIOS_VIDEO_START)
			type = PPAGE_FREE;
		else if (ppaddr < BIOS_VIDEO_END)
			type = PPAGE_HWMAP;
		else if (ppaddr < *kbase)
			type = PPAGE_FREE;
		else if (ppaddr < *ktop)
			type = PPAGE_KERNEL;
		else
			type = PPAGE_FREE;
			
		ppage_total++;
		
		switch (type)
		{
			case PPAGE_FREE:
				ppage->ref = 0;
				list_push_front(ppage, free_ppages);
				break;
			case PPAGE_KERNEL:
			case PPAGE_HWMAP:
			case PPAGE_USED:
				ppage->ref = 1;
				list_push_front(ppage, used_ppages);
				ppage_used++;
				break;
			case PPAGE_RESERVED:
				break;
		}
	}
	
	return OK;
}

void memory_ppages_status (count_t * total_pg, count_t * used_pg)
{
	*total_pg = ppage_total;
	*used_pg  = ppage_used;
}

paddr memory_new_ppage()
{
	struct ppage * ppage;
	
	if (!free_ppages)
	{
		errno = ENOMEM;
		return (paddr)NULL;
	}
	
	ppage = list_pop_front(free_ppages);
	
	assert(ppage->ref == 0);
	
	ppage->ref++;
	
	list_push_back(ppage, used_ppages);
	ppage_used++;
	
	return ppage->ppaddr;
}

inline static struct ppage * ppage_at_paddr (paddr ppaddr)
{
	if (ppaddr & PAGE_MASK)
		return NULL;
		
	if ((ppaddr < pbase) || (ppaddr >= ptop))
		return NULL;
	
	return ppage_descr_array + (ppaddr >> PAGE_SHIFT);
}

result memory_incref_ppage (paddr ppaddr)
{
	struct ppage * ppage = ppage_at_paddr (ppaddr);
	
	if (!ppage)
		return EINVAL;
		
	ppage->ref++;
	
	if (ppage->ref == 1)
	{
		list_remove(ppage, free_ppages);
		list_push_back(ppage, used_ppages);
		ppage_used++;
		return EPPAGEREF;
	}
	
	return OK;
}

result memory_decref_ppage (paddr ppaddr)
{
	struct ppage * ppage = ppage_at_paddr (ppaddr);
	
	if (!ppage)
		return EINVAL;
		
	if (ppage->ref <= 0)
		return EINVAL;
		
	ppage->ref--;
	
	if (ppage->ref <= 0)
	{
		list_remove(ppage, used_ppages);
		list_push_back(ppage, free_ppages);
		ppage_used--;
		return EPPAGEREF;
	}

	return OK;
}
