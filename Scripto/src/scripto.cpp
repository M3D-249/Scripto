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
	struct BackendConfig
	{

	} _config;
	QJsonDocument _jconfig;

#pragma region Globals
	QMap<QString, Script> _scripts;
	QMap<long long, QProcess*> _runningProcesses;
	QMap<long long, QProcess*> _scheduledScripts;
#pragma endregion

#pragma region Initialization
	void Init(const QString& appName, const QString& orgName)
	{
		QCoreApplication::setApplicationName(appName);
		QCoreApplication::setOrganizationDomain(orgName);
	}
#pragma endregion

#pragma region Local Functions Declarations
	bool IsScriptAvalible(const QString& name);
	QString GetScriptID(const QString& scriptName);
	ScriptType ScriptTypeFromString(const QString& str);
	QString ScriptTypeToString(ScriptType type);
	RunPolicy RunPolicyFromString(const QString& str);
	QString RunPolicyToString(RunPolicy rp);
	QJsonDocument LoadJsonFile(const QString& path);
	bool SaveJsonFile(const QJsonDocument& source, const QString& destination);
	QJsonObject ScriptToJson(const Script& script);
	Script JsonToScript(const QJsonObject& j);
	bool SaveScript(const Script& script);
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

	ScriptType ScriptTypeFromString(const QString& str)
	{
		if (str == "python") return ScriptType::Python;
		else if (str == "exe") return ScriptType::Executable;
		else if (str == "bash") return ScriptType::Bash;
		else return ScriptType::None;
	}

	QString ScriptTypeToString(ScriptType type)
	{
		switch (type)
		{
		case Scripto::ScriptType::None: return "none";
		case Scripto::ScriptType::Python: return "python";
		case Scripto::ScriptType::Bash: return "bash";
		case Scripto::ScriptType::Executable: return "exe";
		default: return "none";
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
	QStringList GetStoredScriptsNames() // TODO: make global variable to hold a list of scripts names
	{
		QStringList names;
		for (const auto& script : _scripts.values())
		{
			names.append(script.name);
		}
		return names;
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
		case Scripto::ScriptType::Executable: filePath += ".exe"; break;
#endif
		case Scripto::ScriptType::Python: filePath += ".py"; break;
		case Scripto::ScriptType::Bash: filePath += ".sh"; break;
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
		script.workingDir = workingDir;
		script.type = type;
		script.runPolicy = runPolicy;

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
		
		qDebug() << "Script removed successfuly: " << script.name;

		return SaveJsonFile(doc, ScriptsFilePath());
	}

	long long RunScript(const QString& name, std::function<void(const QString&)> onOutput, std::function<void(const QString&)> onError, std::function<void(QProcess::ExitStatus)> onFinish)
	{
		if (IsScriptAvalible(name))
		{
			const auto& script = _scripts[GetScriptID(name)];
			QString cmd = "";
			switch (script.type)
			{
			default:
			case Scripto::ScriptType::None:
			case Scripto::ScriptType::Executable: break;
			case Scripto::ScriptType::Python: cmd = "python"; break;
			case Scripto::ScriptType::Bash: cmd = "bash"; break;
			}

			QProcess* process = new QProcess;
			QObject::connect(process, &QProcess::readyReadStandardOutput, [=] {
				QString output = QString::fromUtf8(process->readAllStandardOutput());
				onOutput(output);
			});
			QObject::connect(process, &QProcess::finished, [=] {
				onFinish(process->exitStatus());
				process->deleteLater();
			});
			QObject::connect(process, &QProcess::readyReadStandardError, [=] {
				QString error = QString::fromUtf8(process->readAllStandardError());
				onError(error);
			});

			if (!script.workingDir.isEmpty())
				if (script.workingDir == ".") // run in the same directory as the script file
				{
					QString cwd = script.path.chopped(script.path.length() - script.path.lastIndexOf("/") - 1);
					qDebug() << "script file name length" << cwd;
					process->setWorkingDirectory(cwd);
				}
				else if (QDir().exists(script.workingDir))
					process->setWorkingDirectory(script.workingDir);
				
			process->start(cmd, { script.path });
			_runningProcesses[process->processId()] = process;
			return process->processId();
		}

		return SCRIPTO_ERROR;
	}

	bool ScheduleScript(const QString& name, const QDateTime& targetDate, std::function<void(const QString&)> onOutput, std::function<void(const QString&)> onError, std::function<void(QProcess::ExitStatus)> onFinish)
	{
		/// TODO: Make it better with logs ability
		if (!IsScriptAvalible(name))
			return false;
		
		long long msTime = QDateTime::currentDateTime().msecsTo(targetDate);
		if (msTime < 0) // past time 
			return false;

		QTimer::singleShot(msTime, [=]() {
			RunScript(name, onOutput, onError, onFinish);
		});
	}
	bool ScheduleScript(const QString& name, long long afterPeriod, std::function<void(const QString&)> onOutput, std::function<void(const QString&)> onError, std::function<void(QProcess::ExitStatus)> onFinish)
	{
		if (!IsScriptAvalible(name))
			return false;

		if (afterPeriod < 0)
			return false;
		
		long long ms = afterPeriod * 1000;

		QTimer::singleShot(ms, [=]() {
			RunScript(name, onOutput, onError, onFinish);
		});
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
