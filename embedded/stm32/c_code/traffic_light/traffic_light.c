
typedef unsigned int uint32_t;
#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830)
#define GPIOA_MODER (*(volatile uint32_t *)0x40020000)
#define GPIOA_BSRR (*(volatile uint32_t *)0x40020018)
// почему мне ODR? Потому что ODR при переключении пинов будет удалять ВСЮ переферию, а BSRR - только юзанные

// Маски для управления пинами
#define RED_ON (1 << 1) // Пин A1 на плате
#define YELLOW_ON (1 << 2) // Пин A2 на плате
#define GREEN_ON (1 << 3) // Пин A3 на плате
#define RED_OFF (1 << (1 + 16)) // Пин A1 на плате
#define YELLOW_OFF (1 << (2 + 16)) // Пин A2 на плате
#define GREEN_OFF (1 << (3 + 16)) // Пин A3 на плате
// Делаем самый простецкую задержку
void delay(uint32_t ms) {
    while (ms--) {
        for (uint32_t i = 0; i < 3000; i++) {
            __asm__("nop");
        }
    }
}
int main(void) {
    RCC_AHB1ENR |= (1 << 0); // Включаем тактирование порта A
    GPIOA_MODER &= ~((3 << 2) | (3 << 4) | (3 << 6)); // Очищаем
    GPIOA_MODER |= (1 << 2) | (1 << 4) | (1 << 6); // Устанавливаем режим пинов PA1, PA2, PA3 в выход
    while (1) {
        GPIOA_BSRR = RED_ON;
        delay(1000);
        GPIOA_BSRR = RED_OFF;
        GPIOA_BSRR = YELLOW_ON;
        delay(1000);
        GPIOA_BSRR = YELLOW_OFF;
        GPIOA_BSRR = GREEN_ON;
        delay(1000);
        GPIOA_BSRR = GREEN_OFF;
    }
}

void Reset_Handler(void) { // дефолтный обработчик сброса
    main();
    while (1);
}
__attribute__((section(".isr_vector"), used)) // дефолтная таблица векторов
void (*const vector_table[])(void) = {
    (void (*)(void))0x20020000,
    Reset_Handler,
};
