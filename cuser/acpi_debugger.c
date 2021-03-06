#include "common.h"

#define log printf
#if 0
#define debug log
#else
#define debug(...) (void)0
#endif

static const uintptr_t acpi_handle = 4;

static void prompt() {
	puts("Enter debugger command: (Esc cancels)\n");
	for (;;) {
		uintptr_t c = getchar();
		uintptr_t msg;
		switch (c) {
		case '\n': msg = MSG_ACPI_DEBUGGER_CMD; break;
		case 27: c = '\n'; msg = MSG_ACPI_DEBUGGER_CLR_BUFFER; break;
		default: msg = MSG_ACPI_DEBUGGER_BUFFER; break;
		}
		// Even the buffer message can cause ACPI to do output, which will
		// deadlock because the console thinks we own it.
		putchar(c);
		sendrcv1(msg, acpi_handle, &c);
		if (msg != MSG_ACPI_DEBUGGER_BUFFER) {
			break;
		}
	}
}

void start() {
	__default_section_init();
	sendrcv0(MSG_ACPI_DEBUGGER_INIT, acpi_handle);
	puts("ACPICA Debugger Shell\n");
	for (;;) {
		prompt();
	}
}
