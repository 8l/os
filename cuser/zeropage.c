#include "common.h"

/* Silly little service that'll give you read-only (and execute) access to any
 * number of pages filled with zeroes. */

static const uintptr_t ALLOWED_FLAGS = PROT_READ | PROT_EXECUTE;

static const char zeropage[4096] __attribute__((aligned(4096)));

void start() {
	const uintptr_t fresh = 256;
	map(0, MAP_ANON | PROT_READ, (void*)&zeropage, 0, sizeof(zeropage));
	/* Page is zeroed when we get it from pfalloc. PFALLOC gives one unique
	 * page frame for each page faulted in from it. Until it runs out of
	 * memory... */
	/* Likewise from the kernel anonymous memory allocator, as long as we use
	 * the backdoor... */

	printf("zeropage: page at %p\n", (void*)&zeropage);
	if (*(volatile char*)zeropage) {
		puts("zeropage: nonzero value in zero page!?\n");
	} else {
		puts("zeropage: zero page is indeed zero\n");
	}

	// Try to suicide
	// Sweet! This does crash!
	//((volatile char*)zeropage)[0]++;

	for (;;) {
		uintptr_t arg1, arg2;
		uintptr_t rcpt = fresh;
		uintptr_t msg = recv2(&rcpt, &arg1, &arg2);
		// PFAULT: source handle, offset, requested flags
		switch (msg & 0xff) {
		case MSG_PFAULT: {
			printf("zeropage: %x pfault %x %x\n", rcpt, arg1, arg2);
			arg2 &= ALLOWED_FLAGS;
			arg1 = (uintptr_t)zeropage;
			ipc2(MSG_GRANT, &rcpt, &arg1, &arg2);
			break;
		}
		}
		if (rcpt == fresh) {
			hmod(rcpt, 0, 0);
		}
	}
}
