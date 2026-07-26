# Day 5 Journal

## Section 1 — Design Improvements

### Task 1: Supporting Custom Hash Functions

The first improvement I made was modifying the `HashMap` to accept a third template parameter representing the hash function. Instead of keeping the hashing logic inside the `HashMap`, I moved it into a separate `DefaultHash<Key>` functor, allowing users to provide their own hashing implementation for custom key types.

### Task 2: Improving the Default Hash Function

After restructuring the `HashMap`, I improved the default hash function by adding support for `double` values and thinking about how unsupported key types should be handled.

### Task 3: Refactoring Bucket Storage

I then refactored the `HashMap` to use my existing `DynamicArray` implementation as the bucket container. While doing this, I discovered and fixed a hidden bug in `DynamicArray`.

### Task 4: Template and Memory Management Bugs

During the refactoring process, I encountered several template syntax mistakes and object lifetime bugs that required careful debugging.

---

## Section 2 — Investigation and Understanding

The first major improvement was separating the hashing logic from the `HashMap` itself. Instead of hardcoding the hash function inside the container, I created a separate `DefaultHash<Key>` functor and made it the third template parameter of the `HashMap`. This keeps the responsibilities separate: the `HashMap` manages key-value pairs, while the functor is responsible only for generating hash values.

To verify the design, I created a custom `Employee` class along with its own hash functor. The tests confirmed that insertion, updating existing keys, collision handling through separate chaining, and automatic rehashing all continued to work correctly.

While making this change, I encountered a template bug. Although I updated the class declaration to include the third template parameter, I forgot to update several out-of-class member function definitions. Since the `template<>` declarations still contained only two template parameters, the compiler reported confusing template errors. Updating every function definition to match the class declaration resolved the issue.

Next, I improved the default hash function by adding support for `double`. Initially, I considered converting floating-point values directly to integers, but I learned that this causes many different values to produce the same integer after truncation, leading to unnecessary collisions. Instead, I generated the hash using the bit representation of the `double`, preserving much more information.

I also considered how the `HashMap` should behave when users provide completely unknown key types without defining a custom hash function. I decided to use the object's memory address as a fallback hash. Although this provides identity-based hashing rather than value-based hashing, it still allows unsupported types to be stored. To reduce incorrect usage, I added a compile-time requirement that key types implement `operator==`. Since this check uses a `requires` expression, I upgraded the project from **C++17** to **C++20**.

While refactoring the `HashMap` to reuse my `DynamicArray` as the bucket container, I discovered a hidden bug in `DynamicArray::append()`. The function was assigning values into memory that had been allocated but never constructed. This worked for primitive types such as `int`, but failed when storing objects like `LinkedList` because their assignment operators expect properly constructed objects.

To fix this, I modified both `append()` and the resizing logic to construct new objects using placement `new` instead of assigning into raw memory. Once this was corrected, I replaced the manually managed bucket array inside the `HashMap` with `DynamicArray`. As a result, the constructor, destructor, copy constructor, copy assignment operator, and `rehash()` all became significantly simpler because `DynamicArray` now manages the lifetime of the bucket storage.

During the refactoring, I introduced another bug by manually destroying every bucket inside `rehash()` before assigning the new bucket array. Later I realized that the `DynamicArray` assignment operator already destroys its existing elements, meaning every bucket destructor was being called twice. Removing the manual destructor calls fixed the problem and made ownership much clearer.

I also encountered a simple template syntax mistake while working with nested template types. I forgot a closing `>` in a declaration such as:

```cpp
DA<LinkedList<KV<Key, Value>>>
```

Although the mistake was small, the compiler generated many unrelated template errors. After fixing the missing bracket, all of the errors disappeared.

---

## Section 3 — Work Completed

**Work Completed**

- Added support for custom hash functors through a third template parameter.
- Created a `DefaultHash<Key>` functor.
- Tested the design with a custom `Employee` class.
- Added hashing support for `double`.
- Added a fallback hashing strategy for unsupported key types.
- Added a compile-time requirement for `operator==`.
- Upgraded the project from **C++17** to **C++20**.
- Refactored the `HashMap` to use `DynamicArray` as bucket storage.
- Fixed the object lifetime bug in `DynamicArray::append()`.
- Updated the resizing logic to use placement `new`.
- Simplified the `HashMap` constructor, destructor, copy constructor, assignment operator, and `rehash()`.
- Fixed the double-destruction bug during rehashing.
- Fixed template syntax errors caused by missing template parameters and angle brackets.

---

## Section 4 — Learning Reflection

Today I realized how much easier code becomes to maintain when responsibilities are separated properly. Moving the hashing logic into a separate functor made the `HashMap` much cleaner, and it also made it easy to support custom key types without changing the container itself. It showed me how generic programming is about designing components that can work together instead of putting everything into one class.

I also learned an important lesson about object lifetime. The bug in `DynamicArray` had been there for a while, but it only became visible when I started storing more complex objects like `LinkedList`. It reminded me that just because code works for primitive types doesn't mean it is correct. Testing with user-defined types helped expose problems that were hidden before.

Another thing I learned was that reusing existing components can greatly simplify a project. By replacing the manually managed bucket array with `DynamicArray`, I removed a lot of repetitive memory management code and made the `HashMap` easier to understand. It also reinforced the idea that once a data structure is implemented correctly, it should be reused instead of rewriting the same logic again.

Finally, today reminded me that many template errors come from very small mistakes. Missing a template parameter or a single closing `>` produced pages of compiler errors that looked much more complicated than the actual problem. As I continue working with templates, I'm learning to first check for simple syntax mistakes before assuming the bug is somewhere deeper in the code.