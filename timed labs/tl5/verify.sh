#!/bin/bash
e=0; [[ $(sha512sum tl5.h | cut -d " " -f 1) == ad1659a8e47644dcca21c1b83f5c83d98796d364e96eecb94496bdd05d93567aa119dd060690de87c558d5bd111980c3c0177c9cd784831f9ae0613944162267 ]] || { printf 'error: tl5.h was modified! re-download it and try again\n'>&2; e=1; }; exit $e
