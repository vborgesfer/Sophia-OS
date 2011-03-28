/**
 * @file test.c
 * @brief Some tests
 * @author Victor Borges
 * @date Mar 12, 2011
 */

#include <types.h>
#include <clist.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <mem/memory.h>
#include <io/video.h>
#include <io/bochs.h>

#define MY_PPAGE_SIZE	1022
struct my_ppage
{
	u32	data[MY_PPAGE_SIZE];
	struct my_ppage *prev, *next;
};

void test_ppage(void)
{
	struct my_ppage * ppage_list = NULL, * my_ppage;
	count_t num_alloc = 0, num_free = 0;
	
	count_t totalpg, usedpg;
	
	memory_ppages_status(&totalpg, &usedpg);
	printf("Total pages: %d, used pages initial: %d", totalpg, usedpg);
	
	while ((my_ppage = (struct my_ppage*)memory_new_ppage()) != NULL)
	{
		int i;
		bochs_printf("\nCould allocate %d pages", num_alloc);
		num_alloc++;
		
		for (i = 0; i < MY_PPAGE_SIZE; i++)
			my_ppage->data[i] = (u32)my_ppage;
		
		list_push_back(my_ppage, ppage_list);
	}
	printf("\nCould allocate %d pages", num_alloc);
	
	while ((my_ppage = list_pop_front(ppage_list)) != NULL)
	{
		int i;
		for (i = 0; i < MY_PPAGE_SIZE; i++)
		{
			if (my_ppage->data[i] != (u32)my_ppage)
			{
				printf("\nPage overwriten");
				return;
			}
		}
			
		if (memory_decref_ppage((paddr)my_ppage) != EPPAGEREF)
		{
			printf("\nCannot release page");
			return;
		}
		num_free++;
		bochs_printf("\nCould release %d pages", num_free);
	}
	printf("\nCould free %d pages", num_free);
	
	printf("\nCould allocate %d bytes and could free %d bytes", 
		num_alloc << PAGE_SHIFT, num_free << PAGE_SHIFT);
		
	assert(num_alloc == num_free);
}
