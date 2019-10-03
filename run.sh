#!/bin/bash

OS=$(uname -s)
if [ "${OS}" == "Linux" ] ; then
    export LD_PRELOAD=`pwd`/libft_malloc_x86_64_Linux.so
	export LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH
    $@
else
    env DYLD_LIBRARY_PATH=$(pwd) DYLD_INSERT_LIBRARIES=$(pwd)/"libft_malloc.so" DYLD_FORCE_FLAT_NAMESPACE=1 $@
fi
