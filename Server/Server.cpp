// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <WinUser.h>
#include "Common.h"

using boost::asio::ip::udp;

void SwitchNumLock(INPUT input[])
{
	input[0].ki.wVk = VK_NUMLOCK;
	UINT uSent = SendInput(1, input, sizeof(input));
	if (uSent != 1)
	{
		std::cerr << (L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
	}
}

int main()
{
	try
	{
		boost::asio::io_context io_context;
		INPUT input[1] = {};
		input[0].type = INPUT_KEYBOARD;
		
		std::string str;
		str.resize(2);
		udp::socket socket(io_context, udp::endpoint(udp::v4(), 6942));
		for (;;)
		{
			//std::array<DWORD, 2> recv_buf;
			udp::endpoint remote_endpoint;
			//socket.receive_from(boost::asio::buffer(str), remote_endpoint);
			if (socket.receive_from(boost::asio::buffer(str), remote_endpoint) > 0)
			//if (str.size() > 0)
			{
				//std::cout << str;
				std::istringstream archive_stream(str);
				INPUT_RECORD inc_rec;
				boost::archive::text_iarchive archive(archive_stream);
				archive >> inc_rec;
				
				switch (inc_rec.EventType)
				{
				case KEY_EVENT:
					if (inc_rec.Event.KeyEvent.bKeyDown)
					{
						if (inc_rec.Event.KeyEvent.dwControlKeyState = SHIFT_PRESSED)
						{
							input[0].ki.wVk = inc_rec.Event.KeyEvent.wVirtualKeyCode;
							UINT uSent = SendInput(1, input, sizeof(input));
							if (uSent != 1)
							{
								std::cerr << (L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
							}
						}
						/*input[0].ki.wVk = inc_rec.Event.KeyEvent.wVirtualKeyCode;
						UINT uSent = SendInput(1, input, sizeof(input));
						if (uSent != 1)
						{
							std::cerr << (L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
						}*/
						std::cout << sizeof(inc_rec.Event.KeyEvent.uChar.UnicodeChar);
					}
					break;
				}
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}