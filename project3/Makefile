# Makefile for xkcdpwgen

# set the script name, can be custom
SCRIPT_NAME = xkcdpwgen

# python3 interpreter path
PYTHON = /usr/bin/python3

# make all (apply to all)
all: $(SCRIPT_NAME)

$(SCRIPT_NAME): $(SCRIPT_NAME).py
    echo '#!$(PYTHON)' > $@
    cat $< >> $@
    chmod +x $@

clean:
    rm -f $(SCRIPT_NAME)

.PHONY: all clean