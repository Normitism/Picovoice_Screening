# Picovoice_Screening

## Overview
Questions 1, 2 and 3 were completed. Questions 1 and 2 were answered in python, while 3 was answered in C. For question 1, the probabilities of each day were each assumed to be independent. For question 2, the assumption that the phonetics dictionary used would resemble the given example. For the third question, the assumption that words that were separated by punctuation such as pale--they and tiger-footed, were considered to be two separate words, whereas the apostrophe ' character was exempted from this rule, such that words such as school'd were considered to be 1. Additionally the assumption that memory was not limited.

## Question 1
The traditional poisson binomial distribution was computed via FFT to improve the efficiency of the program as the data set was 365 elements long. Thus, utilizing FFT can massively improve the efficiency of the program.

## Question 2
A dynamic programming approach was taken to solve the problem through the use of memoization. The initial phonetics dictionary was inverted mapping the pronunciations, as tuples, to their words. Then a recursive approach was taken to build a list of all the possible segmentations of the input and the valid ones returned. An additional hashmap was used to keep track of previously computed results.

## Question 3
In order to keep track of the most frequent word, a hashmap was implemented in C. This involved the implementation for both the insert and get functions as well as the hashkey generation function and memory deallocation function. The txt file was read through line by line, at each line, the text was normalized to have lower case and to have no punctuation excluding the ' character. Each word was then counted. A bucket sort algorithm was used to find the n most frequent words.
