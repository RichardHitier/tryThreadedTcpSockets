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

##
# Rules
#

%.o: %.c
	gcc -c -o$@ $< 

threadedServer.o: threadedServer.c
	gcc -pthread -c -o$@ $<
threadedServer: threadedServer.o clientserverTools.o
	gcc -pthread -o$@ $^

.SECONDEXPANSION:

$(tcpTargets): $$@.o clientserverTools.o
	gcc -o$@ $^

$(threadsTargets): $$@.c
	gcc -pthread -o$@ $@.c
