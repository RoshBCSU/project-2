#include <stdio.h>

// Define the Instruction struct
typedef struct {
    int args[3];
    int* registers;
    int* memory;
    int pc;
    int halt;
} Instruction;

// Define the Halt struct, which inherits from Instruction
typedef struct {
    Instruction base;
} Halt;

// Define the Add struct, which inherits from Instruction
typedef struct {
    Instruction base;
} Add;

// Define the Nand struct, which inherits from Instruction
typedef struct {
    Instruction base;
} Nand;

// Define the Mult struct, which inherits from Instruction
typedef struct {
    Instruction base;
} Mult;

// Define the LW struct, which inherits from Instruction
typedef struct {
    Instruction base;
} LW;

// Define the SW struct, which inherits from Instruction
typedef struct {
    Instruction base;
} SW;

// Define the BEQ struct, which inherits from Instruction
typedef struct {
    Instruction base;
} BEQ;

// Define the NoOp struct, which inherits from Instruction
typedef struct {
    Instruction base;
} NoOp;




// Function to execute the Halt instruction
void executeHalt(Instruction *instruction) {
    Halt *halt = (Halt *)instruction;
    halt->base.halt = 1;
}

// Function to execute the NoOp instruction
void executeNoOp(Instruction *instruction) {
    // Do nothing
}

// Function to execute the Add instruction
void executeAdd(Instruction* instruction) {
    Add* add = (Add*)instruction;
    int reg_a = instruction->args[0];
    int reg_b = instruction->args[1];
    int reg_c = instruction->args[2];
    instruction->registers[reg_a] = instruction->registers[reg_b] + instruction->registers[reg_c];
}

// Function to execute the Nand instruction
void executeNand(Instruction* instruction) {
    Nand* nand = (Nand*)instruction;
    int reg_a = instruction->args[0];
    int reg_b = instruction->args[1];
    int reg_c = instruction->args[2];
    instruction->registers[reg_a] = ~(instruction->registers[reg_b] & instruction->registers[reg_c]);
}

// Function to execute the Mult instruction
void executeMult(Instruction* instruction) {
    Mult* mult = (Mult*)instruction;
    int reg_a = instruction->args[0];
    int reg_b = instruction->args[1];
    int reg_c = instruction->args[2];
    instruction->registers[reg_a] = instruction->registers[reg_b] * instruction->registers[reg_c];
}

// Function to execute the LW instruction
void executeLW(Instruction* instruction) {
    LW* lw = (LW*)instruction;
    int reg_a = instruction->args[0];
    int reg_b = instruction->args[1];
    int offset = instruction->args[2];
    instruction->registers[reg_a] = instruction->memory[instruction->registers[reg_b] + offset];
}

// Function to execute the SW instruction
void executeSW(Instruction* instruction) {
    SW* sw = (SW*)instruction;
    int reg_a = instruction->args[0];
    int reg_b = instruction->args[1];
    int offset = instruction->args[2];
    instruction->memory[instruction->registers[reg_b] + offset] = instruction->registers[reg_a];
}

// Function to execute the BEQ instruction
void executeBEQ(Instruction* instruction) {
    BEQ* beq = (BEQ*)instruction;
    int reg_a = instruction->args[0];
    int reg_b = instruction->args[1];
    int label = instruction->args[2];
    if (instruction->registers[reg_a] == instruction->registers[reg_b]) {
        instruction->pc += label;
    }
}



int main() {
    // Set up registers and memory
    int registers[4] = {0, 0, 0, 0};
    int memory[256] = {1};

    // Create an instance of BEQ instruction
    BEQ beqInstruction;
    beqInstruction.base.args[0] = 0;
    beqInstruction.base.args[1] = 1;
    beqInstruction.base.args[2] = 4;

    // Set up BEQ instruction
    beqInstruction.base.registers = registers;
    beqInstruction.base.memory = memory;
    beqInstruction.base.pc = 0;

    // Execute BEQ instruction
    executeBEQ((Instruction*)&beqInstruction);

    // Print result
    printf("PC after BEQ instruction: %d\n", beqInstruction.base.pc);

    // Create an instance of Halt instruction
    Halt haltInstruction;
    haltInstruction.base.halt = 0;

 // Create an instance of NoOp instruction
    NoOp noOpInstruction;
    
    // Execute the Halt instruction
    executeHalt((Instruction *)&haltInstruction);
    printf("Halt Instruction: %d\n", haltInstruction.base.halt);

    
    // Execute the NoOp instruction
    executeNoOp((Instruction *)&noOpInstruction);

    // Create an instance of LW instruction
    LW lwInstruction;
    lwInstruction.base.args[0] = 0;
    lwInstruction.base.args[1] = 1;
    lwInstruction.base.args[2] = 3;

    // Set up LW instruction
    lwInstruction.base.registers = registers;
    lwInstruction.base.memory = memory;
    lwInstruction.base.pc = 0;

    // Execute LW instruction
    executeLW((Instruction*)&lwInstruction);

    // Print result
    printf("Result of LW instruction: %d\n", registers[0]);

    // Create an instance of SW instruction
    SW swInstruction;
    swInstruction.base.args[0] = 0;
    swInstruction.base.args[1] = 1;
    swInstruction.base.args[2] = 3;

    // Set up SW instruction
    swInstruction.base.registers = registers;
    swInstruction.base.memory = memory;
    swInstruction.base.pc = 0;

    // Execute SW instruction
    executeSW((Instruction*)&swInstruction);

    // Print result
    printf("Result of SW instruction: %d\n", memory[3]);

    // Set up Add instruction
    Add addInstruction;
    addInstruction.base.registers = registers;
    addInstruction.base.memory = memory;
    addInstruction.base.pc = 0;

    // Execute Add instruction
    executeAdd((Instruction*)&addInstruction);

    // Print result
    printf("Result of Add instruction: %d\n", registers[0]);

    // Create an instance of Nand instruction
    Nand nandInstruction;
    nandInstruction.base.args[0] = 0;
    nandInstruction.base.args[1] = 1;
    nandInstruction.base.args[2] = 2;

    // Set up Nand instruction
    nandInstruction.base.registers = registers;
    nandInstruction.base.memory = memory;
    nandInstruction.base.pc = 0;

    // Execute Nand instruction
    executeNand((Instruction*)&nandInstruction);

    // Print result
    printf("Result of Nand instruction: %d\n", registers[0]);

    // Create an instance of Mult instruction
    Mult multInstruction;
    multInstruction.base.args[0] = 0;
    multInstruction.base.args[1] = 1;
    multInstruction.base.args[2] = 2;

    // Set up Mult instruction
    multInstruction.base.registers = registers;
    multInstruction.base.memory = memory;
    multInstruction.base.pc = 0;

    // Execute Mult instruction
    executeMult((Instruction*)&multInstruction);

    // Print result
    printf("Result of Mult instruction: %d\n", registers[0]);

    return 0;
}

