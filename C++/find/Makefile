CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

% : %.cpp
		 g++ $(CFLAGS) $(LIBS) -o $@ $<

main : main.cpp
	g++	-std=c++11	$(CFLAGS) $(LIBS) -o main tkk.cpp