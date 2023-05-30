
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
void Conn::readRC(Conn* modbus) {
	while (true) {
		do {
			modbus->rc = modbus_receive(modbus->ctx, modbus->request);
		} while (modbus->rc == 0);
		if (modbus->rc < 0) {
			perror("Error in modbus receive");
		}
		printf("Request received rc= %d\n", modbus->rc);
		modbus->mtx.lock();
		modbus->ret = modbus_reply(modbus->ctx, modbus->request, modbus->rc, modbus->mb_mapping);//rc, request size must be given back to modbus_reply as well as "request" data
		modbus->mtx.unlock();
		if (modbus->ret < 0) {
			perror("modbus reply error");
		}
	}
}
void Conn::disconnect()
{
	modbus_close(ctx);
	modbus_free(ctx);
}

int* Conn::reg_read_ten(Conn* con, int start)
{
	int* ret = new int[10];
	con->mtx.lock();
	for (int i = 0; i < 10; i++)
	{
		ret[i] = (*con->registers)[(start * 10) + i];
	}
	con->mtx.unlock();
	return ret;
	
}

int* Conn::reg_read_multiple(Conn* con, int start, int nb)
{
	int* ret = new int[nb];
	con->mtx.lock();
	for (int i = 0; i < nb; i++)
	{
		ret[i] = (*con->registers)[start  + i];
	}
	con->mtx.unlock();
	return ret;
}

int Conn::reg_read_single(Conn* con, int start)
{
	con->mtx.lock();
	auto ret = (*con->registers)[start];
	con->mtx.unlock();
	return ret;
}

void Conn::reg_clear(Conn* con, int start)
{
	con->mtx.lock();
	for (int i = 0; i < 10; i++)
	{
		(*con->registers)[(start * 10) + i] = 0;
	}
	con->mtx.unlock();
}

void Conn::reg_write_token(Conn* con, uint16_t* token, int tier)
{
	con->mtx.lock();
	for (int i = 0; i < 6; i++)
	{
		(*con->registers)[2 + i] = token[i];
	}
	(*con->registers)[1] = tier;
	con->mtx.unlock();
}

uint16_t* Conn::Reg_read_token(Conn* con)
{
	uint16_t* ret = new uint16_t[6];
	for (int i = 0; i < 6; i++)
	{
		ret[i] = (*con->registers)[i + 2];
	}
	return ret;
}

void Conn::reg_write(Conn* con, int start,int id, std::string str)
{
	con->mtx.lock();
	(*con->registers)[(start * 10) + 0] = id;
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
		(*con->registers)[(start * 10) + (i+1)] = low+high;

	}
	con->mtx.unlock();
}
void Conn::reg_write(Conn* con, int start, int value)
{
	con->mtx.lock();
	(*con->registers)[start] = value;
	con->mtx.unlock();
}

void Conn::reg_write_Second(Conn* con, int output)
{
	Conn::reg_write(con, 1, output);
}