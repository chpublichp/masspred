PROJECT = region_fail

COMPILER       = gcc
COMPILER_FLAGS = -c -I.
LINKER         = gcc
LINKER_FLAGS   =
LINKER_LIBS    =

SOURCES   = $(wildcard *.c)
OBJECTS   = $(SOURCES:.c=.o)
INCLUDES  = $(wildcard *.h)
TEST_OUT  = out

.DEFAULT_GOAL = all
.PHONNY: all clean test

all: $(PROJECT)

clean:
	rm -rf $(OBJECTS) $(PROJECT) $(TEST_OUT) rf_fail_out.sql rf_fail_out.load

test: clean $(PROJECT) $(TEST_OUT)
	./$(PROJECT) -m a  -s -o $(TEST_OUT)/rf_fail -p abc01 -r bca01 -f cab01
	./$(PROJECT) -m d  -s -o $(TEST_OUT)/rf_fail -p abc02 -r bca02 -f cab02
	./$(PROJECT) -m e  -s -o $(TEST_OUT)/rf_fail -p abc03 -r bca03 -f cab03
	./$(PROJECT) -m il -s -o $(TEST_OUT)/rf_fail -p abc04 -r bca04 -f cab04
	./$(PROJECT) -m is -s -o $(TEST_OUT)/rf_fail -p abc05 -r bca05 -f cab05
	./$(PROJECT) -m o  -s -o $(TEST_OUT)/rf_fail -p abc06 -r bca06 -f cab06
	./$(PROJECT) -m p  -s -o $(TEST_OUT)/rf_fail -p abc07 -r bca07 -f cab07
	./$(PROJECT) -m r  -s -o $(TEST_OUT)/rf_fail -p abc08 -r bca08 -f cab08
	./$(PROJECT) -m u  -s -o $(TEST_OUT)/rf_fail -p abc09 -r bca09 -f cab09
	./$(PROJECT) -m v  -s -o $(TEST_OUT)/rf_fail -p abc10 -r bca10 -f cab10

$(PROJECT): $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) -o $@ $(OBJECTS) $(LINKER_LIBS)

%.o: %.c $(SOURCES) $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $<

$(TEST_OUT):
	mkdir -p $(TEST_OUT)
