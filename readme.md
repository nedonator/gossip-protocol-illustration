This program creates random connected network graph and illustrates how does message spread using gossip protocol.
Message can be sent from new computer by clicking on it. Color indicates status of the computer:
Red - waiting for message.
Green - it just got a message.
Grey - it got a message a long time ago.
Connections between computers are shown in red.
Some parametres of program can be changed:
main.cpp/N - the number of computers
main.cpp/p - the number of additional connection:
If p = 0 - the network graph will have no cycles.
If p > 10 - the network graph will be like a full graph.
main.cpp/eps - the deviriation of speed.
If eps = 0 - the speed will be constant.
If eps a bit less than 1 - some messages will be very slow.
Project.h/WIDTH, Project.h/HEIGHT - the size of window.
Project.h/speed - the average speed of messages, in pixels per second.
Project.h/FPS - number of frames per second
