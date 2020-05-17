PROJECT = region_filter

COMPILER       = gcc
COMPILER_FLAGS = -c -I.
LINKER         = gcc
LINKER_FLAGS   =
LINKER_LIBS    =

SOURCES     = $(wildcard *.c)
OBJECTS     = $(SOURCES:.c=.o)
INCLUDES    = $(wildcard *.h)
PROTOTYPE   = prototype.i

TEST_OUT_PLAIN   = test-out.plain
TEST_OUT_NUMERIC = test-out.numeric
TEST_IN_DIR      = test-in
TEST_IN_01       = $(TEST_IN_DIR)/anchor.in
TEST_IN_02       = $(TEST_IN_DIR)/disopred.in
TEST_IN_03       = $(TEST_IN_DIR)/disembl.in
TEST_IN_04       = $(TEST_IN_DIR)/disembl.in
TEST_IN_05       = $(TEST_IN_DIR)/disembl.in
TEST_IN_06       = $(TEST_IN_DIR)/iupred-long.in
TEST_IN_07       = $(TEST_IN_DIR)/iupred-short.in
TEST_IN_08       = $(TEST_IN_DIR)/ond.in
TEST_IN_09       = $(TEST_IN_DIR)/predisorder.in
TEST_IN_10       = $(TEST_IN_DIR)/ronn.in
TEST_IN_11       = $(TEST_IN_DIR)/isunstruct.in
TEST_IN_12       = $(TEST_IN_DIR)/vsl2.in

.DEFAULT_GOAL = all
.PHONNY: all clean test

all: $(PROJECT)

clean:
	rm -rf $(PROTOTYPE) $(OBJECTS) $(PROJECT) $(TEST_OUT_PLAIN) $(TEST_OUT_NUMERIC)

test: clean $(PROJECT) $(TEST_OUT_PLAIN) $(TEST_OUT_NUMERIC) $(TEST_IN_01) $(TEST_IN_02) $(TEST_IN_03) $(TEST_IN_04) $(TEST_IN_05) $(TEST_IN_06) $(TEST_IN_07) $(TEST_IN_08) $(TEST_IN_09) $(TEST_IN_10) $(TEST_IN_11) $(TEST_IN_12)
	./$(PROJECT) -m a  -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_01) -p abc01 -r bca01 -f cab01
	./$(PROJECT) -m d  -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_02) -p abc02 -r bca02 -f cab02
	./$(PROJECT) -m e1 -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_03) -p abc03 -r bca03 -f cab03
	./$(PROJECT) -m e2 -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_04) -p abc04 -r bca04 -f cab04
	./$(PROJECT) -m e3 -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_05) -p abc05 -r bca05 -f cab05
	./$(PROJECT) -m il -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_06) -p abc06 -r bca06 -f cab06
	./$(PROJECT) -m is -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_07) -p abc07 -r bca07 -f cab07
	./$(PROJECT) -m o  -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_08) -p abc08 -r bca08 -f cab08
	./$(PROJECT) -m p  -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_09) -p abc09 -r bca09 -f cab09
	./$(PROJECT) -m r  -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_10) -p abc10 -r bca10 -f cab10
	./$(PROJECT) -m u  -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_11) -p abc11 -r bca11 -f cab11
	./$(PROJECT) -m v  -s -o $(TEST_OUT_PLAIN)/rf $(TEST_IN_12) -p abc12 -r bca12 -f cab12
	./$(PROJECT) -m a  -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_01) -p abc01 -r bca01 -f cab01
	./$(PROJECT) -m d1 -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_02) -p abc02 -r bca02 -f cab02
	./$(PROJECT) -m d2 -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_02) -p abc02 -r bca02 -f cab02
	./$(PROJECT) -m e1 -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_03) -p abc03 -r bca03 -f cab03
	./$(PROJECT) -m e2 -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_04) -p abc04 -r bca04 -f cab04
	./$(PROJECT) -m e3 -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_05) -p abc05 -r bca05 -f cab05
	./$(PROJECT) -m il -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_06) -p abc06 -r bca06 -f cab06
	./$(PROJECT) -m is -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_07) -p abc07 -r bca07 -f cab07
	./$(PROJECT) -m o  -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_08) -p abc08 -r bca08 -f cab08
	./$(PROJECT) -m p  -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_09) -p abc09 -r bca09 -f cab09
	./$(PROJECT) -m r  -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_10) -p abc10 -r bca10 -f cab10
	./$(PROJECT) -m u  -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_11) -p abc11 -r bca11 -f cab11
	./$(PROJECT) -m v  -s -n -o $(TEST_OUT_NUMERIC)/rf $(TEST_IN_12) -p abc12 -r bca12 -f cab12

$(PROJECT): $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) -o $@ $(OBJECTS) $(LINKER_LIBS)

%.o: %.c $(SOURCES) $(PROTOTYPE) $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $<

$(PROTOTYPE): $(SOURCES)
	cat $(SOURCES) | sed -e '/_FUNCTION_DECLARATION_BEGIN_/{s/.*_FUNCTION_DECLARATION_BEGIN_//;:l;/_FUNCTION_DECLARATION_END_/{s/_FUNCTION_DECLARATION_END_.*/;/;b};n;bl};d' > $@

$(TEST_OUT_PLAIN) $(TEST_OUT_NUMERIC):
	mkdir -p $@
