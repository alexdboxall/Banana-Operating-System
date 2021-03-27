#include "krnl/env.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "dbg/kconsole.hpp"

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

void EnvVarContainer::deleteEnv(const char* envname)
{

}

void EnvVarContainer::__loadUser()
{

}

void EnvVarContainer::__loadSystem()
{

}

EnvVarContainer::EnvVarContainer(Process* p)
{
	kprintf("making env.\n");
	count = 0;
	process = p;
	envarr = nullptr;
	kprintf("made env.\n");
}

EnvVarContainer::~EnvVarContainer()
{
	kprintf("deleting env.\n");
	if (envarr != nullptr && count) {
		free(envarr);
	}
	kprintf("deleted env.\n");
}

namespace Krnl
{
	EnvVarContainer* systemEnv = nullptr;
	EnvVarContainer* userEnv = nullptr;

	char* getEnv(Process* prcss, const char* envname)
	{
		if (prcss != kernelProcess && prcss != nullptr) {
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

	EnvVarContainer* newProcessEnv(Process* prcss)
	{
		return new EnvVarContainer(prcss);
	}

	EnvVarContainer* copyProcessEnv(Process* oldProcess, Process* newProcess)
	{
		EnvVarContainer* e = oldProcess->env;
		EnvVarContainer* copy = new EnvVarContainer(newProcess);
		copy->count = e->count;
		copy->envarr = (EnvVar*) malloc(sizeof(EnvVar) * e->count);
		memcpy(copy->envarr, e->envarr, sizeof(EnvVar) * e->count);
		return copy;
	}

	void loadSystemEnv()
	{
		systemEnv = new EnvVarContainer(kernelProcess);
		systemEnv->__loadSystem();
	}

	void loadUserEnv()
	{
		userEnv = new EnvVarContainer(kernelProcess);
		userEnv->__loadUser();
	}

	void flushEnv()
	{

	}
}