#include <iostream>
#include <utility>

using namespace std;

template <typename T>
void print_arg(T&& arg) {
    cout << forward<T>(arg);
}

template <typename T, typename... Args>
void print_arg(T&& arg, Args&&... args) {
    print_arg(forward<T>(arg));
    cout << " ";
    print_arg(forward<Args>(args)...);
}

template <typename... Args>
void print(Args&&... args) {
    print_arg(forward<Args>(args)...);
    cout << endl;
}