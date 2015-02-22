#ifndef DEPFILE_H
#define DEPFILE_H

/** Records a URL into the dependency file.
 * Although only URLs without scheme or `file:` scheme will be recorded, this function can be called with all URLs.
 * It will analyze the URL itself and ignore URLs which are with scheme different from `file:`.
 *
 * If there is no dependency file open, this function will simply do nothing.
 *
 * @param url
 *      URL to be recorded into the dependency file.
 */
extern void DepFile_recordUrl(const char *url);

/** Opens the dependency file.
 *
 * The name of the dependency file is derived by replacing the suffix of \p outputPathname with `.d`.
 * If there is no suffix, `.d` will be appended instead.
 *
 * If the dependency file could not be opened, a warning message will be printed.
 * In that case, other DepFile methods can still be called but will simply do nothing.
 *
 * @param outputPathname
 *      Pathname of the output file.
 *      Used for deriving the dependency file name and writing the start of the dependency rule.
 */
extern void DepFile_open(const char *outputPathnameOrNull);

/** Closes the dependency file.
 * If the dependency file was not open, this method simply does nothing.
 */
extern void DepFile_close(void);

#endif
