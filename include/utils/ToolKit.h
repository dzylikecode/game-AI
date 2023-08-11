#include <cassert>
#include <functional>
#include <unordered_map>

template <typename R, typename... Args>
std::function<R(Args...)> memo(R (*fn)(Args...)) {
  std::map<std::tuple<Args...>, R> table;
  return [fn, table](Args... args) mutable -> R {
    auto argt = std::make_tuple(args...);
    auto memoized = table.find(argt);
    if (memoized == table.end()) {
      auto result = fn(args...);
      table[argt] = result;
      return result;
    } else {
      return memoized->second;
    }
  };
}

template <typename T>
class Singleton {
 private:
  /** @brief Explicit private copy constructor. This is a forbidden operation.*/
  Singleton(const Singleton<T>&);

  /** @brief Private operator= . This is a forbidden operation. */
  Singleton& operator=(const Singleton<T>&);

 protected:
  static T* msSingleton;

 public:
#if defined(__has_attribute)
#if __has_attribute(no_sanitize)
  // The `static_cast` happens so early in the construction of the inheriting
  // classes that the `this` pointer is still detected as the super class
  // pointer. Therefore, disabling vptr checks.
  __attribute__((no_sanitize("vptr")))
#endif
#endif
  Singleton(void) {
    assert(!msSingleton && "There can be only one singleton");
    msSingleton = static_cast<T*>(this);
  }
  ~Singleton(void) {
    assert(msSingleton);
    msSingleton = 0;
  }
  /// Get the singleton instance
  static T& getSingleton(void) {
    assert(msSingleton);
    return (*msSingleton);
  }
  /// @copydoc getSingleton
  static T* getSingletonPtr(void) { return msSingleton; }
};

// class S {
//  public:
//   static S& getInstance() {
//     static S instance;
//     return instance;
//   }

//  private:
//   S() {}
//   S(S const&) = delete;
//   void operator=(S const&) = delete;
// };

#define createSingleton(S)             \
  class S {                            \
   public:                             \
    static S& getInstance() {          \
      static S instance;               \
      return instance;                 \
    }                                  \
                                       \
   private:                            \
    S() {}                             \
    S(S const&) = delete;              \
    void operator=(S const&) = delete; \
  };