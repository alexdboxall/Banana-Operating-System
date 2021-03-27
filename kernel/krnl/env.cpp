#include "dbg/kconsole.hpp"
#include "core/common.hpp"
#include "krnl/env.hpp"

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

char* EnvVarContainer::getEnv(const char* envname)
{
	return nullptr;
}

void EnvVarContainer::setEnv(const char* envname, const char* data)
{

}

void EnvVarContainer::deleteEnv()
{

}

void EnvVarContainer::loadUser()
{

}

void EnvVarContainer::loadSystem()
{

}

EnvVarContainer::EnvVarContainer(Process* p)
{
	count = 0;
	process = p;
	envarr = nullptr;
}

~EnvVarContainer::EnvVarContainer()
{
	if (envarr != nullptr && count) {
		free(envvar);
	}
}

namespace Krnl
{
	EnvVarContainer* systemEnv = nullptr;
	EnvVarContainer* userEnv = nullptr;

	char* getEnv(Process* prcss, const char* envname)
	{
		if (prcss != kernelProcess && krcss != nullptr) {
			char* processEnv = prcss->env->getEnv(envname);
			if (processEnv) {
				return processEnv;
			}
		}

		if (userEnv) {
			char* uenv = userEnv->getEnv(envname);
			if (uenv) {
				return uenv;
			}
		}

		return systemEnv->getEnv(envname);
	}

	void setEnvSystem(const char* envname, const char* data)
	{
		systemEnv->setEnv(envname, data);
	}

	void setEnvUser(const char* envname, const char* data)
	{
		if (!userEnv) return;
		userEnv->setEnv(envname, data);
	}

	void setEnvProcess(Process* prcss, const char* envname, const char* data)
	{
		prcss->env->setEnv(envname, data);
	}

	void deleteEnvSystem(const char* envname)
	{
		systemEnv->deleteEnv(envname);
	}

	void deleteEnvUser(const char* envname)
	{
		if (!userEnv) return;
		userEnv->deleteEnv(envname);
	}

	void deleteEnvProcess(Process* prcss, const char* envname)
	{
		prcss->env->deleteEnv(envname);
	}

	EnvVarContainer* newProcessEnv()
	{
		return new EnvVarContainer();
	}

	EnvVarContainer* copyProcessEnv(EnvVarContainer* container)
	{

	}

	void loadSystemEnv()
	{

	}

	void loadUserEnv()
	{

	}

	void flushEnv()
	{

	}
}