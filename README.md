# Los Trucks Hermanos

don't read me. Or maybe do ehehe

To start a truck (the port is the one of the leader):  
`./Implementation/main --mode truck --port 11111 --leader_ip 172.20.10.3 --my_port 12345 --my_ip 172.20.10.4`

to start a leader:  
`./Implementation/main --mode leader --port 11111`


To compile (OLD, my man ALI is doing the make file)
```
 /usr/local/opt/llvm/bin/clang++ -fopenmp -g $(find .  -type f -iregex ".*\.cpp") -o main
```


# Documentation
https://www.overleaf.com/1627393419xtwssngpxdbp

 
# TO-DO

- Implement remaining behaviours
- Do that GPU thingy
-We can think about adding a "cut in" behaviour



