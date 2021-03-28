#include "krnl/env.hpp"
#include "core/common.hpp"
#include "thr/prcssthr.hpp"
#include "dbg/kconsole.hpp"
#include "fs/vfs.hpp"

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

char defaultSysEnv[] = "PATH=C:/Banana/System;C:/Banana/Applications;C:/Banana/Applications/System;\n";

void EnvVarContainer::loadFrom(const char* filename, const char* defaultN)
{
	File* f = new File(filename, process);
	int br;

	if (!f->exists()) {
		f->open(FILE_OPEN_WRITE_NORMAL);
		f->write(strlen(defaultN), defaultN, &br);
		f->close();
	}

	char line[256];
	int linePtr = 0;
	int equSpot = 0;
	f->open(FILE_OPEN_READ);
	do {
		f->read(1, &c, &br);
		if (c == '\n' || br == 0 || linePtr >= 255) {
			EnvVar e;
			e.key = (char*) malloc(equSpot + 1);
			e.value = (char*) malloc(linePtr - equSpot + 4);
			memset(e.key, 0, equSpot + 1);
			memcpy(e.key, line, equSpot);

			memset(e.value, 0, linePtr - equSpot + 4);
			memcpy(e.value, line + equSpot, strlen(line + equSpot));

			count++;
			envarr = realloc(envarr, count * sizeof(EnvVar));
			memcpy((void*) (envarr + count - 1), &e, sizeof(EnvVar));

			memset(line, 0, 256);
			linePtr = 0;

		} else if (c == '=') {
			equSpot = linePtr;
		} else {
			line[linePtr++] = c;
		}

	} while (br);

	kprintf("loaded %d system environment variables...\n", count);
}

void EnvVarContainer::__loadSystem()
{
	loadFrom("C:/Banana/Registry/System/env.txt", defaultSysEnv)
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