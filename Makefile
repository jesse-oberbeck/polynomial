CPPFLAGS+=-Wall -Wextra -Wpedantic
CPPFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal
CPPFLAGS+=-Waggregate-return -Winline

CFLAGS+=-std=c11

LDLIBS+=-lm

BIN=test
DEPS=polynomial.o

$(BIN) : $(DEPS)

.PHONY: debug profile clean

debug: CFLAGS+=-g
debug: $(BIN)

profile: CFLAGS+=-pg
profile: LDFLAGS+=-pg

clean:
	$(RM) $(BIN) $(DEPS)

run:
	./$(BIN)

val:
	valgrind -v ./$(BIN)
