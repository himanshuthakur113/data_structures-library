# Day 8 Journal

## Section 1 — Project Progress

### Task 1: Memory Validation

I started the day by integrating **Valgrind** into my project using CMake. This allows me to perform memory checking directly from the build system without manually typing long Valgrind commands every time I want to test the project.

### Task 2: Testing HashMap with User-Defined Types

After validating the existing implementation, I created a new test file to verify that my templated `HashMap` works correctly with user-defined classes.

### Task 3: Learning Web Crawler Architecture

In the second session, I shifted my focus to learning how a Web Crawler works. Instead of implementing it immediately, I first wanted to understand its overall architecture and how its different components interact.

---

## Section 2 — Investigation and Understanding

The first task of the day was integrating **Valgrind** with CMake. Once the integration was complete, I ran the entire Google Test suite under Valgrind. All **240 unit tests** passed successfully, and Valgrind reported no memory leaks, invalid memory accesses, or lost memory blocks. This confirmed that the manual memory management throughout my data structure library is working correctly.

Next, I created a new test file named `HMuserdefined_test.cpp` to verify that my `HashMap` supports user-defined key types. I created an `Employee` class and wrote several unit tests covering insertion, lookup, updates, and collision handling.

While writing these tests, I revised how templates interact with user-defined types. I reinforced my understanding that custom key types require `operator==` so that keys stored within the same bucket can be compared correctly. I also understood why a custom hash functor is necessary when the default hashing strategy is not suitable for a user-defined class.

I also explored the fallback behavior of my `DefaultHash` implementation. For unsupported types, it hashes the object's memory address instead of its value. To better understand this behavior, I wrote a test that verifies the same object instance can still be found successfully because its address remains unchanged.

In the second session, I began studying the design of a Web Crawler. Instead of immediately focusing on implementation details, I first tried to understand the complete crawling workflow.

I learned that the crawler begins with one or more **seed URLs**. Each URL is downloaded, its HTML is parsed, all hyperlinks are extracted, and any newly discovered URLs are added to the Frontier. The downloaded page is stored, and the crawler continues this process until either there are no more URLs to visit or predefined limits such as maximum depth or maximum pages have been reached.

I also spent some time understanding how search engines use web crawlers. Initially, I assumed that a search engine searches the Internet whenever a user submits a query. After reading about search engine architecture, I learned that this is not how they operate. Search engines continuously crawl the web beforehand, download web pages, and build an index. When a user searches for something, the search engine queries this index instead of the live web, allowing results to be returned almost instantly.

Finally, I studied the three primary data structures used in a crawler:

- **Frontier** – stores the URLs waiting to be crawled.
- **Seen Set** – keeps track of URLs that have already been visited to prevent duplicate crawling.
- **Page Store** – stores the downloaded HTML pages for future processing or indexing.

Understanding how these components work together gave me a much clearer picture of how a crawler operates internally.

---

## Section 3 — Design Diagram

### Overall Web Crawler Workflow

```text
          Seed URL
              │
              ▼
        Frontier (Queue)
              │
              ▼
          Fetch Page
              │
              ▼
        Download HTML
              │
              ▼
        Extract Links
              │
      ┌───────┴────────┐
      │                │
      ▼                ▼
 Store HTML       New URLs Found
      │                │
      ▼                ▼
  Page Store      Seen Set Check
                       │
          Already Seen? ───► Yes → Ignore
                       │
                      No
                       │
                       ▼
              Add to Frontier
```

---

### Search Engine Pipeline

```text
          Web
           │
           ▼
     Web Crawler
           │
           ▼
    Download Pages
           │
           ▼
      Build Index
           │
           ▼
      User Search
           │
           ▼
     Search the Index
           │
           ▼
        Search Results
```

---

### HashMap with User-Defined Types

```text
Employee Object
        │
        ▼
Custom Hash Functor
        │
        ▼
Hash Value
        │
        ▼
HashMap Bucket
        │
        ▼
operator==
        │
        ▼
Matching Employee
```

---

## Section 4 — Work Completed

**Work Completed**

- Integrated Valgrind into the CMake build system.
- Executed the complete test suite using Valgrind.
- Verified there were no memory leaks or invalid memory accesses.
- Created `HMuserdefined_test.cpp`.
- Tested `HashMap` with a custom `Employee` class.
- Verified support for custom hash functors.
- Tested the fallback behavior of `DefaultHash`.
- Started studying Web Crawler architecture.
- Learned the complete crawling workflow.
- Studied how search engines build and use an index.
- Learned the responsibilities of the Frontier, Seen Set, and Page Store.

---

## Section 5 — Learning Reflection

Today gave me confidence that the work I have done over the past few days is reliable. Running the entire project under Valgrind and seeing every test pass without any memory errors was satisfying because it confirmed that the manual memory management in my data structures is working as intended.

Working with user-defined types also helped me understand that templates become much more useful when they are tested with more than just primitive data types. Creating the `Employee` class reminded me that generic containers depend on the user to define operations like hashing and equality whenever the library cannot infer them automatically.

The second half of the day shifted my focus from implementation to system design. Learning how a Web Crawler works made me realize that the crawler itself is only one part of a much larger search engine pipeline. Understanding the roles of the Frontier, Seen Set, and Page Store gave me a clear mental model of how pages move through the system, and I now feel much more prepared to start designing and implementing my own crawler.