# Daily Journal

**Date: 10/07/2026**

I started by building the HashMap's constructor and destructor, which followed the same manual memory management pattern I'd already used in DynamicArray and LinkedList. Instead of relying on `new[]`, I allocated raw memory with `std::malloc`, constructed objects inside that memory using placement `new`, and made sure every object was explicitly destroyed before freeing the memory back to the system. The difference this time was that I wasn't allocating an array of values anymore—I was allocating an array of `LinkedList` objects, so it also made me think about ownership more carefully. The HashMap owns the bucket array, each bucket owns a `LinkedList`, and each `LinkedList` owns its own nodes.

The biggest new concept today was compile-time type logic. Since the HashMap is templated, the hash function needs to work for different key types. My first instinct was to use a normal runtime `if`, but I realized that templates don't work that way. Every branch of a normal `if` still has to compile, even if that branch is never executed. That immediately breaks because string hashing contains a character loop that simply doesn't compile for an `int` key. Using `if constexpr` solved the problem because the compiler evaluates the condition during compilation and completely discards the branch that doesn't apply to the current key type. Along with that, I learned how type traits like `std::is_integral` and `std::is_same` let the compiler reason about types at compile time, and I used `static_assert` so unsupported key types fail with a clear error message instead of producing pages of confusing template errors.

I also spent some time thinking about integer types and array indexing. One thing I learned was that signed integer overflow is undefined behavior in C++, and although many systems appear to wrap into negative values, the language doesn't actually guarantee that behavior. Since hash values are eventually used as array indices, using `size_t` makes much more sense because it represents unsigned sizes and indices. I also started using `static_cast<size_t>` instead of functional-style casts because it makes the conversion explicit and much easier to read.

The hashing algorithm itself turned out to be more interesting than I expected. A simple hash that only adds up character codes produces a lot of collisions because character order doesn't matter. For example, `"cat"` and `"act"` would produce exactly the same result. To avoid that I implemented a polynomial rolling hash using the formula `hash = hash * 31 + character`, where multiplying by 31 makes each character contribute according to its position in the string. I also learned why each character should first be converted to `unsigned char` before participating in the calculation. On many systems `char` is signed, so characters with larger byte values could otherwise become negative and affect the hash computation.

Once the hash function was working, I moved on to the core operations of the HashMap. I implemented insertion with update-in-place behavior, separate chaining for collision handling, automatic rehashing once the load factor exceeds `0.9`, and the remaining public operations like `get()`, `contains()`, and `remove()`. Implementing these forced me to go back and improve the LinkedList itself. I replaced the old boolean-only search with a `find()` function that returns a pointer to the stored element, added `deleteValue()` so elements can be removed directly by value, implemented a simple iterator so the list works with range-based `for` loops, and finally completed the LinkedList copy constructor that I had declared earlier but never actually implemented. After that I was able to implement the HashMap's Rule of Three by building on LinkedList's deep-copy behavior.

One bug followed me throughout the day because I repeated the same mistake more than once. While defining template member functions outside the class, I forgot to prefix them with `LinkedList<T>::` or `HashMap<K,V>::`. Without the class scope qualifier, the compiler treats the definition as a completely unrelated free function, which then has no access to the class members and produces a confusing chain of "not declared in this scope" errors. It's a small mistake, but one that's easy to overlook, so it's something I want to check automatically before assuming a deeper bug exists.

# Day 4 Journal

## Section 1 — Implementation Progress

### Task 1: HashMap Memory Management

I started implementing the `HashMap` by writing its constructor and destructor. Since the project uses manual memory management, I followed the same approach used in `DynamicArray` and `LinkedList`, allocating raw memory with `std::malloc`, constructing objects using placement `new`, and explicitly destroying them before calling `std::free`.

### Task 2: Generic Hash Function

The next major task was implementing a generic hash function that could support multiple key types while remaining type-safe at compile time.

### Task 3: Core HashMap Operations

After completing the hash function, I implemented the remaining `HashMap` operations, including insertion, lookup, deletion, collision handling, and automatic rehashing. This also required improving the `LinkedList` implementation to better support the HashMap.

### Task 4: Template Compilation Bug

While defining template member functions outside the class, I repeatedly encountered compilation errors caused by forgetting to qualify function definitions with the appropriate class scope.

---

## Section 2 — Investigation and Understanding

While implementing the constructor and destructor, I realized that the ownership model of the `HashMap` is more complex than my previous data structures. Instead of storing elements directly, the `HashMap` owns an array of `LinkedList` objects, and each `LinkedList` owns its own nodes. This helped me better understand ownership relationships and how destructors recursively clean up dynamically allocated resources.

The biggest concept I learned today was **compile-time type selection**. My initial idea was to use a normal `if` statement inside the hash function to handle different key types. However, I discovered that every branch of a normal `if` must still compile, even if it is never executed. Since the string hashing logic cannot be compiled for integer keys, this approach failed.

I solved this problem by using `if constexpr`, which allows the compiler to discard branches that are not valid for the current template type during compilation. While implementing this, I also learned how type traits such as `std::is_integral` and `std::is_same` enable compile-time type checking. I additionally used `static_assert` so that unsupported key types generate clear compilation errors instead of long template diagnostics.

While implementing the hashing algorithm, I also learned why `size_t` is preferred for hash values and array indexing. Since signed integer overflow is undefined behavior in C++, using an unsigned type designed for indexing is both safer and more appropriate. I also replaced functional-style casts with `static_cast<size_t>` because it makes conversions explicit and easier to understand.

For string hashing, I initially considered simply adding the character values together. After thinking about it, I realized this would generate many collisions because character order would not affect the result. To solve this, I implemented a **polynomial rolling hash** using the formula:

```cpp
hash = hash * 31 + character;
```

This ensures that each character contributes according to its position within the string. I also learned that each character should first be converted to `unsigned char` because `char` may be signed on some systems, which could otherwise produce inconsistent hash values.

After completing the hash function, I implemented insertion with update-in-place behavior, separate chaining for collision resolution, automatic rehashing once the load factor exceeds **0.9**, and the remaining public operations such as `get()`, `contains()`, and `remove()`.

While implementing these operations, I improved the `LinkedList` by replacing the previous boolean-only search with a `find()` function that returns a pointer to the stored element, adding `deleteValue()`, implementing an iterator to support range-based `for` loops, and completing the copy constructor. These improvements allowed me to implement the `HashMap` Rule of Three using the `LinkedList`'s deep-copy behavior.

One recurring bug throughout the day was forgetting to qualify template member function definitions with their class scope, for example:

```cpp
LinkedList<T>::functionName(...)
```

or

```cpp
HashMap<K, V>::functionName(...)
```

Without the class qualifier, the compiler interprets the function as an unrelated free function, leading to a series of confusing compilation errors because it no longer has access to the class members.

---

## Section 3 — Work Completed

**Work Completed**

- Implemented the `HashMap` constructor and destructor.
- Implemented generic compile-time hashing using `if constexpr`.
- Used type traits such as `std::is_integral` and `std::is_same`.
- Added `static_assert` for unsupported key types.
- Implemented a polynomial rolling hash for strings.
- Used `size_t` and `static_cast` appropriately for hashing.
- Implemented insertion with update-in-place behavior.
- Implemented separate chaining for collision handling.
- Added automatic rehashing when the load factor exceeds **0.9**.
- Implemented `get()`, `contains()`, and `remove()`.
- Added `find()` and `deleteValue()` to `LinkedList`.
- Implemented a `LinkedList` iterator.
- Completed the `LinkedList` copy constructor.
- Implemented the `HashMap` Rule of Three.
- Fixed template member function definition errors caused by missing class scope qualifiers.

---

## Section 4 — Learning Reflection

## Section 4 — Learning Reflection

Today I learned a lot about how templates work internally. Before today, I thought a normal `if` statement would be enough to choose different hashing logic for different key types. After implementing the hash function, I understood why `if constexpr` exists and how the compiler removes branches that are not valid for the current template type. This was my first time using compile-time type checking in a practical project.

I also got a better understanding of generic programming. Using type traits like `std::is_integral`, `std::is_same`, and `static_assert` showed me that templates are much more powerful than I initially thought. Instead of waiting for runtime errors, I can make the compiler check whether a type is supported before the program is even built.

Another thing I learned was that implementing a HashMap is not just about writing a hash function. Small design decisions like handling collisions, deciding when to rehash, and making sure objects own and clean up their memory correctly all affect the overall implementation. Improving the `LinkedList` to support the `HashMap` also showed me how one data structure often needs to evolve to support another.

Finally, I realized that many of the compiler errors I was getting were caused by very small mistakes, such as forgetting the class scope while defining template member functions. Although the error messages looked complicated, the actual problem was simple once I understood how template definitions are matched with their declarations. This reminded me to always check for small mistakes before assuming there's a deeper bug.