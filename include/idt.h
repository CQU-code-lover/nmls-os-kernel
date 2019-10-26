#ifndef INCLUDE_IDT_H_
#define INCLUDE_IDT_H_
#include "types.h"


// 定义IRQ
#define  IRQ0     32    // 电脑系统计时器
#define  IRQ1     33    // 键盘
#define  IRQ2     34    // 与 IRQ9 相接，MPU-401 MD 使用
#define  IRQ3     35    // 串口设备
#define  IRQ4     36    // 串口设备
#define  IRQ5     37    // 建议声卡使用
#define  IRQ6     38    // 软驱传输控制使用
#define  IRQ7     39    // 打印机传输控制使用
#define  IRQ8     40    // 即时时钟
#define  IRQ9     41    // 与 IRQ2 相接，可设定给其他硬件
#define  IRQ10    42    // 建议网卡使用
#define  IRQ11    43    // 建议 AGP 显卡使用
#define  IRQ12    44    // 接 PS/2 鼠标，也可设定给其他硬件
#define  IRQ13    45    // 协处理器使用
#define  IRQ14    46    // IDE0 传输控制使用
#define  IRQ15    47    // IDE1 传输控制使用

// 声明 IRQ 函数
// IRQ:中断请求(Interrupt Request)
void irq0();        // 电脑系统计时器
void irq1();        // 键盘
void irq2();        // 与 IRQ9 相接，MPU-401 MD 使用
void irq3();        // 串口设备
void irq4();        // 串口设备
void irq5();        // 建议声卡使用
void irq6();        // 软驱传输控制使用
void irq7();        // 打印机传输控制使用
void irq8();        // 即时时钟
void irq9();        // 与 IRQ2 相接，可设定给其他硬件
void irq10();       // 建议网卡使用
void irq11();       // 建议 AGP 显卡使用
void irq12();       // 接 PS/2 鼠标，也可设定给其他硬件
void irq13();       // 协处理器使用
void irq14();       // IDE0 传输控制使用
void irq15();       // IDE1 传输控制使用

//******************************
//结构体声明区

// 中断描述符
typedef
struct idt_entry_t {
    uint16_t base_lo;        // 中断处理函数地址 15 ～ 0 位
    uint16_t sel;            // 目标代码段描述符选择子
    uint8_t  always0;        // 置 0 段
    uint8_t  flags;          // 一些标志，文档有解释
    uint16_t base_hi;        // 中断处理函数地址 31 ～ 16 位
}__attribute__((packed)) idt_entry_t;

//注意 IDTR寄存器存放的是IDTR结构体指针  
// IDTR
typedef
struct idt_ptr_t {
    uint16_t limit;     // 限长
    uint32_t base;      // 基址
} __attribute__((packed)) idt_ptr_t;


// 寄存器类型
typedef
struct pt_regs_t {
    uint32_t ds;        // 用于保存用户的数据段描述符
    uint32_t edi;       // 从 edi 到 eax 由 pusha 指令压入
    uint32_t esi; 
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t int_no;    // 中断号
    uint32_t err_code;      // 错误代码(有中断错误代码的中断会由CPU压入)
    uint32_t eip;       // 以下由处理器自动压入
    uint32_t cs;        
    uint32_t eflags;
    uint32_t useresp;
    uint32_t ss;
} pt_regs;



// 声明中断处理函数 0 ~ 19 属于 CPU 的异常中断
// ISR:中断服务程序(interrupt service routine)
extern void isr0();        // 0 #DE 除 0 异常 
extern void isr1();        // 1 #DB 调试异常 
extern void isr2();        // 2 NMI 
extern void isr3();        // 3 BP 断点异常 
extern void isr4();        // 4 #OF 溢出 
extern void isr5();        // 5 #BR 对数组的引用超出边界 
extern void isr6();        // 6 #UD 无效或未定义的操作码 
extern void isr7();        // 7 #NM 设备不可用(无数学协处理器) 
extern void isr8();        // 8 #DF 双重故障(有错误代码) 
extern void isr9();        // 9 协处理器跨段操作 
extern void isr10();       // 10 #TS 无效TSS(有错误代码) 
extern void isr11();       // 11 #NP 段不存在(有错误代码) 
extern void isr12();       // 12 #SS 栈错误(有错误代码) 
extern void isr13();       // 13 #GP 常规保护(有错误代码) 
extern void isr14();       // 14 #PF 页故障(有错误代码) 
extern void isr15();       // 15 CPU 保留 
extern void isr16();       // 16 #MF 浮点处理单元错误 
extern void isr17();       // 17 #AC 对齐检查 
extern void isr18();       // 18 #MC 机器检查 
extern void isr19();       // 19 #XM SIMD(单指令多数据)浮点异常
 
// 20 ~ 31 Intel 保留
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
// 32 ~ 255 用户自定义异常
extern void isr255();
//****************************


//******************************
//函数声明与extern声明区

// 初始化中断描述符表
void init_idt();

// 定义中断处理函数指针
typedef void (*interrupt_handler_t)(pt_regs *);

// 中断处理函数的指针数组
interrupt_handler_t interrupt_handlers[256];

// 注册一个中断处理函数
void register_interrupt_handler(uint8_t n, interrupt_handler_t h);

// 调用中断处理函数
void isr_handler(pt_regs *regs);
void irq_handler(pt_regs *regs);

//extern声明汇编函数
extern void idt_flush(uint32_t);



#endif  // INCLUDE_IDT_H_