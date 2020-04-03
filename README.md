# CFPB_Consumer_Complaints
**Short Compilation of Issues about Products from Companies, 2018 to 2020**


**I. Choice of Compiler Language**

   The source code was written with C++ and its Standard Template Library.


**II. Reading the Data**

   To analyze the input file, a function called Reading_Data was written that (a) determines, from the header line, the respective column position of the terms ‘Date received,’ ‘Product’ and ‘Company.’ Next, the data from the ‘Product’ and ‘Company’ columns are collected character by character into respective vector containers. These two vector containers contain the universe of responses for that input data.

   Toward that universe of data, a n-ary tree vector container is compared in a second function called Filing_the_Data. This function selectively reads the input file again, line by line. In each line, the respective input from the year according to the ‘Date received,’ is compared against the parts of the n-art tree that has the ‘Product’ and ‘Company.’ An increment occurs to the term product count if there is a match for the ‘Product’ and then an increment for a complaint count term with the respective ‘Company.’

   The data itself is from the years 2010 to 2020. The Consumer Financial Protection Bureau (CFPB) was created in 2010 by the Dodd-Frank Wall Street Reform and Consumer Protection Act, Pub. L. 111–203, title X, § 1011, July 21, 2010, 124 Stat. 1964. CFPB is an independent bureau within the Federal Reserve System.


**III. Addressing Duplicates, Exceptional Errors, and Verbose Input**

   As with any input written by human beings, sometimes there are creative interpretations or unexpected errors. Yet, there are common patters that emerge. For the ‘Company’ and ‘Product’ inputs, the duplicates were addressed in the Filing_the_Data function. Also, input that consisting of blanks or single character punctuation was called “blanks” in the n-ary tree vector container. Input that exceeded  78 characters was called “verbose, misentered response.”

**IV. Calculations**

   The computations were based upon finding the maximum of the complaint count as well as a summation of the complaint count. From the Standard Template Library, the functions maximum_element and accumulate were deployed.

**V. Remaining Refinements**

   Even with accounting for duplicates, the input data was still very large. A lexical analysis is required to further identify repetitive data. Before addressing duplicates, the number of products was 1,628,337. After resizing, there were 1,207,061 inputs, which is a difference of 421,276. Similarly, the number of inputs for company were 1,545,285. After resizing, the number was reduced to 1,311,998, for a difference of 233,287.
