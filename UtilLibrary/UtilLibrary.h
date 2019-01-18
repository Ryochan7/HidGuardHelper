#pragma once

using namespace System;

namespace UtilLibrary {
	public ref class Class1
	{
		// TODO: Add your methods for this class here.
	public:
		static cli::array<String^>^ HidGuardWhitelist();
		static void DeleteSubKey(String^ key);
		static void CreateSubKey(String^ key);
	};
}
