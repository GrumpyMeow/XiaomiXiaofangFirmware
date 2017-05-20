#!/bin/sh
PATH=/bin:/sbin:/usr/web/cgi-bin:$PATH
export PATH

date
sleep $1
date
autorecordtest $2 $3

exit
       
