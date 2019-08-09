FT\_MALLOC
=================

TINY : Zone which contains at least 100 alloc
SMALL : Same
LARGE : mmaped directly

Zone should be a multiple of getpagesize()

Zone\_TINY = 4096*8192
TINY = 80 (alignement)

ZONE\_SMALL = 4096*4 = 16384
SMALL = 160

how to align : 
155 -> 160
155 + 16-(155%16)
mem\_size + mem\_align-(mem\_size%mem\_align)

Malloc method : 
```
#MALLOC_ALIGN_MASK 16 - 1
#define aligned_OK(m)  ((m & MALLOC_ALIGN_MASK) == 0))
```


