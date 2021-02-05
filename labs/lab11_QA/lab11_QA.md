# Lab 11

## <b>Required</b> deliverables for this lab

* Fill out this poll if you haven't already! <https://forms.gle/8TmorHSjA4ASF7Ls5>

* Meet with your project group ONCE and screenshot it. Turn this screenshot into the Assignment in Canvas. Due Oct 23, 11:55pm.

## Iteration 1 Deliverable 2 Delayed!

<b>Important:</b> turn in your Doxygen by zipping your html folder! Then turn in the zip file. (when its due, Oct 23 11:55pm)

### Required group meeting between now and Oct 23 11:55pm

There have been some students that still haven't connected with their group, so we are now going to require it for this lab grade. All that needs to happen is a synchronous meeting over zoom/discord once this week. During the meeting, everyone needs to screenshot some portion of their screen that contains all the names of the group members and makes it obvious that you were in a meeting at the time of the screenshot.

Some things you might have something to say about:

* Discuss broad topic C++/coding stuff. Any lingering questions that you may have.

* Talk about how to implement the drone_simulation. A key design philosophy with the Facade pattern is breaking work up into smaller subsystems. What subsystems do you think would be most helpful? Remember, the goal is to move <b>as much</b> logic out of the DroneSimulation class as possible.

* Anything Doxygen that you feel like you want to discuss before the deliverable? Do you want to compare/contrast documentation before you turn in your Doxygen?



## Regarding the intermediate results of the poll<a name="rtirotp"></a>

# Table of contents

1. [The project clarifications](#proj)
1. [Concerns about the new technologies](#catnt)
    1. [Docker](#docker)
    2. [Doxygen](#doxygen)
    3. [GoogleTest](#googletest)
    4. [Git](#git)
    5. [Picojson](#picojson)


<a name="proj"></a>

### Project

We are currently working on clarifying the goals and specifications of the project. Currently, the project wiki locatated: https://github.umn.edu/umn-csci-3081-f20/project-portal/wiki is a good way to get on top of some new information.

If you haven't already read and <b>fully</b> digested the pdf here: <https://github.umn.edu/umn-csci-3081-f20/project-portal/blob/master/Iteration1Requirements.pdf> Do so <b>ASAP</b>. There are many questions that can't/haven't been addressed in this pdf, but there have also been some that are in here.

### Concerns about the new technologies<a name="catnt"></a>

#### Docker: What you need to know<a name=docker></a>

* Docker is becoming more and more popular for environment control. Docker provides a flexible and efficient way to create virtual environments where code 'just works'.

* Getting docker set up on a machine is not necessarily an easy task, but once it is set up it should not take much maintenance.

* You <b>do NOT</b> need to understand the in's and out's of Docker for this class.

* You <b>DO</b> need to either use Vole3D or Docker for this class. If you want to use Docker and need help with the first time setup, come to office hours or post on piazza.

* If you do want to use Docker, you do need to know how to execute the scripts in the `bin` folders. There isn't much more to it than just executing them, but if you need help straightening the process out, come to office hours or post on piazza. Also, they can mess up due to some unintuitive things. If they don't work, it's probably some unforeseen variable on our part, so please get help from us for debugging.

* If you want to learn more about Docker which is recommended because it is getting (is already?) popular, go here: <https://docs.docker.com/get-started/>. This is a good first thing to look at, otherwise start googling around for a tutorial you like.

#### Doxygen: What you need to know<a name="doxygen"></a>

* Doxygen is a common documentation generator for programming source code. It allows you to turn comments in source code into rigidly structured documentation.

* You need to be able to tell good documentation from bad documentation. Bad documentation is absent or provides little to no information beyond what is obvious from the code. Bad documentation only tells you what you could have figured out on your own. <b>Good</b> documentation tells you succintly what something is and (sometimes) how it works. Good documentation stops the reader from having to look at code to figure out the thought process behind it. Good documentation is also hard, you will find examples of good <b>and</b> bad documentation in our own support code.

* You <b>NEED</b> to know everything in Lab08 regarding doxygen. That includes:

  - How to generate a `Doxyfile`: use `doxygen -g <path>/Doxyfile`
  
  - What a `Doxyfile` is: It is basically a configuration file which specifies how the documentation will be generated (and where the source code is)

  - What a `mainpage.h` is: It is the 'homepage' of the documentation. It is what opens when you open `index.html`

  - How to comment a C++ file such that good documentaiton will be generated for it: This <https://www.doxygen.nl/manual/docblocks.html> is the best place to look for syntax help.

* You <b>DO NOT</b> need to know the nitty gritty details of how Doxygen generates the code, or anything about how/why it works. If you can generate documentation with Doxygen, your understanding is sufficient for this class.

<a name="googletest"></a>

#### GoogleTest: What you need to know

* GoogleTest is a testing framework designed by, you guessed it, [Alphabet Inc.](https://en.wikipedia.org/wiki/Alphabet_Inc.)

* You <b>NEED</b> to know everything from Lab09 regarding GoogleTest. That includes:

  - How to write a test and/or test fixture with GoogleTest. This: <https://github.com/google/googletest/blob/master/googletest/docs/primer.md> is probably the best place to solidfy your understanding about the pertinent information.

  - How to design a test so that it catches a particular bug.

* You <b>DO NOT</b> need to know how GoogleTest goes from a bunch of `TEST_F()` function lookin' things to executable code.

* You <b>DO NOT</b> need to know how to write a `Makefile` for GoogleTest from scratch, but you <b>SHOULD</B> be comfortable modifying one of our (given direction).

<a name="git"></a>
#### Git: What you need to know

* Git is by far the technology that you need to get most comfortable with out of all of these.

* Git is a Version Control Software (VCS). There are many others, but Git is probably the most powerful, most widespread, and most desired (probably). If you can use Git proficiently you can also likely use any other VCS proficiently.

* Git uses a system of branches to keep track of source code. Git uses commits to add code to branches, and uses merges to combine branches with other branches. These are things you should know and be comfortable with.

* Git termonology, you should be <b>VERY</b> comfortable with these terms and definitions

  - Branch: a state of the code separate from other branches

  - To checkout: Move your change the branch you are currently working on.

  - Commit: a record of change to a branch

  - "local": The state of the code as it currently exists on your hard drive. ("local" isn't so much a noun as an adjective but hopefully that makes sense)

  - HEAD: The current state of the code, applying only the changes that you have "staged".

  - To stage: To add a change made to your HEAD.

  - To commit: To aggregate all changes currently in your HEAD into a single commit.

  - To push: To update your currently checked out branch's remote to match the current state of your HEAD.

  - To pull: To get the current state of your remote on to your machine. Doesn't necessarily overwrite your current changes.

  - "remote(s)": Anywhere your code is that is not on your machine. In this class, your remote is whatver is on github.umn.edu in your repo, and what is in shared-upstream.

  - "origin": The main remote that corresponds to your code, so specifically your repo-x500 on github.umn.edu

  - To merge: To bring all commits from one branch to another (not both ways). Brings commits <b>to</b> the branch you are currently on, <b>from</b> whatever branch name you specify in: `git merge <branchname>`

Again, these should all be easily within your comfort zone. The best place to solidify your understanding of Git is probably here: https://try.github.io/

* Use `git push` and `git pull` often. These commands 'push' code to the almighty cloud, and 'pull' your code from said cloud. The more often you push code to the cloud the less you have to worry if your computer breaks.

* If your git repository on your local machine breaks beyond your skills to fix it, one of the best ways to naively fix it is to remove everything and start over (sometimes referred to by 'nuke').

  - To do this, rename (or delete if you are feeling lucky) your repo-x500 or whatever folder your repository is in on your local machine. Then `git clone` your repo back to your machine. This will completely reset your local state to match your remote repository. For the purposes of this class you will need to go through lab01 again to set up the `shared-upstream` stuff. You will lose any work that was local that you had not `push`'ed so calculate the risks/benefits. You will do less nuking the better you git with git.

* Last thing you <b>NEED</b> to know about Git, is that you don't know anything about Git. I (Aaron) would probably say that I barely know anything about Git, and that's fine. The greatest skill you can have regarding Git is the ability to learn. If you want to do something in Git, you need to google it and find the answer. That's the most important part.

<a name="make"></a>

#### Make: What you need to know

* You should be comfortable with creating a simple `Makefile` from scratch.

* You should be able to run a `Makefile` that we give to you.

* You should be able to edit a `Makefile` that we give to you, given direction on how to edit it.

* You <b>DO NOT</b> need to know how to write an incredibly robust `Makefile` that handles whatever you throw at it.


<a name="picojson"></a>

#### Picojson: What you need to know

* Picojson is a <b>library</b>. (in the general sense, not DLL sense (if this aside doesn't make any sense don't worry about it)).

* You should know that picojson documentation is here: <https://github.com/kazuho/picojson/blob/master/README.mkdn>

* You <b>do</b> need to know that working with external libraries is unavoidable when programming anything non-trival.

* You <b>do</b> need to know how to read documentation (but you are allowed to complain that documentation is bad).

* In the case of picojson, the best resource for syntax is the above link, and the best way to learn it is to just try it out. If what you are doing still eludes you, come to office hours or piazza, but once you get the first few lines of code I think you'll realize that it isn't that bad.

* You should also know that a picojson helper courtesy of the 3081 staff is on its way. You can either choose to use it or just use picojson itself.

### Miscellaneous question/answer session

We will try to keep the FAQ on github up to date, reflecting any questions posed during this session.

<https://github.umn.edu/umn-csci-3081-f20/project-portal/wiki/Frequently-Asked-Questions>
