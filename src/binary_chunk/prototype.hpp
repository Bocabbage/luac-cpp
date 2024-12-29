//
// Created by Bocabbage on 2024/12/29.
//
#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include "types.hpp"

namespace luac {
    // constant type tag
    enum class ConstantTag : uint8_t {
        NIL = 0x00,
        BOOLEAN = 0x01,
        NUMBER = 0x03,
        INTEGER = 0x13,
        SHORT_STR = 0x04,
        LONG_STR = 0x14,
    };

    // \brief convert read byte to type-tag
    // \throws std::invalid_argument if the byte-value is illegal
    ConstantTag ConstantTagFromByte(uint8_t byte);

    struct Constant
    {
        ConstantTag tag;
        ANY constant;
    };

    using Constant_ARRAY = std::vector<Constant>;

    struct UpValue
    {
        uint8_t in_stack;
        uint8_t idx;
    };

    using UpValue_ARRAY = std::vector<UpValue>;

    struct LocVar
    {
        STRING var_name;
        uint32_t start_pc;
        uint32_t end_pc;

        LocVar() = default;

        LocVar(STRING var_name_, uint32_t start_pc_, uint32_t end_pc_):
            var_name(var_name_), start_pc(start_pc_), end_pc(end_pc_)
        {  }

        LocVar(LocVar&& loc_var_r) noexcept:
            var_name(std::move(loc_var_r.var_name)), start_pc(loc_var_r.start_pc), end_pc(loc_var_r.end_pc)
        {  }

        LocVar&
        operator=(LocVar&& loc_var_r) noexcept
        {
            if (&loc_var_r == this)
                return *this;

            this->var_name = std::move(loc_var_r.var_name);
            this->start_pc = loc_var_r.start_pc;
            this->end_pc = loc_var_r.end_pc;
            return *this;
        }
    };
    using LocVar_ARRAY = std::vector<LocVar>;

    // Lua function struct
    // todo constructor refactor
    struct Prototype
    {
        STRING source;				// source file name

        uint32_t line_defined{};		// Func start line number
        uint32_t last_line_defined{};	// Func end line number

        uint8_t num_params{};
        uint8_t is_vararg{};
        uint32_t max_stack_size{};

        UWORD32_ARRAY code;						// Instruction table
        Constant_ARRAY constants;				// Constant table
        UpValue_ARRAY upvalues;
        std::vector<Prototype> protos;			// Sub-func table

        WORD32_ARRAY line_info;					// Line number table
        LocVar_ARRAY loc_vars;					// Local variable table
        STRING_ARRAY upvalue_names;

        Prototype() = default;

        Prototype(Prototype&& ptt_r) noexcept:
            source(std::move(ptt_r.source)),
            line_defined(ptt_r.line_defined),
            last_line_defined(ptt_r.last_line_defined),
            num_params(ptt_r.num_params),
            is_vararg(ptt_r.is_vararg),
            max_stack_size(ptt_r.max_stack_size),
            code(std::move(ptt_r.code)),
            upvalues(std::move(ptt_r.upvalues)),
            protos(std::move(ptt_r.protos)),
            line_info(std::move(ptt_r.line_info)),
            loc_vars(std::move(ptt_r.loc_vars)),
            upvalue_names(std::move(ptt_r.upvalue_names))
        { }

        Prototype&
        operator=(Prototype&& ptt_r) noexcept
        {
            if (&ptt_r == this)
                return *this;

            source = std::move(ptt_r.source);
            line_defined = ptt_r.line_defined;
            last_line_defined = ptt_r.last_line_defined;
            num_params = ptt_r.num_params;
            is_vararg = ptt_r.is_vararg;
            max_stack_size = ptt_r.max_stack_size;
            code = std::move(ptt_r.code);
            upvalues = std::move(ptt_r.upvalues);
            protos = std::move(ptt_r.protos);
            line_info = std::move(ptt_r.line_info);
            loc_vars = std::move(ptt_r.loc_vars);
            upvalue_names = std::move(ptt_r.upvalue_names);
            return *this;
        }
    };
    using Prototype_ARRAY = std::vector<Prototype>;
}

#endif //PROTOTYPE_H
