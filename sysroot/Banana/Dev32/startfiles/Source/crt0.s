.section .text
.extern __i_libraryInit

.global _start
_start:
	# Set up end of the stack frame linked list.
	movl $0, %ebp
	pushl %ebp	#eip = 0
	pushl %ebp	#ebp = 0
	movl %esp, %ebp

	# Run the global constructors.
	call _init

	# This inits the lib, sets up the terminal session, parses cmd line args and CALLS MAIN
	call __i_libraryInit
	
	# Call 'special stuff'
	call _fini

	# Terminate the process with the exit code.
	pushl %eax
	call exit		#this will end up doing a close terminal session as well
	
.size _start, . - _start
