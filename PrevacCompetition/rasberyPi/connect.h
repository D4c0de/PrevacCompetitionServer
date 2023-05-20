#pragma once
#include <string>
#include <vector>
#include <modbus.h>


struct Conn
{
	int ret, rc;
	uint8_t request[180];
	modbus_t* ctx;
	uint16_t** registers;
	modbus_mapping_t* mb_mapping;
	Conn();
	Conn(std::string,int);
	~Conn();
	void connect(const char*,int);
	static void readRC(Conn*);

	void disconnect();
	static std::vector<int> reg_read_ten(Conn*, int);
	static std::vector<int>* reg_read_muliple(Conn*, int, int);

	static int reg_read_single(Conn*, int);
	static void reg_clear(Conn*,int);
	static void reg_write(Conn*,int,int,std::string);
	static void reg_write(Conn*, int, int);
	static void reg_write_Second(Conn*, int);
};
