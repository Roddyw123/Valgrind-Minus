#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>

void *malloc(size_t size) 
    {
        static void *(*og_malloc)(size_t) = NULL;
        if (!og_malloc) 
            {
                og_malloc = dlysm (RTLD_NEXT, "malloc");
            }
        void *ptr = og_malloc (size);
        static size_t allocated_bytes;
        allocated_bytes += size;
        fprintf (stderr, "malloc(%zu) -> total: %zu bytes\n", size, allocated_bytes);
        return ptr;
    }