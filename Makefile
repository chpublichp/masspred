.DEFAULT_GOAL = all
.PHONY: all
all: tools

.PHONY: clean
clean: MTARGET = clean
clean: tools

.PHONY: tools
tools:
	$(MAKE) -C tools $(MTARGET)
