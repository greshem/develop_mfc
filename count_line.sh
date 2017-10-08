#!/bin/bash
bash ./clean.sh
#find . -type f  |grep -v svn  |grep -v mars |grep -v o$ |grep -v s$ |grep -v Makefile| xargs wc 
find -type f |egrep 'h$|cpp$|hpp$|sh$|pl$|txt$|py$' |xargs wc
