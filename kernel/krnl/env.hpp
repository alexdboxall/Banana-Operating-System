#ifndef _ENV_KRNL_HPP_
#define _ENV_KRNL_HPP_

#include "core/main.hpp"
#include "thr/prcssthr.hpp"

struct EnvVar
{
	char* key;
	char* value;
};

class EnvVarContainer
{
private:
	int count;
	EnvVar* envarr;
	Process* process;

protected:
	friend void Krnl::loadSystemEnv();
	friend void Krnl::loadUserEnv();

	void loadUser();
	void loadSystem();

public:
	char* getEnv(const char* envname);
	void setEnv(const char* envname, const char* data);
	void deleteEnv();

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

	EnvVarContainer* newProcessEnv();
	EnvVarContainer* copyProcessEnv(EnvVarContainer* container);
}

#endif