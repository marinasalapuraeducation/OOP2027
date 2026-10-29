//What this error means
//
//This error is a direct illustration of the encapsulation principle in OOP.It means :
//
//Encapsulation is working : The class queue has a member named sloc that is declared in the private section(or has no explicit access modifier in a class, making it private by default).
//
//Access violation : Your code(which is outside the queue class) is trying to read, modify, or access sloc directly.
//
//Compiler rule : In C++, private members are strictly hidden from the outside world.The compiler blocks this access and throws error C2248.
//
//In short, the error says : "You are trying to access a private part of the queue class from the outside, which is forbidden."