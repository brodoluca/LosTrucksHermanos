cpu: ./Implementation/src/TruckSocket.cpp
	g++ ./Implementation/main.cpp ./Implementation/src/TruckOMP.cpp ./Implementation/src/Simulations.cpp ./Implementation/src/utils/JsonHandler.cpp ./Implementation/src/TruckSocket.cpp -o main -fopenmp
gpu: ./Implementation/src/TruckSocket.cpp
	nvcc ./Implementation/main.cpp ./Implementation/src/TruckOMP.cpp ./Implementation/src/Simulations.cpp ./Implementation/src/utils/JsonHandler.cpp ./Implementation/src/TruckSocket.cpp ./Implementation/src/sorter.cu -o main -Xcompiler -fopenmp
leader: ./main
	./main --mode leader --port 11111
truck1: ./main
	./main --mode truck --port 11111 --leader_ip 127.0.0.1 --my_port 99999 --my_ip 127.0.0.1
truck2: ./main
	./main --mode truck --port 11111 --leader_ip 127.0.0.1 --my_port 88888 --my_ip 127.0.0.1
truck3: ./main
	./main --mode truck --port 11111 --leader_ip 127.0.0.1 --my_port 77777 --my_ip 127.0.0.1
truck4: ./main
	./main --mode truck --port 11111 --leader_ip 127.0.0.1 --my_port 66666 --my_ip 127.0.0.1
truck5: ./main
	./main --mode truck --port 11111 --leader_ip 127.0.0.1 --my_port 55555 --my_ip 127.0.0.1