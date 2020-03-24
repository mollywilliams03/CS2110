#!/bin/bash
e=0; [[ $(sha512sum my_malloc.h | cut -d " " -f 1) == 3f2c75c37429237197f0b6a0a6848526936987b93553852872411ff57a064073142143722fedefd2fb26fe8e5ecd8f1d93ac00b96eabc9c3386ceb0d7635406b ]] || { printf 'error: my_malloc.h was modified! re-download it and try again\n'>&2; e=1; }; exit $e
