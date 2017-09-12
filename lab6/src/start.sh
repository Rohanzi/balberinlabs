#!/bin/bash
nohup shmemsemserver > server.txt &
nohup shmemsemclient > client.txt &
echo "Wait for 60 seconds"
sleep 60
#Interrupts latest processes with names specified
kill -INT $(pgrep -n shmemsemclient)
kill -INT $(pgrep -n shmemsemclient)
echo "Server work results"
cat server.txt
echo "Client work results"
cat client.txt
