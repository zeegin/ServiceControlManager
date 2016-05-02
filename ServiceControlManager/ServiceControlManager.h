#pragma once

using namespace System;

namespace InstDrv
{
	public ref class ServiceControlManager : public IDisposable
	{
	public:
		ServiceControlManager(void);
		void AddDriver(String^ ServiceName, String^ BinaryPathName);
		void DeleteDriver(String^ ServiceName);
		void StartDriver(String^ ServiceName);
		void StopDriver(String^ ServiceName);
	protected:
		~ServiceControlManager();
		!ServiceControlManager();
	private:
		SC_HANDLE SCMHandle;
	};
}

