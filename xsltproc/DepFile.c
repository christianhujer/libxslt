/* Implements option -MMD to let xsltproc create a dependency file on the fly, just like gcc or clang. */

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH_OF_SUFFIX_PLUS_NUL_BYTE 3


/** The dependency file to be written.
 * Can be NULL in which case writing the dependency file simply does not happen.
 */
static FILE *depFile = NULL;

/** Returns whether or not specified \p candidateFileUrl is a `file:` URL or URL without scheme.
 * @param candidateFileUrl
 *      URL to inspect.
 * @return `true` in case \p candidateFileUrl has `file:` URL scheme or no scheme, otherwise `false`.
 */
static bool isFileUrl(const char *candidateFileUrl)
{
    return !strstr(candidateFileUrl, ":") || strstr(candidateFileUrl, "file:") == candidateFileUrl;
}

/** Gets the pathname from the file url.
 * @param fileUrl
 *     URL from which to get the pathname.
 * @return pathname from the URL.
 * @warning The behavior is undefined if \p fileUrl is not a URL with `file:` scheme or without scheme.
 */
static const char *getPathnameFromFileURL(const char *fileUrl)
{
    assert(isFileUrl(fileUrl));
    const char *colon = strstr(fileUrl, ":");
    return colon ? ++colon : fileUrl;
}

/** Allocates a dependency filename.
 * @param outputPathname
 *      Pathname from which to derive the dependency filename.
 * @return dependency filename, which was allocated with `malloc()` and therefore must be freed with `free()`.
 * @retval NULL in case `malloc()` failed.
 */
static char *getDependencyFilename(const char *outputPathname)
{
    const char *positionOfDot = rindex(outputPathname, '.');
    size_t lengthOfPathnameBeforeDot = positionOfDot ? (positionOfDot - outputPathname) : strlen(outputPathname);
    size_t sizeOfDepFilePathname = lengthOfPathnameBeforeDot + LENGTH_OF_SUFFIX_PLUS_NUL_BYTE;
    char *depFilePathname = malloc(sizeOfDepFilePathname);
    if (depFilePathname) {
	strncpy(depFilePathname, outputPathname, lengthOfPathnameBeforeDot);
	depFilePathname[lengthOfPathnameBeforeDot + 0] = '.';
	depFilePathname[lengthOfPathnameBeforeDot + 1] = 'd';
	depFilePathname[lengthOfPathnameBeforeDot + 2] = '\0';
    }
    return depFilePathname;
}

void DepFile_recordUrl(const char *url)
{
    if (depFile && isFileUrl(url))
	fprintf(depFile, " %s", getPathnameFromFileURL(url));
}

void DepFile_open(const char *outputPathname)
{
    char *depFilePathname;
    if (!outputPathname) return;
    depFilePathname = getDependencyFilename(outputPathname);
    if (!depFilePathname) {
        warn("Cannot allocate buffer for dependency file pathname");
        return;
    }
    depFile = fopen(depFilePathname, "w");
    if (!depFile) {
        warn("Cannot write %s", depFilePathname);
        goto exit;
    }
    fprintf(depFile, "%s:", outputPathname);
exit:
    free(depFilePathname);
}

void DepFile_close(void)
{
    if (depFile) {
        fprintf(depFile, "\n");
        fclose(depFile);
    }
    depFile = NULL;
}
