warlight2-starterbot
===================

AIGames warlight2 C++ starter bot

Basics
------

This is a starter bot for 
http://theaigames.com/competitions/warlight-ai-challenge-2

Basic documentation and infos on how to get started can be found there.

This bot just implements the communication with the game and saves you from starting by scratch.
This has a parser that implments the complete engine communication protocol and 
has datastructures which represent the different objet in the game

Getting the Bot
---------------

Either clone the bot with 
```
git clone https://github.com/pizzard/warlight-starterbot.git your-bot-dir
```
or download the zip file at 
https://github.com/pizzard/warlight-starterbot/archive/master.zip


Getting Started
---------------

The bot comes in a set of Header and source files, all in your current source dir and 
a sudirectory tools/ for helper classes and tools.
There are currently 4 classes:
 * Bot: handles game interaction and if basically the meat of your bot
 * Parser: handle communication of the game engine
 * Region and SuperRegion: data representation of the Map

To get started first skim around (especialls in the headers of Region, SuperRegion and Bot
to see what information you have and how its accessed)

Then when you want start implementing bot behavoiur, find 
```c++
void Bot::pickStartingRegion() { ... }
void Bot::placeArmies() { ... }
void Bot::makeMoves() { ... }
```
methods in Bot.cpp.

Start adding your own logic on how to move and your own game logic there.


Building
--------

For the challenge you don't need to build your bot, you can just upload it.
But for the convienience of local testing it is highly recommended to do so.

This describes the build environment used on linux, you can use a build envirenment of your choice.

Requirements are:
 * Current c++ compiler e.g. g++ >= 4.7 (engine on server uses g++ 4.9 with -std=c++14)
 * gnu-automake (Makefiles)
 * zip (for automatic zip file creation for upload)
 * QT5's qmake (if you want to use the given qmake .pro file)

You don't need to install the whole QT5 framework, the bot does not use it, just look
for a qt5-qmake standalone package.

Then just go to the source directory of your bot.
```bash
mkdir -p build # creates the build dir
cd build
qmake-qt5 ../starterbot.pro #creates your Makefile
```
(you might want to rename the .pro file in advance to reflect the name of your cool bot, heh ;-))
Then you can build your bot with 
```bash
make all 
```
or just make

Because you mostly will use your local builds for testing your bot is by default created with debug 
symbols enabled, ready to use with e.g. gdb or valgrind. Also all warnings are on.

Testing locally
---------------

Once you successfully built your bot you will want to test your bot.
The first very basicv test ist just run it from sour src dir with:
(you can change the executeable name in the .pro file by changing the TARGET variable)
```bash
./build/starterbot
```
Now your bot should be running and will expect input from you over standard input,
test typing something
```
test
```
then your bot will answer
```
test
```
because the parser just prints back an input it does not recognize.
If you give it a valid engine command, e.g.
```
settings timebank 10000
```
It will parse that and in this case give no response.

If this works, you can let the bot play a simulated game.
Therefore under testgames/, there are some tesgames where the complete engine output is captured
you can run your bot with them using
```bash
cat testgames/testmatch.game | ./build/starterbot 
```
Then you see the complete output of your bot for that game.

CAVEAT: The "engine" does in this case not really react to your moves and if
you conquer different regions then the bot did in the real test game then the game state can be invalid,
so don't wonder about strange moves of your bot after the first round.
It is still fine to see whether your bot crashes of does something roughly useful, though.

Compete!
--------
If you done local testing and want to see your bot online, go into the build directory of your bot
and use
```bash
make zip
```
to create a zip file.

Then go to http://theaigames.com/profile, select Warlight AI Challenge 2 if neccessary and upload
your zip file there.

On the server there are 5 phases:
 1. Upload
 2. Compilation Queue
 3. Compiling 
 4. Simple Input Test
 5. Test Game

You can access the output of all phases there.
If all this works to your statisfaction, select your current version from the list and click set
to add it to the Challenge.

CAUTION: When you first add a bot, it needs to be added into the match queue, this can take several hours.

Advanced Topics 
================

Advanced Debugging
------------------

If your bots behaviour is strictly deterministic (which is often prefereable and certainly not true
for the starterbot) you can debug games as follows:

 * Locally build the same bot as currently in the competition. 
 * Get the dump from the game you are interested in. (adding /dump the URL does the job) 
 * Save it to a file. (you don't need to clean it up, the bot will ignore all other stuff in there)
 * Fire up your debugger with your bot
 * Specifiy breakpoints where useful, e.g. in your move logic.
 * Run the bot with your game file as above.

Because you not get the same inputs your bot will do the same moves as in the real game, but know
you can observe the deciision process instruction by instruction.
This is some work to set up, but if classical printf debugging doesn't help you any more, its a very 
powerful tool. 

Online Compilation Options
-----------------------

Here all information so far published about the online build system are collected, if you want to set up
your own build to match these as closely as possible.

The online compiler is g++ 4.9 in a recent version, it does compile your bot with
-std=c++14 enabled and it has -Ipath/to/your/sources that you can easily use both include sytaxes 
(angle brackets) and double quotes.

You can use subdirectories, but you have to care that in the zip file, the files are plced directly
in the zip files root and not in a subdirectory, otherwise your includes won't work.
make zip does take care of that for you






