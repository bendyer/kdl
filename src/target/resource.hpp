// Copyright (c) 2019-2020 Tom Hancocks
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#if !defined(KDL_RESOURCE_HPP)
#define KDL_RESOURCE_HPP

#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <any>
#include "parser/lexeme.hpp"
#include "target/types.hpp"
#include "target/template_reference.hpp"
#include "libGraphite/data/data.hpp"

namespace kdl
{

    class resource
    {
    private:
        std::string m_type_code;
        std::vector<std::tuple<lexeme, type>> m_template;
        std::map<int, std::any> m_values;

        auto write(const lexeme field, std::any value) -> void;
        auto index_of(const lexeme field) const -> int;

    public:
        resource(const std::string code, std::vector<std::tuple<lexeme, type>> tmpl);

        auto write_byte(const template_reference ref, const uint8_t value) -> void;
        auto write_short(const template_reference ref, const uint16_t value) -> void;
        auto write_long(const template_reference ref, const uint32_t value) -> void;
        auto write_quad(const template_reference ref, const uint64_t value) -> void;
        auto write_signed_byte(const template_reference ref, const int8_t value) -> void;
        auto write_signed_short(const template_reference ref, const int16_t value) -> void;
        auto write_signed_long(const template_reference ref, const int32_t value) -> void;
        auto write_signed_quad(const template_reference ref, const int64_t value) -> void;

        auto write_pstr(const template_reference ref, const std::string value) -> void;
        auto write_cstr(const template_reference ref, const std::string value, const std::size_t length = 0) -> void;

        auto write_data(const template_reference ref, const std::string value) -> void;
        auto write_rect(const template_reference ref, const int16_t t, const int16_t l, const int16_t b, const int16_t r) -> void;

        auto assemble() const -> std::shared_ptr<graphite::data::data>;
    };

};

#endif //KDL_RESOURCE_HPP
