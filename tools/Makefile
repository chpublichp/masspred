FASTA_TOOL     = fasta_tool-0.4
PARJOB         = parjob-0.5
REGION_FAIL    = region_fail-0.15
REGION_FILTER  = region_filter-0.19
EPITOPE_FAIL   = epitope_fail-0.12
EPITOPE_FILTER = epitope_filter-0.13
HYDRO          = hydro-0.2
COMMAND        = command-0.1

DIRS =                    \
	$(FASTA_TOOL)     \
	$(PARJOB)         \
	$(REGION_FAIL)    \
	$(REGION_FILTER)  \
	$(EPITOPE_FAIL)   \
	$(EPITOPE_FILTER) \
	$(HYDRO)          \
	$(COMMAND)        \

BIN = ../bin

.DEFAULT_GOAL = all
.PHONY: all
all: $(DIRS)
	mkdir -p $(BIN)
	cp $(FASTA_TOOL)/fasta_tool $(BIN)
	cp $(PARJOB)/parjob $(BIN)
	cp $(REGION_FAIL)/region_fail $(BIN)
	cp $(REGION_FILTER)/region_filter $(BIN)
	cp $(EPITOPE_FAIL)/epitope_fail $(BIN)
	cp $(EPITOPE_FILTER)/epitope_filter $(BIN)
	cp $(HYDRO)/hydro $(BIN)
	cp $(COMMAND)/fasta_stat $(BIN)

.PHONY: clean
clean: MTARGET = clean
clean: $(DIRS)
	rm -rf $(BIN)

.PHONY: $(DIRS)
$(DIRS):
	$(MAKE) -C $@ $(MTARGET)
