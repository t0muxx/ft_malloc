#!/bin/bash

OS=$(uname -s)
if [ $OS == "Linux" ] ; then
    export LD_PRELOAD=`pwd`/libft_malloc_x86_64_Linux.so
	export LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH
    $@
else
	export DYLD_LIBRARY_PATH=.
	export DYLD_INSERT_LIBRARIES="libft_malloc.so"
	export DYLD_FORCE_FLAT_NAMESPACE=1
	$@
fi
