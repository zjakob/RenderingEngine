
#include "KeyUpEvent.h"

const std::string KeyUpEvent::KEY_UP_EVENT_TYPE = "KEY_UP_EVENT";

KeyUpEvent::KeyUpEvent(char key) : Event(KEY_UP_EVENT_TYPE), key(key)
{

}
