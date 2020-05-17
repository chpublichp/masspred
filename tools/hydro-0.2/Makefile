PROJECT = hydro

COMPILER       = gcc
COMPILER_FLAGS = -c -I.
LINKER         = gcc
LINKER_FLAGS   =
LINKER_LIBS    =

SOURCES  = hydro.c
INCLUDES =
OBJECTS  = $(patsubst %.c, %.o, $(SOURCES))
TEST_OUT = out
TEST_IN  = test.faa

.DEFAULT_GOAL = all
.PHONNY: all clean test

all: $(PROJECT)

clean:
	rm -rf $(OBJECTS) $(PROJECT) $(TEST_OUT) hy_out.sql hy_out.load

test: clean $(PROJECT) $(TEST_OUT) $(TEST_IN)
	./$(PROJECT) -s -o $(TEST_OUT)/hy $(TEST_IN)  -p abc -r bca -f cab

$(PROJECT): $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) -o $@ $(OBJECTS) $(LINKER_LIBS)

%.o: %.c $(SOURCES) $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $<

$(TEST_OUT):
	mkdir -p $(TEST_OUT)
