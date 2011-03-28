/**
 * @file memory.c
 * @brief Keyboard management
 * @author Victor Borges
 * @date Mar 15, 2011
 */

struct kb_stream {
	volatile char stream[256];
	unsigned int size;
};

extern struct kb_stream kb_cache;

/**
 * Setup keyboard
 **/
result kb_setup();
