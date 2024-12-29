//
// Created by Bocabbage on 2024/12/29.
//
#include "prototype.hpp"

#include <iomanip>
#include <sstream>

using namespace luac;

ConstantTag luac::ConstantTagFromByte(uint8_t byte) {
    switch (byte) {
        case static_cast<uint8_t>(ConstantTag::NIL):
        case static_cast<uint8_t>(ConstantTag::BOOLEAN):
        case static_cast<uint8_t>(ConstantTag::NUMBER):
        case static_cast<uint8_t>(ConstantTag::INTEGER):
        case static_cast<uint8_t>(ConstantTag::SHORT_STR):
        case static_cast<uint8_t>(ConstantTag::LONG_STR):
            return static_cast<ConstantTag>(byte); break;
        default: {
            std::ostringstream oss;
            oss << "Invalid Constant Tag: 0x" << std::hex << std::uppercase << std::setfill('0') << byte << std::setw(2)
            << byte;
            throw std::invalid_argument(oss.str());
        }
    }
}