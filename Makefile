all:
	@gcc tcp_client.c func.c -o ./tcp_client
	@gcc tcp_server.c func.c -o ./tcp_server
