
#include "KeyDownEvent.h"

const std::string KeyDownEvent::KEY_DOWN_EVENT_TYPE = "KEY_DOWN_EVENT";

KeyDownEvent::KeyDownEvent(char key) : Event(KEY_DOWN_EVENT_TYPE), key(key)
{

}
