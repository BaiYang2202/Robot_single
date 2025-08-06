CC=g++
OBJ=run_robot
SRCO= ./tmp/pack_data.o ./tmp/unsport.o ./tmp/init_send.o ./tmp/key_input.o ./tmp/run_leg_robot.o
VPATH=include src
CPPFLAGS= -I./include

$(OBJ):$(SRCO)
	$(CC) $(CPPFLAGS) $(SRCO) -o $@ -pthread

./tmp/%.o:./src/%.cc
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) ./tmp/*
