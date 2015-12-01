tcpTargets = tcpServer tcpClient
threadTargets = threadUser
alltargets = $(tcpTargets)  $(threadTargets)

threadUser: threadUser.c
	gcc -lpthread -o$@ $<

.PHONY: all
all: $(tcpTargets)

.PHONY: clean 
clean: 
	- rm $(alltargets)

