otherTargets = dynamicalBuffer
tcpTargets = HectorLassoEcho tcpServer tcpClient frameClient frameServer selectServer
threadsTargets = threadUser ficheux pesenti simpleSem
tcpThrTargets = threadedServer threadedClient
alltargets = $(tcpTargets)  $(threadsTargets) $(tcpThrTargets) $(otherTargets)


gccopt=-Wall
GCC=gcc ${gccopt}

.PHONY: all
all: $(alltargets)

.PHONY: allThreads
allThreads: $(threadsTargets)

.PHONY: allTcp
allTcp: $(tcpTargets)

.PHONY: others
others: $(otherTargets)

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

$(otherTargets): $$@.o 
	${GCC} -o$@ $^

$(tcpTargets): $$@.o clientserverTools.o
	${GCC} -o$@ $^

$(threadsTargets): $$@.c
	${GCC} -pthread -o$@ $^

$(tcpThrTargets): $$@.o clientserverTools.o
	${GCC} -pthread -o$@ $^

tryFloat2N: tryFloat2N.o netencodingTools.o
	${GCC} -o$@ $^

