#ifndef _ENV_KRNL_HPP_
#define _ENV_KRNL_HPP_

#include "core/main.hpp"

class Process;

struct EnvVar
{
	char* key;
	char* value;
};

class EnvVarContainer
{
private:

protected:

public:
	int count;
	EnvVar* envarr;
	Process* process;

	void __loadUser();
	void __loadSystem();

	char* getEnv(const char* envname);
	void setEnv(const char* envname, const char* data);
	void deleteEnv(const char* envname);

	EnvVarContainer(Process* p);
	~EnvVarContainer();
};

namespace Krnl
{
	extern EnvVarContainer* systemEnv;
	extern EnvVarContainer* userEnv;

	char* getEnv(Process* prcss, const char* envname);

	void setEnvSystem(const char* envname, const char* data);
	void setEnvUser(const char* envname, const char* data);
	void setEnvProcess(Process* prcss, const char* envname, const char* data);

	void deleteEnvSystem(const char* envname);
	void deleteEnvUser(const char* envname);
	void deleteEnvProcess(Process* prcss, const char* envname);

	void loadSystemEnv();
	void loadUserEnv();

	void flushEnv();

	EnvVarContainer* newProcessEnv(Process* prcss);
	EnvVarContainer* copyProcessEnv(Process* newProcess);
}

#endif