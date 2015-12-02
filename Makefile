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

# guess prerequisites from target name
#
.SECONDEXPANSION:

$(tcpTargets): $$@.o clientserverTools.o
	gcc -o$@ $^

$(threadsTargets): $$@.c
	gcc -pthread -o$@ $^

$(tcpThrTargets): $$@.o clientserverTools.o
	gcc -pthread -o$@ $^
