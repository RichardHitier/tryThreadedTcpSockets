tcpTargets = tcpServer tcpClient frameClient frameServer
threadsTargets = threadUser ficheux pesenti simpleSem
tcpThrTargets = threadedServer threadedClient
alltargets = $(tcpTargets)  $(threadsTargets) $(tcpThrTargets)

gccopt=-Wall
GCC=gcc ${gccopt}

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
	${GCC} -c -o$@ $< 

# guess prerequisites from target name
#
.SECONDEXPANSION:

$(tcpTargets): $$@.o clientserverTools.o
	${GCC} -o$@ $^

$(threadsTargets): $$@.c
	${GCC} -pthread -o$@ $^

$(tcpThrTargets): $$@.o clientserverTools.o
	${GCC} -pthread -o$@ $^
