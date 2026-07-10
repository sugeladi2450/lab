#include "simulator.h"

Simulator::Simulator() : pc(0) {
}

void Simulator::run(const int max_steps) {
    int step = 0;
    Status status = Status::AOK;
    for (step = 0; step < max_steps && status == Status::AOK; step++) {
        status = next_instruction();
    }
    report_stopped(step, status);
}

static uint8_t get_hi4(const uint8_t pack) { return (pack >> 4) & 0xF; }
static uint8_t get_lo4(const uint8_t pack) { return pack & 0xF; }

Status Simulator::next_instruction() {
    uint64_t next_pc = pc;

    // get code and function (1 byte)
    const std::optional<uint8_t> codefun = memory.get_byte(next_pc);
    if (!codefun) {
        report_bad_inst_addr();
        return Status::ADR;
    }
    const auto icode = static_cast<InstructionCode>(get_hi4(codefun.value()));
    uint8_t ifun = get_lo4(codefun.value());
    next_pc++;

    // TODO: get registers if needed (1 byte)
    std::optional<uint8_t> reg_byte;
    uint8_t regA = 0, regB = 0;
    if (need_regids(icode)) {
        reg_byte = memory.get_byte(next_pc);
        if (!reg_byte) {
            report_bad_inst_addr();
            return Status::ADR;
        }
        regA = get_hi4(reg_byte.value());
        regB = get_lo4(reg_byte.value());
        switch (icode) {
            case InstructionCode::IRMOVQ:

                    if (error_invalid_reg(regB)) {
                        return Status::INS;
                    }
            break;
            case InstructionCode::PUSHQ:
            case InstructionCode::POPQ:
                if (regA != 0xf && error_invalid_reg(regA)) {
                    return Status::INS;
                }
            break;
            default:
                if (error_invalid_reg(regA) || error_invalid_reg(regB)) {
                    return Status::INS;
                }
            break;
        }
        next_pc++;
    }

    // TODO: get immediate if needed (8 bytes)
    std::optional<uint64_t> imm;
    if (need_imm(icode)) {
        imm = memory.get_long(next_pc);
        if (!imm) {
            report_bad_inst_addr();
            return Status::ADR;
        }
        next_pc += 8;
    }

    // execute the instruction
    switch (icode) {
        case InstructionCode::HALT: // 0:0
        {
            return Status::HLT;
        }
        case InstructionCode::NOP: // 1:0
        {
            pc = next_pc;
            return Status::AOK;
        }
        case InstructionCode::RRMOVQ: // 2:x regA:regB
        {
            auto cond = static_cast<Condition>(ifun);
            if (ifun == 0 || cc.satisfy(cond)) {
                registers[regB] = registers[regA];
            }
            pc = next_pc;
            return Status::AOK;
        }
        case InstructionCode::IRMOVQ: // 3:0 F:regB imm
        {
            if (error_invalid_reg(regB)) {
                return Status::INS;
            }
            registers[regB] = *imm;
            pc = next_pc;
            return Status::AOK;
        }
        case InstructionCode::RMMOVQ:
        {
            uint64_t addr = registers[regB] + *imm;
            if (!memory.set_long(addr, registers[regA])) {
                report_bad_data_addr(addr);
                return Status::ADR;
            }
            pc = next_pc;
            return Status::AOK;
        }
        case InstructionCode::MRMOVQ: // 5:0 regA:regB imm
        {
            uint64_t addr = registers[regB] + *imm;
            auto val = memory.get_long(addr);
            if (!val) {
                report_bad_data_addr(addr);
                return Status::ADR;
            }
            registers[regA] = *val;
            pc = next_pc;
            return Status::AOK;
        }
        case InstructionCode::ALU: // 6:x regA:regB
        {
            auto op = static_cast<AluOp>(ifun);
            uint64_t a = registers[regA];
            uint64_t b = registers[regB];
            uint64_t result;
            switch (op) {
                case AluOp::ADD:
                    result = a + b;
                    break;
                case AluOp::SUB:
                    result = b - a;
                    break;
                case AluOp::AND:
                    result = a & b;
                    break;
                case AluOp::XOR:
                    result = a ^ b;
                    break;
                default:
                    report_bad_inst(codefun.value());
                    return Status::INS;
            }
            registers[regB] = result;
            cc = ConditionCodes::compute(op, a, b, result);
            pc = next_pc;
            return Status::AOK;
        }
        case InstructionCode::JMP: // 7:x imm
        {
            auto cond = static_cast<Condition>(ifun);
            if (cc.satisfy(cond)) {
                pc = *imm;
            } else {
                pc = next_pc;
            }
            return Status::AOK;
        }
        case InstructionCode::CALL: // 8:0 imm
        {
            uint64_t sp = registers[RegId::RSP];
            if (sp < 8) {
                sp = 0xfffffffffffffff8;
                report_bad_stack_addr(sp);
                return Status::ADR;
            }
            sp -= 8;
            if (!memory.set_long(sp, next_pc)) {
                report_bad_stack_addr(sp);
                return Status::ADR;
            }
            registers[RegId::RSP] = sp;
            pc = *imm;
            return Status::AOK;
        }
        case InstructionCode::RET: // 9:0
        {
            uint64_t sp = registers[RegId::RSP];
            auto ret_addr = memory.get_long(sp);
            if (!ret_addr) {
                report_bad_stack_addr(sp);
                return Status::ADR;
            }
            sp += 8;
            registers[RegId::RSP] = sp;
            pc = *ret_addr;
            return Status::AOK;
        }
        case InstructionCode::PUSHQ:
        {
            if (regA != 0xf && error_invalid_reg(regA)) {
                return Status::INS;
            }
            uint64_t sp = registers[RegId::RSP];
            if (sp < 8) {
                sp = 0xfffffffffffffff8;
                report_bad_stack_addr(sp);
                return Status::ADR;
            }
            sp -= 8;
            if (!memory.set_long(sp, registers[regA])) {
                report_bad_stack_addr(sp);
                return Status::ADR;
            }
            registers[RegId::RSP] = sp;
            pc = next_pc;
            return Status::AOK;
        }
        case InstructionCode::POPQ:
        {
            if (regA != 0xf && error_invalid_reg(regA)) {
                return Status::INS;
            }
            uint64_t sp = registers[RegId::RSP];
            auto val = memory.get_long(sp);
            if (!val) {
                report_bad_stack_addr(sp);
                return Status::ADR;
            }

            if (static_cast<RegId>(regA) == RegId::RSP) {
                registers[RegId::RSP] = *val;
            } else {
                registers[regA] = *val;
                registers[RegId::RSP] = sp + 8;
            }

            pc = next_pc;
            return Status::AOK;
        }
        default:
            report_bad_inst(codefun.value());
            return Status::INS;
    }
}