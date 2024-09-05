# Playbook
### This program facilitates large-scale solo roleplaying scenarios that use [Tupperbox](https://tupperbox.app).
## Origins
I initially created this program to help out with scripting large sequences for one of my solo role-plays: *Alien: Inside Out*. (Yes, it’s an *Alien* and *Inside Out* crossover. Who would have thought?) I was getting tired of writing ten messages at a time, complete with the emojis I had to find or autocomplete on my keyboard, both on laptop and phone.

And knowing that I had some background in programming, first with Node.js, then Python, and my final form: C++, something brewed in my silly little head. Since the latter-most is the language I was best at, I thought: **why not make a program that automatically splits the messages ten at a time?**

That’s when the idea for **Playbook** was born. Actually, I didn’t call it **Playbook** yet, it didn’t have a proper name until I thought of a placeholder: **alienio**, in reference to the solo role-play I was trying to complete. (It took six days to complete; day two was when I thought of programming this utility!)

It wasn’t until a week after completing *Alien: Inside Out* that I decided to *finally* name it **Playbook**.

## How does it work?
Actually, it’s **an entire scripting language.** This is what a sample Playbook file looks like (as of version 3):
```
::: (hw.pbk)
::: Hello World
::: by Nicole
::: Self-explanatory
--[section]--
nicole.talk:
    Hello world!
    This is Playbook 3 going live!
github.talk:
    World, hello!
    Going live, this is Playbook 3!
```
You would compile it like this (as of version 3):
```
playbook3 hw
```
The result is this, in the file on directory `hw/section` with name `part_1.txt`:
```
👩 Hello, world!
This is Playbook 3 going live!
🤖 World, hello!
Going live, this is Playbook 3!
```
Now, it doesn’t look like a lot. But when you get to scripting large projects with lots of multi-line messages, *this* is where Playbook shines with its 10-at-a-time message splitting.

## How do I use this?
Currently, **I only have Mac binaries** that work under my current version, macOS Sonoma 14.2.1. I haven’t uploaded them because I have no idea if it works on anything older.

So for now, the `CMakeLists.txt` should be your starting point, *if you’re building Playbook 4.*\
Do the following on a terminal/command prompt:
- `cmake -S . -B build` on Playbook 4’s root directory
- `cd build`, then `make`

Otherwise, you can just compile the other versions from Playbook 3 and older with the following command: `g++ -std=c++11 playbook(version).cpp -o playbook`.

***Okay, now you have compiled the Playbook source into something useable. What’s next?***
- You can try putting it on your `$PATH` (macOS, Linux) or environment variables (Windows) so you can compile Playbook script files anywhere.
- Write a simple script in Playbook format, save it as a `.pbk` file.
- - If you’re working on a Playbook 2 or later compatible file, [refer to the syntax here](https://github.com/elegantlyclandestine/playbook?tab=readme-ov-file#how-does-it-work).
- - If you’re working on a Playbook 1 compatible file (not recommended), [refer to the syntax here](https://github.com/elegantlyclandestine/playbook?tab=readme-ov-file#playbook-1-alienio).
- In your command prompt (assuming you have Playbook on your `$PATH` or environment variables), type `playbook <yourscript.pbk>`. Depending on the version of Playbook you’re running, the output will be as follows:
- - **Playbook 1**: The output files will be on the same directory as your script.
- - **Playbook 2+**: The output files will be on a directory named after your project, split into sections you define in the script.
- You’re ready to send the messages now! Go to any Discord server with Tupperbox on it, and copy-paste your messages from each part file.
#### If you spam with Playbook-processed messages, *you* did this yourself, not me. To anyone about to complain, please do so to the spammer, because this activity isn’t my intention.

## What are the features?
**Here’s the history of them, from latest to oldest (as of version 3):**
### Playbook 3
- supports project creation on the fly with `playbook3 create <project-name> <projectID>`
- removed need for strict `.pbk` extension when typing in script name for compilation
- added full debug logging arguments as program looks through a `.pbk` file line by line:
- - `--debug-full` to print per-line output to the console
- - `--debug-full-[printout/po]` to send above output to a log file
- `--debug` and `--debug-printout` now only print ‘major events’ happening during compilation

### Playbook 2
- changed symbol-to-emoji configuration system to separate `emoji_config.txt` for easy additions/modifications/deletions
- now outputs resulting separated message text files into directory named after the `.pbk` file it compiles
- section support defined with `--[section-name-here]--`, will separate into another folder within output directory if found
- error detection during compilation, also shows what line the program failed
- debug arguments to show what happens line by line:
- - `--debug` to print per-line output to the console
- - `--debug-printout` to send above output to a log file
- support for global execution so you could just run it from anywhere instead of copying the `playbook2` binary

### Playbook 1 (alienio)
- initial syntax defined as this:
```=== envy escape BEGIN ===
fr -# kneels to Envy's level
   Envy, you have to listen to me VERY CAREFULLY!
   -# holds her shoulders
   I mean it!
ev -# looks to Fear, shaking but nodding
fr You can run fast, right?
ev I wish I could...
   -# sniffs
fr I saw you. You *can*.
ev I... can?
   -# stops sniffling
fr Okay. You get to the escape pods at the west end of this hallway right now!
ev Uh huh, uh huh...
fr # AND DON'T LOOK BACK!
ev -# shakes uncontrollably
xn -# chewing noises
fr I'm telling you. Don't look back. I'll follow you eventually!
ev Promise?
   -# shows my pinky finger
fr -# shows my whole hand
ev -# opens my hand
fr Promise.
   -# shakes hands.
   Now go! Go!
```
- symbol-to-emoji configuration was initially hardcoded
- rudimentary support for sections, was actually just ignored
- text files would just output in the same folder as the project
- `playbook1` (then named `alienio`) would need to be in the same folder as the `.pbk` being compiled

## What’s next?
**Playbook 4** will introduce the following features:
- cleaner codebase to work with (if you’re a developer looking to fork this project)
- `--limit [1-10]` argument depending on how many messages you want to trigger a file split
- `--premium-bypass` argument to allow up to a 30-message split for `--limit`
- more detailed error and debug outputs
- ~~comment support for debug files – same syntax as playbook script files `::: like this`~~ **IMPLEMENTED**
- ~~you can check the version with `--v/--version`! (trivial, I know LOL)~~ **IMPLEMENTED**
- config support for symbols to either be added to the beginning or end of each message (or both) like one of these:
- - `👋 Hello!`
- - `Hello! 👋`
- - `👋 Hello! 👋`
- PluralKit support (I may already have this by accident, but no way of knowing for sure until I tested this)
