#pragma once

using namespace System;

namespace UtilLibrary {
	public ref class Class1
	{
		// TODO: Add your methods for this class here.
	public:
		static DWORD REGISTRY_OPTION_VOLATILE = REG_OPTION_VOLATILE;
		static String^ WHITELIST_PATH = gcnew String("SYSTEM\\CurrentControlSet\\Services\\HidGuardian\\Parameters\\Whitelist");

		static cli::array<String^>^ HidGuardWhitelist();
		static void DeleteSubKey(String^ key);
		static void CreateSubKey(String^ key);
		static void CreateSubKey(String^ key, unsigned long options);
	};
}
