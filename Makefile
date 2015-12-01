tcpTargets = tcpServer tcpClient
threadTargets = threadUser
alltargets = $(tcpTargets)  $(threadTargets)

threadUser: threadUser.c
	gcc -pthread -o$@ $<

.PHONY: allTcp
allTcp: $(tcpTargets)

.PHONY: clean 
clean: 
	- rm $(alltargets)

