OBJDIR = obj

CLAGS = -Wall -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes \
		-Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -O
CC = gcc
RM = rm
MD = mkdir

.PHONY: all
all: MDOBJ

.PHONY: MDOBJ
MDOBJ:
	@$(MD) -p $(OBJDIR)

.PHONY: clean
clean: 
	@$(RM) -rf $(OBJDIR)/*.o