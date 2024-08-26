#include <iostream>
#include <string_view>
#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "Common.h"

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
		/*if (argc != 3)
		{
			std::cerr << "Usage: client <host> <port>" << std::endl;
			return 1;
		}*/
		boost::asio::io_context io_context;

		udp::resolver resolver(io_context);
		udp::endpoint receiver_endpoint =
			//*resolver.resolve(udp::v4(), argv[1], argv[2]).begin();
			*resolver.resolve(udp::v4(), host, port).begin();
		udp::socket socket(io_context);
		socket.open(udp::v4());
	/*fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hIn, fdwMode))
		return -1;*/
		while (Continue)
		{
			//ShowWindow(GetConsoleWindow(), SW_SHOW);
			ReadConsoleInput(hIn, &InRec, 1, &NumRead);
			std::ostringstream archive_stream;
			boost::archive::text_oarchive archive(archive_stream);
			archive << InRec;
			socket.send_to(boost::asio::buffer(archive_stream.str()), receiver_endpoint);
			//std::cout << "Bytes transferred" << archive_stream.str();
			//switch (InRec.EventType)
			//{
			//case KEY_EVENT:
			//	DWORD d1[2] = { InRec.Event.KeyEvent.uChar.UnicodeChar, InRec.Event.KeyEvent.dwControlKeyState};
			////	//std::cout << InRec.Event.KeyEvent.bKeyDown;
			//	if (InRec.Event.KeyEvent.bKeyDown)
			//	{
			////		//auto strin = archive_stream.str();
			////		//auto buff = boost::asio::const_buffer((const void*)&strin, strin.size(), [](){});
			////		//auto data = buff.data();
			////		//auto sp = static_cast<const std::string*>(data);
			////		///*for (auto var = buff.begin(); var != buff.end(); ++var)
			////		//{
			////		//	std::cout << var;
			////		//}*/
			////		//std::string s = *sp;
			////		//std::cout << strin <<"\n";
			////		//std::istringstream iarchive_stream(s);
			////		//INPUT_RECORD inc_rec;
			////		//boost::archive::text_iarchive archive(iarchive_stream);
			////		//archive >> inc_rec;
			////		std::cout << InRec.Event.KeyEvent.dwControlKeyState << "\t" << InRec.Event.KeyEvent.wRepeatCount <<"\n";
			////		std::cout << inc_rec.Event.KeyEvent.dwControlKeyState << "\t" << inc_rec.Event.KeyEvent.wRepeatCount <<"\n";
			////		//std::cout << archive_stream.str() << std::endl;
			//		
			//std::cout << "Bytes transferred" << socket.send_to(boost::asio::buffer(d1), receiver_endpoint);
			////		//delete sp;
			//	}
			//	break;
			//}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
		return 0;
}
