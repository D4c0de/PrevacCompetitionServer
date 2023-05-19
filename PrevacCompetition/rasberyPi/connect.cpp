
#include "connect.h"
#include <iostream>
#define UART_PATH "COM7"
#define ConnectViaRtu true

Conn::Conn()
{
	ctx = nullptr;
	//connect("192.168.1.116", 12345);
	connect("127.0.0.1", 502);

	}
Conn::Conn(std::string ip, int port)
{
	ctx = nullptr;
	connect(ip.c_str(), port);
}
Conn::~Conn()
{

	disconnect();
	delete ctx;
}
void Conn::connect(const char *ip,int port)
{
	if (ConnectViaRtu)
	{
		ctx = modbus_new_rtu(UART_PATH, 9600, 'N', 8, 1);
	}
	else
	{
		ctx = modbus_new_tcp(ip, port);
	}

	if (ctx == NULL) {
		perror("Unable to create the libmodbus context");

	}

	modbus_set_debug(ctx, 1);//debug mode on

	ret = modbus_set_slave(ctx, 1);//Set slave address
	if (ret < 0) {
		perror("modbus_set_slave error");

	}

	ret = modbus_connect(ctx);
	if (ret < 0) {
		perror("modbus_connect error");

	}
	//Init the modbus mapping structure, will contain the data
	//that will be read/write by a client.
	mb_mapping = modbus_mapping_new(0, 0,MODBUS_MAX_READ_REGISTERS, 0);
	registers = &mb_mapping->tab_registers;
	if (mb_mapping == NULL) {
		perror("Cannot allocate mb_mapping");
	}
	
}
void Conn::readRC() {

	do {
		rc = modbus_receive(ctx, request);
	} while (rc == 0);
	if (rc < 0) {
		perror("Error in modbus receive");
	}
	printf("Request received rc= %d\n", rc);
	ret = modbus_reply(ctx, request, rc, mb_mapping);//rc, request size must be given back to modbus_reply as well as "request" data
	if (ret < 0) {
		perror("modbus reply error");
	}
}
void Conn::disconnect()
{
	modbus_close(ctx);
	modbus_free(ctx);
}

std::vector<int> Conn::reg_read_ten(Conn* con, int start)
{

	std::vector<int> ret;
	for (int i = 0; i < 10; i++)
	{
		ret.push_back((*con->registers)[(start * 10) + i]);
	}
	return ret;
	
}

std::vector<int>* Conn::reg_read_muliple(Conn* con, int start, int nb)
{
	std::vector<int>* ret =new std::vector<int>;
	for (int i = 0; i < nb; i++)
	{
		ret->push_back((*con->registers)[(start * 10) + i]);
	}
	return ret;

}

int Conn::reg_read_single(Conn* con, int start)
{
	return *(con->registers)[start];
}

void Conn::reg_clear(Conn* con, int start)
{
	for (int i = 0; i < 10; i++)
	{
		(*con->registers)[(start * 10) + i] = 0;
	}

}

void Conn::reg_write(Conn* con, int start, std::string str)
{
	int lenght = str.length();
	for (int i = 0; i*2 < str.length(); i++)
	{
		int low = (int)str[(i*2)];
		int high;
		if (lenght>=(i*2)+1)
		{
			high = ((int)str[(i*2) + 1])*255;
			
		}
		else
		{
			high = 0;
		}
		(*con->registers)[(start * 10) + i] = low+high;

	}
}
void Conn::reg_write(Conn* con, int start, int value)
{
	(*con->registers)[start] = value;

}

void Conn::reg_write_Second(Conn* con, int output)
{
	Conn::reg_write(con, 0, 11);
	Conn::reg_write(con, 1, output);
}