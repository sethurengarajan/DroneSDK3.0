"Nothing gets the taste of shame and humiliation out of your mouth like a piece of [BebopRebopAPI]" 
 
 \-Garrison Keillor

The official Parrot ArDrone SDK v3 is pretty user unfriendly and poorly documented, with very little sample code, especially for the Bebop. This (soon to be) library aims to fix that. Stay tuned.

Current todo-list:

- [ ] Thread that monitors network connection to automatically reconnect upon disconnection
- [ ] Reader thread that pulls and parses all incoming data into user buffers for consumption on a per message basis
- [ ] Vehicle specific status manager (latest and greatest of status info parsed in, so users can poll when they want instead of consuming messages.
- [ ] SendWithTimeout (combines send with readwithtimeout to let you do a blocking send in one call, for things like takeoff, land, etc)
- [ ] Finishing adding all of the sendable commands for the Bebop (piloting commands are in, but there is a bunch of media and network stuff to add)
- [ ] Creating and using custom status/error codes instead of just using bools. Bools are easy to work with to start, but you're going to want to know why things failed, sooner or later.
- [ ] Armhf build configuration
- [ ] Probably more, but I don't know what yet

Feel free to make suggestions!

Some notes:
* I am developing this in Eclipse, so this includes project files. You can also use the makefile in the /Build/ folder.
* You may be wondering where all of the ArSDK3 lib files are, as built. I simply combined them into a single static library.
* You may not like my coding style, and I may not like yours, but I will still happily accept your pull requests. I'll make sure everything stays consistent, so don't let that stop you from contributing.
* I've only partially tested this stuff! Beware! 

I PROVIDE NO GUARANTEES OF THE FUNCTIONALITY OF THIS CODE, YOUR SAFETY, OTHERS' SAFETY, OR YOUR PROPERTY'S SAFETY!
USE AT YOUR OWN RISK!
