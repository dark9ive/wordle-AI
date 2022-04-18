FINAL_TARGET    = Main
O_DIR           = O
SOURCES         = framework AI
SRCS            = ${SOURCES:%=%.cpp}
OBJS            = ${SRCS:%.cpp=$(O_DIR)/%.o}
FLAGS       	= -std=c++11 -O2

$(FINAL_TARGET): $(O_DIR) $(OBJS)
	g++ $(OBJS) $(FLAGS) -o $(FINAL_TARGET)

$(O_DIR) :
	mkdir $@

$(O_DIR)/%.o: %.cpp
	g++ $(FLAGS) -c -o $@ $<

clean:
	rm -r $(O_DIR)
	rm $(FINAL_TARGET)
