/*
  GPL
  (c) 2015, thorsten.johannvorderbrueggen@t-online.de

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

#include "libarietta.h"

/*
 * check for version info
 */
#if !defined VER_MAYOR
#error VER_MAYOR not defined
// only to satisfy the build
#define VER_MAYOR 0
#endif

#if !defined VER_MINOR
#error VER_MINOR not defined
// only to satisfy the build
#define VER_MINOR 0
#endif

#if !defined VER_BUGFIX
#error VER_BUGFIX not defined
// only to satisfy the build
#define VER_BUGFIX 0
#endif


/*
 * show version info based on file ./VERSION
 */
void
print_lib_version()
{
	fprintf(stdout, "libarietta@version.%d.%d.%d\n",
		VER_MAYOR,
		VER_MINOR,
		VER_BUGFIX);
}

/*
 * common error function which is called in all exported error handling
 * functions
 */
static void
error_common(int errno_flag, int error, const char *fmt, va_list va)
{
	char buf[MAXLINE];

	vsnprintf(buf, MAXLINE-1, fmt, va);

	if (errno_flag)
		snprintf(buf+strlen(buf),
			 MAXLINE-strlen(buf)-1,
			 ": %s",
			 strerror(error));

	strcat(buf, "\n");

	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
}

/*
 * print error message and exit
 */
void
__attribute__((noreturn)) error_exit(const char *fmt, ...)
{
	va_list va;

	va_start(va, fmt);
	error_common(0, 0, fmt, va);
	va_end(va);

	exit(EXIT_FAILURE);
}

/*
 * print error message
 */
void
error_msg(const char *fmt, ...)
{
	va_list	va;

	va_start(va, fmt);
	error_common(0, 0, fmt, va);
	va_end(va);
}





