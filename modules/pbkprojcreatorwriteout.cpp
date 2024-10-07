#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <ctime>
#include <unistd.h>
#include "../header/playbookmaster.h"

namespace fs = std::filesystem;

void writeConfig(std::ofstream& configOut) {
    configOut << "::: Format:" << std::endl
              << "::: symbol=trigger" << std::endl
              << "" << std::endl
              << "foo=😀" << std::endl
              << "bar=😁" << std::endl
              << "narrator=🎬" << std::endl;
    configOut.close();
}

void writePbkFile(std::ofstream& pbkOut) {
    pbkOut << "::: " << projectName << std::endl
           << "::: by Author" << std::endl
           << "::: Description goes here." << std::endl
           << "::: If you want to make comments, type ::: before your comment." << std::endl
           << ":::" << std::endl
           << "--[sample-section-1]--" << std::endl
           << "narrator.talk:" << std::endl
           << "    -# Foo and Bar walk on stage to a rousing applause." << std::endl
           << "    -# They wave at the crowd with smiles and waves all aobut." << std::endl
           << "foo.talk:" << std::endl
           << "    Hello!" << std::endl
           << "    This is how you make me talk." << std::endl
           << "bar.talk:" << std::endl
           << "    And *this* is how you make *me* say something." << std::endl
           << "    # Markdown works pretty well too." << std::endl
           << "    -# You see that?" << std::endl
           << "foo.talk:" << std::endl
           << "    Okay, showoff. Anyway, this is what a PLAYBOOK " << playbookMajorVersion << " script looks like." << std::endl
           << "    You can edit it as much as you want, hell you can have thousands of lines and it will process just fine!" << std::endl
           << "    It's scalable to any size of roleplay you want. Just edit the emojiconfig.txt to add, change or remove characters as needed." << std::endl
           << "bar.talk:" << std::endl
           << "    For every ten symbols you processs, it splits off to another file." << std::endl
           << "foo.talk:" << std::endl
           << "    That's right, Bar! How about continuing the show for the rest of our folks here?" << std::endl
           << "bar.talk:" << std::endl
           << "    With pleasure." << std::endl
           << "    You can define sections as we've already done for you, with --[section name here]--." << std::endl
           << "foo.talk:" << std::endl
           << "    Make sure you disable special dashes, because the program doesn't recognise those!" << std::endl
           << "bar.talk:" << std::endl
           << "    Right. Also, we almost forgot, your dialogue after a symbol.talk declaration has to be in a new line, with FOUR spaces before you make us talk." << std::endl
           << "    It's there for clean-up and organisation reasons!" << std::endl
           << "foo.talk:" << std::endl
           << "    Right again, Bar! And since this is the tenth symbol declaration, it looks like I'll see you on the other side!" << std::endl
           << "bar.talk:" << std::endl
           << "    Oh, hello! I'm on file #2. Neat, huh?" << std::endl
           << "foo.talk:" << std::endl
           << "    Hey there, Bar! How are things?" << std::endl
           << "bar.talk:" << std::endl
           << "    Handy dandy nice over here! After all of that, after you're done with your project... go to your command prompt or terminal and type PLAYBOOK3 " << projectName << ".pbk to see your hard-worked roleplay script come to life." << std::endl
           << "foo.talk:" << std::endl
           << "    You will *no* longer have to worry about Tupperbox's proxy limits again!" << std::endl
           << "bar.talk:" << std::endl
           << "    To close, we'll see you in another section of the project!" << std::endl
           << "--[sample-section-2]--" << std::endl
           << "foo.talk:" << std::endl
           << "    Hello from another section, ladies and gentlemen! Bar, I believe you have some closing things to say?" << std::endl
           << "bar.talk:" << std::endl
           << "    Yup. If you want to see what's behind the scenes when PLAYBOOK " << playbookMajorVersion << " compiles your script, you can type --debug to see what it's doing!" << std::endl
           << "    And if you don't want that log cluttering your command line display, you can type --debug-printout and look at the log file after it finishes!" << std::endl
           << "foo.talk:" << std::endl
           << "    But watch it, folks! You could make a mistake when making Playbook scripts. Don't worry, the program will catch it for you!" << std::endl
           << "bar.talk:" << std::endl
           << "    Correctomundo, Foo! I guess that's it for us at the Foo and Bar show, featuring yours truly with my partner!" << std::endl
           << "foo.talk:" << std::endl
           << "    -# together" << std::endl
           << "    # Have a good night!" << std::endl
           << "bar.talk:" << std::endl
           << "    -# together" << std::endl
           << "    # Have a good night!" << std::endl
           << "narrator.talk:" << std::endl
           << "    -# The crowd goes wild!" << std::endl
           << "    -# Foo and Bar wave goodbye to the crowd as the curtains close and the spotlight turns off." << std::endl;
    pbkOut.close();
}