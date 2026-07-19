# Daily Journal

## Date: Jul 16

Today I worked on both my Data Structures Library and started learning about the design of a Web Crawler.

In the first session, I integrated Valgrind into my project using CMake so I can run memory checking directly from the build system. After that I executed my complete Google Test suite with Valgrind. All 240 tests passed successfully with no memory leaks, no invalid memory access, and all allocated memory was freed correctly. This gave me confidence that my data structures are handling memory properly.

After this I created another test file, `HMuserdefined_test.cpp`, to verify that my templated HashMap also works with user-defined objects. I created an `Employee` class and wrote different test cases for it. While doing this I revised how templates work with custom types, why `operator==` is required for comparison, and why a custom hash functor is needed for hashing user-defined objects. I also explored the behavior of my `DefaultHash` implementation for unsupported types and learned that it hashes objects using their memory addresses. I wrote a test to verify that the same object instance can still be found correctly.

In the second session, I started learning about the architecture of a Web Crawler. I understood the complete crawling workflow starting from a seed URL, fetching the HTML page, extracting all links from that page, storing the downloaded page, and continuing the same process until there are no more URLs left in the Frontier or the crawler reaches a predefined limit like maximum depth or maximum pages.

I also learned how search engines work internally. Instead of searching the live web whenever a user enters a query, they first crawl the web, download pages, and build an index. Later, the search engine simply searches that index, which makes the results much faster.

Finally, I learned about the three main data structures used in a crawler. The **Frontier** stores the URLs that need to be crawled next, the **Seen** set keeps track of already visited URLs to avoid duplicate crawling, and the **Page Store** stores the downloaded HTML pages. Understanding how these three components work together helped me understand the complete crawling pipeline and will make it easier for me to design my own crawler.
