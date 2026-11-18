#pragma once
#include "text_fit_enums.hpp"

/// Checks that the title and the text of the error fit their layout in every language,
/// or only in @p only_lang when it is given
void test_error(const ErrorEntry &error, const char *only_lang = nullptr);
