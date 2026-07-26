# Day 7 Journal

## Section 1 — Implementation Progress

### Task 1: Understanding Iterators

I started the day by revisiting the custom `Iterator` implementation in my `LinkedList`. Although I had implemented it earlier, I wanted to understand why it was written the way it was instead of simply knowing that it worked.

### Task 2: HashMap Testing

After that, I completed the unit tests for the `HashMap`. While doing so, I spent some time understanding how Google Test organizes and executes different kinds of test cases.

### Task 3: Redis Lite Implementation

Once the HashMap tests were complete, I started implementing Redis Lite. Since Redis Lite is built on top of my own `HashMap`, most of the work involved connecting user commands to the underlying data structure through a simple REPL and command handlers.

### Task 4: Improving the Data Structure Library

While implementing Redis Lite, I discovered a few missing features in my data structures. I added const-correct overloads and introduced a reusable `clear()` function that simplified both the library and the Redis Lite implementation.

---

## Section 2 — Investigation and Understanding

I began the day by studying my `LinkedList` iterator in more detail. While reading about iterators, I also learned why template code sometimes requires the `typename` keyword before nested types such as:

```cpp
typename LinkedList<T>::Iterator
```

Initially, I thought `typename` was just another template keyword, but I learned that the compiler cannot immediately determine whether `Iterator` is a type because it depends on the template parameter `T`. Writing `typename` explicitly tells the compiler that `Iterator` is a type, allowing the template to compile correctly.

While writing the HashMap tests, I became confused because Google Test grouped some tests separately from others. At first, I thought the tests written with `TEST` were not executing. After reading the documentation, I realized that Google Test groups tests by **test suite**, not by source file. Both `TEST` and `TEST_F` were executing correctly; they simply appeared under different suite names.

After finishing the tests, I started implementing Redis Lite. Since it is built directly on top of my own `HashMap`, I did not need to implement another storage mechanism. Instead, I focused on building the REPL, command tokenization, command dispatching, and implementing the core commands:

- `SET`
- `GET`
- `DEL`
- `EXISTS`
- `COUNT`
- `CLEAR`

While writing the command handlers, I encountered a const-correctness issue. The handlers accepted `const DA<std::string>&`, but my `DynamicArray` only provided a non-const version of `operator[]`. This prevented elements from being accessed through const objects.

To solve this, I added another overload:

```cpp
const T& operator[](int index) const;
```

While implementing this overload, I finally understood the difference between the two uses of `const`.

- The first `const` (`const T&`) means the returned element cannot be modified.
- The second `const` (after the function) promises that calling the function will not modify the state of the object itself.

This made const-correctness much clearer than before.

Later, while implementing the `CLEAR` command, I realized my `HashMap` did not provide a `clear()` function. My first thought was to implement the deletion logic directly inside Redis Lite, but I realized that would mix application logic with container logic.

Instead, I implemented `clear()` inside `LinkedList`, reused it to build `HashMap::clear()`, and then simply called:

```cpp
store.clear();
```

from Redis Lite. This not only kept responsibilities separated but also allowed the `LinkedList` destructor to reuse the same cleanup logic instead of maintaining duplicate code.

Finally, I completed the Redis Lite test suite and added regression tests for the newly introduced `clear()` functions to ensure the refactoring had not broken any existing functionality.

---

## Section 3 — Design Diagram

### Redis Lite Architecture

```text
              User
                │
                ▼
        Command Line (REPL)
                │
                ▼
        Tokenize Input
                │
                ▼
        Command Dispatcher
                │
      ┌─────────┼──────────┐
      │         │          │
      ▼         ▼          ▼
    SET()     GET()     CLEAR()
      │         │          │
      └─────────┼──────────┘
                │
                ▼
      HashMap<std::string, std::string>
                │
                ▼
      DynamicArray<LinkedList<KV>>
                │
                ▼
             LinkedList
                │
                ▼
               Nodes
```

---

### Const Overloads

```text
Non-const Object
        │
        ▼
operator[]()
        │
        ▼
T&  ← Element can be modified

-------------------------------

Const Object
        │
        ▼
operator[]() const
        │
        ▼
const T&  ← Read-only access
```

---

### `clear()` Reuse

```text
Redis Lite
     │
store.clear()
     │
     ▼
HashMap::clear()
     │
     ▼
LinkedList::clear()
     │
     ▼
Delete Every Node
```

Instead of each class implementing its own deletion logic, each layer reuses the functionality provided by the layer beneath it.

---

## Section 4 — Work Completed

**Work Completed**

- Studied the implementation of the custom `LinkedList` iterator.
- Learned the purpose of `typename` in template code.
- Completed the `HashMap` unit tests.
- Learned the difference between `TEST` and `TEST_F` in Google Test.
- Implemented the Redis Lite REPL.
- Implemented command tokenization.
- Implemented command dispatching.
- Added support for `SET`, `GET`, `DEL`, `EXISTS`, `COUNT`, and `CLEAR`.
- Added a const overload for `DynamicArray::operator[]`.
- Implemented `LinkedList::clear()`.
- Implemented `HashMap::clear()`.
- Simplified the `LinkedList` destructor by reusing `clear()`.
- Completed the Redis Lite unit tests.
- Added regression tests for the new `clear()` implementations.
- Successfully passed **240 unit tests** across the entire project.

---

## Section 5 — Learning Reflection

Today I spent more time understanding concepts that I had already used instead of learning completely new ones. Revisiting the iterator implementation helped me understand that writing code that works is different from understanding why it works. Learning about the `typename` keyword also made templates feel a little less mysterious because I finally understood the problem it solves rather than just memorizing the syntax.

I also gained a much better understanding of const correctness. Before today, I knew that some member functions ended with `const`, but I never fully understood what that meant. After adding the const overload of `operator[]`, I now understand why standard library containers provide both const and non-const versions of many functions and how they help prevent accidental modification of objects.

Another thing I learned was the importance of keeping responsibilities separated. When I needed the `CLEAR` command, my first instinct was to implement the deletion logic inside Redis Lite. After thinking about it, I realized that the data structure itself should provide that functionality. By adding `clear()` to `LinkedList` and reusing it in `HashMap`, the application code became much simpler and the library became more reusable.

Finally, seeing all **240 unit tests** pass gave me confidence that the project is becoming more stable as it grows. Every time I add a new feature or refactor existing code, the tests help verify that I haven't accidentally broken something that was already working.