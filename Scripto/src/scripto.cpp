#include <qstringlist.h>
#include <qmap.h>
#include <qjsondocument.h>
#include <qfile.h>
#include <qstandardpaths.h>
#include <qdir.h>
#include <qcoreapplication.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qprocess.h>
#include <qobject.h>
#include <functional>
#include <qtimer.h>

#include "scripto.h"

namespace Scripto
{
#pragma region Globals
	QMap<QString, Script> _scripts;
	QMap<long long, QProcess*> _runningProcesses;
	QMap<long long, QProcess*> _scheduledScripts;

	std::atomic<int> _onNewScriptAddedCallbacksCounter = 0;
	std::atomic<int> _onScriptRemovedCallbacksCounter = 0;
	QMap<int, std::function<void(const QString&)>> _onNewScriptAddedCallbacks;
	QMap<int, std::function<void(const QString&)>> _onScriptRemovedCallbacks;

	// constants
	const QString SCRIPT_TYPE_PYTHON = "python";
	const QString SCRIPT_TYPE_BASH = "bash";
	const QString SCRIPT_TYPE_EXE = "exe";
	const QString SCRIPT_TYPE_NONE = "none";
	const QString SCRIPT_TYPE_PYTHON_EXTENTION = ".py";
	const QString SCRIPT_TYPE_BASH_EXTENTION = ".sh";
	const QString SCRIPT_TYPE_EXE_EXTENTION = ".exe";
	const QString SCRIPT_TYPE_NONE_EXTENTION = "";

	const  QStringList ALLOWED_SCRIPTS_TYPES_NAMES = { 
		SCRIPT_TYPE_PYTHON,
		SCRIPT_TYPE_BASH,
		SCRIPT_TYPE_EXE,
		SCRIPT_TYPE_NONE 
	};
	const  QStringList ALLOWED_SCRIPTS_TYPES_EXTENTIONS = { 
		SCRIPT_TYPE_PYTHON_EXTENTION,
		SCRIPT_TYPE_BASH_EXTENTION,
		SCRIPT_TYPE_EXE_EXTENTION,
		SCRIPT_TYPE_NONE_EXTENTION
	};
#pragma endregion

#pragma region Initialization
	void Init(const QString& appName, const QString& orgName)
	{
		QCoreApplication::setApplicationName(appName);
		QCoreApplication::setOrganizationDomain(orgName);
		LoadScripts();
	}
#pragma endregion

#pragma region Local Functions Declarations
	bool IsScriptAvalible(const QString& name);
	QString GetScriptID(const QString& scriptName);
	QJsonDocument LoadJsonFile(const QString& path);
	bool SaveJsonFile(const QJsonDocument& source, const QString& destination);
	QJsonObject ScriptToJson(const Script& script);
	Script JsonToScript(const QJsonObject& j);
	bool SaveScript(const Script& script);
	void SaveSchedules();
#pragma endregion

#pragma region Local Functions Definitions

	bool IsScriptAvalible(const QString& name)
	{
		QString id = GetScriptID(name);
		return _scripts.contains(id);
	}

	QString GetScriptID(const QString& scriptName)
	{
		QString id = scriptName.toLower().trimmed();
		id.replace(QRegularExpression("[^a-z0-9]+"), "-");
		while (id.startsWith("-"))
			id.removeFirst();
		while (id.endsWith("-"))
			id.removeLast();
		return id;
	}

	QJsonDocument LoadJsonFile(const QString& path)
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
		{
			qWarning() << "Failed to open: " << path;
			return {};
		}

		QJsonParseError err;
		QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &err);
		if (err.error != QJsonParseError::NoError)
		{
			qWarning() << "Json parse error: " << err.errorString();
			return {};
		}

		return document;
	}

	bool SaveJsonFile(const QJsonDocument& source, const QString& destination)
	{
		QFile file(destination);
		if (!file.open(QIODevice::WriteOnly))
		{
			qWarning() << "Failed to open: " << destination;
			return {};
		}

		return file.write(source.toJson(QJsonDocument::Indented)) != -1;
	}

	QJsonObject ScriptToJson(const Script& script)
	{
		QJsonObject object;
		object["id"] = script.id;
		object["name"] = script.name;
		object["path"] = script.path;
		object["type"] = ScriptTypeToString(script.type);
		object["working-dir"] = script.workingDir;
		object["run-policy"] = RunPolicyToString(script.runPolicy);

		return object;
	}

	Script JsonToScript(const QJsonObject& j)
	{
		Script s;
		s.id = j["id"].toString();
		s.name = j["name"].toString();
		s.path = j["path"].toString();
		s.type = ScriptTypeFromString(j["type"].toString());
		s.runPolicy = RunPolicyFromString(j["run-policy"].toString());
		s.workingDir = j["working-dir"].toString();
		return s;
	}

	bool SaveScript(const Script& script)
	{
		if (!IsScriptAvalible(script.name))
		{
			_scripts[script.id] = script;
			QJsonObject jScript = ScriptToJson(script);
			QJsonDocument doc = LoadJsonFile(ScriptsFilePath());
			QJsonObject root = doc.object();
			QJsonArray scriptsArray = root["scripts"].toArray();

			scriptsArray.append(jScript);
			root["scripts"] = scriptsArray;
			doc.setObject(root);

			qDebug() << "Script added successfuly: " << script.name;
			return SaveJsonFile(doc, ScriptsFilePath());
		}

		return false;
	}

#pragma endregion

#pragma region Public API Functions Definitions

	QStringList AllowedScriptsTypes()
	{
		return ALLOWED_SCRIPTS_TYPES_NAMES;
	}

	QStringList AllowedScriptsTypesFileExtentions()
	{
		return ALLOWED_SCRIPTS_TYPES_EXTENTIONS;
	}

	ScriptType ScriptTypeFromString(const QString& str)
	{
		if (str == SCRIPT_TYPE_PYTHON) return ScriptType::Python;
		else if (str == SCRIPT_TYPE_EXE) return ScriptType::Executable;
		else if (str == SCRIPT_TYPE_BASH) return ScriptType::Bash;
		else return ScriptType::None;
	}

	ScriptType ScriptTypeFromExtentionString(const QString& str)
	{
		if (str == SCRIPT_TYPE_PYTHON_EXTENTION) return ScriptType::Python;
		else if (str == SCRIPT_TYPE_EXE_EXTENTION) return ScriptType::Executable;
		else if (str == SCRIPT_TYPE_BASH_EXTENTION) return ScriptType::Bash;
		else if (str == SCRIPT_TYPE_NONE_EXTENTION) return ScriptType::None;
		else return ScriptType::None;
	}

	QString ScriptTypeToString(ScriptType type)
	{
		switch (type)
		{
		case Scripto::ScriptType::None: return SCRIPT_TYPE_NONE;
		case Scripto::ScriptType::Python: return SCRIPT_TYPE_PYTHON;
		case Scripto::ScriptType::Bash: return SCRIPT_TYPE_BASH;
		case Scripto::ScriptType::Executable: return SCRIPT_TYPE_EXE;
		default: return SCRIPT_TYPE_NONE;
		}
	}

	RunPolicy RunPolicyFromString(const QString& str)
	{
		if (str == "admin") return RunPolicy::Administrator;
		else return RunPolicy::NormalUser;
	}

	QString RunPolicyToString(RunPolicy rp)
	{
		switch (rp)
		{
		case Scripto::RunPolicy::Administrator: return "admin";
		case Scripto::RunPolicy::NormalUser:
		default: return "normal";
		}
	}

	QStringList GetStoredScriptsNames() // TODO: make global variable to hold a list of scripts names
	{
		QStringList names;
		for (const auto& script : _scripts.values())
		{
			names.append(script.name);
		}
		return names;
	}

	int setOnNewScriptAddedCallback(std::function<void(const QString& scriptName)> functr)
	{
		int id = _onNewScriptAddedCallbacksCounter++;
		_onNewScriptAddedCallbacks[id] = functr;
		return id;
	}

	int setOnScriptRemovedCallback(std::function<void(const QString& scriptName)> functr)
	{
		int id = _onScriptRemovedCallbacksCounter++;
		_onScriptRemovedCallbacks[id] = functr;
		return id;
	}

	void unsetOnNewScriptAddedCallback(int id)
	{
		if (_onNewScriptAddedCallbacks.contains(id))
			_onNewScriptAddedCallbacks.remove(id);
	}

	void unsetOnScriptRemovedCallback(int id)
	{
		if (_onScriptRemovedCallbacks.contains(id))
			_onScriptRemovedCallbacks.remove(id);
	}

	int LoadScripts()
	{
		QJsonDocument doc = LoadJsonFile(ScriptsFilePath());
		QJsonObject root = doc.object();

		for (const QJsonValue& value : root["scripts"].toArray())
		{
			Script s = JsonToScript(value.toObject());
			_scripts[s.id] = s;

			qDebug() << value.toJson(QJsonDocument::Indented);
		}

		return _scripts.size();
	}

	bool AddScript(const QString& name, const QString& path, const QString& workingDir, ScriptType type, RunPolicy runPolicy)
	{
		if (IsScriptAvalible(name))
			return false;

		Script script;
		script.id = GetScriptID(name);
		script.name = name;
		script.path = path;
		script.workingDir = workingDir;
		script.type = type;
		script.runPolicy = runPolicy;

		for (auto& functr : _onNewScriptAddedCallbacks)
			functr(script.name);

		return SaveScript(script);
	}

	bool AddInplaceScript(const QString& name, const QString& code, const QString& workingDir, ScriptType type, RunPolicy runPolicy)
	{
		if (IsScriptAvalible(name))
			return false;

		QString filePath = ScriptsPath() + "/" + name.trimmed().replace(QRegularExpression("[^a-zA-Z0-9]+"), "");

		switch (type)
		{
		default:
		case Scripto::ScriptType::None: break;
#if _WIN32
		case Scripto::ScriptType::Executable: filePath += SCRIPT_TYPE_EXE_EXTENTION; break;
#endif
		case Scripto::ScriptType::Python: filePath += SCRIPT_TYPE_PYTHON_EXTENTION; break;
		case Scripto::ScriptType::Bash: filePath += SCRIPT_TYPE_BASH_EXTENTION; break;
		}

		QFile file(filePath);
		if (!file.open(QIODevice::WriteOnly))
			return false;

		qDebug() << "Created file script: " << filePath;
		if (file.write(code.toUtf8() + "\n") < 0)
			return false;
		file.close();

		Script script;
		script.id = GetScriptID(name);
		script.name = name;
		script.path = filePath;
		
		if (workingDir == ".")
			script.workingDir = ScriptsPath();
		else
			script.workingDir = workingDir;

		script.type = type;
		script.runPolicy = runPolicy;

		for (auto& functr : _onNewScriptAddedCallbacks)
			functr(script.name);

		return SaveScript(script);
	}

	bool RemoveScript(const QString& name)
	{
		if (!IsScriptAvalible(name))
			return false;

		QString id = GetScriptID(name);
		Script script = _scripts[id]; // TODO: add to .removed/scripts.json
		_scripts.remove(id);

		QJsonDocument doc = LoadJsonFile(ScriptsFilePath());
		QJsonObject root = doc.object();
		QJsonArray scriptsArray = root["scripts"].toArray();

		for (int i = 0; i < scriptsArray.size(); ++i)
		{
			QJsonObject s = scriptsArray.at(i).toObject();
			if (s["id"] == id)
			{
				scriptsArray.removeAt(i);
				break;
			}
		}

		root["scripts"] = scriptsArray;
		doc.setObject(root);
		
		for (auto& functr : _onScriptRemovedCallbacks)
			functr(script.name);

		qDebug() << "Script removed successfuly: " << script.name;

		return SaveJsonFile(doc, ScriptsFilePath());
	}

	long long RunScript(const QString& name, std::function<void(const QString&)> onOutput, std::function<void(const QString&)> onError, std::function<void(QProcess::ExitStatus)> onFinish)
	{
		if (IsScriptAvalible(name))
		{
			const auto& script = _scripts[GetScriptID(name)];
			QString cmd = "";
			QString args = "";
			switch (script.type)
			{
			default:
			case Scripto::ScriptType::None:
			case Scripto::ScriptType::Executable: cmd = script.path; break;
			case Scripto::ScriptType::Python: cmd = "python"; args = script.path; break;
			case Scripto::ScriptType::Bash: cmd = "bash"; args = script.path; break;
			}

			QProcess* process = new QProcess;
			if (onOutput)
				QObject::connect(process, &QProcess::readyReadStandardOutput, [=] {
					QString output = QString::fromUtf8(process->readAllStandardOutput());
					onOutput(output);
				});
			if (onError)
				QObject::connect(process, &QProcess::readyReadStandardError, [=] {
					QString error = QString::fromUtf8(process->readAllStandardError());
					onError(error);
				});
			if (onFinish)
				QObject::connect(process, &QProcess::finished, [=] {
					onFinish(process->exitStatus());
					process->deleteLater();
				});
			QObject::connect(process, &QProcess::errorOccurred, [=](QProcess::ProcessError err) {
 				// handle this properly
				qDebug() << "Failed to start process to execute script with name: " << script.name << ", cmd = " << cmd << ", error: " << err; 
			});

			if (!script.workingDir.isEmpty())
				if (QFileInfo(script.workingDir).exists() && QFileInfo(script.workingDir).isDir())
					process->setWorkingDirectory(script.workingDir);
				else
					qDebug() << "script working dir doesn't exist please update. Script Name: " << script.name << ", Working Dir: " << script.workingDir;
				
			qDebug() << "Started Running Script: " << name;
			process->start(cmd, args.isEmpty() ? QStringList{} : QStringList{ args });

			_runningProcesses[process->processId()] = process;
			return process->processId();
		}

		return SCRIPTO_ERROR;
	}

	void RunScriptRepeatedilyScript(const QString& name,
		long long timeperiod, int repeatsCount,
		std::function<void(const QString& scriptName)> onExecutionStarted,
		std::function<void(const QString&)> onOutput,
		std::function<void(const QString&)> onError,
		std::function<void(QProcess::ExitStatus)> onFinish)
	{
		int repeatsRemaining = repeatsCount - 1;
		if (repeatsRemaining < 0)
			return;

		QTimer::singleShot(timeperiod, [=]() {
			RunScript(name, onOutput, onError, onFinish);
			if (onExecutionStarted)
				onExecutionStarted(name);
			RunScriptRepeatedilyScript(name, timeperiod, repeatsRemaining, onExecutionStarted, onOutput, onError, onFinish);
			});
	}

	bool ScheduleScript(const QString& name,
		const QDateTime& targetDate,
		bool repeat, int repeatsCount,
		std::function<void(const QString& scriptName)> onExecutionStarted, 
		std::function<void(const QString&)> onOutput, 
		std::function<void(const QString&)> onError, 
		std::function<void(QProcess::ExitStatus)> onFinish)
	{
		/// TODO: Make it better with logs ability
		if (!IsScriptAvalible(name))
			return false;
		
		// store them in json file to run if they were not executed and to remove otherwise and keep other file to save repeated ones
		long long msTime = QDateTime::currentDateTime().msecsTo(targetDate);
		if (msTime < 0) // past time 
			return false;

		if (repeat)
			RunScriptRepeatedilyScript(name, msTime, repeatsCount, onExecutionStarted, onOutput, onError, onFinish);
		else
			QTimer::singleShot(msTime, [=] {
			RunScript(name, onOutput, onError, onFinish);
		});

		return true;
	}

	bool ScheduleScript(const QString& name, long long afterPeriod,
		bool repeat, int repeatsCount,
		std::function<void(const QString& scriptName)> onExecutionStarted,
		std::function<void(const QString&)> onOutput,
		std::function<void(const QString&)> onError,
		std::function<void(QProcess::ExitStatus)> onFinish)
	{
		if (!IsScriptAvalible(name))
			return false;

		if (afterPeriod < 0)
			return false;

		if (repeat)
			RunScriptRepeatedilyScript(name, afterPeriod, repeatsCount, onExecutionStarted, onOutput, onError, onFinish);
		else
			QTimer::singleShot(afterPeriod, [=] {
			RunScript(name, onOutput, onError, onFinish);
				});

		return true;
	}

	bool WriteInputToProcess(long long processID, const QString& input)
	{
		if (_runningProcesses.contains(processID))
		{
			QProcess* process = _runningProcesses[processID];
			
			if (process->state() == QProcess::Running || process->state() == QProcess::Starting)
				return process->write((input + "\n").toUtf8()) != -1;
		}
		return false;
	}

	QString DataDirectory()
	{
		if (!QDir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).exists())
			QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
		return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
	}

	QString ConfigFilePath()
	{
		return QDir(DataDirectory()).filePath("config.json");
	}

	QString ScriptsFilePath()
	{
		return QDir(DataDirectory()).filePath("scripts.json");
	}

	QString ScriptsPath()
	{
		if (!QDir(QDir(DataDirectory()).filePath("Scripts")).exists())
			QDir().mkdir(QDir(DataDirectory()).filePath("Scripts"));
		return QDir(DataDirectory()).filePath("Scripts");
	}

#pragma endregion
}
