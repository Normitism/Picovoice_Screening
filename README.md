# Picovoice_Screening

##Overview
Questions 1, 2 and 3 were completed. Questions 1 and 2 were answered in python, while 3 was answered in C. For question 1, the probabilities of each day were each assumed to be independant. For question 2, the assumption that the phonetics dictionary used would resemble the given example. For the third question, the assumption that words that were separated by punctuation such as pale--they and tiger-footed, were considered to be two separate words, while words such as school'd were considered to be 1. 

##Question 1
The traditional poisson binomial distribution was calculated via FFT to improve the efficiency of the program as the data set was 365 elements long. Thus, utilizing FFT can massively improve the efficiency of the program.

##Question 2
A Dynamic programming approach was taken to solve the problem through the use of memoization. The initial phonetics dictionary was inverted to where the pronouncation was converted into a tuple and made to be the key and the words were linked to the pronounciations. Then a recursive approach was taken to build a list of all the possible permutations of the phonetics. An additional hashmap was used to keep track of previously found words.

##Question 3
In order to keep track of the most frequent word, a hashmap was implemented in C. This involved the implementation for both the insert and get functions as well as the hashkey generation function and free function. The txt file was read through line by line, at each line, the text was normallized to have lower case and to have no punctuation excluding the ' character. Each word was stored in a return buffer and then counted and the most frequent element tracked.
