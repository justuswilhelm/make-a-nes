.PHONY: testfiles all c

all: testfiles c

c:
	$(MAKE) -C $@
