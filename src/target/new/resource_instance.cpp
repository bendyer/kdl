// Copyright (c) 2020 Tom Hancocks
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

#include <string>
#include "diagnostic/fatal.hpp"
#include "target/new/resource_instance.hpp"
#include "libGraphite/data/writer.hpp"


// MARK: - Constructors

kdl::build_target::resource_instance::resource_instance(const int64_t id, const std::string code,
                                                        const std::string name, type_template tmpl)
    : m_id(id), m_name(name), m_code(code), m_tmpl(tmpl)
{

}

// MARK: - Accessor

auto kdl::build_target::resource_instance::type_code() const -> std::string
{
    return m_code;
}

auto kdl::build_target::resource_instance::id() const -> int64_t
{
    return m_id;
}

auto kdl::build_target::resource_instance::name() const -> std::string
{
    return m_name;
}

// MARK: - Field Usage

auto kdl::build_target::resource_instance::field_use_count(const kdl::lexeme field) const -> int
{
    if (m_field_counts.find(field.text()) == m_field_counts.end()) {
        return 0;
    }
    return m_field_counts.at(field.text());
}

auto kdl::build_target::resource_instance::acquire_field(const kdl::lexeme field, const int initial_count) -> int
{
    if (m_field_counts.find(field.text()) == m_field_counts.end()) {
        m_field_counts[field.text()] = initial_count - 1;
    }

    auto n = m_field_counts[field.text()];
    m_field_counts[field.text()] = ++n;
    return n;
}

auto kdl::build_target::resource_instance::reset_acquistion_locks() -> void
{
    m_field_counts.clear();
}

// MARK: - Name Extensions

auto kdl::build_target::resource_instance::available_name_extensions(const type_field field) const -> std::map<std::string, lexeme>
{
    std::map<std::string, lexeme> vars;

    if (m_field_counts.find(field.name().text()) != m_field_counts.end()) {
        vars.emplace("FieldNumber", lexeme(std::to_string(m_field_counts.at(field.name().text())), lexeme::integer));
    }

    return vars;
}

// MARK: - Values

auto kdl::build_target::resource_instance::index_of(const std::string field) const -> int
{
    for (auto i = 0; i < m_tmpl.binary_field_count(); ++i) {
        if (m_tmpl.binary_field_at(i).label.is(field)) {
            return i;
        }
    }
    throw std::logic_error("Attempting to write value for binary field '" + field + "' that does not exist.");
}

auto kdl::build_target::resource_instance::write(const std::string field, std::any value) -> void
{
    m_values[index_of(field)] = value;
}

auto kdl::build_target::resource_instance::write_byte(const type_field field, const type_field_value field_value, const uint8_t value) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), value);
}

auto kdl::build_target::resource_instance::write_short(const type_field field, const type_field_value field_value, const uint16_t value) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), value);
}

auto kdl::build_target::resource_instance::write_long(const type_field field, const type_field_value field_value, const uint32_t value) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), value);
}

auto kdl::build_target::resource_instance::write_quad(const type_field field, const type_field_value field_value, const uint64_t value) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), value);
}

auto kdl::build_target::resource_instance::write_signed_byte(const type_field field, const type_field_value field_value, const int8_t value) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), value);
}

auto kdl::build_target::resource_instance::write_signed_short(const type_field field, const type_field_value field_value, const int16_t value) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), value);
}

auto kdl::build_target::resource_instance::write_signed_long(const type_field field, const type_field_value field_value, const int32_t value) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), value);
}

auto kdl::build_target::resource_instance::write_signed_quad(const type_field field, const type_field_value field_value, const int64_t value) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), value);
}

auto kdl::build_target::resource_instance::write_pstr(const type_field field, const type_field_value field_value, const std::string value, const std::size_t len) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), std::tuple(len, value));
}

auto kdl::build_target::resource_instance::write_wstr(const type_field field, const type_field_value field_value, const std::string value) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), value);
}

auto kdl::build_target::resource_instance::write_lstr(const type_field field, const type_field_value field_value, const std::string value) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), value);
}

auto kdl::build_target::resource_instance::write_cstr(const type_field field, const type_field_value field_value, const std::string value, const std::size_t len) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), std::tuple(len, value));
}

auto kdl::build_target::resource_instance::write_data(const type_field field, const type_field_value field_value, const std::vector<char> data) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), data);
}

auto kdl::build_target::resource_instance::write_data(const type_field field, const type_field_value field_value, const std::vector<uint8_t> data) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), data);
}

auto kdl::build_target::resource_instance::write_rect(const type_field field, const type_field_value field_value, const int16_t t, const int16_t l, const int16_t b, const int16_t r) -> void
{
    write(field_value.extended_name(available_name_extensions(field)).text(), std::tuple(t, l, b, r));
}

// MARK: - Assembly

auto kdl::build_target::resource_instance::assemble() const -> std::shared_ptr<graphite::data::data>
{
    auto data = std::make_shared<graphite::data::data>();
    graphite::data::writer writer(data);

    for (auto n = 0; n < m_tmpl.binary_field_count(); ++n) {
        auto field = m_tmpl.binary_field_at(n);
        auto type = field.type;
        auto field_name = field.label;
        auto index = index_of(field_name.text());

        if (m_values.find(index) == m_values.end()) {
            writer.write_byte(0, build_target::binary_type_base_size(type));
            continue;
        }

        auto wrapped_value = m_values.at(index);

        switch (type & ~0xFFF) {
            case build_target::HBYT: {
                writer.write_byte(std::any_cast<uint8_t>(wrapped_value));
                break;
            }
            case build_target::HWRD: {
                writer.write_short(std::any_cast<uint16_t>(wrapped_value));
                break;
            }
            case build_target::HLNG: {
                writer.write_long(std::any_cast<uint32_t>(wrapped_value));
                break;
            }
            case build_target::HQAD: {
                writer.write_quad(std::any_cast<uint64_t>(wrapped_value));
                break;
            }
            case build_target::DBYT: {
                writer.write_signed_byte(std::any_cast<int8_t>(wrapped_value));
                break;
            }
            case build_target::DWRD: {
                writer.write_signed_short(std::any_cast<int16_t>(wrapped_value));
                break;
            }
            case build_target::DLNG: {
                writer.write_signed_long(std::any_cast<int32_t>(wrapped_value));
                break;
            }
            case build_target::DQAD: {
                writer.write_signed_quad(std::any_cast<int64_t>(wrapped_value));
                break;
            }
            case build_target::RECT: {
                auto rect = std::any_cast<std::tuple<int16_t, int16_t, int16_t, int16_t>>(wrapped_value);
                writer.write_signed_short(std::get<0>(rect));
                writer.write_signed_short(std::get<1>(rect));
                writer.write_signed_short(std::get<2>(rect));
                writer.write_signed_short(std::get<3>(rect));
                break;
            }
            case build_target::HEXD: {
                if (wrapped_value.type() == typeid(std::vector<char>)) {
                    auto bytes = std::any_cast<std::vector<char>>(wrapped_value);
                    writer.write_bytes(bytes);
                }
                else if (wrapped_value.type() == typeid(std::vector<uint8_t>)) {
                    auto bytes = std::any_cast<std::vector<uint8_t>>(wrapped_value);
                    writer.write_bytes(bytes);
                }
                break;
            }
            case build_target::PSTR:{
                auto pstr = std::any_cast<std::tuple<std::size_t, std::string>>(wrapped_value);
                writer.write_pstr(std::get<1>(pstr));
                break;
            }
            case build_target::Cnnn:
            case build_target::CSTR: {
                auto cstr = std::any_cast<std::tuple<std::size_t, std::string>>(wrapped_value);
                writer.write_cstr(std::get<1>(cstr), std::get<0>(cstr));
                break;
            }
            default: {
                throw std::logic_error("Type not handled");
            }
        }
    }

    return data;
}

auto kdl::build_target::resource_instance::synthesize_variables() const -> std::map<std::string, lexeme>
{
    std::map<std::string, lexeme> vars;

    vars.emplace("id", lexeme(std::to_string(m_id), lexeme::res_id));
    vars.emplace("name", lexeme(m_name, lexeme::string));

    for (auto n = 0; n < m_tmpl.binary_field_count(); ++n) {
        auto field = m_tmpl.binary_field_at(n);
        auto type = field.type;
        auto field_name = field.label;
        auto index = index_of(field_name.text());
        if (m_values.find(index) == m_values.end()) {
            continue;
        }
        auto wrapped_value = m_values.at(index);

        switch (field.type & ~0xFFF) {
            case build_target::HBYT: {
                vars.emplace(field_name.text(), lexeme(std::to_string(std::any_cast<uint8_t>(wrapped_value)), lexeme::integer));
                break;
            }
            case build_target::HWRD: {
                vars.emplace(field_name.text(), lexeme(std::to_string(std::any_cast<uint16_t>(wrapped_value)), lexeme::integer));
                break;
            }
            case build_target::HLNG: {
                vars.emplace(field_name.text(), lexeme(std::to_string(std::any_cast<uint32_t>(wrapped_value)), lexeme::integer));
                break;
            }
            case build_target::HQAD: {
                vars.emplace(field_name.text(), lexeme(std::to_string(std::any_cast<uint64_t>(wrapped_value)), lexeme::integer));
                break;
            }
            case build_target::DBYT: {
                vars.emplace(field_name.text(), lexeme(std::to_string(std::any_cast<int8_t>(wrapped_value)), lexeme::integer));
                break;
            }
            case build_target::DWRD: {
                vars.emplace(field_name.text(), lexeme(std::to_string(std::any_cast<int16_t>(wrapped_value)), lexeme::integer));
                break;
            }
            case build_target::DLNG: {
                vars.emplace(field_name.text(), lexeme(std::to_string(std::any_cast<int32_t>(wrapped_value)), lexeme::integer));
                break;
            }
            case build_target::DQAD: {
                vars.emplace(field_name.text(), lexeme(std::to_string(std::any_cast<int64_t>(wrapped_value)), lexeme::integer));
                break;
            }
            case build_target::PSTR:
            case build_target::CSTR:
            case build_target::Cnnn: {
                auto str = std::any_cast<std::tuple<std::string, std::size_t>>(wrapped_value);
                vars.emplace(field_name.text(), lexeme(std::get<0>(str), lexeme::string));
                break;
            }
        }
    }

    return vars;
}

