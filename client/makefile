include makefile.conf

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) 


clean:
	$(RM) *.o
	$(RM) $(TARGET)

remake:
	$(RM) *.o
	$(RM) $(TARGET)
	make
