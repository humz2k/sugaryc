%.h: %.o
	./$< > $@

%.o: %.c
	$(CC) $< -o $@

clean:
	rm -rf *.h
	rm -rf *.o