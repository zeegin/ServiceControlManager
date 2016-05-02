#pragma once
using namespace System;

namespace InstDrv
{
	[Serializable]
	public ref class KernelErrorException : Exception
	{
	public:
		KernelErrorException(void);
		
		virtual String^ ToString() override;

		property virtual String^ Message
		{
			String^ get() override;
		};

		property virtual DWORD ErrorCode
		{
			DWORD get();
		};

	private:
		DWORD errorCode;
	
	internal:
        KernelErrorException(DWORD ErrorCode);
	};
}
