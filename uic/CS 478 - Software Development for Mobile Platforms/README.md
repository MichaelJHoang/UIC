This is a README for CS 478.
There's nothing much to say at the moment
but there will be something in the future.

Project 1:
	Consists of 2/3 Activities.

	The first one has a welcome text and two buttons. Upon pressing the Address button,
	the app displays a second activity containing a user input text field where the user
	has to input an address or location. Once that happens,the user then presses the done 
	or return key in the soft keyboard to return to the main activity which would allow them
	to press the other button to activate an implicit intent to open a map app which displays
	the location of the address/place they have put in the input field earlier. If there were
	no inputs, a toast message will pop up - telling them to enter in a location.

	This project pretty much exercises how to use intents and activites.

Project 2:
	Consists of 3 Activities.

	First one is pretty much a scrollable view of phones and when the user clicks on one of them,
	activates a second activity which contains information in respect to the phone selected.
	A long click displays a context menu with options to select which pulls up respective info, etc.

	This project pretty much exercises how to use different layouts, menus, and adapters

Project 3:
	Consists of 4 Activities, 2 Broadcast Receivers, and 2 Fragments divided between 3 separate
	applications

	The first one has a welcome message and a button. When the button is pressed, ask the user for
	permissions. If granted, go to the second app.

	The second app is pretty much like the first app but goes to the third app on permission granted.

	The third app contains an activity with 2 fragments and defines the permission used
	throughout the project. Initially, the application starts with one fragment in view and when
	an item is selected within the fragment, a second fragment pops up with the image of the item
	in respect to the user's selection. There is also an action bar with two options:

		The first one sends an ordered intent to start the second app and then the first app.
			Activates second app's broadcast receiver and display a toast and then
			activate the first app's second activity which then opens the respective
			selection's webpage.

		The second one closes the third application.

	This project pretty much uses application to application communication with broadcasts, fragments
	and retaining fragments, and manipulation of the backstack.

Project 4:

[ IN PROGRESS ]

	It's a gopher hunting game.

	afaik, this project focuses on using and manipulation worker and UI threads.

