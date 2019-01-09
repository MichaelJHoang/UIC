PROGRAM4: jhoang6_MAIN_linkedListFunctions.o jhoang6_SUB_linkedListFunctions.o jhoang6_userInterface.o
	gcc -o PROGRAM4 jhoang6_SUB_linkedListFunctions.o jhoang6_MAIN_linkedListFunctions.o jhoang6_userInterface.o
	
jhoang6_MAIN_linkedListFunctions.o: jhoang6_MAIN_linkedListFunctions.c jhoang6_restaurantWaitingListSystem.h
	gcc -c jhoang6_MAIN_linkedListFunctions.c

jhoang6_SUB_linkedListFunctions.o: jhoang6_SUB_linkedListFunctions.c jhoang6_restaurantWaitingListSystem.h
	gcc -c jhoang6_SUB_linkedListFunctions.c

jhoang6_userInterface.o: jhoang6_userInterface.c jhoang6_restaurantWaitingListSystem.h
	gcc -c jhoang6_userInterface.c

clean:
	rm jhoang6_MAIN_linkedListFunctions.o jhoang6_SUB_linkedListFunctions.o jhoang6_userInterface.o












