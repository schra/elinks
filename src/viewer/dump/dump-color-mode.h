/* Partially specialized functions for dumping to a file.
 *
 * This include file defines a function that dumps the document to a
 * file.  The function is specialized to one color mode.  This is
 * supposedly faster than runtime checks.  The file that includes this
 * file must define several macros to select the specialization.
 *
 * The following macros must be defined as names of functions that
 * this file should define:
 *
 * - DUMP_FUNCTION_COLOR: The main function.  It calls one of the others.
 * - DUMP_FUNCTION_UNIBYTE: For dumping in unibyte charsets.
 * - DUMP_FUNCTION_UTF8: For dumping in the UTF-8 charset.
 *   (The function names could be generated with the ## preprocessor
 *   operator, but that would make grepping more difficult.)
 *
 * At most one of the following macros may be defined:
 *
 * - DUMP_COLOR_MODE_16
 * - DUMP_COLOR_MODE_256
 * - DUMP_COLOR_MODE_TRUE
 */

#define DUMP_FUNCTION_SPECIALIZED DUMP_FUNCTION_UNIBYTE
#include "dump-specialized.h"
#undef DUMP_FUNCTION_SPECIALIZED

#ifdef CONFIG_UTF8
# define DUMP_CHARSET_UTF8
# define DUMP_FUNCTION_SPECIALIZED DUMP_FUNCTION_UTF8
# include "dump-specialized.h"
# undef DUMP_FUNCTION_SPECIALIZED
# undef DUMP_CHARSET_UTF8
#endif	/* CONFIG_UTF8 */

static int
DUMP_FUNCTION_COLOR(struct document *document, int fd,
		    unsigned char buf[D_BUF])
{
#ifdef CONFIG_UTF8
	if (is_cp_utf8(document->options.cp))
		return DUMP_FUNCTION_UTF8(document, fd, buf);
#endif	/* CONFIG_UTF8 */

	return DUMP_FUNCTION_UNIBYTE(document, fd, buf);
}