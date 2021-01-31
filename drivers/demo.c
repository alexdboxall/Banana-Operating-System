void Computer::start()
{
	lockScheduler();
	schedule();
	unlockScheduler();
	asm("sti");

	setBootMessage("Starting kernel threads");

	Process* idleProcess = new Process(true, "Idle Process", kernelProcess);
	idleProcess->createThread(idleFunction, nullptr, 255);

	cleanerThread = kernelProcess->createThread(cleanerTaskFunction, nullptr, 122);

	setBootMessage("Setting up the clock");

	clock = setupClock();
	addChild(clock);
	clock->open(0, 0, nullptr);

	kprintf("RTCL = 0x%X (%d)\n", (uint32_t) clock->timeInSecondsUTC(), sizeof(time_t));
	//kprintf("RTCH = 0x%X\n", (uint32_t) (clock->timeInSecondsUTC() >> 32));

	schedulingOn = true;

	setBootMessage("Setting up the filesystem");

	initVFS();
	setupSystemCalls();

	setBootMessage("Loading drivers");
	root->open(0, 0, nullptr);

	setBootMessage("Loading symbol table");
	loadKernelSymbolTable("C:/Banana/System/KERNEL32.EXE");

	setBootMessage("Creating swap file");
	VirtMem::setupPageSwapping(1);

	setBootMessage("Loading drivers");
	executeDLL(loadDLL("C:/Banana/Drivers/ps2.sys"), computer);
	loadDriversForAll();

	//for each cpu
		//start it
		//cpu[i]->open(i, 0, nullptr);

	executeDLL(loadDLL("C:/Banana/System/system.dll"), computer);

	VgaText::hiddenOut = false;
	debugTerminal.showCursor(true);
	preemptionOn = true;

	Process* usertask = new Process("C:/Banana/System/command.exe");
	setActiveTerminal(usertask->terminal);
	usertask->createUserThread();

	while (1) {
		blockTask(TaskState::Paused);
	}
}