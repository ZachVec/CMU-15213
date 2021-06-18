This file contains materials for one instance of the attacklab.

Files:

    ctarget

Linux binary with code-injection vulnerability.  To be used for phases
1-3 of the assignment.

    rtarget

Linux binary with return-oriented programming vulnerability.  To be
used for phases 4-5 of the assignment.

     cookie.txt

Text file containing 4-byte signature required for this lab instance.

     farm.c

Source code for gadget farm present in this instance of rtarget.  You
can compile (use flag -Og) and disassemble it to look for gadgets.

     hex2raw

Utility program to generate byte sequences.  See documentation in lab
handout.

============================= Added for solutions ===========================
Files:

    phase1.txt phase2.txt phase3.txt

Solutions for code injection attack, i.e., ctarget. Example Usage:

    unix> cat phase1.txt | ./hex2raw | ./ctarget -q

Files:

    phase4.txt

Solutions for return programming attack, i.e., rtarget. Example Usage:

    unix> cat phase4.txt | ./hex2raw | ./rtarget -q

