/* 
Filename: Exercise8-8.c
Author: Antonio Gutierrez
Description: Write a routine bfree(p, n) that will free an arbitrary block of p of n characters into the free list maintained by malloc and free. By using bfree, a user can add a static or external array to the free list at any time
Created: 20/10/2014
*/

#include <stdio.h>

typedef long Align;         // for alignment to long boundary

union header {              // block header
    struct {
        union header *ptr;  // next block if on free list
        unsigned size;      // size of this block
    } s;
    Align x;                // force alignment block
};

typedef union header Header;


void free(void *ap);

int main(int argc, char *argv[])
{
    
    return 0;
}

/* bfree: deallocates block of chars p of size n */
unsigned bfree(char *p, size_t n)
{
    Header *h;

    if (n < sizeof(Header)) {
        fprintf(stderr, "error: size %lu too small to be used by free list\n", n);
        return 0;
    }
    h = (Header *) p;
    h->s.size = n / sizeof(Header);     // calculate size in units of Header
    free( (void *)(h + 1));             // free rest of block
    return h->s.size;                   // return rest
}

    
static Header base;     // empty list to get started
static Header *freep = NULL;    // start of free list
static unsigned max_allocation;     // biggest allocation so far
    
void free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;                          // point to block header
    if (bp->s.size == 0 || bp->s.size > max_allocation) {
        fprintf(stderr, "error: free cannot deallocate %u units\n", bp->s.size);
        return;                                 
    }
    for (p = freep; !(bp > p && bp < p->s.ptr); p->s.ptr) {     // traverse through free list
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break;                                  // freed block at start or end of arena
        }
    }
    if (bp + bp->s.size == p->s.ptr) {              // join to upper neighbour
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp) {                      // join to lower neighbour
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}

