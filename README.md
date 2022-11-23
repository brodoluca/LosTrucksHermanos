# Los Trucks Hermanos

don't read me. Or maybe do ehehe

To start a truck (the port is the one of the leader):  
`./implementation/main --mode truck --port 8080 --my_ip 172.20.10.4 --leader_ip 172.20.10.3`

to start a leader:  
`./implementation/main --mode leader`


To compile (OLD, my man ALI is doing the make file)
```
 /usr/local/opt/llvm/bin/clang++ -fopenmp -g $(find .  -type f -iregex ".*\.cpp") -o main
```

TO-DO

- Implement remaining behaviours
- Do that GPU thingy



