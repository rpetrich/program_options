// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef ERRORS_VP_2003_01_02
#define ERRORS_VP_2003_01_02

#include <boost/program_options/config.hpp>
#define DECL BOOST_PROGRAM_OPTIONS_DECL

#include <string>
#include <stdexcept>
#include <vector>



namespace boost { namespace program_options {

    /** Base class for all errors in the library. */
    class DECL error : public std::logic_error {
    public:
        error(const std::string& what) : std::logic_error(what) {}
    };

    class DECL invalid_syntax : public error {
    public:
        invalid_syntax(const std::string& tokens, const std::string& msg)
        : error(std::string(msg).append(" in '").append(tokens).append("'")),
          tokens(tokens), msg(msg)                       
        {}

        // gcc says that throw specification on dtor is loosened
        // without this line
        ~invalid_syntax() throw() {}

        // TODO: copy ctor might throw
        std::string tokens, msg;
    };

    /** Class thrown when option name is not recognized. */
    class DECL unknown_option : public error {
    public:
        unknown_option(const std::string& name)
        : error(std::string("unknown option ").append(name)) 
        {}
    };

    /** Class thrown when there's ambiguity between several possible options. */
    class DECL ambiguous_option : public error {
    public:
        ambiguous_option(const std::string& name, 
                         const std::vector<std::string>& alternatives)
        : error(std::string("ambiguous option ").append(name)),
          alternatives(alternatives)
        {}

        ~ambiguous_option() throw() {}

        // TODO: copy ctor might throw
        std::vector<std::string> alternatives;
    };

    /** Class thrown when there are several option values, but
        user called a method which cannot return them all. */
    class DECL multiple_values : public error {
    public:
        multiple_values(const std::string& what) : error(what) {}
    };

    /** Class thrown when there are several occurences of an
        option, but user called a method which cannot return 
        them all. */
    class DECL multiple_occurences : public error {
    public:
        multiple_occurences(const std::string& what) : error(what) {}
    };

    /** Class thrown when value of option is incorrect. */
    class DECL validation_error : public error {
    public:
        validation_error(const std::string& what) : error(what) {}
    };

    /** Class thrown then there are too many positional options. */
    class DECL too_many_positional_options_error : public error {
    public:
        too_many_positional_options_error(const std::string& what) 
        : error(what) {}
    };

    /** Class thrown then there are too few positional options. */
    class DECL too_few_positional_options_error : public error {
    public:
        too_few_positional_options_error(const std::string& what) 
        : error(what) {}
    };

    class DECL invalid_command_line_syntax : public invalid_syntax {
    public:
        enum kind_t {
            long_not_allowed,
            long_adjacent_not_allowed,
            short_adjacent_not_allowed,
            empty_adjacent_parameter,
            missing_parameter,
            extra_parameter
        };

        invalid_command_line_syntax(const std::string& tokens, kind_t kind);
        kind_t kind() const;
    protected:
        static std::string error_message(kind_t kind);
    private:
        kind_t m_kind;        
    };

    class DECL invalid_command_line_style : public error {
    public:
        invalid_command_line_style(const std::string& msg)
        : error(msg)
        {}
    };

}}

#undef DECL

#endif
