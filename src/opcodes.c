#include "./headers/opcodes.h"
#include "./headers/register.h"
#include "./headers/memory.h"

// INC and DEC 8 bit instr - must check half carry before incrementing
void instr_inc_8b(Register *reg, uint8_t *value)
{
    if ((*value & 0x0F) == 0x0F)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_h_flag(reg);
    }

    (*value)++;

    unset_n_flag(reg);

    check_if_op_zero_and_set_z(reg, *value);
}

void instr_dec_8b(Register *reg, uint8_t *value)
{
    if ((*value & 0x0F) == 0x00)
    {
        set_HFlag(reg);
    }
    else
    {
        unset_h_flag(reg);
    }

    (*value)--;
    set_n_flag(reg);
    check_if_op_zero_and_set_z(reg, *value);
}

// LD 8 bit instr
void instr_ld_8b_in_8b(Register *reg, uint8_t *fromValue, uint8_t *toValue)
{
    *fromValue = *toValue;
}

void instr_ld_nxt_8b_addr_reg(Register *reg, Memory *mem, uint8_t *value)
{
    uint8_t addrValue = memory_read(mem, reg->PC + 1);
    *value = addrValue;
    reg->PC += 2;
}

void instr_ld_addr_8b_reg(Register *reg, Memory *mem, uint16_t memAddr, uint8_t *value)
{
    uint8_t addrValue = memory_read(mem, memAddr);
    *value = addrValue;
}

// LD 16 bit instr
void instr_ld_nxt_16b_addr_reg(Register *reg, Memory *mem, uint16_t *regValue)
{
    uint16_t value = memory_read_16t(mem, reg->PC + 1);
    *regValue = value;
    reg->PC += 3;
}

// ADD/SUBTR 16 bit instr
void instr_add_16b(Register *reg, uint16_t *regToAdd, uint16_t valueToAdd)
{
    uint32_t sumValue = (uint32_t)(*regToAdd) + (uint32_t)valueToAdd;
    unset_n_flag(reg);
    check_if_has_carry_and_set_h_16b(reg, (((*regToAdd) & 0x0FFF) + (valueToAdd & 0x0FFF)));
    set_c_flag_if_add_op_gt_FFFF(reg, sumValue);
    *regToAdd = (uint16_t)sumValue;
}

// ADD/SUBTR 8 bit instr
void instr_add_8b(Register *reg, uint8_t *regToAdd, uint8_t valueToAdd)
{
    uint16_t sumValue = (uint16_t)(*regToAdd) + (uint16_t)valueToAdd;
    unset_n_flag(reg);
    set_c_flag_if_add_op_gt_FF(reg, sumValue);
    check_if_op_zero_and_set_z(reg, (uint8_t)sumValue);
    check_if_has_carry_and_set_8b(reg, *regToAdd, valueToAdd);
    *regToAdd = (uint8_t)sumValue;
}

void instr_add_8b_with_carry(Register *reg, uint8_t *regToAdd, uint8_t valueToAdd)
{
    uint8_t carry = get_c_flag(reg);
    uint16_t sumValue = (uint16_t)(*regToAdd) + (uint16_t)valueToAdd + (uint16_t)carry;
    unset_n_flag(reg);
    set_c_flag_if_add_op_gt_FF(reg, sumValue);
    check_if_op_zero_and_set_z(reg, (uint8_t)sumValue);
    check_if_has_carry_and_set_8b_with_carry(reg, *regToAdd, valueToAdd, carry);
    *regToAdd = (uint8_t)sumValue;
}

void instr_sub_8b(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub)
{
    uint8_t originalValue = *regToSubFrom;
    uint8_t subrResult = *regToSubFrom - valueToSub;

    set_n_flag(reg);
    check_if_has_borrow_and_set_8b(reg, originalValue, valueToSub);
    check_if_has_borrow_and_set_c_8b(reg, originalValue, valueToSub);
    // set_c_flag_if_add_lt_0(reg, subrResult);

    *regToSubFrom = subrResult;

    check_if_op_zero_and_set_z(reg, *regToSubFrom);
}

void instr_sub_8b_with_carry(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub)
{
    uint8_t carry = get_c_flag(reg);
    uint8_t originalValue = *regToSubFrom;
    uint8_t subrResult = *regToSubFrom - valueToSub - carry;

    set_n_flag(reg);
    check_if_has_borrow_and_set_8b_with_carry(reg, originalValue, valueToSub, carry);
    check_if_has_borrow_and_set_c_8b_with_carry(reg, originalValue, valueToSub, carry);
    // set_c_flag_if_add_lt_0(reg, subrResult);

    *regToSubFrom = subrResult;

    check_if_op_zero_and_set_z(reg, *regToSubFrom);
}

// Normal bitwise
void instr_and(Register *reg, uint8_t *from, uint8_t to)
{
    *from = (*from) & to;
    check_if_op_zero_and_set_z(reg, *from);
    set_HFlag(reg);
    unset_n_flag(reg);
    unset_c_flag(reg);
}
void instr_xor(Register *reg, uint8_t *from, uint8_t to)
{
    *from = (*from) ^ to;
    check_if_op_zero_and_set_z(reg, *from);
    unset_h_flag(reg);
    unset_n_flag(reg);
    unset_c_flag(reg);
}
void instr_or(Register *reg, uint8_t *from, uint8_t to)
{
    *from = (*from) | to;
    check_if_op_zero_and_set_z(reg, *from);
    unset_h_flag(reg);
    unset_n_flag(reg);
    unset_c_flag(reg);
}

// CP
void instr_cp_8b(Register *reg, uint8_t *regToSubFrom, uint8_t valueToSub)
{
    uint8_t originalValue = *regToSubFrom;
    uint8_t subrResult = *regToSubFrom - valueToSub;

    set_n_flag(reg);
    check_if_has_borrow_and_set_8b(reg, originalValue, valueToSub);
    // set_c_flag_if_add_lt_0(reg, subrResult);

    check_if_op_zero_and_set_z(reg, subrResult);
    if (originalValue < valueToSub)
    {
        set_c_flag(reg);
    }
    else
    {
        unset_c_flag(reg);
    }
}

// Stack Instructions
void instr_callAddr16(Register *reg, Memory *mem)
{
    uint16_t stackPushAddr = reg->PC + 3;
    stack_push16(reg, mem, stackPushAddr);
    uint16_t callAddr = memory_read_16t(mem, reg->PC + 1);
    reg->PC = callAddr;
}
void instr_jp_nxt16(Register *reg, Memory *mem)
{
    uint16_t jmpAddr = memory_read_16t(mem, reg->PC + 1);
    reg->PC = jmpAddr;
}

void instr_ret(Register *reg, Memory *mem)
{
    uint16_t stackAddr = stack_pop16(reg, mem);
    reg->PC = stackAddr;
}

void instr_rst(Register *reg, Memory *mem, uint16_t rstAddr)
{
    uint16_t stackPushAddr = reg->PC + 1;
    stack_push16(reg, mem, stackPushAddr);
    reg->PC = rstAddr;
}