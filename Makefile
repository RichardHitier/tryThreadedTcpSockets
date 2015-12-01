tcpTargets = tcpServer tcpClient
threadsTargets = threadUser ficheux pesenti simpleSem
alltargets = $(tcpTargets)  $(threadsTargets)

.PHONY: all
all: $(alltargets);

.PHONY: allThreads
allThreads: $(threadsTargets)

.PHONY: allTcp
allTcp: $(tcpTargets)

.PHONY: clean 
clean: 
	- rm $(alltargets)


$(threadsTargets):
	gcc -pthread -o$@ $@.c
