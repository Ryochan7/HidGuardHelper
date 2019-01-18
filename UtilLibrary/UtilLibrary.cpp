#include "stdafx.h"

#include <msclr/marshal_cppstd.h>
#include <Windows.h>
#include "UtilLibrary.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace msclr::interop;

cli::array<String^>^ UtilLibrary::Class1::HidGuardWhitelist()
{
	HKEY pHandle;
	cli::array<String^>^ temp;
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\HidGuardian\\Parameters\\Whitelist", 0, KEY_READ, &pHandle) == ERROR_SUCCESS)
	{
		List<String^> tempList;
		int ind = 0;
		TCHAR temptest[255];
		DWORD cbName = 255;
		_FILETIME ftLastWriteTime;
		while (RegEnumKeyEx(pHandle, ind, temptest, &cbName, NULL, NULL, NULL, &ftLastWriteTime) == ERROR_SUCCESS)
		{
			tempList.Add(gcnew String(temptest));
			ind++;
		}

		temp = gcnew cli::array<String^>(tempList.Count);
		for (int i = 0; i < tempList.Count; i++)
		{
			temp[i] = tempList[i];
		}

		RegCloseKey(pHandle);
	}
	else
	{
		temp = gcnew cli::array<String^>(0);
	}

	return temp;
}

void UtilLibrary::Class1::DeleteSubKey(String ^ key)
{
	marshal_context context;
	LPCSTR temper = context.marshal_as<LPCSTR>(key);
	RegDeleteKeyA(HKEY_LOCAL_MACHINE, temper);
}

void UtilLibrary::Class1::CreateSubKey(String ^ key)
{
	HKEY hKey;
	marshal_context context;
	LPCWSTR temper = context.marshal_as<const TCHAR*>(key);
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, temper, 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
	RegCloseKey(hKey);
}
