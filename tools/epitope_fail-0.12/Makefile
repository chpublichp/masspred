PROJECT = epitope_fail

COMPILER       = gcc
COMPILER_FLAGS = -c -I.
LINKER         = gcc
LINKER_FLAGS   =
LINKER_LIBS    =

SOURCES   = epitope_fail.c
INCLUDES  =
OBJECTS   = $(patsubst %.c, %.o, $(SOURCES))
TEST_OUT  = out

.DEFAULT_GOAL = all
.PHONNY: all clean test

all: $(PROJECT)

clean:
	rm -rf $(OBJECTS) $(PROJECT) $(TEST_OUT) ef_fail_out.sql ef_fail_out.load

test: clean $(PROJECT) $(TEST_OUT)
	./$(PROJECT) -m 1-3.0c     -s -o $(TEST_OUT)/ef_fail -a x01 -l 01 -p abc01 -r bca01 -f cab01
	./$(PROJECT) -m 1-3.4a     -s -o $(TEST_OUT)/ef_fail -a x02 -l 02 -p abc02 -r bca02 -f cab02
	./$(PROJECT) -m 2-2.2      -s -o $(TEST_OUT)/ef_fail -a x03 -l 03 -p abc03 -r bca03 -f cab03
	./$(PROJECT) -m pan_1-2.0c -s -o $(TEST_OUT)/ef_fail -a x04 -l 04 -p abc04 -r bca04 -f cab04
	./$(PROJECT) -m pan_1-2.4a -s -o $(TEST_OUT)/ef_fail -a x05 -l 05 -p abc05 -r bca05 -f cab05
	./$(PROJECT) -m pan_1-2.8a -s -o $(TEST_OUT)/ef_fail -a x06 -l 06 -p abc06 -r bca06 -f cab06
	./$(PROJECT) -m pan_2-1.0b -s -o $(TEST_OUT)/ef_fail -a x07 -l 07 -p abc07 -r bca07 -f cab07
	./$(PROJECT) -m pan_2-2.0b -s -o $(TEST_OUT)/ef_fail -a x08 -l 08 -p abc08 -r bca08 -f cab08
	./$(PROJECT) -m pan_2-3.0c -s -o $(TEST_OUT)/ef_fail -a x09 -l 09 -p abc09 -r bca09 -f cab09
	./$(PROJECT) -m pan_2-3.1a -s -o $(TEST_OUT)/ef_fail -a x10 -l 10 -p abc10 -r bca10 -f cab10

$(PROJECT): $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) -o $@ $(OBJECTS) $(LINKER_LIBS)

%.o: %.c $(SOURCES) $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $<

$(TEST_OUT):
	mkdir -p $(TEST_OUT)
