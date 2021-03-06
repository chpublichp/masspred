PROJECT = epitope_filter

COMPILER       = gcc
COMPILER_FLAGS = -c -I.
LINKER         = gcc
LINKER_FLAGS   =
LINKER_LIBS    =

SOURCES   = epitope_filter.c
INCLUDES  =
OBJECTS   = $(patsubst %.c, %.o, $(SOURCES))

TEST_OUT_PLAIN   = test-out.plain
TEST_OUT_NUMERIC = test-out.numeric
TEST_IN          = test-in
TEST_IN_01       = $(TEST_IN)/netmhc-3.0c-1.in
TEST_IN_02       = $(TEST_IN)/netmhc-3.0c-2.in
TEST_IN_03       = $(TEST_IN)/netmhc-3.4a.in
TEST_IN_04       = $(TEST_IN)/netmhcii-2.2.in
TEST_IN_05       = $(TEST_IN)/netmhcpan-2.0c.in
TEST_IN_06       = $(TEST_IN)/netmhcpan-2.4a.in
TEST_IN_07       = $(TEST_IN)/netmhcpan-2.8a.in
TEST_IN_08       = $(TEST_IN)/netmhciipan-1.0b.in
TEST_IN_09       = $(TEST_IN)/netmhciipan-2.0b.in
TEST_IN_10       = $(TEST_IN)/netmhciipan-3.0c.in
TEST_IN_11       = $(TEST_IN)/netmhciipan-3.1a.in

.DEFAULT_GOAL = all
.PHONNY: all clean test

all: $(PROJECT)

clean:
	rm -rf $(OBJECTS) $(PROJECT) $(TEST_OUT_PLAIN) $(TEST_OUT_NUMERIC)

test: clean $(PROJECT) $(TEST_OUT_PLAIN) $(TEST_OUT_NUMERIC) $(TEST_IN_01) $(TEST_IN_02) $(TEST_IN_03) $(TEST_IN_04) $(TEST_IN_05) $(TEST_IN_06) $(TEST_IN_07) $(TEST_IN_08) $(TEST_IN_09) $(TEST_IN_10) $(TEST_IN_11)
	./$(PROJECT) -m 1-3.0c     -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_01) -a x01 -l 01 -p abc01 -r bca01 -f cab01
	./$(PROJECT) -m 1-3.0c     -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_02) -a x02 -l 02 -p abc02 -r bca02 -f cab02
	./$(PROJECT) -m 1-3.4a     -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_03) -a x03 -l 03 -p abc03 -r bca03 -f cab03
	./$(PROJECT) -m 2-2.2      -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_04) -a x04 -l 04 -p abc04 -r bca04 -f cab04
	./$(PROJECT) -m pan_1-2.0c -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_05) -a x05 -l 05 -p abc05 -r bca05 -f cab05
	./$(PROJECT) -m pan_1-2.4a -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_06) -a x06 -l 06 -p abc06 -r bca06 -f cab06
	./$(PROJECT) -m pan_1-2.8a -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_07) -a x07 -l 07 -p abc07 -r bca07 -f cab07
	./$(PROJECT) -m pan_2-1.0b -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_08) -a x08 -l 08 -p abc08 -r bca08 -f cab08
	./$(PROJECT) -m pan_2-2.0b -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_09) -a x09 -l 09 -p abc09 -r bca09 -f cab09
	./$(PROJECT) -m pan_2-3.0c -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_10) -a x10 -l 10 -p abc10 -r bca10 -f cab10
	./$(PROJECT) -m pan_2-3.1a -s -o $(TEST_OUT_PLAIN)/ef $(TEST_IN_11) -a x11 -l 11 -p abc11 -r bca11 -f cab11
	./$(PROJECT) -m 1-3.0c     -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_01) -a x01 -l 01 -p abc01 -r bca01 -f cab01
	./$(PROJECT) -m 1-3.0c     -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_02) -a x02 -l 02 -p abc02 -r bca02 -f cab02
	./$(PROJECT) -m 1-3.4a     -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_03) -a x03 -l 03 -p abc03 -r bca03 -f cab03
	./$(PROJECT) -m 2-2.2      -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_04) -a x04 -l 04 -p abc04 -r bca04 -f cab04
	./$(PROJECT) -m pan_1-2.0c -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_05) -a x05 -l 05 -p abc05 -r bca05 -f cab05
	./$(PROJECT) -m pan_1-2.4a -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_06) -a x06 -l 06 -p abc06 -r bca06 -f cab06
	./$(PROJECT) -m pan_1-2.8a -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_07) -a x07 -l 07 -p abc07 -r bca07 -f cab07
	./$(PROJECT) -m pan_2-1.0b -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_08) -a x08 -l 08 -p abc08 -r bca08 -f cab08
	./$(PROJECT) -m pan_2-2.0b -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_09) -a x09 -l 09 -p abc09 -r bca09 -f cab09
	./$(PROJECT) -m pan_2-3.0c -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_10) -a x10 -l 10 -p abc10 -r bca10 -f cab10
	./$(PROJECT) -m pan_2-3.1a -s -n -o $(TEST_OUT_NUMERIC)/ef $(TEST_IN_11) -a x11 -l 11 -p abc11 -r bca11 -f cab11

$(PROJECT): $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) -o $@ $(OBJECTS) $(LINKER_LIBS)

%.o: %.c $(SOURCES) $(INCLUDES)
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $<

$(TEST_OUT_PLAIN) $(TEST_OUT_NUMERIC):
	mkdir -p $@
