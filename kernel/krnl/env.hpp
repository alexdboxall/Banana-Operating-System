#ifndef _ENV_KRNL_HPP_
#define _ENV_KRNL_HPP_

#include "krnl/main.hpp"

class Process;

struct EnvVar
{
	char* key;
	char* value;
};

class EnvVarContainer
{
private:
	void loadFrom(const char* filename, const char* defaultN);

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


extern EnvVarContainer* KeSystemEnv;
extern EnvVarContainer* KeUserEnv;

char* KeGetEnv(Process* prcss, const char* envname);

void KeSetEnvSystem(const char* envname, const char* data);
void KeSetEnvUser(const char* envname, const char* data);
void KeSetEnvProcess(Process* prcss, const char* envname, const char* data);

void KeDeleteEnvSystem(const char* envname);
void KeDeleteEnvUser(const char* envname);
void KeDeleteEnvProcess(Process* prcss, const char* envname);

void KeLoadSystemEnv();
void KeLoadUserEnv();

void KeFlushEnv();

EnvVarContainer* KeNewProcessEnv(Process* prcss);
EnvVarContainer* KeCopyProcessEnv(Process* oldProcess, Process* newProcess);

int KeGetProcessTotalEnvCount(Process* prcss);
EnvVar KeGetProcessEnvPair(Process* prcss, int num);


#endif