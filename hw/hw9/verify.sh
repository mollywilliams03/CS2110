#!/bin/bash
e=0; [[ $(sha512sum list.h | cut -d " " -f 1) == efc2f51793b8ac239c55c7fe612beacf06b9d101325440a22ea5e94992dee23a6c0b5fb2152885fc61610aaa6b7ba75a8e7f45828091f2f4a190a69fca651324 ]] || { printf 'error: list.h was modified! re-download it and try again\n'>&2; e=1; }; exit $e
