/**
 * Tools for string processing.
 *
 * @authors: Denis Chernikov, Vladislav Kuleykin
 */

#ifndef C_PARSER_STRING_TOOLS_H_INCLUDED
#define C_PARSER_STRING_TOOLS_H_INCLUDED

/// Are the given strings equal?
///
/// \param str1 First string for comparison
/// \param str2 Second string to compare with
/// \return `true' - strings contents are identical, `false' - otherwise
_Bool str_eq(char *str1, char *str2);

/// Wrap a given string into double quotes.
/// If the string contains special symbols, it escapes them.
/// Needs to be released.
///
/// \param str String to wrap
/// \return New string inside quotes
char *wrap_by_quotes(char *str);

/// Convert a constant string to an allocated memory.
/// Needs to be released.
///
/// \param str String to allocate memory for
/// \return Pointer in a heap to the copy of a given string
char *alloc_const_str(const char *str);

/// Concatenate an array of strings into one string.
/// Needs to be released.
///
/// \param array Array of strings
/// \param n Number of strings in array
/// \param delimiter Delimiter to be placed between strings
/// \return String of concatenated strings
char *concat_array(char **array, int n, char *delimiter);

/// Repeat given source `n' times.
/// Needs to be released.
///
/// \param n Number of repetitions
/// \param str String pattern to repeat
/// \return `str' repeated `n' times
char *repeat(int n, char *str);

#endif //C_PARSER_STRING_TOOLS_H_INCLUDED
