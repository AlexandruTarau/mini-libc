// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	// If the list is empty, initialize it
	if (mem_list_num_items() == 0) {
		mem_list_init();
	}

	void *res = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	// If memory mapping didn't fail, add it to the list
	if (res != MAP_FAILED) {
		mem_list_add(res, size);
		return res;
	}

	return NULL;
}

void *calloc(size_t nmemb, size_t size)
{
	// If the list is empty, initialize it
	if (mem_list_num_items() == 0) {
		mem_list_init();
	}

	size_t total_size = nmemb * size;
	void *res = malloc(total_size);

	// If memory allocation didn't fail, add it to the list and set every byte to 0
	if (res) {
		mem_list_add(res, total_size);
		memset(res, 0, total_size);
	}

	return res;
}

void free(void *ptr)
{
	// If the pointer isn't NULL, search it in the list, remove it and unmap the memory
	if (ptr) {
		struct mem_list *item = mem_list_find(ptr);

		if (item) {
			munmap(item->start, item->len);
			mem_list_del(item->start);
		}
	}

	ptr = NULL;
}

void *realloc(void *ptr, size_t size)
{
	void *res;

	// If the pointer is NULL, allocate the memory and add it to the list
	if (!ptr) {
		res = malloc(size);

		if (res) {
			mem_list_add(res, size);
		}
		return res;

	// Else if the size is 0, free the memory
	} else if (size == 0) {
		free(ptr);

	// Else remap the memory with the new size
	} else {
		res = mremap(ptr, sizeof(ptr), size, MREMAP_MAYMOVE);

		// If remapping didn't fail, update the list item with the new size and address
		if (res != MAP_FAILED) {
			struct mem_list *item = mem_list_find(ptr);
			item->len = size;
			item->start = res;
			return res;
		}
	}

	return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	// Check for overflow
	if (nmemb > 0 && size > 0 && nmemb > __INT_MAX__ / size) {
		return NULL;
	}

	size_t total_size = nmemb * size;

	void *res = realloc(ptr, total_size);

	if (res) {
		struct mem_list *item = mem_list_find(ptr);
		item->len = total_size;
		item->start = res;
	}

	return res;
}
