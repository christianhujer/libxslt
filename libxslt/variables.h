/*
 * variable.h: interface for the variable matching and lookup.
 *
 * See Copyright for the status of this software.
 *
 * Daniel.Veillard@imag.fr
 */

#ifndef __XML_XSLT_VARIABLES_H__
#define __XML_XSLT_VARIABLES_H__

#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include "xsltInternals.h"

#ifdef __cplusplus
extern "C" {
#endif

#define XSLT_REGISTER_VARIABLE_LOOKUP(ctxt)			\
    xmlXPathRegisterVariableLookup((ctxt)->xpathCtxt,		\
	       xsltXPathVariableLookup,	(void *)(ctxt)) 

/*
 * Interfaces for the variable module.
 */

void		xsltPushStack			(xsltTransformContextPtr ctxt);
void		xsltPopStack			(xsltTransformContextPtr ctxt);
void		xsltParseStylesheetVariable	(xsltTransformContextPtr ctxt,
						 xmlNodePtr cur);
void			xsltFreeVariableHashes	(xsltTransformContextPtr ctxt);
xmlXPathObjectPtr	xsltVariableLookup	(xsltTransformContextPtr ctxt,
						 const xmlChar *name,
						 const xmlChar *ns_uri);
int			xsltRegisterVariable	(xsltTransformContextPtr ctxt,
						 const xmlChar *name,
						 const xmlChar *ns_uri,
						 const xmlChar *select,
						 xmlXPathObjectPtr value);
xmlXPathObjectPtr	xsltXPathVariableLookup	(void *ctxt,
						 const xmlChar *name,
						 const xmlChar *ns_uri);
#ifdef __cplusplus
}
#endif

#endif /* __XML_XSLT_VARIABLES_H__ */
