#pragma once

#ifdef SCRIPTO_EXPORTS
	#define SCRIPTO_API __declspec(dllexport)
#else
	#define SCRIPTO_API __declspec(dllimport)
#endif


#include <string>

namespace Scripto
{
	// types declarations
	struct Script;

	// public API
	extern "C" SCRIPTO_API bool RunScript(Script script);
	extern "C" SCRIPTO_API bool Test();

	enum class ScriptType : uint8_t { Python, Bash, Shell };
	enum class RunPolicy : uint8_t { Administrator, NormalUser };

	// types definitions
	struct Script
	{
		std::string name;
		std::string path;
		ScriptType type;
		RunPolicy runPolicy;
	};
}