#include "Rules.h"
#include QParse_RULES____COUT_INCLUDE

void QParse::Rules::UndoRedo::print_error(Iterator & iterator, const char * indent) {
  QParse_RULES____COUT_NO_SPACE << rang::fg::blue;
  
    QParse_RULES____COUT_NO_SPACE << indent << "  at source: " << rang::fg::yellow << iterator.name << ":" << iterator.line() << ":" << iterator.column() << ": " << rang::fg::blue QParse_RULES____COUT_ENDL;
    QParse_RULES____COUT_NO_SPACE_NO_QUOTE << indent << "    input: \"" << iterator.lineString() << "\"" QParse_RULES____COUT_ENDL;

    QParse_RULES____STRING pre = "           ";
    QParse_RULES____STRING_APPEND(spacing, " ", iterator.column());
    QParse_RULES____STRING cursor = spacing + "^";
    QParse_RULES____STRING full_cursor = pre + spacing + "^";
    
    QParse_RULES____COUT_NO_SPACE << rang::fg::green;

    QParse_RULES____COUT_NO_SPACE_NO_QUOTE << indent << full_cursor QParse_RULES____COUT_ENDL;
    
    QParse_RULES____COUT_NO_SPACE << rang::fg::red;
    
    QParse_RULES____COUT_NO_SPACE << "" QParse_RULES____COUT_ENDL;
    
    QParse_RULES____COUT_NO_SPACE << rang::fg::reset;
}

void QParse::Rules::print(const QParse_RULES____STRING & message, Iterator & iterator, UndoRedo & undo)
{
    QParse_RULES____COUT_NO_SPACE << rang::fg::reset << "       " << rang::fg::reset << message QParse_RULES____COUT_ENDL;
    undo.print_error(iterator);
    undo.print([&](auto description) {
        QParse_RULES____COUT_NO_SPACE << description QParse_RULES____COUT_ENDL;
        undo.undo();
        undo.print_error(iterator);
    });
    QParse_RULES____COUT_NO_SPACE << rang::fg::reset;
}

void QParse::Rules::printError(const QParse_RULES____STRING & message, Iterator & iterator, UndoRedo & undo)
{
    QParse_RULES____COUT_NO_SPACE << rang::fg::red << "ERROR: " << rang::fg::reset << message QParse_RULES____COUT_ENDL;
    undo.print_error(iterator);
    undo.print([&](auto description) {
        QParse_RULES____COUT_NO_SPACE << description QParse_RULES____COUT_ENDL;
        undo.undo();
        undo.print_error(iterator);
    });
    QParse_RULES____COUT_NO_SPACE << rang::fg::reset;
}

void QParse::Rules::printNote(const QParse_RULES____STRING & message, Iterator & iterator, UndoRedo & undo)
{
    QParse_RULES____COUT_NO_SPACE << rang::fg::blue << "NOTE: " << rang::fg::reset << message QParse_RULES____COUT_ENDL;
    undo.print_error(iterator);
    undo.print([&](auto description) {
        QParse_RULES____COUT_NO_SPACE << description QParse_RULES____COUT_ENDL;
        undo.undo();
        undo.print_error(iterator);
    });
    QParse_RULES____COUT_NO_SPACE << rang::fg::reset;
}

QParse::Rules::Error::Error(const QParse_RULES____STRING &message, Action action) : Rule(action), message(message) {}

std::optional<QParse::IteratorMatcher::MatchData> QParse::Rules::Error::match(Iterator &iterator, UndoRedo *undo, bool doAction, bool logErrors) {
    IteratorMatcher::MatchData match(iterator, false);
    if (doAction) action(Input(iterator, match, undo, 0));
    //iterator.popInfo(match.matches);
    if (logErrors) printError(message, iterator, *undo);
    return std::nullopt;
}

QParse::Rules::SilentError::SilentError(Action action) : Rule(action) {}

std::optional<QParse::IteratorMatcher::MatchData> QParse::Rules::SilentError::match(Iterator &iterator, UndoRedo *undo, bool doAction, bool logErrors) {
    IteratorMatcher::MatchData match(iterator, false);
    if (doAction) action(Input(iterator, match, undo, 0));
    //iterator.popInfo(match.matches);
    return std::nullopt;
}

QParse::Rules::ErrorIfMatch::ErrorIfMatch(Rule *rule, const QParse_RULES____STRING &message, Action action) : RuleHolder(rule, action), message(message) {}

std::optional<QParse::IteratorMatcher::MatchData> QParse::Rules::ErrorIfMatch::match(Iterator &iterator, UndoRedo *undo, bool doAction, bool logErrors) {
    auto match_ = rule->match(iterator, undo, doAction, logErrors);
    if (!match_.has_value()) return std::nullopt;
    auto match = *match_;
    if (!match) {
      iterator.popInfo(match.matches);
      match.matches = 0;
    }
    if (match) {
        if (doAction) action(Input(iterator, match, undo, 0));
        //iterator.popInfo(match.matches);
        if (logErrors) printError(message, iterator, *undo);
        return std::nullopt;
    }
    match.matched = true;
    return match;
}

QParse::Rules::ErrorIfNotMatch::ErrorIfNotMatch(Rule *rule, const QParse_RULES____STRING &message, Action action) : RuleHolder(rule, action), message(message) {}

std::optional<QParse::IteratorMatcher::MatchData> QParse::Rules::ErrorIfNotMatch::match(Iterator &iterator, UndoRedo *undo, bool doAction, bool logErrors) {
    auto match_ = rule->match(iterator, undo, doAction, logErrors);
    if (!match_.has_value()) return std::nullopt;
    auto match = *match_;
    if (!match) {
      iterator.popInfo(match.matches);
      match.matches = 0;
    }
    if (!match) {
        if (doAction) action(Input(iterator, match, undo, 0));
        //iterator.popInfo(match.matches);
        if (logErrors) printError(message, iterator, *undo);
        return std::nullopt;
    }
    return match;
}
