#include "StdAfx.h"
#include "ServiceControlManager.h"
#include "KernelErrorException.h"

using namespace System::Runtime::InteropServices;
using namespace InstDrv;

ServiceControlManager::ServiceControlManager(void)
{
	this->SCMHandle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!this->SCMHandle)
		throw gcnew KernelErrorException();
}

ServiceControlManager::~ServiceControlManager()
{
	this->!ServiceControlManager();
	GC::SuppressFinalize(this);
}

ServiceControlManager::!ServiceControlManager()
{
	CloseServiceHandle(this->SCMHandle);
}

void ServiceControlManager::AddDriver(String^ ServiceName, String^ BinaryPathName)
{
	IntPtr serviceNamePtr = Marshal::StringToHGlobalUni(ServiceName);
	IntPtr binaryPathNamePtr = Marshal::StringToHGlobalUni(BinaryPathName);
	SC_HANDLE SCMHandleService = CreateService(this->SCMHandle, (LPCTSTR)serviceNamePtr.ToPointer(),
		(LPCTSTR)serviceNamePtr.ToPointer(), SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER,
		SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, (LPCTSTR)binaryPathNamePtr.ToPointer(), NULL, NULL, NULL, NULL, NULL);
	DWORD errorCode = GetLastError();
	Marshal::FreeHGlobal(serviceNamePtr);
	Marshal::FreeHGlobal(binaryPathNamePtr);
	if (!SCMHandleService)
		throw gcnew KernelErrorException(errorCode);
	if (!CloseServiceHandle(SCMHandleService))
		throw gcnew KernelErrorException();
}

void ServiceControlManager::DeleteDriver(String^ ServiceName)
{
	IntPtr serviceNamePtr = Marshal::StringToHGlobalUni(ServiceName);
	SC_HANDLE SCMHandleService = OpenService(this->SCMHandle, (LPCTSTR)serviceNamePtr.ToPointer(), SERVICE_ALL_ACCESS);
	DWORD errorCode = GetLastError();
	Marshal::FreeHGlobal(serviceNamePtr);
	if (!SCMHandleService )
		throw gcnew KernelErrorException(errorCode);
	if (!DeleteService(SCMHandleService))
		throw gcnew KernelErrorException();
	if (!CloseServiceHandle(SCMHandleService))
		throw gcnew KernelErrorException();
}

void ServiceControlManager::StartDriver(String^ ServiceName)
{
	IntPtr serviceNamePtr = Marshal::StringToHGlobalUni(ServiceName);
	SC_HANDLE SCMHandleService = OpenService(this->SCMHandle, (LPCTSTR)serviceNamePtr.ToPointer(), SERVICE_ALL_ACCESS);
	DWORD errorCode = GetLastError();
	Marshal::FreeHGlobal(serviceNamePtr);
	if (!SCMHandleService)
		throw gcnew KernelErrorException(errorCode);
	if (!StartService(SCMHandleService, 0, 0))
		throw gcnew KernelErrorException();
	if (!CloseServiceHandle(SCMHandleService))
		throw gcnew KernelErrorException();
}

void ServiceControlManager::StopDriver(String^ ServiceName)
{
	IntPtr serviceNamePtr = Marshal::StringToHGlobalUni(ServiceName);
	SC_HANDLE SCMHandleService = OpenService(this->SCMHandle, (LPCTSTR)serviceNamePtr.ToPointer(), SERVICE_ALL_ACCESS);
	DWORD errorCode = GetLastError();
	Marshal::FreeHGlobal(serviceNamePtr);
	if (!SCMHandleService)
		throw gcnew KernelErrorException(errorCode);
	SERVICE_STATUS serviceStatus;
	if (!ControlService(SCMHandleService, SERVICE_CONTROL_STOP, &serviceStatus))
		throw gcnew KernelErrorException();
	if (!CloseServiceHandle(SCMHandleService))
		throw gcnew KernelErrorException();
}