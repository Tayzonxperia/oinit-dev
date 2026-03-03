#!/bin/bash

gcc init.c -o init
doas mv init /sbin/oinit
sudo mv init /sbin/oinit

nim c init2.nim 
doas mv init2 /sbin/oinit-service
sudo mv init2 /sbin/oinit-service

gcc init3.c -o init3
doas mv init3 /sbin/oinit-finale
