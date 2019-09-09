### ROBOT  TAKESHI
This repository is for work whit Service Robot **HSR**, we are a group of researchers beloging to National Autonomous University of Mexico. Our research group is called [Biorobotics Laboratory](https://biorobotics.fi-p.unam.mx/), we are focused in navigation and planning action task.
                                                                                                     
-----------------
### INSTALL

# Using CMUsphinx with Takeshi

In order to drop the MS windows for voice recognition we can use
pocketSphinx integration with ROS provided by Mr Julio Profe.
However some extra steps are required:

1.  Install BaseSphinx.
2.  Install PocketSphinx.
3.  Install python binding to pocket sphinx with pip .
4.  Create the dictionary.
5.  Create the grammars.

## Install BaseSphinx and PocketSphinx

Go to the CMUsphinx git hub and install, you need to both install
[BaseSphinx](https://github.com/cmusphinx/sphinxbase) and
[PocketSphinx](https://github.com/cmusphinx/pocketsphinx) both need to be
compiled with Make and installed, follow the instructions on both Git's.
This is specially important as the language model for English is
installed as part of process.

## Install Python bindings using pip

Relatively easy, just type.

    python -m pip install --upgrade pip setuptools wheel
    pip install --upgrade pocketsphinx

Be carefull as sometimes this install on python3 and ROS Kinetic uses python2
by default. In theory this step is optional as installing pocket sphinx should install
the python bindings but sometimes it does not.

## Creating the dictionary

For some reason configuration is a pain. For operation CMUsphinx requires 3 things:
1\. A language Model file.lm.bin pdm files and whatnot.
2\. A dictionary file.dict or file.dic
3\. A grammar or keyword list file.jsfg and file.kwlist

The first one is a whole directory the default is installed with Pocket sphins and
its default location is `/usr/local/share/pocketsphinx/model/en-us/en-us`. This contains
the hidden markov model for the selected language separated in a lot of files.
The dictionary contains a mapping from words to graphemes as CMUsphinx recognizes
phonemes not words.
A sample dictionary can be found in [CMUDict](https://github.com/cmusphinx/cmudict)
but it is easy to create a custom one using [lmtool](http://www.speech.cs.cmu.edu/tools/lmtool-new.html). Just create a simple
file with one line per each phrase you want to recognize. Example taken from lmtools website:

    THIS IS AN EXAMPLE SENTENCE
    EACH LINE IS SOMETHING THAT YOU'D WANT YOUR SYSTEM TO RECOGNIZE
    ACRONYMS PRONOUNCED AS LETTERS ARE BEST ENTERED AS A T_L_A
    NUMBERS AND ABBREVIATIONS OUGHT TO BE SPELLED OUT FOR EXAMPLE
    TWO HUNDRED SIXTY THREE ET CETERA
    YOU CAN UPLOAD A FEW THOUSAND SENTENCES
    BUT THERE IS A LIMIT

Finally you need a grammar file, this uses a rather cumbresome sintax so please refer to existing examples provides on the hri/cmusphinx package.
