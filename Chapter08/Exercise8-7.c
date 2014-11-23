/* 
Filename: Exercise8-7.c
Author: Antonio Gutierrez
Description: malloc accepts a size request without checking its plausability; free believes that the block it is asked to free contains a valid size field. Improve these routines so they take more pains with error checking. 

Created: 19/10/2014
*/

#include <stdio.h>

#define MAXALLOCATABLE  (long unsigned int) 1048576         // maximum allocatable block

/* structure declarations */

typedef long Align;         // for alignment to long boundary

union header {              // block header
    struct {
        union header *ptr;  // next block if on free list
        unsigned size;      // size of this block
    } s;
    Align x;                // force alignment block
};

typedef union header Header;

/* function declarations */

void free(void *ap);
static Header *morecore(unsigned nu);
void *malloc(size_t nbytes);

int main(int argc, char *argv[])
{
    
    return 0;
}


/*
 
Rather than allocating from a compiled-in fixed-sized array, malloc will
request space from the operating system as needed. Since other activities in the
program may also request space without calling this allocator, the space that
malloc manages may not be contiguous. Thus its free storage is kept as a list
of free blocks. Each block contains a size, a pointer to the next block, and the
space itself. The blocks are kept in order of increasing storage address, and the
last block (highest address) points to the first.

When a request is made, the free list is scanned until a big-enough block is
found. This algorithm is called "first fit," by contrast with "best fit," which
looks for the smallest block that will satisfy the request. If the block is exactly
the size requested it is unlinked from the list and returned to the user. If the
block is too big, it is split, and the proper amount is returned to the user while
the residue remains on the free list. If no big-enough block is found, another
large chunk is obtained from the operating system and linked into the free list.

Freeing also causes a search of the free list, to find the proper place to insert
the block being freed. If the block being freed is adjacent to a free block on
either side, it is coalesced with it into a single bigger block, so storage does not
become too fragmented. Determining adjacency is easy because the free list is
maintained in order of increasing address.

One problem, which we alluded to in Chapter 5, is to ensure that the storage
returned by malloc is aligned properly for the objects that will be stored in it.
Although machines vary, for each machine there is a most restrictive type: if the
most restrictive type can be stored at a particular address, all other types may
be also. On some machines, the most restrictive type is a double; on others,
int or long suffices.

A free block contains a pointer to the next block in the chain, a record of the
size of the block, and then the free space itself; the control information at the
beginning is called the "header." To simplify alignment, all blocks are 
multiples of the header size, and the header is aligned properly. This is achieved by
a union that contains the desired header structure and an instance of the most
restrictive alignment type, which we have arbitrarily made a long:

The Align field is never used; it just forces each header to be aligned on a
worst-case boundary.

In malloc, the requested size in characters is rounded up to the proper
number of header-sized units; the block that will be allocated contains one more
unit, for the header itself, and this is the value recorded in the size field of the
header. The pointer returned by malloc points at the free space, not at the
header itself. The user can do anything with the space requested, but if 
anything is written outside of the allocated space the list is likely to be scrambled.

The size field is necessary because the blocks controlled by malloc need not be
contiguous—it is not possible to compute sizes by pointer arithmetic.

The variable base is used to get started. If freep is NULL, as it is at the
first call of malloc, then a degenerate free list is created; it contains one block
of size zero, and points to itself. In any case, the free list is then searched. The
search for a free block of adequate size begins at the point (freep) where the
last block was found; this strategy helps keep the list homogeneous. If a too-big
block is found, the tail end is returned to the user; in this way the header of the
original needs only to have its size adjusted. In all cases, the pointer returned to
the user points to the free space within the block, which begins one unit beyond
the header.

The function morecore obtains storage from the operating system. The
details of how it does this vary from system to system. Since asking the system
for memory is a comparatively expensive operation, we don't want to do that on
every call to malloc, so morecore requests at least NALLOC units; this larger
block will be chopped up as needed. After setting the size field, morecore
inserts the additional memory into the arena by calling free.

The UNIX system call sbrk(n) returns a pointer to n more bytes of
storage, sbrk returns -1 if there was no space, even though NULL would have
been a better design. The -1 must be cast to char so it can be compared
with the return value. Again, casts make the function relatively immune to the
details of pointer representation on different machines. There is still one
assumption, however, that pointers to different blocks returned by sbrk can be
meaningfully compared. This is not guaranteed by the standard, which permits
pointer comparisons only within an array. Thus this version of malloc is 
portable only among machines for which general pointer comparison is meaningful.

free itself is the last thing. It scans the free list, starting at freep, 
looking for the place to insert the free block. This is either between two existing
blocks or at one end of the list. In any case, if the block being freed is adjacent
to either neighbor, the adjacent blocks are combined. The only troubles are
keeping the pointers pointing to the right things and the sizes correct.

*/

static Header base;     // empty list to get started
static Header *freep = NULL;    // start of free list
static unsigned max_allocation;     // biggest allocation so far


void *malloc(size_t nbytes)
{
    Header *p, *prevp;
    Header *morecode(unsigned);
    unsigned nunits;


    if (nbytes > MAXALLOCATABLE) {
        fprintf(stderr, "error: %lu is more than than max allocatable size %lu\n", nbytes, MAXALLOCATABLE);
        return NULL;
    }

    nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {          // no free list yet
        base.s.ptr = freep = prevp = &base;      
        base.s.size = 0;
    }
    for (p = prevp->s.ptr;  ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {          // big enough
            if (p->s.size == nunits) {      // exactly
                prevp->s.ptr = p->s.ptr;
            } else {                        // allocate tail end
                p-> s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);         
        }
        if (p == freep) {                   // wrapped around free list
            if ((p = morecore(nunits)) == NULL) {
                return NULL;
            }
        }
    }
}

#define NALLOC 1024

static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC) {                  // allocate at least NALLOC (because calls to sbrk at costly)
        nu = NALLOC;
    }
    cp = sbrk(nu * sizeof(Header)); 
    if (cp == (char *) -1 ) {           // check if it could be allocated
        return NULL;
    }
    up = (Header *) cp;
    up->s.size = nu;                    // store size
    free((void *) (up + 1));            // add space in free list
    max_allocation = (up->s.size > max_allocation) ? up->s.size : max_allocation;   // maintain largest allocation so far
    return freep;
}

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
