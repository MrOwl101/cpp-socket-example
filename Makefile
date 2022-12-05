app:
	g++ client_tcp.cpp -o client.exe
	g++ server_tcp.cpp -o server.exe
	
clean:
	-rm client.exe
	-rm server.exe
