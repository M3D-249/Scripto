#pragma once

#ifdef SCRIPTO_EXPORTS
	#define SCRIPTO_API __declspec(dllexport)
#else
	#define SCRIPTO_API __declspec(dllimport)
#endif


#include <string>
#include <vector>
#include <unordered_set>

#include <qdatetime.h>
#include <qstring.h>
#include <qprocess.h>

// macros
#define SCRIPTO_ERROR -1
#define SCRIPTO_INVALID_PROCESS_ID -2

namespace Scripto
{
	// types declarations
	struct Script;

	enum class ScriptType : uint8_t { None, Python, Bash, Executable };
	enum class RunPolicy : uint8_t { Administrator, NormalUser };

	// types definitions
	struct Script
	{
		QString id;
		QString name;
		QString path;
		QString workingDir;
		ScriptType type;
		RunPolicy runPolicy;
	};

	// TODO: Make logs for scripts executions
	//struct Schedule
	//{
	//	const QDateTime placedTime = QDateTime::currentDateTime();
	//	QString scriptName;
	//	QDateTime targetTime;
	//};

	// public API
	QString SCRIPTO_API DataDirectory();
	QString SCRIPTO_API ConfigFilePath();
	QString SCRIPTO_API ScriptsFilePath();
	QString SCRIPTO_API ScriptsPath();
	QStringList SCRIPTO_API AllowedScriptsTypes();
	QStringList SCRIPTO_API AllowedScriptsTypesFileExtentions();

	// helpers
	ScriptType SCRIPTO_API ScriptTypeFromString(const QString& str);
	/* returns script type provide a script file extention like .py returns ScriptType::Python */
	ScriptType SCRIPTO_API ScriptTypeFromExtentionString(const QString& str);
	QString SCRIPTO_API ScriptTypeToString(ScriptType type);
	RunPolicy SCRIPTO_API RunPolicyFromString(const QString& str);
	QString SCRIPTO_API RunPolicyToString(RunPolicy rp);

	// callbacks
	void SCRIPTO_API setOnNewScriptAddedCallback(std::function<void(const QString& scriptName)> functr);
	void SCRIPTO_API setOnScriptRemovedCallback(std::function<void(const QString& scriptName)> functr);

	void SCRIPTO_API Init(const QString& appName, const QString& companyName);

	int SCRIPTO_API LoadScripts();
	QStringList SCRIPTO_API GetStoredScriptsNames();

	bool SCRIPTO_API AddScript(const QString& name, const QString& path, const QString& workingDir, ScriptType type, RunPolicy runPolicy);
	bool SCRIPTO_API AddInplaceScript(const QString& name, const QString& code, const QString& workingDir, ScriptType type, RunPolicy runPolicy);
	bool SCRIPTO_API RemoveScript(const QString& name);

	bool SCRIPTO_API WriteInputToProcess(long long processID, const QString& input);

	/* returns the process id on success and returns SCRIPTO_ERROR on failure */
	long long SCRIPTO_API RunScript(const QString& scriptName, std::function<void(const QString&)> onOutput, std::function<void(const QString&)> onError, std::function<void(QProcess::ExitStatus)> onFinish);
	/* schedules a script to be run on a given date */
	bool SCRIPTO_API ScheduleScript(const QString& name, const QDateTime& targetDate, std::function<void(const QString&)> onOutput, std::function<void(const QString&)> onError, std::function<void(QProcess::ExitStatus)> onFinish);
	/* schedules a script to be run after a given period of time in seconds */
	bool SCRIPTO_API ScheduleScript(const QString& name, long long afterPeriod, std::function<void(const QString&)> onOutput, std::function<void(const QString&)> onError, std::function<void(QProcess::ExitStatus)> onFinish);
}