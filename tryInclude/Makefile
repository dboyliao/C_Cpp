PREPROCESS_TARGETS=m.i main.i n.i
HEADERS=a.h b.h c.h aa.h

all:
	make $(PREPROCESS_TARGETS)

$(PREPROCESS_TARGETS):%.i:%.c $(HEADERS)
	gcc -E $< -o $@

clean:
	rm -f *.i
