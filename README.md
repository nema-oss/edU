# edU
edU (ed with multiple undos) is a simple command line text editor, which allows to manipulate sequences of strings by insertion and deletion. Moreover, it allows to undo actions and re do them. This work has been assigned as a project in the course Algoritmi e Principi dell'Informatica at Politecnico di Milano, A.Y. 2019/2020.

The text is divided into lines. The editor will accept 5 types of commands:
  
  * **change** - (*ind1*,*ind2*)c: this prepares for the insertion of text on lines from *ind1* to *ind2-ind1+1*. The text that follows must be composed of a number of lines equal to *ind2-ind1+1* and *ind1* has to be either an existing line number or the line after the last line of text (or 1 if there is no text).
  
  * **delete** - (*ind1*,*ind2*)d: deletes the text in between indices *ind1* and *ind2*, extremes included. The deletion of a line that doesn't exist has no effect.
  
  * **print** - (*ind1*,*ind2*)p: prints the lines from *ind1* to *ind2* included. When a line doesn't exist, "." is printed, followed by a newline.
  
  * **undo** - (*n*)u: undoes the last *n* deletions or changes. *n* includes also actions that have no effect, such as the deletion of non existing lines.
  
  * **redo** - (*n*)r: redoes the last *n* actions that have been undone by a previous undo command. 
  
  
The editor assumes well formed commands, where *ind1* is always either an existing line number or the first empty line after the last line of text. Moreover it assumes no commands with *ind1>ind2* or *ind1<1* are issued.
