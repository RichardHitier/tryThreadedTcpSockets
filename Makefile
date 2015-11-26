targets = server client

.PHONY: all
all: $(targets)

.PHONY: clean 
clean: 
	- rm $(targets)

