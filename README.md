# CS300_portfolio_submission
A project that uses hash tables to sort a list of college courses alphanumerically.


# Summary

My intentions with this project were to make a program that sorted a spreadsheet of courses in a alphanermeric order. A variety of sorting methods are viable for this procedure, though many are very slow and can hinder the program from working quickly when sorting larger lists. Something like a vector is very easy to setup and use, but with an average runtime of O(n^2), can slow things down to much. On the contrary, something like a binary tree has a much faster runtime of o(n), but can be quite complex to setup.

During the creation of this program, I ran into quite a few roadblocks. The first was the initial setup of the hashtable, and deciding what methods would be useful to the program I was making. By taking a step back and relearning the way hash tables operate, I was able to draw it out and decide on how I was going to structure it. Another issue I had was parsing the data from the CSV. While I had done similar parsing before, I hadn't built a parser from scratch that worked directly with a CSV file. I was able to find some similar examples on StackOverflow that was able to point me in the right direction. Finally the last issue I ran into was the sorting. The way the hashtable worked allowed the courses to be nearly sorted once they were inserted, but I had to make a decision on how to do the final sorting before printing the courses to the console. I settled on using the algorithm package in C++ to do this heavy lifting for me, though I may decide to go back at some point and do my own sorting method.

Prior to this project, I was not very conscious of a program's runtime and how it could be affected at a larger scale. I was mostly focused on handling edge cases and making sure the program worked as expected. After completing this project, I became much more aware of how slow or fast a program runs, and I’ve even gone back to some of my older personal projects to identify and optimize areas with poor runtime.

Additionally, my sorting skills have improved significantly. I now find myself better equipped to solve challenges on platforms like LeetCode that I struggled with before. This project helped me step back and better understand the full workflow of a program—from planning and pseudocode to structure and performance.

Throughout development, I encountered bugs that made me realize the importance of writing clean, maintainable code. Because the project was built in a modular way, I was able to quickly locate and fix issues. If everything had been crammed into a single main() function, it would have made debugging and scaling far more difficult. This experience reinforced why readable, well-organized code is essential for long-term adaptability.
