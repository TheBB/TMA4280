SRCS_LIB = hello_utils.c goodbye_utils.c
OBJS_LIB = $(SRCS_LIB:.c=.o)
SRCS_EXE = main.c
OBJS_EXE = $(SRCS_EXE:.c=.o)
SRCS_EXE_REV = main_reversed.c
OBJS_EXE_REV = $(SRCS_EXE_REV:.c=.o)

all: lib hello hello_reversed

lib: $(OBJS_LIB)
	$(AR) r libutils.a $(OBJS_LIB)

hello: lib $(OBJS_EXE)
	$(CC) $(CFLAGS) -o hello $(OBJS_EXE) -L. -lutils

hello_reversed: lib $(OBJS_EXE_REV)
	$(CC) $(CFLAGS) -o hello_reversed $(OBJS_EXE_REV) -L. -lutils

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_LIB) $(OBJS_EXE) $(OBJS_EXE_REV) hello hello_reversed libutils.a
