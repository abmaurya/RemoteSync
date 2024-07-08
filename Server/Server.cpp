// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <WinUser.h>

using boost::asio::ip::udp;

int main()
{
	try
	{
		boost::asio::io_context io_context;

		udp::socket socket(io_context, udp::endpoint(udp::v4(), 6942));
		INPUT input[1] = {};
		for (;;)
		{
			std::array<char, 1> recv_buf;
			udp::endpoint remote_endpoint;
			socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);
			if (sizeof(recv_buf) > 0)
			{
				std::cout << recv_buf[0];
				/*input[0].type = INPUT_KEYBOARD;
				input[0].ki.wVk = recv_buf[0];*/

				/*UINT uSent = SendInput(1, input, sizeof(input));
				if (uSent != 1)
				{
					std::cerr << (L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
				}*/
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}