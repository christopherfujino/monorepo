https://stackoverflow.com/questions/21854309/why-do-i-have-to-pass-libraries-in-the-end-of-linker-line

> When the linker hits a static library (libfoo.a), it looks through the object files in that library and if an object contains any symbol which the linker needs, it adds that object to the executable. If it does not contain any symbol the linker needs, it skips that object.
