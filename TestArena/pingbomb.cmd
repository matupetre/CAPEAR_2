@echo off
set timeout_sec=%1
if "%1"=="" set timeout_sec=5
echo on
ping 192.168.0.200 -t -f -w %timeout_sec%000
