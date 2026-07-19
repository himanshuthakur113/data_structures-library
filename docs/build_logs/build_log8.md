# Build Log 8

## Date:Jul 16

### Session - 1

#### Work Completed

- I first integrated Valgrind into the project through CMake so memory checking could be executed directly from the build system. After running the entire Google Test suite under Valgrind, all 240 unit tests passed successfully with zero memory leaks, zero invalid memory accesses, and every allocation correctly freed.

![valgrind_test](images/Valgrind%20test.png)

-After this I implemented one more test file for HashMap HMuserdef_test.cpp I designed a new set of unit tests using a custom Employee class to verify that the templated HashMap works correctly with user-defined objects. While writing these tests, I reviewed how generic containers depend on both operator== and a custom hash functor to correctly compare and hash user-defined keys.

I also explored the behavior of my DefaultHash implementation for unsupported types. Since it hashes objects using their memory addresses, I wrote an additional test to verify that the same object instance can be found correctly when the default hasher is used.

![HM_serdefined test](images/HMuserdefined_test.png)

## Session - 2

#### Work Completed

- I learned the complete crawling workflow, from starting with a seed URL, fetching HTML, extracting links, storing pages, and continuing until the Frontier becomes empty or predefined limits such as maximum depth or maximum pages are reached.

- I also learned how search engines use crawlers to build an index in advance, allowing user queries to be answered quickly without searching the live web.

- There are mainly 3 data structure first the Frontier which contain the URL that are to visited next ,second the seen which will used to check if the page is already visited or not and at last the store which will store the raw htrml file of page.

- The workflow of the crawler is as follows. First, there is one or more seed URLs from where the crawling process starts. Each seed URL is first checked in the Seen set. If it has not been visited before, it is marked as seen so that it will not be crawled again. After that, the Fetcher downloads the HTML page of that URL and the page is stored inside the Page Store. Once the page is downloaded, the Link Extractor extracts all the URLs present in that HTML. Each extracted URL is normalized and checked against the Seen set. If the URL has not been visited before, it is marked as seen and inserted into the Frontier along with its crawl depth. The crawler then repeatedly takes the next URL from the frontier, fetches its page, stores it, extracts new links, and adds only the unseen URLs back into the frontier. This process continues until the frontier becomes empty or a predefined crawl limit is reached.