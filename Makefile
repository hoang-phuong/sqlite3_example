APP = example

OUTDIR = out
SRCDIR = src
INCDIR = inc
OBJDIR = obj

FILES = main

OBJECTS = $(addprefix $(OBJDIR)/,$(addsuffix .o, $(FILES)))


VPATH = .: ./$(SRCDIR) ./$(INCDIR)

CFLAGS = -Wall -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes \
		-Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -O\
		-I $(INCDIR) 
LDFLAGS = -pthread -lsqlite3 -Xlinker -Map=$(OUTDIR)/$(APP).map
CC = gcc
RM = rm
MD = mkdir

.PHONY: all
all: MDOBJ $(OBJECTS) $(OUTDIR)/$(APP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OUTDIR)/$(APP): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: MDOBJ
MDOBJ:
	@$(MD) -p $(OBJDIR)
	@$(MD) -p $(OUTDIR)

.PHONY: clean
clean: 
	@$(RM) -rf $(OBJDIR)/*.o
	@$(RM) -rf $(OUTDIR)/$(APP)
	@$(RM) -rf $(OUTDIR)/$(APP).map
	@$(RM) -rf *.db

.PHONY: run
run: $(OUTDIR)/$(APP)
	$(OUTDIR)/$(APP)
