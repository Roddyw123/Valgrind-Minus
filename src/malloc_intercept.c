#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <malloc/malloc.h>

static size_t allocated_bytes = 0;

void *malloc(size_t size)
    {
        static void *(*og_malloc)(size_t) = NULL;
        if (!og_malloc)
            {
                og_malloc = dlsym (RTLD_NEXT, "malloc");
            }
        void *ptr = og_malloc (size);
        __sync_fetch_and_add(&allocated_bytes, size);
        fprintf (stderr, "malloc(%zu) -> total: %zu bytes\n", size, allocated_bytes);
        return ptr;
    }

/* Extension: Trivially add for free */

void free(void *ptr) {
    static void (*og_free)(void*) = NULL;
    if (!og_free)
        {
            og_free = dlsym (RTLD_NEXT, "free");
        }
    if (ptr != NULL)
        {
            size_t size = malloc_usable_size(ptr);
            __sync_fetch_and_sub(&allocated_bytes, size);
        }
    og_free (ptr);
} 
