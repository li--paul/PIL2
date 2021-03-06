#ifdef PLATEFORM_INCLUDE_SOURCE

#include "NamedEvent_WIN32.h"
#include "../Debug/Exception.h"
#include "../Utils/format/format.h"

namespace pi {


NamedEventImpl::NamedEventImpl(const std::string& name):
	_name(name)
{
	_event = CreateEventA(NULL, FALSE, FALSE, _name.c_str());
	if (!_event)
	{
		DWORD dwRetVal = GetLastError();
        throw SystemException(fmt::sprintf("cannot create named event %s [Error %d]", _name, (int)dwRetVal));
	}
}


NamedEventImpl::~NamedEventImpl()
{
	CloseHandle(_event);
}


void NamedEventImpl::setImpl()
{
	if (!SetEvent(_event))
		throw SystemException("cannot signal named event", _name);
}


void NamedEventImpl::waitImpl()
{
	switch (WaitForSingleObject(_event, INFINITE))
	{
	case WAIT_OBJECT_0:
		return;
	default:
		throw SystemException("wait for named event failed", _name);
	}
}


} // namespace pi

#endif // end of PLATEFORM_INCLUDE_SOURCE
