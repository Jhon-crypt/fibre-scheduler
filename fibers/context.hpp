#ifndef FIBERS_CONTEXT_HPP
#define FIBERS_CONTEXT_HPP

#include <csetjmp>
#include <cstdint>

#ifdef _WIN32
#define NORETURN __declspec(noreturn)
#else
#define NORETURN [[noreturn]]
#endif

struct Context {
    void* rip;  // Instruction pointer
    void* rsp;  // Stack pointer
    void* rbp;  // Base pointer
    void* rbx;  // Callee-saved registers
    void* r12;
    void* r13;
    void* r14;
    void* r15;
    std::jmp_buf env;
};

// Save current context to ctx and return 0
inline int get_context(Context* ctx) {
    return setjmp(ctx->env);
}

// Load context from ctx
NORETURN inline void set_context(Context* ctx) {
    longjmp(ctx->env, 1);
}

// Save current context to old_ctx, then load context from new_ctx
inline void swap_context(Context* old_ctx, Context* new_ctx) {
    if (setjmp(old_ctx->env) == 0) {
        longjmp(new_ctx->env, 1);
    }
}

#endif // FIBERS_CONTEXT_HPP 