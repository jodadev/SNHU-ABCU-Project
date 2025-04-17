# Project Two: Computer Science Course Advisor Program

## Reflection

### What was the problem you were solving in the projects for this course?
The primary problem I was solving throughout this course was how to design a program that efficiently stores, accesses, and displays course data for a computer science advising system. The goal was to allow advisors to load course information from a file, search for specific course details, validate prerequisite relationships, and print a sorted list of courses. This required selecting an appropriate data structure and implementing a working solution that could handle user input and file-based course management reliably.

### How did you approach the problem? Consider why data structures are important to understand.
I approached the problem by first evaluating how different data structures behave in terms of time complexity and operational requirements. I created pseudocode for vector, hash table, and binary search tree implementations, analyzing each structure's strengths and weaknesses. Understanding data structures is critical because the efficiency and scalability of a program depend on how data is organized and accessed. I ultimately selected a binary search tree for its ability to maintain a naturally sorted order, which fit the requirements for displaying an alphanumeric course list.

### How did you overcome any roadblocks you encountered while going through the activities or project?
One roadblock I encountered was related to prerequisite validation, specifically determining whether a listed prerequisite actually existed within the data structure. Each structure required a different approach—linear search for vectors, bucket traversal for hash tables, and recursive or iterative search for BSTs. I overcame these challenges by simulating and walking through each logic step-by-step, using the pseudocode I wrote earlier in the course as a foundation. I also had to ensure that my tree remained functional even with edge cases like missing or misformatted course data. Breaking down the problem into smaller, testable parts helped me move forward with clarity.

### How has your work on this project expanded your approach to designing software and developing programs?
Working on this project has improved how I approach software design. It reinforced the importance of planning and analyzing data structure suitability before implementation. Writing detailed pseudocode helped me clarify logic before translating it into code, which made development smoother and reduced bugs. I also gained more appreciation for balancing readability, efficiency, and structure in my program architecture. The need to think ahead about validation, input handling, and modular design taught me to consider not just how code works, but how it should behave from a user’s perspective.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
This project has made me more conscious of writing clean, maintainable, and adaptable code. I now prioritize descriptive function names, concise in-line comments, and modular class design. Structuring my code around core responsibilities, such as separating file parsing, data validation, and menu interaction, has helped keep my program organized and easier to debug or modify. I’ve also adopted practices like writing reusable utility functions and encapsulating logic inside data structures to reduce duplication. Overall, this experience has elevated the professionalism and scalability of the programs I create.
