#include "StdAfx.h"
#include "KernelErrorException.h"

using namespace InstDrv;

KernelErrorException::KernelErrorException(void)
{
	this->errorCode = GetLastError();
}

KernelErrorException::KernelErrorException(DWORD ErrorCode)
{
	this->errorCode = ErrorCode;
}

String^ KernelErrorException::Message::get()
{
	LPTSTR message = NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
			this->errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&message, 0, NULL);
    String^ messageString = gcnew String(message);
	LocalFree(message);
	return messageString;
}

DWORD KernelErrorException::ErrorCode::get()
{
    return this->errorCode;
}

String^ KernelErrorException::ToString()
{
    return this->Message::get();
}