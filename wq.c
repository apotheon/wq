#include <stdio.h>
#include <string.h>

/*
 * wq - a tool for textfile task queue management
 *
 *      wq help
 *
 * This "wq" tool does something.
 *
 * This work is inspired by the straightforward method of using "backlog" and
 * "done" files to manage task queues.  It is Copyright 2017 Chad Perrin,
 * released under the terms of the COIL.  See end of file for license terms.
 */

int match_help(char *string_argument);
int match_string(char *s, char *m);
int print_wrap(int wrap, char *string, int position);
int wrap_whitespace(int length, char *string, int start);

void print_help();
void print_help_message();
void print_indent(int indent);
void print_indent_wrap(char *string, int indent, int line_length);
void print_usage(char* command);

int main(int argc, char *argv[]) {
    if (argc == 2 && match_help(argv[1])) {
        print_help();
    } else {
        print_usage("help");
    }

    return 0;
}

int match_help(char* s) {
    if (match_string(s, "-h")) return 1;
    else if (match_string(s, "--help")) return 1;
    else if (match_string(s, "help")) return 1;
    else return 0;
}

int match_string(char *s, char *m) {
    int length = strlen(s);
    int match = 1;

    if (length != strlen(m)) {
        match = 0;
    } else {
        for (int i = 0; i < length; ++i) {
            if (*(s+i) != *(m+i)) match = 0;
        }
    }

    return match;
}

int print_wrap(int wrap, char *string, int position) {
    int remaining_string = strlen(string) - position;

    if (wrap > remaining_string) wrap = remaining_string;
    wrap = wrap_whitespace(wrap, string, position);

    for (int c = 0; c < wrap; ++c) printf("%c", *(string+position+c));
    printf("\n");

    return wrap;
}

int wrap_whitespace(int length, char *string, int start) {
    int newline = 0;
    for (int c = 0; c < length && !newline; ++c) {
        if (*(string+start+c) == '\n') {
            length = c;
            newline = 1;
        }
    }

    int whitespace = 0;
    for (int c = length; c > 0 && !newline && !whitespace; --c) {
        if (*(string+start+c) == ' ') {
            length = c;
            whitespace = 1;
        }
    }

    return length;
}

void print_help() {
    print_usage("<COMMAND>");
    printf("\n");
    print_help_message();
}

void print_help_message() {
    printf("SYNOPSIS:\n\n");

    print_indent_wrap(
        "Enter a COMMAND.  I'll figure the rest out later.\n", 8, 80
    );

    printf("\n");

    print_indent_wrap(
        "Enter a COMMAND.  I'll figure the rest out later.\n", 8, 80
    );

    printf("\nOPTIONS:\n\n");

    print_indent_wrap("-h, [--]help    Print this help information.\n", 8, 80);

    printf("\nEXAMPLES:\n\n");

    print_indent_wrap("I have none at this time.\n", 8, 80);
    print_indent_wrap("No, really.\n\n", 8, 80);
}

void print_indent(int indent) {
    for (int i = 0; i < indent; ++i) printf(" ");
}

void print_indent_wrap(char *string, int indent, int line_length) {
    for (int p = 0; p < strlen(string); ++p) {
        int wrap = line_length - indent;

        print_indent(indent);
        p += print_wrap(wrap, string, p);
    }
}

void print_usage(char* command) {
    printf("USAGE: wq %s\n", command);
}

/*
 * # Copyfree Open Innovation License
 *
 * This is version 0.5 of the Copyfree Open Innovation License.
 *
 * ## Terms and Conditions
 *
 * Redistributions, modified or unmodified, in whole or in part, must retain
 * applicable copyright or other legal privilege notices, these conditions, and
 * the following license terms and disclaimer.  Subject to these conditions,
 * the holder(s) of copyright or other legal privileges, author(s) or
 * assembler(s), and contributors of this work hereby grant to any person who
 * obtains a copy of this work in any form:
 *
 * 1. Permission to reproduce, modify, distribute, publish, sell, sublicense,
 * use, and/or otherwise deal in the licensed material without restriction.
 *
 * 2. A perpetual, worldwide, non-exclusive, royalty-free, irrevocable patent
 * license to reproduce, modify, distribute, publish, sell, use, and/or
 * otherwise deal in the licensed material without restriction, for any and all
 * patents:
 *
 *    a. Held by each such holder of copyright or other legal privilege, author
 *    or assembler, or contributor, necessarily infringed by the contributions
 *    alone or by combination with the work, of that privilege holder, author
 *    or assembler, or contributor.
 *
 *    b. Necessarily infringed by the work at the time that holder of copyright
 *    or other privilege, author or assembler, or contributor made any
 *    contribution to the work.
 *
 * NO WARRANTY OF ANY KIND IS IMPLIED BY, OR SHOULD BE INFERRED FROM, THIS
 * LICENSE OR THE ACT OF DISTRIBUTION UNDER THE TERMS OF THIS LICENSE,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 * A PARTICULAR PURPOSE, AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS,
 * ASSEMBLERS, OR HOLDERS OF COPYRIGHT OR OTHER LEGAL PRIVILEGE BE LIABLE FOR
 * ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN ACTION OF CONTRACT, TORT,
 * OR OTHERWISE ARISING FROM, OUT OF, OR IN CONNECTION WITH THE WORK OR THE USE
 * OF OR OTHER DEALINGS IN THE WORK.
 */
