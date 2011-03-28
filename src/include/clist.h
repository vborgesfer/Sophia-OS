/**
 * @file clist.h
 * @brief Circulars lists implementation based on macros
 * @author Victor Borges
 * @date Mar 23, 2011
 * @warning All structures received in parameter need to have a
 * 		prev and next field.
 */
 
#include <stddef.h>
 
#define list_init(list) 						\
	((list) = NULL)

#define list_is_empty(list) 					\
	((list) == NULL)
	
#define list_front(list)						\
	(list)
	
#define list_back(list)							\
	((list) ? ((list)->prev) : NULL)

#define list_add_first_item(item, list)			\
({												\
	(item)->next = (item)->prev = (item);		\
	(list) = (item);							\
})
		
#define list_add(item, list)					\
({												\
	(list)->prev->next = (item);				\
	(item)->prev = (list)->prev;				\
	(list)->prev = (item);						\
	(item)->next = (list);						\
})

#define list_push_front(item, list)				\
({												\
	if (list)									\
	{											\
		list_add(item, list);					\
		(list) = (item);						\
	}											\
	else 										\
		list_add_first_item(item, list);		\
})

#define list_push_back(item, list)				\
({												\
	if (list)									\
		list_add(item, list);					\
	else 										\
		list_add_first_item(item, list);		\
})

#define list_remove(item, list)									\
({																\
	if (((item)->next == (item)) && ((item)->prev == (item)))	\
		(item)->next = (item)->prev = (list) = NULL; 			\
	else 														\
	{															\
		(item)->prev->next = (item)->next;						\
		(item)->next->prev = (item)->prev;						\
		if ((item) == (list))									\
			(list) = (item)->next;								\
		(item)->prev = (item)->next = NULL;						\
	}															\
})

#define list_count(list)						\
({												\
	int n;										\
	typeof(list) item;							\
	for ( n = 0, (item) = (list); 				\
		(item) && (!n || ((item) != (list)));	\
		n++, (item) = ((item)->next) );			\
	n;											\
})

#define list_pop_front(list)					\
({												\
	typeof(list) item = (list);					\
	list_remove(item, list);					\
	item;										\
})

#define list_pop_back(list)						\
({												\
	typeof(list) item = list_back(list);		\
	list_remove(item, list);					\
	item;										\
})

#define list_foreach(index, item, list)				\
	for (index = 0, (item) = (list);				\
		(item) && (!index || ((item) != (list)));	\
		index++; (item) = (item)->next)				\

