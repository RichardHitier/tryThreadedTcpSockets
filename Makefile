tcpTargets = tcpServer tcpClient
threadsTargets = threadUser ficheux pesenti simpleSem
tcpThrTargets = threadedServer threadedClient
alltargets = $(tcpTargets)  $(threadsTargets) $(tcpThrTargets)

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

.SECONDEXPANSION:

$(tcpThrTargets): $$@.o clientserverTools.o
	gcc -pthread -o$@ $^

$(tcpTargets): $$@.o clientserverTools.o
	gcc -o$@ $^

$(threadsTargets): $$@.c
	gcc -pthread -o$@ $@.c
