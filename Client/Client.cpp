//#include <windows.h>
#include <iostream>
//#include <winuser.h>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char* argv[])
{
	HANDLE hIn;

	bool Continue = TRUE;
	INPUT_RECORD InRec;
	DWORD NumRead;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	try 
	{
		if (argc != 3)
		{
			std::cerr << "Usage: client <host> <port>" << std::endl;
			return 1;
		}
		boost::asio::io_context io_context;

		udp::resolver resolver(io_context);
		udp::endpoint receiver_endpoint =
			*resolver.resolve(udp::v4(), argv[1], argv[2]).begin();
		udp::socket socket(io_context);
		socket.open(udp::v4());
	/*fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hIn, fdwMode))
		return -1;*/
		while (Continue)
		{
			//ShowWindow(GetConsoleWindow(), SW_SHOW);
			ReadConsoleInput(hIn,
				&InRec,
				1,
				&NumRead);

			switch (InRec.EventType)
			{
			case KEY_EVENT:
				char d1[1] = { InRec.Event.KeyEvent.uChar.AsciiChar };
				socket.send_to(boost::asio::buffer(d1), receiver_endpoint);
				break;

				/*case MOUSE_EVENT:
					++MouseEvents;
					SetConsoleCursorPosition(hOut,
						MouseWhere);
					break;*/
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
		return 0;
}
