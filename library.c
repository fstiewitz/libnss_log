/*
 * Copyright 2019      Fabian Stiewitz<fabian@stiewitz.pw>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <stdio.h>
#include <nss.h>
#include <errno.h>
#include <netdb.h>
#include <memory.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAMEBUFLEN 64

enum nss_status _nss_log_gethostbyname2_r(const char *name, int af,
                                                struct hostent *ret, char *buf, size_t buflen,
                                                int *errnop, int *h_errnop);

enum nss_status _nss_log_gethostbyname_r(const char *name,
                                               struct hostent *ret, char *buf, size_t buflen,
                                               int *errnop, int *h_errnop)
{
    return _nss_log_gethostbyname2_r(name, AF_INET, ret, buf, buflen, errnop, h_errnop);
}

enum nss_status _nss_log_gethostbyname2_r(const char *name, int af,
                                                struct hostent *ret, char *buf, size_t buflen,
                                                int *errnop, int *h_errnop)
{
    char filenamebuf[FILENAMEBUFLEN];
    size_t blen = strlen(name) + strlen("gethostbyname ") + 2;
    int log;
    if(buflen < blen) {
        *errnop = ERANGE;
        *h_errnop = NETDB_INTERNAL;
        return NSS_STATUS_TRYAGAIN;
    }
    strcpy(buf, "gethostbyname ");
    strcat(buf, name);
    strcat(buf, "\n");
    snprintf(filenamebuf, FILENAMEBUFLEN, "/tmp/nss-log-%u.log", getuid());
    log = open(filenamebuf, O_APPEND | O_WRONLY | O_CREAT, S_IRWXU);
    if(log == -1) {
        return NSS_STATUS_UNAVAIL;
    }
    write(log, buf, blen);
    close(log);
    return NSS_STATUS_NOTFOUND;
}

