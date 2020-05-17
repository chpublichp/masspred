PROJECT = fasta_tool

COMPILER       = gcc
COMPILER_FLAGS = -c -I.
LINKER         = gcc
LINKER_FLAGS   =
LINKER_LIBS    = -lcrypt

SOURCES     = $(wildcard *.c)
OBJECTS     = $(SOURCES:.c=.o)
INCLUDES    = $(wildcard *.h)
PROTOTYPE   = prototype.i
TEST_IN  = test.faa
TEST_OUT = out

.DEFAULT_GOAL = all
.PHONNY: all clean test

all: $(PROJECT)

clean:
	rm -rf $(PROTOTYPE) $(OBJECTS) $(PROJECT) $(TEST_OUT)

test: $(PROJECT) $(TEST_OUT) $(TEST_IN)
	./$(PROJECT) -s $(TEST_OUT) $(TEST_IN)
	./$(PROJECT) -i $(TEST_IN)
	./$(PROJECT) -c $(TEST_IN)
	./$(PROJECT) -l $(TEST_IN)
	./$(PROJECT) -g 3 $(TEST_IN)
	./$(PROJECT) -g 2 $(TEST_IN)
	./$(PROJECT) -g 1 $(TEST_IN)

$(PROJECT): $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) -o $@ $(OBJECTS) $(LINKER_LIBS)

%.o: %.c $(SOURCES) $(PROTOTYPE) $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $<

$(PROTOTYPE): $(SOURCES)
	cat $(SOURCES) | sed -e '/_FUNCTION_DECLARATION_BEGIN_/{s/.*_FUNCTION_DECLARATION_BEGIN_//;:l;/_FUNCTION_DECLARATION_END_/{s/_FUNCTION_DECLARATION_END_.*/;/;b};n;bl};d' > $@

$(TEST_OUT):
	mkdir -p $(TEST_OUT)
