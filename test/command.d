command.o command.d : command.cc command.h ../protocol.h ../connection.h \
 ../connectionclosedexception.h database.h InMemoryDatabase.h newsGroup.h
