               The International Obfuscated C Code Contest

Copyright (c) Landon Curt Noll, Simon Cooper, Peter Seebach
and Leonid A. Broukhis, 2001-2009.
All Rights Reserved.  Permission for personal, educational or non-profit
use is granted provided this this copyright and notice are included in its
entirety and remains unaltered.  All other uses must receive prior permission
from the contest judges.

Obfuscate:  tr.v.  -cated, -cating, -cates.  1. a.  To render obscure.
        b.  To darken.  2. To confuse:  Their emotions obfuscated their
        judgment.  [LLat. obfuscare, to darken : ob(intensive) +
        Lat. fuscare, to darken < fuscus, dark.] -obfuscation n.
        obfuscatory adj.


	    Last updated: Tue Jun 29 13:29:27 PDT 1999

The official IOCCC web site is:

	http://www.ioccc.org


How it was started:

The original inspiration of the International Obfuscated C Code
Contest came from the Bourne Shell source and the finger command as
distributed in 4.2BSD.  If this is what could result from what some
people claim is reasonable programming practice, then to what depths
might quality sink if people really tried to write poor code?

I put that question to the USENET news groups net.lang.c and
net.unix-wizards in the form of a contest.  I selected a form similar
to the contest (Bulwer-Lytton) that asks people to create the worst
opening line to a novel.  (that contest in turn was inspired by disgust
over a novel that opened with the line "It was a dark and stormy
night.")  The rules were simple: write, in 512 bytes or less, the worst
complete C program.

Thru the contest I have tried to instill two things in people.  First
is a disgust for poor coding style.  Second was the notion of just how
much utility is lost when a program is written in an unstructured
fashion.  Contest winners help do this by what I call satirical
programming.  To see why, observe one of the definitions of satire:

	Keen or energetic activity of the mind used for the purpose
	of exposing and discrediting vice or folly.

The authors of the winning entries placed a great deal of thought into
their programs.  These programs in turn exposed and discredited what I
considered to be the programmer's equivalent of "vice or folly".

There were two unexpected benefits that came from the contest winners.
First was an educational value to the programs.  To understand these C
programs is to understand subtle points of the C programming language.
The second benefit is the entertainment value, which should become
evident as you read further!



Suggestions on how to understand the winning entries:

You are strongly urged to try to determine what each program will
produce by visual inspection.  Often this is an impossible task, but
the difficulty that you encounter should give you more appreciation
for the entry.

If you have the energy to type in the text, or if you have access to
a machine readable version of these programs, you should next consider
some preprocessing such as:

	sed -e '/^#.*include/d' program.c | cc -E

This strips away comments and expands the program's macros without
having things such as <stdio.h> macros clutter up the output.  If the
entry requires or suggests the use of compile line options (such as
-Dindex=strchr) they should be added after the '-E' flag.

The next stage towards understanding is to use a C beautifier or C
indenting program on the source.  Be warned that a number of these
entries are so twisted that such tools may abort or become very
confused.  You may need to help out by doing some initial formatting
with an editor.  You might also try renaming variables and labels to
give more meaningful names.

Now try linting the program.  You may be surprised at how little lint
complains about these programs.  Pay careful attention to messages
about unused variables, wrong types, pointer conversions, etc.  But be
careful, some lints produce incorrect error messages or even abort!
Your lint may detect syntax errors in the source.  See the next
paragraph for suggestions on how to deal with this.

When you get to the stage where you are ready to compile the program
examine the compilation comments above each entry.  A simple define or
edit may be required due to differing semantics between operating
systems.  If you are able to successfully compile the program,
experiment with it by giving it different arguments or input.
You may also use the makefile provided to compile the program.
Keep in mind that C compilers often have bugs, or features which
result the program failing to compile.  You may have to do some
syntax changing as we did to get old programs to compile on strict
ANSI C compilers.

Last, read the judges' comments/spoilers on the program.  Hints
for `foo.c' are given in `foo.hint'.  Often they will contain suggested
arguments or recommended data to use.

If you do gain some understanding of how a program works, go back to
the source and reexamine it using some of the techniques outlined above.
See if you can convince yourself of why the program does what it does.


Regarding the source archive:

Each sub-directory contains all the entries for a single year.  Often
the file names match one of the last names of the author.  Judges'
hints are given in files of the form ``*.hint''.

You may need to tweak the Makefile to get everything to compile correctly.
Read the hint files for suggestions.

The rules for a given year are given in the file named ``rules''.  Each
archive contains a copy of the rules for the upcoming contest.

The following URL is the official archive of the winning entries:

	http://www.ioccc.org/years.html


Regarding the distribution of sources:

All contest results are in the public domain.  We do ask that you observe
the following request:

You may share these files with others, but please do not prevent them of
doing the same.  If some of these files and/or contest entries are
published in printed form, or if you use them in a business or classroom
setting, please let us know.  We ask that you drop a line to the
'judges' EMail box.  See the following page for instructions on
how to send us a message,

	http://www.ioccc.org/contact.html

Some final things to remember:

While the idea for the contests has remained the same through the
years, the contest rules and guidelines vary.  What was novel one year
may be considered common the next.  The categories for awards differ
because they are determined after the judges examine all of the
entries.

The judges' hints assume that the program resides in a file with the
same username as the author.  Where there is more than one author, the
first named author is used.

Some C compilers are unable to compile some of these programs.  The
judges tried to select programs that were widely portable and
compilable, but did not always succeed.  As of 1990, and entry
may use both ``K&R'' and ANSI C compilers.  Makefiles for both
types of C compilers are used.  See the contest rules for details.

You are strongly encouraged to read the new contest rules before
sending any entries.  The rules, and sometimes the contest Email
address itself, change from time to time.  A valid entry one year may
be rejected in a later year due to changes in the rules.  See:

	http://www.ioccc.org/index.html#enter

for up to date information on how to enter.

Last, PLEASE don't code in the style of these programs It is hoped that
you will gain an understanding that poor style destroys an otherwise
correct program.  Real programmers don't write obfuscated programs,
unless they are submitting a contest entry!  :-)

Happy pondering!
