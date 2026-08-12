/* Скрипт для линкера STM32F411CEU6 */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}
SECTIONS
{
    .isr_vector : {
        KEEP(*(.isr_vector)) /* укахываем линкеру что бы он не удалил нафиг эту секцию */
    } > FLASH
    .text : {
        *(.text) /* сюда идут все остальные секции */
    } > FLASH
}

/* Мы не будем выделять RAM, bss, data по причине ненадобности в данном коде (ибо юзаем всего 3 регистра) */
