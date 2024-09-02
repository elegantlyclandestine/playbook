# Playbook
### This program facilitates large-scale solo roleplaying scenarios that use [Tupperbox](https://tupperbox.app).
## Origins
I initially created this program to help out with scripting large sequences for one of my solo role-plays: *Alien: Inside Out*. (Yes, it’s an *Alien* and *Inside Out* crossover. Who would have thought?) I was getting tired of writing ten messages at a time, complete with the emojis I had to find or autocomplete on my keyboard, both on laptop and phone.

And knowing that I had some background in programming, first with Node.js, then Python, and my final form: C++. Since the latter-most is the language I was best at, I thought: **why not make a program that automatically splits the messages ten at a time?**

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
github.talk:
    World, hello!
```
You would compile it like this (as of version 3):
```
playbook3 hw.pbk
```
The result is this, in the file on directory `hw/section` with name `part_1.txt`:
```
👩 Hello, world!
🤖 World, hello!
```
Now, it doesn’t look like a lot. But when you get to scripting large projects, *this* is where Playbook shines with its 10-at-a-time message splitting.

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