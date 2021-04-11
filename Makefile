all: compile link run

compile:
	 cl /c  main.c board_actions.c game_engine.c moves_queue.c game_rules.c
	 
link:
	 link main.obj board_actions.obj game_engine.obj moves_queue.obj game_rules.obj /OUT:ConnectFour.exe

run:
	ConnectFour.exe
clean:
 	del *.exe
	del *.obj
	del *.lib