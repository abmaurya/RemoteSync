#include <boost/asio.hpp>

const std::string_view host = "localhost";
const std::string_view port = "6942";

namespace boost {
	namespace serialization {

		template<class Archive>
		void serialize(Archive& ar, COORD& g, const unsigned int version)
		{
			ar& g.X;
			ar& g.X;
		}
		
		template<class Archive>
		void serialize(Archive& ar, MOUSE_EVENT_RECORD& g, const unsigned int version)
		{
			ar& g.dwButtonState;
			ar& g.dwControlKeyState;
			ar& g.dwEventFlags;
			ar& g.dwMousePosition;
		}
		
		template<class Archive>
		void serialize(Archive& ar, KEY_EVENT_RECORD& g, const unsigned int version)
		{
			ar& g.bKeyDown;
			ar& g.dwControlKeyState;
			ar& g.uChar.AsciiChar;
			ar& g.uChar.UnicodeChar;
			ar& g.wRepeatCount;
			ar& g.wVirtualKeyCode;
			ar& g.wVirtualScanCode;
		}

		template<class Archive>
		void serialize(Archive& ar, FOCUS_EVENT_RECORD& g, const unsigned int version)
		{
			ar& g.bSetFocus;
		}

		template<class Archive>
		void serialize(Archive& ar, MENU_EVENT_RECORD& g, const unsigned int version)
		{
			ar& g.dwCommandId;
		}
		
		template<class Archive>
		void serialize(Archive& ar, WINDOW_BUFFER_SIZE_RECORD& g, const unsigned int version)
		{
			ar& g.dwSize;
		}

		template<class Archive>
		void serialize(Archive& ar, INPUT_RECORD& g, const unsigned int version)
		{
			ar& g.Event.FocusEvent;
			ar& g.Event.KeyEvent;
			ar& g.Event.WindowBufferSizeEvent;
			ar& g.Event.MenuEvent;
			ar& g.EventType;
		}

	} // namespace serialization
} // namespace boost
