#include <dlfcn.h>
#include <stddef.h>

static size_t allocated_bytes;

void *malloc(size_t size) 
    {
        static void *(*og_malloc)(size_t) = NULL;
        if (!og_malloc) 
            {
                og_malloc = dlysm( RTLD_NEXT, "malloc");
            }
        void *ptr = og_malloc (size);
    }