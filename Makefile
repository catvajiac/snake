CMP = g++
DEP = gfxnew
CLASS = snake
LIST = list
MAIN = final
FLAGS = -std=c++11 -lX11 -I/opt/X11/include/ -L/opt/X11/lib/

$(MAIN): $(CLASS).o $(LIST).cpp $(DEP)_mac.o $(MAIN).cpp
	$(CMP) $(FLAGS) $(CLASS).o $(LIST).cpp $(DEP)_mac.o $(MAIN).cpp -o $(MAIN)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(FLAGS) $(DEP)_mac.o $(CLASS).cpp -o $(CLASS).o

clean:
	rm $(CLASS).o $(MAIN)
