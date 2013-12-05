/*********************@FUNCTION_HEADER_START*************************
*@FUNCTION NAME:	write()											*
*																	*
*@DESCRIPTION:		Low-Level function for printf()					*
*																	*
*@PARAMETER:		file no., pointer to buffer, size-byte of data	*
*																	*
*@RETURN:			size or error(-1)								*
*																	*
***********************@FUNCTION_HEADER_END*************************/
/*
#define HEAP_SIZE       1564			/* memory size */
/*
static long     brk_siz = 0;
#if HEAP_SIZE
	static char     heap[HEAP_SIZE];
	#define         heap_size      HEAP_SIZE
#else
	extern char     * heap;
	extern long     heap_size;
#endif

extern char *sbrk(int size)
{
    if (brk_siz + size > heap_size || brk_siz + size < 0)
        return((char*)-1);			/* return error */
/*    brk_siz += size;				/* allocate memory */
/*    return( heap + brk_siz - size); /* return allocatable memory */
//}
