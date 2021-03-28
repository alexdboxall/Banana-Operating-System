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
	for (int i = 0; i < count; ++i) {
		if (!strcmp(envname, envarr[i].key)) {
			return envarr[i].value;
		}
	}
	return nullptr;
}

void EnvVarContainer::setEnv(const char* envname, const char* data)
{
	EnvVar e;
	e.key = (char*) malloc(strlen(envname) + 1);
	e.value = (char*) malloc(strlen(data) + 1);

	memset(e.key, 0, strlen(envname) + 1);
	memcpy(e.key, envname, strlen(envname) + 1);

	memset(e.value, 0, strlen(data) + 1);
	memcpy(e.value, data, strlen(data) + 1);

	count++;
	envarr = (EnvVar*) realloc(envarr, count * sizeof(EnvVar));
	memcpy((void*) (envarr + count - 1), &e, sizeof(EnvVar));
}

void EnvVarContainer::deleteEnv(const char* envname)
{

}

char defaultSysEnv[] = "PATH=C:/Banana/System;C:/Banana/Applications;C:/Banana/Applications/System;\n";

void EnvVarContainer::loadFrom(const char* filename, const char* defaultN)
{
	File* f = new File(filename, process);
	int br;

	if (!f->exists()) {
		f->open(FILE_OPEN_WRITE_NORMAL);
		f->write(strlen(defaultN), (void*) defaultN, &br);
		f->close();
	}

	char line[256];
	memset(line, 0, 256);
	int linePtr = 0;
	int equSpot = 0;
	f->open(FILE_OPEN_READ);
	char c;
	do {
		f->read(1, &c, &br);
		if (c == '\r') continue;
		if (equSpot && (c == '\n' || br == 0 || linePtr >= 255)) {
			EnvVar e;
			e.key = (char*) malloc(equSpot + 1);
			e.value = (char*) malloc(linePtr - equSpot + 4);
			memset(e.key, 0, equSpot + 1);
			memcpy(e.key, line, equSpot);

			memset(e.value, 0, linePtr - equSpot + 4);
			memcpy(e.value, line + equSpot, strlen(line + equSpot) + 1);

			count++;
			envarr = (EnvVar*) realloc(envarr, count * sizeof(EnvVar));
			memcpy((void*) (envarr + count - 1), &e, sizeof(EnvVar));

			memset(line, 0, 256);
			linePtr = 0;
			equSpot = 0;

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
	loadFrom("C:/Banana/Registry/System/env.txt", defaultSysEnv);
}

void EnvVarContainer::__loadUser()
{

}

EnvVarContainer::EnvVarContainer(Process* p)
{
	count = 0;
	process = p;
	envarr = nullptr;
}

EnvVarContainer::~EnvVarContainer()
{
	if (envarr != nullptr && count) {
		free(envarr);
	}
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

	int getProcessTotalEnvCount(Process* prcss)
	{
		if (!userEnv) {
			return prcss->env->count + systemEnv->count;
		}
		return prcss->env->count + systemEnv->count + userEnv->count;
	}

	EnvVar getProcessEnvPair(Process* prcss, int num)
	{
		if (!userEnv) {
			if (num < prcss->env->count) {
				return prcss->env->envarr[num];

			} else if (num < prcss->env->count + systemEnv->count) {
				kprintf("got env %d -> '%s'\n", num, systemEnv->envarr[num - prcss->env->count].value);
				return systemEnv->envarr[num - prcss->env->count];
			}

		} else {
			if (num < prcss->env->count) {
				return prcss->env->envarr[num];

			} else if (num < prcss->env->count + userEnv->count) {
				return userEnv->envarr[num - prcss->env->count];

			} else if (num < prcss->env->count + userEnv->count + systemEnv->count) {
				return systemEnv->envarr[num - prcss->env->count - userEnv->count];
			}

		}
		
		panic("getProcessEnvPair FAILURE");

		EnvVar e;
		e.key = nullptr;
		e.value = nullptr;
		return e;
	}
}