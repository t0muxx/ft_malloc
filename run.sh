#!/bin/bash

OS=$(uname -s)
if [ $OS == "Linux" ] ; then
    export LD_PRELOAD=`pwd`/libft_malloc_x86_64_Linux.so
	export LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH
#   export DEBUG_FREE=1
#	export DEBUG_FREE_MEM=1
#	export DEBUG_MALLOC=1
#	export DEBUG_MALLOC_RET=1
#	export DEBUG_CALLOC=1
#	export DEBUG_CALLOC_RET=1
#	export DEBUG_REALLOC=1
#	export DEBUG_REALLOC_RET=1
#	export DEBUG_MMAP=1
#	export DEBUG_MUNMAP=1
	$@
else
	export DYLD_LIBRARY_PATH=.
	export DYLD_INSERT_LIBRARIES="libft_malloc.so"
	export DYLD_FORCE_FLAT_NAMESPACE=1
#	export DEBUG_FREE=1
#	export DEBUG_FREE_MEM=1
#	export DEBUG_MALLOC=1
#	export DEBUG_MALLOC_RET=1
#	export DEBUG_CALLOC=1
#	export DEBUG_CALLOC_RET=1
#	export DEBUG_REALLOC=1
#	export DEBUG_REALLOC_RET=1
#	export DEBUG_MMAP=1
#	export DEBUG_MUNMAP=1
	$@
fi
