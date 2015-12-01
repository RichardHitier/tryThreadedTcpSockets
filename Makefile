tcpTargets = tcpServer tcpClient
threadsTargets = threadUser ficheux pesenti simpleSem
alltargets = $(tcpTargets)  $(threadsTargets)

.PHONY: all
all: $(alltargets)

.PHONY: allThreads
allThreads: $(threadsTargets)

.PHONY: allTcp
allTcp: $(tcpTargets)

.PHONY: clean 
clean: 
	- rm $(alltargets)
	- rm *.o

.SECONDEXPANSION:

$(tcpTargets): $$@.o clientserverTools.o
	gcc -o$@ $^

$(threadsTargets): $$@.c
	gcc -pthread -o$@ $@.c

%.o: %.c
	gcc -c -o$@ $< 
