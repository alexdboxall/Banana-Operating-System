#include "krnl/env.hpp"
#include "krnl/common.hpp"
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
		br = 0;
		f->read(1, &c, &br);
		if (!c) break;
		if (c == '\r') continue;
		if (equSpot && (c == '\n' || br == 0 || linePtr >= 255)) {
			EnvVar e;
			e.key = (char*) malloc(equSpot + 1);
			e.value = (char*) malloc(linePtr - equSpot + 4);
			memset(e.key, 0, equSpot + 1);
			memcpy(e.key, line, equSpot);

			memset(e.value, 0, linePtr - equSpot + 4);
			memcpy(e.value, line + equSpot, strlen(line + equSpot));

			count++;
			if (!envarr) {
				envarr = (EnvVar*) malloc(sizeof(EnvVar));
			} else {
				envarr = (EnvVar*) realloc(envarr, count * sizeof(EnvVar));
			}
			memcpy((void*) (envarr + count - 1), &e, sizeof(EnvVar));

			memset(line, 0, 256);
			linePtr = 0;
			equSpot = 0;

		} else if (c == '=') {
			equSpot = linePtr;

		} else {
			if (linePtr < sizeof(line) - 1) {
				line[linePtr++] = c;
			} else {
				line[sizeof(line) - 1] = 0;
			}
		}

	} while (br);

	f->close();
	delete f;
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


EnvVarContainer* KeSystemEnv = nullptr;
EnvVarContainer* KeUserEnv = nullptr;

char* KeGetEnv(Process* prcss, const char* envname)
{
	if (prcss != kernelProcess && prcss != nullptr) {
		char* processEnv = prcss->env->getEnv(envname);
		if (processEnv) {
			return processEnv;
		}
	}

	if (KeUserEnv) {
		char* uenv = KeUserEnv->getEnv(envname);
		if (uenv) {
			return uenv;
		}
	}

	return KeSystemEnv->getEnv(envname);
}

void KeSetEnvSystem(const char* envname, const char* data)
{
	KeSystemEnv->setEnv(envname, data);
}

void KeSetEnvUser(const char* envname, const char* data)
{
	if (!KeUserEnv) return;
	KeUserEnv->setEnv(envname, data);
}

void KeSetEnvProcess(Process* prcss, const char* envname, const char* data)
{
	prcss->env->setEnv(envname, data);
}

void KeDeleteEnvSystem(const char* envname)
{
	KeSystemEnv->deleteEnv(envname);
}

void KeDeleteEnvUser(const char* envname)
{
	if (!KeUserEnv) return;
	KeUserEnv->deleteEnv(envname);
}

void KeDeleteEnvProcess(Process* prcss, const char* envname)
{
	prcss->env->deleteEnv(envname);
}

EnvVarContainer* KeNewProcessEnv(Process* prcss)
{
	return new EnvVarContainer(prcss);
}

EnvVarContainer* KeCopyProcessEnv(Process* oldProcess, Process* newProcess)
{
	EnvVarContainer* e = oldProcess->env;
	EnvVarContainer* copy = new EnvVarContainer(newProcess);
	copy->count = e->count;
	copy->envarr = (EnvVar*) malloc(sizeof(EnvVar) * e->count);
	memcpy(copy->envarr, e->envarr, sizeof(EnvVar) * e->count);
	return copy;
}

void KeLoadSystemEnv()
{
	KeSystemEnv = new EnvVarContainer(kernelProcess);
	KeSystemEnv->__loadSystem();
}

void KeLoadUserEnv()
{
	KeUserEnv = new EnvVarContainer(kernelProcess);
	KeUserEnv->__loadUser();
}

void KeFlushEnv()
{

}

int KeGetProcessTotalEnvCount(Process* prcss)
{
	if (!KeUserEnv) {
		return prcss->env->count + KeSystemEnv->count;
	}
	return prcss->env->count + KeSystemEnv->count + KeUserEnv->count;
}

EnvVar KeGetProcessEnvPair(Process* prcss, int num)
{
	if (!KeUserEnv) {
		if (num < prcss->env->count) {
			return prcss->env->envarr[num];

		} else if (num < prcss->env->count + KeSystemEnv->count) {
			return KeSystemEnv->envarr[num - prcss->env->count];
		}

	} else {
		if (num < prcss->env->count) {
			return prcss->env->envarr[num];

		} else if (num < prcss->env->count + KeUserEnv->count) {
			return KeUserEnv->envarr[num - prcss->env->count];

		} else if (num < prcss->env->count + KeUserEnv->count + KeSystemEnv->count) {
			return KeSystemEnv->envarr[num - prcss->env->count - KeUserEnv->count];
		}

	}

	KePanic("getProcessEnvPair FAILURE");

	EnvVar e;
	e.key = nullptr;
	e.value = nullptr;
	return e;
}