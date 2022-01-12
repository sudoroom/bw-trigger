

trigger: trigger.c
	$(CC) -o trigger trigger.c -L nethogs/src -lnethogs


all: trigger
